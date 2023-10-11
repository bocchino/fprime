// ======================================================================
// \title  DpTest.hpp
// \author bocchino
// \brief  cpp file for DpTest test harness implementation class
// ======================================================================

#include <cstdio>
#include <cstring>

#include "FppTest/dp/test/ut/Tester.hpp"
#include "STest/Pick/Pick.hpp"

namespace FppTest {

// ----------------------------------------------------------------------
// Construction and destruction
// ----------------------------------------------------------------------

Tester::Tester()
    : DpTestGTestBase("Tester", Tester::MAX_HISTORY_SIZE),
      container1Data{},
      container1Buffer(this->container1Data, DpTest::CONTAINER_1_SIZE),
      container2Data{},
      container2Buffer(this->container2Data, DpTest::CONTAINER_2_SIZE),
      container3Data{},
      container3Buffer(this->container3Data, DpTest::CONTAINER_3_SIZE),
      container4Data{},
      container4Buffer(this->container4Data, DpTest::CONTAINER_4_SIZE),
      container5Data{},
      container5Buffer(this->container5Data, DpTest::CONTAINER_5_SIZE),
      component("DpTest",
                STest::Pick::any(),
                STest::Pick::any(),
                this->u8ArrayRecordData,
                this->u32ArrayRecordData,
                this->dataArrayRecordData) {
    this->initComponents();
    this->connectPorts();
    this->component.setIdBase(ID_BASE);
    // Fill in arrays with random data
    for (U8& elt : this->u8ArrayRecordData) {
        elt = static_cast<U8>(STest::Pick::any());
    }
    for (U32& elt : this->u32ArrayRecordData) {
        elt = static_cast<U8>(STest::Pick::any());
    }
    for (DpTest_Data& elt : this->dataArrayRecordData) {
        elt.set(static_cast<U16>(STest::Pick::any()));
    }
}

Tester::~Tester() {}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void Tester::schedIn_OK() {
    this->invoke_to_schedIn(0, 0);
    this->component.doDispatch();
    ASSERT_PRODUCT_REQUEST_SIZE(3);
    ASSERT_PRODUCT_REQUEST(0, ID_BASE + DpTest::ContainerId::Container1, FwSizeType(DpTest::CONTAINER_1_SIZE));
    ASSERT_PRODUCT_REQUEST(1, ID_BASE + DpTest::ContainerId::Container2, FwSizeType(DpTest::CONTAINER_2_SIZE));
    ASSERT_PRODUCT_REQUEST(2, ID_BASE + DpTest::ContainerId::Container3, FwSizeType(DpTest::CONTAINER_3_SIZE));
    ASSERT_PRODUCT_GET_SIZE(3);
    ASSERT_PRODUCT_GET(0, ID_BASE + DpTest::ContainerId::Container1, FwSizeType(DpTest::CONTAINER_1_SIZE));
    ASSERT_PRODUCT_GET(1, ID_BASE + DpTest::ContainerId::Container2, FwSizeType(DpTest::CONTAINER_2_SIZE));
    ASSERT_PRODUCT_GET(2, ID_BASE + DpTest::ContainerId::Container3, FwSizeType(DpTest::CONTAINER_3_SIZE));
}

void Tester::productRecvIn_Container1_SUCCESS() {
    Fw::Buffer buffer;
    FwSizeType expectedNumElts;
    // Invoke the port and check the header
    this->productRecvIn_InvokeAndCheckHeader(DpTest::ContainerId::Container1, sizeof(U32),
                                             DpTest::ContainerPriority::Container1, this->container1Buffer, buffer,
                                             expectedNumElts);
    // Check the data
    auto& serialRepr = buffer.getSerializeRepr();
    for (FwSizeType i = 0; i < expectedNumElts; ++i) {
        FwDpIdType id;
        U32 elt;
        auto status = serialRepr.deserialize(id);
        ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
        const FwDpIdType expectedId = this->component.getIdBase() + DpTest::RecordId::U32Record;
        ASSERT_EQ(id, expectedId);
        status = serialRepr.deserialize(elt);
        ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
        ASSERT_EQ(elt, this->component.u32RecordData);
    }
}

void Tester::productRecvIn_Container1_FAILURE() {
    productRecvIn_CheckFailure(DpTest::ContainerId::Container1, this->container1Buffer);
}

void Tester::productRecvIn_Container2_SUCCESS() {
    Fw::Buffer buffer;
    FwSizeType expectedNumElts;
    // Invoke the port and check the header
    this->productRecvIn_InvokeAndCheckHeader(DpTest::ContainerId::Container2, DpTest_Data::SERIALIZED_SIZE,
                                             DpTest::ContainerPriority::Container2, this->container2Buffer, buffer,
                                             expectedNumElts);
    // Check the data
    auto& serialRepr = buffer.getSerializeRepr();
    for (FwSizeType i = 0; i < expectedNumElts; ++i) {
        FwDpIdType id;
        DpTest_Data elt;
        auto status = serialRepr.deserialize(id);
        ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
        const FwDpIdType expectedId = this->component.getIdBase() + DpTest::RecordId::DataRecord;
        ASSERT_EQ(id, expectedId);
        status = serialRepr.deserialize(elt);
        ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
        ASSERT_EQ(elt.getu16Field(), this->component.dataRecordData);
    }
}

void Tester::productRecvIn_Container2_FAILURE() {
    productRecvIn_CheckFailure(DpTest::ContainerId::Container2, this->container2Buffer);
}

void Tester::productRecvIn_Container3_SUCCESS() {
    Fw::Buffer buffer;
    FwSizeType expectedNumElts;
    const FwSizeType dataEltSize = sizeof(FwSizeType) + this->u8ArrayRecordData.size();
    // Invoke the port and check the header
    this->productRecvIn_InvokeAndCheckHeader(DpTest::ContainerId::Container3, dataEltSize,
                                             DpTest::ContainerPriority::Container3, this->container3Buffer, buffer,
                                             expectedNumElts);

    // Check the data
    auto& serialRepr = buffer.getSerializeRepr();
    for (FwSizeType i = 0; i < expectedNumElts; ++i) {
        FwDpIdType id;
        auto status = serialRepr.deserialize(id);
        ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
        const FwDpIdType expectedId = this->component.getIdBase() + DpTest::RecordId::U8ArrayRecord;
        ASSERT_EQ(id, expectedId);
        FwSizeType size;
        status = serialRepr.deserialize(size);
        ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
        ASSERT_EQ(size, this->u8ArrayRecordData.size());
        const U8* const buffAddr = serialRepr.getBuffAddr();
        for (FwSizeType j = 0; j < size; ++j) {
            U8 byte;
            status = serialRepr.deserialize(byte);
            ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
            ASSERT_EQ(byte, this->u8ArrayRecordData.at(j));
        }
    }
}

void Tester::productRecvIn_Container3_FAILURE() {
    productRecvIn_CheckFailure(DpTest::ContainerId::Container3, this->container3Buffer);
}

void Tester::productRecvIn_Container4_SUCCESS() {
    Fw::Buffer buffer;
    FwSizeType expectedNumElts;
    const FwSizeType dataEltSize = sizeof(FwSizeType) + this->u32ArrayRecordData.size() * sizeof(U32);
    // Invoke the port and check the header
    this->productRecvIn_InvokeAndCheckHeader(DpTest::ContainerId::Container4, dataEltSize,
                                             DpTest::ContainerPriority::Container4, this->container4Buffer, buffer,
                                             expectedNumElts);

    // Check the data
    auto& serialRepr = buffer.getSerializeRepr();
    for (FwSizeType i = 0; i < expectedNumElts; ++i) {
        FwDpIdType id;
        auto status = serialRepr.deserialize(id);
        ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
        const FwDpIdType expectedId = this->component.getIdBase() + DpTest::RecordId::U32ArrayRecord;
        ASSERT_EQ(id, expectedId);
        FwSizeType size;
        status = serialRepr.deserialize(size);
        ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
        ASSERT_EQ(size, this->u32ArrayRecordData.size());
        const U8* const buffAddr = serialRepr.getBuffAddr();
        for (FwSizeType j = 0; j < size; ++j) {
            U32 elt;
            status = serialRepr.deserialize(elt);
            ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
            ASSERT_EQ(elt, this->u32ArrayRecordData.at(j));
        }
    }
}

void Tester::productRecvIn_Container4_FAILURE() {
    productRecvIn_CheckFailure(DpTest::ContainerId::Container4, this->container4Buffer);
}

void Tester::productRecvIn_Container5_SUCCESS() {
    Fw::Buffer buffer;
    FwSizeType expectedNumElts;
    const FwSizeType dataEltSize = sizeof(FwSizeType) + this->dataArrayRecordData.size() * DpTest_Data::SERIALIZED_SIZE;
    // Invoke the port and check the header
    this->productRecvIn_InvokeAndCheckHeader(DpTest::ContainerId::Container5, dataEltSize,
                                             DpTest::ContainerPriority::Container5, this->container5Buffer, buffer,
                                             expectedNumElts);

    // Check the data
    auto& serialRepr = buffer.getSerializeRepr();
    for (FwSizeType i = 0; i < expectedNumElts; ++i) {
        FwDpIdType id;
        auto status = serialRepr.deserialize(id);
        ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
        const FwDpIdType expectedId = this->component.getIdBase() + DpTest::RecordId::DataArrayRecord;
        ASSERT_EQ(id, expectedId);
        FwSizeType size;
        status = serialRepr.deserialize(size);
        ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
        ASSERT_EQ(size, this->dataArrayRecordData.size());
        const U8* const buffAddr = serialRepr.getBuffAddr();
        for (FwSizeType j = 0; j < size; ++j) {
            DpTest_Data elt;
            status = serialRepr.deserialize(elt);
            ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
            ASSERT_EQ(elt, this->dataArrayRecordData.at(j));
        }
    }
}

void Tester::productRecvIn_Container5_FAILURE() {
    productRecvIn_CheckFailure(DpTest::ContainerId::Container5, this->container5Buffer);
}

// ----------------------------------------------------------------------
// Helper methods
// ----------------------------------------------------------------------

Fw::Time Tester::randomizeTestTime() {
    const U32 seconds = STest::Pick::any();
    const U32 useconds = STest::Pick::startLength(0, 1000000);
    const Fw::Time time(seconds, useconds);
    this->setTestTime(time);
    this->component.setSendTime(time);
    return time;
}

namespace {

