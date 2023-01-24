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
// Types
// ----------------------------------------------------------------------

DpDevDpComponentBase::DpContainer::DpContainer(FwDpIdType id, const Fw::Buffer& buffer, FwDpIdType baseId)
    : Fw::DpContainer(id, buffer), baseId(baseId) {}

Fw::SerializeStatus DpDevDpComponentBase::DpContainer::serializeRecord_U32Record(U32 elt) {
    auto& serializeRepr = buffer.getSerializeRepr();
    const FwDpIdType id = this->baseId + RecordId::U32Record;
    auto status = serializeRepr.serialize(id);
    if (status == Fw::FW_SERIALIZE_OK) {
        status = serializeRepr.serialize(elt);
    }
    if (status == Fw::FW_SERIALIZE_OK) {
        this->dataSize += sizeof(FwDpIdType);
        this->dataSize += sizeof elt;
    }
    return status;
}

Fw::SerializeStatus DpDevDpComponentBase::DpContainer::serializeRecord_DataRecord(const DpDev_Data& elt  //! The element
) {
    auto& serializeRepr = buffer.getSerializeRepr();
    const FwDpIdType id = this->baseId + RecordId::DataRecord;
    auto status = serializeRepr.serialize(id);
    if (status == Fw::FW_SERIALIZE_OK) {
        status = serializeRepr.serialize(elt);
    }
    if (status == Fw::FW_SERIALIZE_OK) {
        this->dataSize += sizeof(FwDpIdType);
        this->dataSize += sizeof elt;
    }
    return status;
}

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

void DpDevDpComponentBase::productRecvIn_handler(const NATIVE_INT_TYPE portNum,
                                                 FwDpIdType id,
                                                 const Fw::Buffer& buffer) {
    DpContainer container(id, buffer, this->getIdBase());
    this->Dp_Recv_handler(container);
}

void DpDevDpComponentBase::Dp_Recv_handler(DpContainer& container) {
    // Convert global id to local id
    const auto idBase = this->getIdBase();
    const auto id = container.getId();
    FW_ASSERT(id >= idBase);
    const auto localId = id - idBase;
    // Switch on the local id
    switch (localId) {
        case ContainerId::Container1:
            // Set the priority
            container.setPriority(DpDev_Priority::Container1);
            // Call the handler
            this->Dp_Recv_Container1_handler(container);
            break;
        case ContainerId::Container2:
            // Set the priority
            container.setPriority(DpDev_Priority::Container2);
            // Call the handler
            this->Dp_Recv_Container2_handler(container);
            break;
        default:
            FW_ASSERT(0);
            break;
    }
}

}  // end namespace Svc
