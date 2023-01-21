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

void DpDevDpComponentBase ::Dp_Request(ContainerId::T containerId, FwDpBuffSizeType size) {
    this->productRequestOut_out(0, containerId, size);
}

Fw::SerializeStatus DpDevDpComponentBase ::Dp_Write(DpPacket& dpPacket) {
    // Store the data length into the buffer
    auto& serialRepr = dpPacket.buffer.getSerializeRepr();
    serialRepr.resetSer();
    auto status = serialRepr.serialize(static_cast<FwDpBuffSizeType>(dpPacket.dataSize));
    // If everything is OK, send the buffer
    if (status == Fw::FW_SERIALIZE_OK) {
      this->productSendOut_out(0, dpPacket.id, dpPacket.buffer);
    }
    // Return the status
    return status;
}

// ----------------------------------------------------------------------
// Private Dp handling functions
// ----------------------------------------------------------------------

void DpDevDpComponentBase ::productRecvIn_handler(const NATIVE_INT_TYPE portNum,
                                                  FwDpIdType id,
                                                  const Fw::Buffer& buffer) {
    DpPacket dpPacket(static_cast<ContainerId::T>(id), buffer);
    this->Dp_Recv_handler(dpPacket);
}

}  // end namespace Svc
