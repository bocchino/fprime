// ======================================================================
// \title  DpDevDpComponentBase.cpp
// \author bocchino
// \brief  cpp file for DpDev Dp component base (to be auto-generated)
// ======================================================================

#include "Svc/DpDev/DpDevDpComponentBase.hpp"
#include "FpConfig.hpp"
#include "Fw/Types/Assert.hpp"

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
    const auto globalId = this->getIdBase() + containerId;
    this->productRequestOut_out(0, globalId, size);
}

void DpDevDpComponentBase ::Dp_Send(DpContainer& container) {
    // Update the time tag
    const Fw::Time timeTag = this->getTime();
    container.setTimeTag(timeTag);
    // Serialize the header into the packet
    auto status = container.serializeHeader();
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);
    // Update the size of the buffer according to the data size
    const auto packetSize = container.getPacketSize();
    Fw::Buffer buffer = container.getBuffer();
    FW_ASSERT(packetSize <= buffer.getSize());
    buffer.setSize(packetSize);
    // Send the buffer
    this->productSendOut_out(0, container.getId(), buffer);
}

// ----------------------------------------------------------------------
// Private Dp handling functions
// ----------------------------------------------------------------------

void DpDevDpComponentBase ::productRecvIn_handler(const NATIVE_INT_TYPE portNum,
                                                  FwDpIdType id,
                                                  const Fw::Buffer& buffer) {
    DpContainer container(id, buffer, this->getIdBase());
    this->Dp_Recv_handler(container);
}

}  // end namespace Svc
