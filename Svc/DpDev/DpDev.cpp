// ======================================================================
// \title  DpDev.cpp
// \author bocchino
// \brief  cpp file for DpDev component implementation class
// ======================================================================

#include <cstdio>

#include "Fw/Types/Assert.hpp"
#include "Svc/DpDev/DpDev.hpp"

namespace Svc {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

DpDev ::DpDev(const char* const compName, U32 u32RecordData, U32 dataRecordData)
    : DpDevDpComponentBase(compName), u32RecordData(u32RecordData), dataRecordData(dataRecordData) {}

void DpDev ::init(const NATIVE_INT_TYPE queueDepth, const NATIVE_INT_TYPE instance) {
    DpDevComponentBase::init(queueDepth, instance);
}

DpDev ::~DpDev() {}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void DpDev ::schedIn_handler(const NATIVE_INT_TYPE portNum, NATIVE_UINT_TYPE context) {
    // Request a buffer for Container 1
    this->Dp_Request(ContainerId::Container1, CONTAINER_1_SIZE);
    // Request a buffer for Container 2
    this->Dp_Request(ContainerId::Container2, CONTAINER_2_SIZE);
}

// ----------------------------------------------------------------------
// Data product handler impelentations
// ----------------------------------------------------------------------

// TODO: Move this switch statement into the auto-generated code
void DpDev ::Dp_Recv_handler(DpPacket& dpPacket) {
    // Convert global id to local id
    const auto idBase = this->getIdBase();
    FW_ASSERT(dpPacket.id >= idBase);
    const auto localId = dpPacket.id - idBase;
    // Switch on the local id
    switch (localId) {
        case ContainerId::Container1:
            this->Dp_Recv_Container1_handler(dpPacket);
            break;
        case ContainerId::Container2:
            this->Dp_Recv_Container2_handler(dpPacket);
            break;
        default:
            FW_ASSERT(0);
            break;
    }
}

void DpDev ::Dp_Recv_Container1_handler(DpPacket& dpPacket) {
    auto status = Fw::FW_SERIALIZE_OK;
    for (FwSizeType i = 0; i < CONTAINER_1_SIZE; ++i) {
        status = dpPacket.serializeRecord_U32Record(this->u32RecordData);
        if (status == Fw::FW_SERIALIZE_NO_ROOM_LEFT) {
            break;
        }
        FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);
    }
    status = this->Dp_Write(dpPacket);
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);
}

void DpDev ::Dp_Recv_Container2_handler(DpPacket& dpPacket) {
    const DpDev_Data dataRecord(this->dataRecordData);
    auto status = Fw::FW_SERIALIZE_OK;
    for (FwSizeType i = 0; i < CONTAINER_2_SIZE; ++i) {
        status = dpPacket.serializeRecord_DataRecord(dataRecord);
        if (status == Fw::FW_SERIALIZE_NO_ROOM_LEFT) {
            break;
        }
        FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);
    }
    status = this->Dp_Write(dpPacket);
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);
}

}  // end namespace Svc
