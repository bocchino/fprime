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
      u8ArrayRecordArray(this->u8ArrayRecordData, sizeof this->u8ArrayRecordData),
      component("DpTest", STest::Pick::any(), STest::Pick::any(), this->u8ArrayRecordArray) {
    this->initComponents();
    this->connectPorts();
    this->component.setIdBase(ID_BASE);
    // Fill in array with random data
    for (FwSizeType i = 0; i < this->u8ArrayRecordArray.size; ++i) {
        this->u8ArrayRecordArray.bytes[i] = static_cast<U8>(STest::Pick::any());
    }
}

Tester::~Tester() {}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void Tester::schedIn_OK() {
    this->invoke_to_schedIn(0, 0);
    this->component.doDispatch();
    ASSERT_FROM_PORT_HISTORY_SIZE(6);
    ASSERT_from_productRequestOut_SIZE(3);
    ASSERT_from_productRequestOut(0, ID_BASE + DpTest::ContainerId::Container1, FwSizeType(DpTest::CONTAINER_1_SIZE));
    ASSERT_from_productRequestOut(1, ID_BASE + DpTest::ContainerId::Container2, FwSizeType(DpTest::CONTAINER_2_SIZE));
    ASSERT_from_productRequestOut(2, ID_BASE + DpTest::ContainerId::Container3, FwSizeType(DpTest::CONTAINER_3_SIZE));
    Fw::Buffer buffer;
    ASSERT_from_productGetOut_SIZE(3);
    ASSERT_from_productGetOut(0, ID_BASE + DpTest::ContainerId::Container1, FwSizeType(DpTest::CONTAINER_1_SIZE),
                              buffer);
    ASSERT_from_productGetOut(1, ID_BASE + DpTest::ContainerId::Container2, FwSizeType(DpTest::CONTAINER_2_SIZE),
                              buffer);
    ASSERT_from_productGetOut(2, ID_BASE + DpTest::ContainerId::Container3, FwSizeType(DpTest::CONTAINER_3_SIZE),
                              buffer);
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
    const FwSizeType dataEltSize = sizeof(FwSizeType) + this->u8ArrayRecordArray.size;
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
        ASSERT_EQ(size, this->u8ArrayRecordArray.size);
        const U8* const buffAddr = serialRepr.getBuffAddr();
        for (FwSizeType j = 0; j < size; ++j) {
            U8 byte;
            status = serialRepr.deserialize(byte);
            ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
            ASSERT_EQ(byte, this->u8ArrayRecordArray.bytes[j]);
        }
    }
}

void Tester::productRecvIn_Container3_FAILURE() {
    productRecvIn_CheckFailure(DpTest::ContainerId::Container3, this->container3Buffer);
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
    this->invoke_to_productRecvIn(0, globalId, inputBuffer, Fw::Success::SUCCESS);
    this->component.doDispatch();
    // Check the port history size
    ASSERT_FROM_PORT_HISTORY_SIZE(1);
    ASSERT_from_productSendOut_SIZE(1);
    // Get the history entry
    const auto entry = this->fromPortHistory_productSendOut->at(0);
    // Check the container id
    ASSERT_EQ(entry.id, globalId);
    // Check the buffer size
    outputBuffer = entry.buffer;
    const auto bufferSize = outputBuffer.getSize();
    ASSERT_GE(bufferSize, FwSizeType(DpTest::DpContainer::Header::SIZE));
    // Deserialize the packet header
    Fw::TestUtil::DpContainerHeader header;
    header.deserialize(outputBuffer);
    // Check the container id
    ASSERT_EQ(header.id, globalId);
    // Check the priority
    ASSERT_EQ(header.priority, priority);
    // Check the time tag
    ASSERT_EQ(header.timeTag, timeTag);
    // Check the data size
    const auto dataCapacity = bufferSize - DpTest::DpContainer::Header::SIZE;
    const auto eltSize = sizeof(FwDpIdType) + dataEltSize;
    expectedNumElts = dataCapacity / eltSize;
    const auto expectedDataSize = expectedNumElts * eltSize;
    ASSERT_EQ(header.dataSize, expectedDataSize);
    // Check the buffer size
    const auto expectedBufferSize = DpTest::DpContainer::Header::SIZE + expectedDataSize;
    ASSERT_EQ(bufferSize, expectedBufferSize);
}

void Tester::productRecvIn_CheckFailure(FwDpIdType id, Fw::Buffer buffer) {
    // Invoke the port
    const auto globalId = ID_BASE + id;
    this->invoke_to_productRecvIn(0, globalId, buffer, Fw::Success::FAILURE);
    this->component.doDispatch();
    // Check the port history size
    ASSERT_FROM_PORT_HISTORY_SIZE(0);
    ASSERT_from_productSendOut_SIZE(0);
}

// ----------------------------------------------------------------------
// Handlers for typed from ports
// ----------------------------------------------------------------------

Fw::Success Tester::from_productGetOut_handler(const NATIVE_INT_TYPE portNum,
                                               FwDpIdType id,
                                               FwSizeType size,
                                               Fw::Buffer& buffer) {
    this->pushFromPortEntry_productGetOut(id, size, buffer);
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

void Tester::from_productRequestOut_handler(const NATIVE_INT_TYPE portNum, FwDpIdType id, FwSizeType size) {
    this->pushFromPortEntry_productRequestOut(id, size);
}

void Tester::from_productSendOut_handler(const NATIVE_INT_TYPE portNum, FwDpIdType id, const Fw::Buffer& buffer) {
    this->pushFromPortEntry_productSendOut(id, buffer);
}

}  // end namespace FppTest
