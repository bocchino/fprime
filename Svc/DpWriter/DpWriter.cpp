// ======================================================================
// \title  DpWriter.cpp
// \author bocchino
// \brief  cpp file for DpWriter component implementation class
// ======================================================================

#include "Fw/Dp/DpContainer.hpp"
#include "Fw/Types/SuccessEnumAc.hpp"
#include "Svc/DpWriter/DpWriter.hpp"
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

void DpWriter::bufferSendIn_handler(const NATIVE_INT_TYPE portNum, Fw::Buffer& fwBuffer) {
    Fw::Success::T status = Fw::Success::SUCCESS;
    // Check that buffer is valid
    if (!fwBuffer.isValid()) {
        this->log_WARNING_HI_BufferInvalid();
        status = Fw::Success::FAILURE;
    }
    // Check that buffer size is large enough to hold a data product container
    if (status == Fw::Success::SUCCESS) {
        const FwSizeType bufferSize = fwBuffer.getSize();
        if (bufferSize < Fw::DpContainer::MIN_PACKET_SIZE) {
            this->log_WARNING_HI_BufferTooSmall(bufferSize);
            status = Fw::Success::FAILURE;
        }
    }
    // TODO
}

void DpWriter::schedIn_handler(const NATIVE_INT_TYPE portNum, NATIVE_UINT_TYPE context) {
    // Write telemetry
    this->tlmWrite_NumDataProducts(this->m_numDataProducts);
    this->tlmWrite_NumBytes(this->m_numBytes);
}

}  // end namespace Svc
