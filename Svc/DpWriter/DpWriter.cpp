// ======================================================================
// \title  DpWriter.cpp
// \author bocchino
// \brief  cpp file for DpWriter component implementation class
// ======================================================================

#include <FpConfig.hpp>
#include <Svc/DpWriter/DpWriter.hpp>

namespace Svc {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

DpWriter::DpWriter(const char* const compName) : DpWriterComponentBase(compName) {}

DpWriter::~DpWriter() {}

// ----------------------------------------------------------------------
// Runtime configuration
// ----------------------------------------------------------------------

void DpWriter::configure(
    const Fw::String& fileNamePrefix,
    const Fw::String& fileNameSuffix
) {
  this->m_fileNamePrefix = fileNamePrefix;
  this->m_fileNameSuffix = fileNameSuffix;
}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void DpWriter::bufferSendIn_handler(const NATIVE_INT_TYPE portNum, Fw::Buffer& fwBuffer) {
    // TODO
}

void DpWriter::schedIn_handler(const NATIVE_INT_TYPE portNum, NATIVE_UINT_TYPE context) {
    // Write telemetry
    this->tlmWrite_NumDataProducts(this->m_numDataProducts);
    this->tlmWrite_NumBytes(this->m_numBytes);
}

}  // end namespace Svc
