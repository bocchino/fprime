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
// Runtime configuration
// ----------------------------------------------------------------------

void DpWriter::configure(const Fw::String& fileNamePrefix, const Fw::String& fileNameSuffix) {
    this->m_fileNamePrefix = fileNamePrefix;
    this->m_fileNameSuffix = fileNameSuffix;
}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void DpWriter::bufferSendIn_handler(const NATIVE_INT_TYPE portNum, Fw::Buffer& buffer) {
    // portNum is unused
    (void) portNum;
    // Validate the packet buffer
    if (this->validatePacketBuffer(buffer) == Fw::Success::SUCCESS) {
        // Perform the requested processing
        this->performProcessing(buffer);
        // Write the file
        this->writeFile(buffer);
        // Send the DpWritten notification
        this->sendNotification(buffer);
        // Update telemetry values
        this->updateTlmValues(buffer);
    }
    // Deallocate the buffer
    if (buffer.isValid()) {
        this->deallocBufferSendOut_out(0, buffer);
    }
}

void DpWriter::schedIn_handler(const NATIVE_INT_TYPE portNum, NATIVE_UINT_TYPE context) {
    // portNum is not used
    (void) portNum;
    // Write telemetry
    this->tlmWrite_NumDataProducts(this->m_numDataProducts);
    this->tlmWrite_NumBytes(this->m_numBytes);
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
    // Check that the buffer is large enough to hold a data product container
    if (status == Fw::Success::SUCCESS) {
        const FwSizeType bufferSize = buffer.getSize();
        if (bufferSize < Fw::DpContainer::MIN_PACKET_SIZE) {
            this->log_WARNING_HI_BufferTooSmall(bufferSize);
            status = Fw::Success::FAILURE;
        }
    }
    // Check that the packet header starts with FW_PACKET_DP
    if (status == Fw::Success::SUCCESS) {
        const FwSizeType bufferSize = buffer.getSize();
        FwPacketDescriptorType packetDescriptor;
        FW_ASSERT(sizeof packetDescriptor <= bufferSize, sizeof packetDescriptor, bufferSize);
        U8 *const data = buffer.getData();
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
    U8 *const data = buffer.getData();
    FW_ASSERT(data != nullptr);
    Fw::ExternalSerializeBuffer serialBuffer(&data[Fw::DpContainer::Header::PROC_TYPES_OFFSET],
                                             sizeof procTypes);
    const Fw::SerializeStatus serialStatus = serialBuffer.deserialize(procTypes);
    FW_ASSERT(serialStatus == Fw::FW_SERIALIZE_OK);
    // Do the processing
    for (FwIndexType portNum = 0; portNum < NUM_PROCBUFFERSENDOUT_OUTPUT_PORTS; ++portNum) {
        if ((procTypes & (1 << portNum)) != 0) {
            this->procBufferSendOut_out(portNum, buffer);
        }
    }
}

void DpWriter::writeFile(const Fw::Buffer& buffer) {
    // TODO
}

void DpWriter::updateTlmValues(const Fw::Buffer& buffer) {
    // TODO
}

}  // end namespace Svc
