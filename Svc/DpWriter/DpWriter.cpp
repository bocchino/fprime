// ======================================================================
// \title  DpWriter.cpp
// \author bocchino
// \brief  cpp file for DpWriter component implementation class
// ======================================================================

#include "Fw/Com/ComPacket.hpp"
#include "Fw/Types/Serializable.hpp"
#include "Os/File.hpp"
#include "Svc/DpWriter/DpWriter.hpp"
#include "config/DpCfg.hpp"
#include "config/FpConfig.hpp"

namespace Svc {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

DpWriter::DpWriter(const char* const compName) : DpWriterComponentBase(compName) {}

DpWriter::~DpWriter() {}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void DpWriter::bufferSendIn_handler(const NATIVE_INT_TYPE portNum, Fw::Buffer& buffer) {
    Fw::Success::T status = Fw::Success::SUCCESS;
    // portNum is unused
    (void)portNum;
    // Update num buffers received
    ++this->m_numBuffersReceived;
    // Check that the buffer is valid
    if (!buffer.isValid()) {
        this->log_WARNING_HI_InvalidBuffer();
        status = Fw::Success::FAILURE;
    }
    // Set up the serial packet buffer
    if (status == Fw::Success::SUCCESS) {
        Fw::SerializeBufferBase& serialBuffer = buffer.getSerializeRepr();
        const Fw::SerializeStatus serialStatus = serialBuffer.setBuffLen(buffer.getSize());
        FW_ASSERT(serialStatus == Fw::FW_SERIALIZE_OK, static_cast<FwAssertArgType>(serialStatus));
    }
    // Deserialize the packet header
    Fw::DpContainer container;
    if (status == Fw::Success::SUCCESS) {
        status = this->deserializePacketHeader(buffer, container);
    }
    // Perform the requested processing
    if (status == Fw::Success::SUCCESS) {
        this->performProcessing(container);
    }
    // Construct the file name
    Fw::FileNameString fileName;
    if (status == Fw::Success::SUCCESS) {
        const FwDpIdType containerId = container.getId();
        const Fw::Time timeTag = container.getTimeTag();
        fileName.format(DP_FILENAME_FORMAT, containerId, timeTag.getSeconds(), timeTag.getUSeconds());
    }
    FwSizeType fileSize = 0;
    // Write the file
    if (status == Fw::Success::SUCCESS) {
        status = this->writeFile(container, fileName, fileSize);
    }
    // Send the DpWritten notification
    if (status == Fw::Success::SUCCESS) {
        this->sendNotification(container, fileName, fileSize);
    }
    // Deallocate the buffer
    if (buffer.isValid()) {
        this->deallocBufferSendOut_out(0, buffer);
    }
    // Update the error count
    if (status != Fw::Success::SUCCESS) {
        this->m_numErrors++;
    }
}

void DpWriter::schedIn_handler(const NATIVE_INT_TYPE portNum, U32 context) {
    // portNum and context are not used
    (void)portNum;
    (void)context;
    // Write telemetry
    this->tlmWrite_NumBuffersReceived(this->m_numBuffersReceived);
    this->tlmWrite_NumBytesWritten(this->m_numBytesWritten);
    this->tlmWrite_NumSuccessfulWrites(this->m_numSuccessfulWrites);
    this->tlmWrite_NumFailedWrites(this->m_numFailedWrites);
}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void DpWriter::CLEAR_EVENT_THROTTLE_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    // opCode and cmdSeq are not used
    (void)opCode;
    (void)cmdSeq;
    // Clear throttling
    this->log_WARNING_HI_InvalidBuffer_ThrottleClear();
    this->log_WARNING_HI_BufferTooSmall_ThrottleClear();
    this->log_WARNING_HI_InvalidPacketHeader_ThrottleClear();
    this->log_WARNING_HI_FileOpenError_ThrottleClear();
    this->log_WARNING_HI_FileWriteError_ThrottleClear();
    // Return command response
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

// ----------------------------------------------------------------------
// Private helper functions
// ----------------------------------------------------------------------

Fw::Success::T DpWriter::deserializePacketHeader(Fw::Buffer& buffer, Fw::DpContainer& container) {
    Fw::Success::T status = Fw::Success::SUCCESS;
    container.setBuffer(buffer);
    const Fw::SerializeStatus serialStatus = container.deserializeHeader();
    if (serialStatus != Fw::FW_SERIALIZE_OK) {
        this->log_WARNING_HI_InvalidPacketHeader(static_cast<U32>(serialStatus));
        status = Fw::Success::FAILURE;
    }
    return status;
}

void DpWriter::performProcessing(const Fw::DpContainer& container) {
    // Get the buffer
    Fw::Buffer buffer = container.getBuffer();
    // Get the bit mask for the processing types
    const Fw::DpCfg::ProcType::SerialType procTypes = container.getProcTypes();
    // Do the processing
    for (FwIndexType portNum = 0; portNum < NUM_PROCBUFFERSENDOUT_OUTPUT_PORTS; ++portNum) {
        if ((procTypes & (1 << portNum)) != 0) {
            this->procBufferSendOut_out(portNum, buffer);
        }
    }
}

Fw::Success::T DpWriter::writeFile(const Fw::DpContainer& container,
                                   const Fw::FileNameString& fileName,
                                   FwSizeType& packetSize) {
    // Get the buffer
    Fw::Buffer buffer = container.getBuffer();
    Fw::Success::T status = Fw::Success::SUCCESS;
    // Get the data size
    const FwSizeType dataSize = container.getDataSize();
    // Compute the packet size
    packetSize = Fw::DpContainer::getPacketSizeForDataSize(dataSize);
    // Check that the packet size fits in the buffer
    const FwSizeType bufferSize = buffer.getSize();
    if (packetSize < bufferSize) {
        this->log_WARNING_HI_BufferTooSmall(bufferSize, packetSize);
        status = Fw::Success::FAILURE;
    }
    // Open the file
    Os::File file;
    if (status == Fw::Success::SUCCESS) {
        const Os::File::Status fileStatus = file.open(fileName.toChar(), Os::File::OPEN_CREATE);
        if (fileStatus != Os::File::OP_OK) {
            this->log_WARNING_HI_FileOpenError(fileName.toChar(), static_cast<U32>(fileStatus));
            status = Fw::Success::FAILURE;
        }
    }
    // Write the file
    if (status == Fw::Success::SUCCESS) {
        // Set write size to packet size
        // On entry to the write call, this is the number of bytes to write
        // On return from the write call, this is the number of bytes written
        FwSignedSizeType writeSize = packetSize;
        const Os::File::Status fileStatus = file.write(buffer.getData(), writeSize);
        // If a successful write occurred, then update the number of bytes written
        if (fileStatus == Os::File::OP_OK) {
            this->m_numBytesWritten += writeSize;
        }
        if ((fileStatus == Os::File::OP_OK) and (writeSize == static_cast<FwSignedSizeType>(packetSize))) {
            // If the write status is success, and the number of bytes written
            // is the expected number, then record the success
            this->log_ACTIVITY_LO_FileWritten(fileName.toChar());
        } else {
            // Otherwise record the failure
            this->log_WARNING_HI_FileWriteError(fileName.toChar(), static_cast<U32>(packetSize),
                                                static_cast<U32>(writeSize), static_cast<U32>(fileStatus));
            status = Fw::Success::FAILURE;
        }
    }
    // Update the count of successful or failed writes
    if (status == Fw::Success::SUCCESS) {
        this->m_numSuccessfulWrites++;
    } else {
        this->m_numFailedWrites++;
    }
    // Return the status
    return status;
}

void DpWriter::sendNotification(const Fw::DpContainer& container,
                                const Fw::FileNameString& fileName,
                                FwSizeType fileSize) {
    if (isConnected_dpWrittenOut_OutputPort(0)) {
        // Construct the file name
        fileNameString portFileName(fileName.toChar());
        // Get the priority
        const FwDpPriorityType priority = container.getPriority();
        this->dpWrittenOut_out(0, portFileName, priority, fileSize);
    }
}

}  // end namespace Svc