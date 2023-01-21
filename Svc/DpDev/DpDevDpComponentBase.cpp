// ======================================================================
// \title  DpDevDpComponentBase.cpp
// \author bocchino
// \brief  cpp file for DpDev Dp component base (to be auto-generated)
// ======================================================================

#include "FpConfig.hpp"
#include "Fw/Types/Assert.hpp"
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
    const auto globalId = this->getIdBase() + containerId;
    this->productRequestOut_out(0, globalId, size);
}

Fw::SerializeStatus DpDevDpComponentBase ::Dp_Write(DpPacket& dpPacket) {
    // Write the header into the packet again
    // This time we have the data length
    auto status = dpPacket.writeHeader();
    // If everything is OK, send the buffer
    if (status == Fw::FW_SERIALIZE_OK) {
      // Update the size of the buffer according to the data size
      const auto bufferSize = dpPacket.getBufferSize();
      FW_ASSERT(bufferSize <= dpPacket.buffer.getSize());
      dpPacket.buffer.setSize(bufferSize);
      // Send the buffer
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
    DpPacket dpPacket(id, buffer);
    this->Dp_Recv_handler(dpPacket);
}

}  // end namespace Svc
