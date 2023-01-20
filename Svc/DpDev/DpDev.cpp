// ======================================================================
// \title  DpDev.cpp
// \author bocchino
// \brief  cpp file for DpDev component implementation class
// ======================================================================

#include "Svc/DpDev/DpDev.hpp"

namespace Svc {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

DpDev ::DpDev(const char* const compName) : DpDevDpComponentBase(compName), u32Data(0) {}

void DpDev ::init(const NATIVE_INT_TYPE queueDepth, const NATIVE_INT_TYPE instance) {
    DpDevComponentBase::init(queueDepth, instance);
}

DpDev ::~DpDev() {}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void DpDev ::schedIn_handler(const NATIVE_INT_TYPE portNum, NATIVE_UINT_TYPE context) {
    // TODO: Request buffers
    ++this->u32Data;
}

// ----------------------------------------------------------------------
// Implementations of data product handlers
// ----------------------------------------------------------------------

void DpDev ::Dp_Write_handler(ContainerId::T containerId, Fw::Buffer& buffer, Fw::SerializeBufferBase& serialRepr) {
    // TODO
}

}  // end namespace Svc
