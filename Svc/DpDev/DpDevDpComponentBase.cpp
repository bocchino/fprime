// ======================================================================
// \title  DpDevDpComponentBase.cpp
// \author bocchino
// \brief  cpp file for DpDev Dp component base (to be auto-generated)
// ======================================================================

#include "FpConfig.hpp"
#include "Svc/DpDev/DpDevDpComponentBase.hpp"

namespace Svc {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

DpDevDpComponentBase ::DpDevDpComponentBase(const char* const compName) : DpDevComponentBase(compName) {}

DpDevDpComponentBase ::~DpDevDpComponentBase() {}

//! ----------------------------------------------------------------------
//! Functions for managing data products
//! ----------------------------------------------------------------------

void DpDevDpComponentBase ::Dp_RequestBuffer(ContainerId::T containerId, FwDpBuffSizeType size) {
    this->productRequestOut_out(0, containerId, size);
}

void DpDevDpComponentBase ::Dp_WriteProduct(ContainerId::T containerId, Fw::Buffer buffer) {
    this->productSendOut_out(0, containerId, buffer);
}

// ----------------------------------------------------------------------
// Private Dp handling functions
// ----------------------------------------------------------------------

void DpDevDpComponentBase ::productRecvIn_handler(const NATIVE_INT_TYPE portNum,
                                                  FwDpIdType id,
                                                  const Fw::Buffer& buffer) {
    this->Dp_WriteProduct(static_cast<ContainerId::T>(id), buffer);
}

}  // end namespace Svc