  void checkHeader(
      Fw::Buffer& buffer,
      FwDpIdType id,
      FwDpPriorityType priority,
      const Fw::Time& timeTag,
      FwSizeType dataSize
  ) {
    // Check the buffer size
    const auto bufferSize = buffer.getSize();
    ASSERT_GE(bufferSize, FwSizeType(Fw::DpContainer::Header::SIZE));
    const auto expectedBufferSize = Fw::DpContainer::Header::SIZE + dataSize;
    ASSERT_EQ(bufferSize, expectedBufferSize);
    // Deserialize the packet header
    Fw::TestUtil::DpContainerHeader header;
    header.deserialize(buffer);
    // Check the container id
    ASSERT_EQ(header.id, id);
    // Check the priority
    ASSERT_EQ(header.priority, priority);
    // Check the time tag
    ASSERT_EQ(header.timeTag, timeTag);
    // Check the data size
    ASSERT_EQ(header.dataSize, dataSize);
  }

}

void Tester::checkProductSend(
      const DpTestTesterBase::DpSend& entry,
      Fw::Buffer& buffer,
      FwDpIdType globalId,
      FwDpPriorityType priority,
      const Fw::Time& timeTag,
      FwSizeType dataSize
) {
  // Check the container id
  ASSERT_EQ(entry.id, globalId);
  // Check the header
  checkHeader(buffer, globalId, priority, timeTag, dataSize);
}

void Tester::productRecvIn_InvokeAndCheckHeader(FwDpIdType id,
                                                FwSizeType dataEltSize,
                                                FwDpPriorityType priority,
                                                Fw::Buffer inputBuffer,
                                                Fw::Buffer& outputBuffer,
                                                FwSizeType& expectedNumElts) {
    const auto globalId = ID_BASE + id;
    // Set the test time
    const Fw::Time timeTag = this->randomizeTestTime();
    // Invoke the productRecvIn port
    this->sendProductResponse(globalId, inputBuffer, Fw::Success::SUCCESS);
    this->component.doDispatch();
    // Check the port history size
    ASSERT_PRODUCT_SEND_SIZE(1);
    // Get the history entry
    const auto entry = this->productSendHistory->at(0);
    // Compute the expected data size
    outputBuffer = entry.buffer;
    const auto bufferSize = outputBuffer.getSize();
    const auto dataCapacity = bufferSize - DpTest::DpContainer::Header::SIZE;
    const auto eltSize = sizeof(FwDpIdType) + dataEltSize;
    expectedNumElts = dataCapacity / eltSize;
    const auto expectedDataSize = expectedNumElts * eltSize;
    // Check the history entry
    // This sets fills the output buffer and sets the deserialization pointer
    // to the start of the data payload
    this->checkProductSend(entry, outputBuffer, globalId, priority, timeTag, expectedDataSize);
}

void Tester::productRecvIn_CheckFailure(FwDpIdType id, Fw::Buffer buffer) {
    // Invoke the port
    const auto globalId = ID_BASE + id;
    this->sendProductResponse(globalId, buffer, Fw::Success::FAILURE);
    this->component.doDispatch();
    // Check the port history size
    ASSERT_PRODUCT_SEND_SIZE(0);
}

// ----------------------------------------------------------------------
// Handlers for typed from ports
// ----------------------------------------------------------------------

Fw::Success::T Tester::productGet_handler(FwDpIdType id, FwSizeType size, Fw::Buffer& buffer) {
    this->pushProductGetEntry(id, size);
    Fw::Success status = Fw::Success::FAILURE;
    FW_ASSERT(id >= ID_BASE, id, ID_BASE);
    const FwDpIdType localId = id - ID_BASE;
    switch (localId) {
        case DpTest::ContainerId::Container1:
            FW_ASSERT(size == DpTest::CONTAINER_1_SIZE);
            buffer = this->container1Buffer;
            status = Fw::Success::SUCCESS;
            break;
        case DpTest::ContainerId::Container2:
            FW_ASSERT(size == DpTest::CONTAINER_2_SIZE);
            buffer = this->container2Buffer;
            status = Fw::Success::SUCCESS;
            break;
        case DpTest::ContainerId::Container3:
            // Make this one fail for testing purposes
            break;
        default:
            break;
    }
    return status;
}

}  // end namespace FppTest
