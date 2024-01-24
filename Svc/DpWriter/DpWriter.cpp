// ======================================================================
// \title  DpWriter.cpp
// \author bocchino
// \brief  cpp file for DpWriter component implementation class
// ======================================================================

#include "Fw/Com/ComPacket.hpp"
#include "Fw/Dp/DpContainer.hpp"
#include "Fw/Types/Serializable.hpp"
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
    // portNum is unused
    (void)portNum;
    // Update num data products received
    ++this->m_numBuffersReceived;
    Fw::Success::T status = Fw::Success::SUCCESS;
    // Check that the buffer is valid
    if (!buffer.isValid()) {
        this->log_WARNING_HI_BufferInvalid();
        status = Fw::Success::FAILURE;
    }
    // Set up the serial packet buffer
    Fw::SerializeBufferBase& serialBuffer = buffer.getSerializeRepr();
    if (status == Fw::Success::SUCCESS) {
        const Fw::SerializeStatus serialStatus = serialBuffer.setBuffLen(buffer.getSize());
        FW_ASSERT(serialStatus == Fw::FW_SERIALIZE_OK, static_cast<FwAssertArgType>(serialStatus));
    }
    FwSizeType fileSize = 0;
    if (status == Fw::Success::SUCCESS) {
        // Validate the packet buffer
        status = this->validatePacketBuffer(serialBuffer);
        // Perform the requested processing
        this->performProcessing(buffer);
        // Write the file
        status = this->writeFile(buffer, fileSize);
    }
    if (status == Fw::Success::SUCCESS) {
        // Send the DpWritten notification
        this->sendNotification(buffer, fileSize);
    }
    // Deallocate the buffer
    if (buffer.isValid()) {
        this->deallocBufferSendOut_out(0, buffer);
    }
}

void DpWriter::schedIn_handler(const NATIVE_INT_TYPE portNum, NATIVE_UINT_TYPE context) {
    // portNum is not used
    (void)portNum;
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
    this->log_WARNING_HI_BufferInvalid_ThrottleClear();
    this->log_WARNING_HI_BufferTooSmall_ThrottleClear();
    this->log_WARNING_HI_InvalidPacketDescriptor_ThrottleClear();
    this->log_WARNING_HI_FileOpenError_ThrottleClear();
    this->log_WARNING_HI_FileWriteError_ThrottleClear();
    // Return command response
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

// ----------------------------------------------------------------------
// Private helper functions
// ----------------------------------------------------------------------

Fw::Success::T DpWriter::validatePacketBuffer(Fw::SerializeBufferBase& serialBuffer) {
    Fw::Success status = Fw::Success::SUCCESS;
    // Check that the buffer is large enough to hold a data product container packet
    if (status == Fw::Success::SUCCESS) {
        const FwSizeType bufferSize = serialBuffer.getBuffLength();
        const FwSizeType minPacketSize = Fw::DpContainer::MIN_PACKET_SIZE;
        if (bufferSize < minPacketSize) {
            this->log_WARNING_HI_BufferTooSmall(bufferSize, minPacketSize);
            status = Fw::Success::FAILURE;
        }
    }
    // Check that the packet header starts with FW_PACKET_DP
    if (status == Fw::Success::SUCCESS) {
        Fw::SerializeStatus serialStatus =
            serialBuffer.moveDeserToOffset(Fw::DpContainer::Header::PACKET_DESCRIPTOR_OFFSET);
        FW_ASSERT(serialStatus == Fw::FW_SERIALIZE_OK);
        FwPacketDescriptorType packetDescriptor = 0;
        serialStatus = serialBuffer.deserialize(packetDescriptor);
        FW_ASSERT(serialStatus == Fw::FW_SERIALIZE_OK);
        if (packetDescriptor != Fw::ComPacket::FW_PACKET_DP) {
            this->log_WARNING_HI_InvalidPacketDescriptor(static_cast<U32>(packetDescriptor));
            status = Fw::Success::FAILURE;
        }
    }
    return status;
}

void DpWriter::performProcessing(Fw::Buffer& buffer) {
    // Set up the serial buffer
    Fw::SerializeBufferBase& serialBuffer = buffer.getSerializeRepr();
    Fw::SerializeStatus serialStatus = serialBuffer.setBuffLen(buffer.getSize());
    // Get the bit mask for the processing types
    serialStatus = serialBuffer.moveDeserToOffset(Fw::DpContainer::Header::PROC_TYPES_OFFSET);
    FW_ASSERT(serialStatus == Fw::FW_SERIALIZE_OK, static_cast<FwAssertArgType>(serialStatus));
    Fw::DpCfg::ProcType::SerialType procTypes = 0;
    serialStatus = serialBuffer.deserialize(procTypes);
    FW_ASSERT(serialStatus == Fw::FW_SERIALIZE_OK, static_cast<FwAssertArgType>(serialStatus));
    // Do the processing
    for (FwIndexType portNum = 0; portNum < NUM_PROCBUFFERSENDOUT_OUTPUT_PORTS; ++portNum) {
        if ((procTypes & (1 << portNum)) != 0) {
            this->procBufferSendOut_out(portNum, buffer);
        }
    }
}

Fw::Success::T DpWriter::writeFile(const Fw::Buffer& buffer, FwSizeType& packetSize) {
    Fw::Success::T status = Fw::Success::SUCCESS;
    // Get the buffer size
    const FwSizeType bufferSize = buffer.getSize();
    // Get the data size out of the packet
    Fw::ExternalSerializeBuffer serialBuffer(buffer.getData(), buffer.getSize());
    Fw::SerializeStatus serialStatus = serialBuffer.setBuffLen(buffer.getSize());
    FW_ASSERT(serialStatus == Fw::FW_SERIALIZE_OK);
    serialStatus = serialBuffer.moveDeserToOffset(Fw::DpContainer::Header::DATA_SIZE_OFFSET);
    FW_ASSERT(serialStatus == Fw::FW_SERIALIZE_OK);
    FwSizeType dataSize = 0;
    serialStatus = serialBuffer.deserialize(dataSize);
    FW_ASSERT(serialStatus == Fw::FW_SERIALIZE_OK);
    // Compute the packet size
    packetSize = Fw::DpContainer::getPacketSizeForDataSize(dataSize);
    // If the packet size doesn't fit in the buffer, error: buffer too small
    if (packetSize < bufferSize) {
        this->log_WARNING_HI_BufferTooSmall(bufferSize, packetSize);
        status = Fw::Success::FAILURE;
    }
    // Construct the file name
    // TODO
    // Open the file
    if (status == Fw::Success::SUCCESS) {
        // TODO
    }
    // If status is success, write the file
    if (status == Fw::Success::SUCCESS) {
        // TODO
    }
    // Update telemetry
    // TODO
    return status;
}

void DpWriter::sendNotification(const Fw::Buffer& buffer, FwSizeType fileSize) {
    // TODO
}

}  // end namespace Svc
