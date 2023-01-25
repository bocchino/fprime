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
    ASSERT_from_productRequestOut(0, ID_BASE + DpTest::ContainerId::Container1,
                                  FwDpBuffSizeType(DpTest::CONTAINER_1_SIZE));
    ASSERT_from_productRequestOut(1, ID_BASE + DpTest::ContainerId::Container2,
                                  FwDpBuffSizeType(DpTest::CONTAINER_2_SIZE));
}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

Fw::Time Tester::randomizeTestTime() {
    const U32 seconds = STest::Pick::any();
    const U32 useconds = STest::Pick::startLength(0, 1000000);
    const Fw::Time time(seconds, useconds);
    this->setTestTime(time);
    return time;
}

// ----------------------------------------------------------------------
// Handlers for typed from ports
// ----------------------------------------------------------------------

void Tester::from_productRequestOut_handler(const NATIVE_INT_TYPE portNum, FwDpIdType id, FwDpBuffSizeType size) {
    this->pushFromPortEntry_productRequestOut(id, size);
}

void Tester::from_productSendOut_handler(const NATIVE_INT_TYPE portNum, FwDpIdType id, const Fw::Buffer& buffer) {
    this->pushFromPortEntry_productSendOut(id, buffer);
}

}  // end namespace FppTest
