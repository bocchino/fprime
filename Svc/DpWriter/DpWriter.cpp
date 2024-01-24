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
    // Validate the packet buffer
    Fw::Success::T status = this->validatePacketBuffer(buffer);
    if (status == Fw::Success::SUCCESS) {
        // Perform the requested processing
        this->performProcessing(buffer);
        // Write the file
        status = this->writeFile(buffer);
    }
    if (status == Fw::Success::SUCCESS) {
        // Send the DpWritten notification
        this->sendNotification(buffer);
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
    (void) opCode;
    (void) cmdSeq;
    // Clear throttling
    this->log_WARNING_HI_BufferInvalid_ThrottleClear();
    this->log_WARNING_HI_BufferTooSmallForContainer_ThrottleClear();
    this->log_WARNING_HI_InvalidPacketDescriptor_ThrottleClear();
    this->log_WARNING_HI_FileOpenError_ThrottleClear();
    this->log_WARNING_HI_FileWriteError_ThrottleClear();
    // Return command response
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

// ----------------------------------------------------------------------
// Private helper functions
// ----------------------------------------------------------------------

Fw::Success::T DpWriter::validatePacketBuffer(const Fw::Buffer& buffer) {
    Fw::Success status = Fw::Success::SUCCESS;
    // Check that the buffer is valid
    if (!buffer.isValid()) {
        this->log_WARNING_HI_BufferInvalid();
        status = Fw::Success::FAILURE;
    }
    // Check that the buffer is large enough to hold a data product container packet
    if (status == Fw::Success::SUCCESS) {
        const FwSizeType bufferSize = buffer.getSize();
        const FwSizeType minPacketSize = Fw::DpContainer::MIN_PACKET_SIZE;
        if (bufferSize < minPacketSize) {
            this->log_WARNING_HI_BufferTooSmallForContainer(bufferSize, minPacketSize);
            status = Fw::Success::FAILURE;
        }
    }
    // Check that the packet header starts with FW_PACKET_DP
    if (status == Fw::Success::SUCCESS) {
        const FwSizeType bufferSize = buffer.getSize();
        FwPacketDescriptorType packetDescriptor;
        FW_ASSERT(sizeof packetDescriptor <= bufferSize, sizeof packetDescriptor, bufferSize);
        U8* const data = buffer.getData();
        FW_ASSERT(data != nullptr);
        Fw::ExternalSerializeBuffer serialBuffer(&data[Fw::DpContainer::Header::PACKET_DESCRIPTOR_OFFSET],
                                                 sizeof packetDescriptor);
        const Fw::SerializeStatus serialStatus = serialBuffer.deserialize(packetDescriptor);
        FW_ASSERT(serialStatus == Fw::FW_SERIALIZE_OK);
        if (packetDescriptor != Fw::ComPacket::FW_PACKET_DP) {
            this->log_WARNING_HI_InvalidPacketDescriptor(static_cast<U32>(packetDescriptor));
            status = Fw::Success::FAILURE;
        }
    }
    return status;
}

void DpWriter::performProcessing(Fw::Buffer& buffer) {
    // Get the buffer size
    const FwSizeType bufferSize = buffer.getSize();
    // Get the bit mask for the processing types
    Fw::DpCfg::ProcType::SerialType procTypes = 0;
    const FwSizeType minDataSize = Fw::DpContainer::Header::PROC_TYPES_OFFSET + (sizeof procTypes);
    FW_ASSERT(minDataSize <= bufferSize, minDataSize, bufferSize);
    U8* const data = buffer.getData();
    FW_ASSERT(data != nullptr);
    Fw::ExternalSerializeBuffer serialBuffer(&data[Fw::DpContainer::Header::PROC_TYPES_OFFSET], sizeof procTypes);
    const Fw::SerializeStatus serialStatus = serialBuffer.deserialize(procTypes);
    FW_ASSERT(serialStatus == Fw::FW_SERIALIZE_OK);
    // Do the processing
    for (FwIndexType portNum = 0; portNum < NUM_PROCBUFFERSENDOUT_OUTPUT_PORTS; ++portNum) {
        if ((procTypes & (1 << portNum)) != 0) {
            this->procBufferSendOut_out(portNum, buffer);
        }
    }
}

Fw::Success::T DpWriter::writeFile(const Fw::Buffer& buffer) {
    // TODO
    return Fw::Success::SUCCESS;
}

}  // end namespace Svc
