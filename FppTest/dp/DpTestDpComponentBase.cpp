// ======================================================================
// \title  DpTestDpComponentBaseHc.cpp
// \author bocchino
// \brief  cpp file for DpTest Dp component base (to be auto-generated)
// ======================================================================

#include "FpConfig.hpp"
#include "FppTest/dp/DpTestDpComponentBase.hpp"
#include "Fw/Types/Assert.hpp"

namespace FppTest {

// ----------------------------------------------------------------------
// Types
// ----------------------------------------------------------------------

DpTestDpComponentBaseHc::DpContainer::DpContainer(FwDpIdType id, const Fw::Buffer& buffer, FwDpIdType baseId)
    : Fw::DpContainer(id, buffer), baseId(baseId) {}

Fw::SerializeStatus DpTestDpComponentBaseHc::DpContainer::serializeRecord_U32Record(U32 elt) {
    auto& serializeRepr = buffer.getSerializeRepr();
    const FwDpIdType id = this->baseId + RecordId::U32Record;
    auto status = serializeRepr.serialize(id);
    if (status == Fw::FW_SERIALIZE_OK) {
        status = serializeRepr.serialize(elt);
    }
    if (status == Fw::FW_SERIALIZE_OK) {
        this->dataSize += sizeof(FwDpIdType);
        this->dataSize += sizeof(U32);
    }
    return status;
}

Fw::SerializeStatus DpTestDpComponentBaseHc::DpContainer::serializeRecord_DataRecord(const DpTest_Data& elt) {
    auto& serializeRepr = buffer.getSerializeRepr();
    const FwDpIdType id = this->baseId + RecordId::DataRecord;
    auto status = serializeRepr.serialize(id);
    if (status == Fw::FW_SERIALIZE_OK) {
        status = serializeRepr.serialize(elt);
    }
    if (status == Fw::FW_SERIALIZE_OK) {
        this->dataSize += sizeof(FwDpIdType);
        this->dataSize += DpTest_Data::SERIALIZED_SIZE;
    }
    return status;
}

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

DpTestDpComponentBaseHc ::DpTestDpComponentBaseHc(const char* const compName) : DpTestComponentBase(compName) {}

DpTestDpComponentBaseHc ::~DpTestDpComponentBaseHc() {}

//! ----------------------------------------------------------------------
//! Functions for managing data products
//! ----------------------------------------------------------------------

void DpTestDpComponentBaseHc ::Dp_Request(ContainerId::T containerId, FwDpBuffSizeType size) {
    const auto globalId = this->getIdBase() + containerId;
    this->productRequestOut_out(0, globalId, size);
}

void DpTestDpComponentBaseHc ::Dp_Send(DpContainer& container) {
    // Update the time tag
    const Fw::Time timeTag = this->getTime();
    container.setTimeTag(timeTag);
    // Serialize the header into the packet
    auto status = container.serializeHeader();
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);
    // Update the size of the buffer according to the data size
    const auto packetSize = container.getPacketSize();
    Fw::Buffer buffer = container.getBuffer();
    FW_ASSERT(packetSize <= buffer.getSize(), packetSize, buffer.getSize());
    buffer.setSize(packetSize);
    // Send the buffer
    this->productSendOut_out(0, container.getId(), buffer);
}

// ----------------------------------------------------------------------
// Private Dp handling functions
// ----------------------------------------------------------------------

void DpTestDpComponentBaseHc::productRecvIn_handler(const NATIVE_INT_TYPE portNum,
                                                  FwDpIdType id,
                                                  const Fw::Buffer& buffer) {
    DpContainer container(id, buffer, this->getIdBase());
    this->Dp_Recv_handler(container);
}

void DpTestDpComponentBaseHc::Dp_Recv_handler(DpContainer& container) {
    // Convert global id to local id
    const auto idBase = this->getIdBase();
    const auto id = container.getId();
    FW_ASSERT(id >= idBase, id, idBase);
    const auto localId = id - idBase;
    // Switch on the local id
    switch (localId) {
        case ContainerId::Container1:
            // Set the priority
            container.setPriority(DpTest_Priority::Container1);
            // Call the handler
            this->Dp_Recv_Container1_handler(container);
            break;
        case ContainerId::Container2:
            // Set the priority
            container.setPriority(DpTest_Priority::Container2);
            // Call the handler
            this->Dp_Recv_Container2_handler(container);
            break;
        default:
            FW_ASSERT(0);
            break;
    }
}

}  // end namespace FppTest
