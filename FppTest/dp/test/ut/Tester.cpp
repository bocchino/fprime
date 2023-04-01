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
      component("DpTest", STest::Pick::any(), STest::Pick::any()),
      container1Data{},
      container1Buffer(this->container1Data, DpTest::CONTAINER_1_SIZE),
      container2Data{},
      container2Buffer(this->container2Data, DpTest::CONTAINER_2_SIZE) {
    this->initComponents();
    this->connectPorts();
    this->component.setIdBase(ID_BASE);
}

Tester::~Tester() {}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void Tester::schedIn_OK() {
    this->invoke_to_schedIn(0, 0);
    this->component.doDispatch();
    ASSERT_FROM_PORT_HISTORY_SIZE(2);
    ASSERT_from_productRequestOut_SIZE(2);
    ASSERT_from_productRequestOut(0, ID_BASE + DpTest::ContainerId::Container1, FwSizeType(DpTest::CONTAINER_1_SIZE));
    ASSERT_from_productRequestOut(1, ID_BASE + DpTest::ContainerId::Container2, FwSizeType(DpTest::CONTAINER_2_SIZE));
}

void Tester::productRecvIn_Container1_OK() {
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

void Tester::productRecvIn_Container2_OK() {
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

// ----------------------------------------------------------------------
// Helper methods
// ----------------------------------------------------------------------

Fw::Time Tester::randomizeTestTime() {
    const U32 seconds = STest::Pick::any();
    const U32 useconds = STest::Pick::startLength(0, 1000000);
    const Fw::Time time(seconds, useconds);
    this->setTestTime(time);
    return time;
}

void Tester::productRecvIn_InvokeAndCheckHeader(FwDpIdType id,
                                                FwSizeType dataEltSize,
                                                FwDpPriorityType priority,
                                                Fw::Buffer inputBuffer,
                                                Fw::Buffer& outputBuffer,
                                                FwSizeType& expectedNumElts) {
    const auto containerId = ID_BASE + id;
    // Set the test time
    const Fw::Time timeTag = this->randomizeTestTime();
    // Invoke the productRecvIn port
    this->invoke_to_productRecvIn(0, containerId, inputBuffer);
    this->component.doDispatch();
    // Check the port history size
    ASSERT_FROM_PORT_HISTORY_SIZE(1);
    ASSERT_from_productSendOut_SIZE(1);
    // Get the history entry
    const auto entry = this->fromPortHistory_productSendOut->at(0);
    // Check the container id
    ASSERT_EQ(entry.id, containerId);
    // Check the buffer size
    outputBuffer = entry.buffer;
    const auto bufferSize = outputBuffer.getSize();
    ASSERT_GE(bufferSize, FwSizeType(DpTest::DpContainer::Header::SIZE));
    // Deserialize the packet header
    Fw::TestUtil::DpContainerHeader header;
    header.deserialize(outputBuffer);
    // Check the container id
    ASSERT_EQ(header.id, containerId);
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

// ----------------------------------------------------------------------
// Handlers for typed from ports
// ----------------------------------------------------------------------

void Tester::from_productRequestOut_handler(const NATIVE_INT_TYPE portNum, FwDpIdType id, FwSizeType size) {
    this->pushFromPortEntry_productRequestOut(id, size);
}

void Tester::from_productSendOut_handler(const NATIVE_INT_TYPE portNum, FwDpIdType id, const Fw::Buffer& buffer) {
    this->pushFromPortEntry_productSendOut(id, buffer);
}

}  // end namespace FppTest
