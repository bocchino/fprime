// ======================================================================
// \title  DpTest.cpp
// \author bocchino
// \brief  cpp file for DpTest component implementation class
// ======================================================================

#include <cstdio>

#include "FppTest/dp/DpTest.hpp"
#include "Fw/Types/Assert.hpp"

namespace FppTest {

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

DpTest ::DpTest(const char* const compName, U32 u32RecordData, U16 dataRecordData, Fw::ByteArray rawRecordData)
    : DpTestComponentBase(compName),
      u32RecordData(u32RecordData),
      dataRecordData(dataRecordData),
      rawRecordData(rawRecordData),
      sendTime(Fw::ZERO_TIME) {}

void DpTest ::init(const NATIVE_INT_TYPE queueDepth, const NATIVE_INT_TYPE instance) {
    DpTestComponentBase::init(queueDepth, instance);
}

DpTest ::~DpTest() {}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void DpTest::schedIn_handler(const NATIVE_INT_TYPE portNum, NATIVE_UINT_TYPE context) {
    // Request a buffer for Container 1
    this->Dp_Request(ContainerId::Container1, CONTAINER_1_SIZE);
    // Request a buffer for Container 2
    this->Dp_Request(ContainerId::Container2, CONTAINER_2_SIZE);
    // Request a buffer for Container 3
    this->Dp_Request(ContainerId::Container3, CONTAINER_3_SIZE);
    // Get a buffer for Container 1
    {
        DpContainer container;
        Fw::Success status = this->Dp_Get(ContainerId::Container1, CONTAINER_1_SIZE, container);
        // Check the container
        if (status == Fw::Success::SUCCESS) {
            this->checkContainer(container, ContainerId::Container1, CONTAINER_1_SIZE);
        }
    }
    // Get a buffer for Container 2
    {
        DpContainer container;
        Fw::Success status = this->Dp_Get(ContainerId::Container2, CONTAINER_2_SIZE, container);
        // Check the container
        if (status == Fw::Success::SUCCESS) {
            this->checkContainer(container, ContainerId::Container2, CONTAINER_2_SIZE);
        }
    }
    // Get a buffer for Container 3
    {
        DpContainer container;
        Fw::Success status = this->Dp_Get(ContainerId::Container3, CONTAINER_3_SIZE, container);
        // Check the container
        if (status == Fw::Success::SUCCESS) {
            this->checkContainer(container, ContainerId::Container3, CONTAINER_3_SIZE);
        }
    }
}

// ----------------------------------------------------------------------
// Data product handler impelentations
// ----------------------------------------------------------------------

void DpTest ::Dp_Recv_Container1_handler(DpContainer& container, Fw::Success::T status) {
    if (status == Fw::Success::SUCCESS) {
        auto serializeStatus = Fw::FW_SERIALIZE_OK;
        for (FwSizeType i = 0; i < CONTAINER_1_SIZE; ++i) {
            serializeStatus = container.serializeRecord_U32Record(this->u32RecordData);
            if (serializeStatus == Fw::FW_SERIALIZE_NO_ROOM_LEFT) {
                break;
            }
            FW_ASSERT(serializeStatus == Fw::FW_SERIALIZE_OK, status);
        }
        // Use the time stamp from the time get port
        this->Dp_Send(container);
    }
}

void DpTest ::Dp_Recv_Container2_handler(DpContainer& container, Fw::Success::T status) {
    if (status == Fw::Success::SUCCESS) {
        const DpTest_Data dataRecord(this->dataRecordData);
        auto serializeStatus = Fw::FW_SERIALIZE_OK;
        for (FwSizeType i = 0; i < CONTAINER_2_SIZE; ++i) {
            serializeStatus = container.serializeRecord_DataRecord(dataRecord);
            if (serializeStatus == Fw::FW_SERIALIZE_NO_ROOM_LEFT) {
                break;
            }
            FW_ASSERT(serializeStatus == Fw::FW_SERIALIZE_OK, status);
        }
        // Provide an explicit time stamp
        this->Dp_Send(container, this->sendTime);
    }
}

void DpTest ::Dp_Recv_Container3_handler(DpContainer& container, Fw::Success::T status) {
    if (status == Fw::Success::SUCCESS) {
        auto serializeStatus = Fw::FW_SERIALIZE_OK;
        for (FwSizeType i = 0; i < CONTAINER_3_SIZE; ++i) {
            serializeStatus = container.serializeRecord_RawRecord(this->rawRecordData);
            if (serializeStatus == Fw::FW_SERIALIZE_NO_ROOM_LEFT) {
                break;
            }
            FW_ASSERT(serializeStatus == Fw::FW_SERIALIZE_OK, status);
        }
        // Use the time stamp from the time get port
        this->Dp_Send(container);
    }
}

// ----------------------------------------------------------------------
// Private helper functions
// ----------------------------------------------------------------------

void DpTest::checkContainer(const DpContainer& container, FwDpIdType localId, FwSizeType size) const {
    FW_ASSERT(container.getBaseId() == this->getIdBase(), container.getBaseId(), this->getIdBase());
    FW_ASSERT(container.getId() == container.getBaseId() + localId, container.getId(), container.getBaseId(),
              ContainerId::Container1);
    FW_ASSERT(container.getBuffer().getSize() == size, container.getBuffer().getSize(), size);
}

}  // end namespace FppTest
