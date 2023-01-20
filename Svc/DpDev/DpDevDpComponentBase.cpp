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

Fw::SerializeStatus DpDevDpComponentBase ::Dp_SerializeRecord_U32Record(Fw::Buffer& buffer, U32 element) {
    // TODO
    return Fw::FW_SERIALIZE_OK;
}

Fw::SerializeStatus DpDevDpComponentBase ::Dp_SerializeRecord_DataRecord(Fw::Buffer& buffer,
                                                                         const DpDev_Data& element) {
    // TODO
    return Fw::FW_SERIALIZE_OK;
}

void DpDevDpComponentBase ::Dp_WriteProduct(ContainerId::T containerId, Fw::Buffer& buffer) {
    // TODO
}

// ----------------------------------------------------------------------
// Private Dp handling functions
// ----------------------------------------------------------------------

void DpDevDpComponentBase ::productRecvIn_handler(const NATIVE_INT_TYPE portNum,
                                                  FwDpIdType id,
                                                  const Fw::Buffer& buffer) {
    // TODO
}

}  // end namespace Svc
