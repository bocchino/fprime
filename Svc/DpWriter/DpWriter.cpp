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

DpWriter ::DpWriter(const char* const compName) : DpWriterComponentBase(compName) {}

DpWriter ::~DpWriter() {}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void DpWriter ::bufferSendIn_handler(const NATIVE_INT_TYPE portNum, Fw::Buffer& fwBuffer) {
    // TODO
}

void DpWriter ::schedIn_handler(const NATIVE_INT_TYPE portNum, NATIVE_UINT_TYPE context) {
    // TODO
}

}  // end namespace Svc
