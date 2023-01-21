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
// Implementation of the data product receive handler
// ----------------------------------------------------------------------

void DpDev ::Dp_Recv_handler(Container& container) {
    auto status = Fw::FW_SERIALIZE_OK;
    switch (container.id) {
        case ContainerId::Container1:
            status = this->fillContainer1(container);
            break;
        case ContainerId::Container2:
            status = this->fillContainer2(container);
            break;
        default:
            FW_ASSERT(0);
            break;
    }
    if (status == Fw::FW_SERIALIZE_OK) {
        status = this->Dp_Write(container);
    }
    else {
      // TODO
    }
    if (status != Fw::FW_SERIALIZE_OK) {
      // TODO
    }
}

// ----------------------------------------------------------------------
// Private helper functions
// ----------------------------------------------------------------------

Fw::SerializeStatus DpDev ::fillContainer1(Container& container) const {
    auto status = Fw::FW_SERIALIZE_OK;
    for (FwSizeType i = 0; i < CONTAINER_1_SIZE; ++i) {
        status = container.serializeRecord_U32Record(this->u32RecordData);
        if (status != Fw::FW_SERIALIZE_OK) {
            break;
        }
    }
    if (status == Fw::FW_SERIALIZE_NO_ROOM_LEFT) {
        // This just means we ran out of room
        status = Fw::FW_SERIALIZE_OK;
    }
    return status;
}

Fw::SerializeStatus DpDev ::fillContainer2(Container& container) const {
    const DpDev_Data dataRecord(this->dataRecordData);
    auto status = Fw::FW_SERIALIZE_OK;
    for (FwSizeType i = 0; i < CONTAINER_2_SIZE; ++i) {
        status = container.serializeRecord_DataRecord(dataRecord);
        if (status != Fw::FW_SERIALIZE_OK) {
            break;
        }
    }
    if (status == Fw::FW_SERIALIZE_NO_ROOM_LEFT) {
        // This just means we ran out of room
        status = Fw::FW_SERIALIZE_OK;
    }
    return status;
}

}  // end namespace Svc
