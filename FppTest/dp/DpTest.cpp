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

DpTest ::DpTest(const char* const compName,
                U32 u32RecordData,
                U16 dataRecordData,
                const U8ArrayRecordData& u8ArrayRecordData,
                const U32ArrayRecordData& u32ArrayRecordData)
    : DpTestComponentBase(compName),
      u32RecordData(u32RecordData),
      dataRecordData(dataRecordData),
      u8ArrayRecordByteArray(const_cast<U8*>(u8ArrayRecordData.data()), u8ArrayRecordData.size()),
      u32ArrayRecordData(u32ArrayRecordData),
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
    this->dpRequest_Container1(CONTAINER_1_SIZE);
    // Request a buffer for Container 2
    this->dpRequest_Container2(CONTAINER_2_SIZE);
    // Request a buffer for Container 3
    this->dpRequest_Container3(CONTAINER_3_SIZE);
    // Get a buffer for Container 1
    {
        DpContainer container;
        Fw::Success status = this->dpGet_Container1(CONTAINER_1_SIZE, container);
        FW_ASSERT(status == Fw::Success::SUCCESS, status);
        // Check the container
        this->checkContainer(container, ContainerId::Container1, CONTAINER_1_SIZE);
    }
    // Get a buffer for Container 2
    {
        DpContainer container;
        Fw::Success status = this->dpGet_Container2(CONTAINER_2_SIZE, container);
        FW_ASSERT(status == Fw::Success::SUCCESS);
        // Check the container
        this->checkContainer(container, ContainerId::Container2, CONTAINER_2_SIZE);
    }
    // Get a buffer for Container 3
    {
        DpContainer container;
        Fw::Success status = this->dpGet_Container3(CONTAINER_3_SIZE, container);
        // This one should fail
        FW_ASSERT(status == Fw::Success::FAILURE);
    }
}

// ----------------------------------------------------------------------
// Data product handler impelentations
// ----------------------------------------------------------------------

void DpTest ::dpRecv_Container1_handler(DpContainer& container, Fw::Success::T status) {
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
        this->dpSend(container);
    }
}

void DpTest ::dpRecv_Container2_handler(DpContainer& container, Fw::Success::T status) {
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
        this->dpSend(container, this->sendTime);
    }
}

void DpTest ::dpRecv_Container3_handler(DpContainer& container, Fw::Success::T status) {
    if (status == Fw::Success::SUCCESS) {
        auto serializeStatus = Fw::FW_SERIALIZE_OK;
        for (FwSizeType i = 0; i < CONTAINER_3_SIZE; ++i) {
            serializeStatus =
                container.serializeRecord_U8ArrayRecord(this->u8ArrayRecordByteArray.bytes, this->u8ArrayRecordByteArray.size);
            if (serializeStatus == Fw::FW_SERIALIZE_NO_ROOM_LEFT) {
                break;
            }
            FW_ASSERT(serializeStatus == Fw::FW_SERIALIZE_OK, status);
        }
        // Use the time stamp from the time get port
        this->dpSend(container);
    }
}

void DpTest ::dpRecv_Container4_handler(DpContainer& container, Fw::Success::T status) {
    // TODO
}

void DpTest ::dpRecv_Container5_handler(DpContainer& container, Fw::Success::T status) {
    // TODO
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
