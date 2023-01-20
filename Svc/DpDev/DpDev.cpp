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

DpDev ::DpDev(const char* const compName) : DpDevDpComponentBase(compName) {}

void DpDev ::init(const NATIVE_INT_TYPE queueDepth, const NATIVE_INT_TYPE instance) {
    DpDevComponentBase::init(queueDepth, instance);
}

DpDev ::~DpDev() {}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

// TODO

// ----------------------------------------------------------------------
// Implementations of data product handlers
// ----------------------------------------------------------------------

Fw::SerializeStatus DpDev ::Dp_Write_handler(ContainerId::T containerId, Fw::Buffer& buffer) {
    // TODO
    return Fw::FW_SERIALIZE_OK;
}

}  // end namespace Svc
