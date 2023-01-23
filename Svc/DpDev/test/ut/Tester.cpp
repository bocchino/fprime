// ======================================================================
// \title  DpDev.hpp
// \author bocchino
// \brief  cpp file for DpDev test harness implementation class
// ======================================================================

#include <cstdio>
#include <cstring>

#include "STest/Pick/Pick.hpp"
#include "Svc/DpDev/test/ut/Tester.hpp"

namespace Svc {

// ----------------------------------------------------------------------
// Construction and destruction
// ----------------------------------------------------------------------

Tester ::Tester()
    : DpDevGTestBase("Tester", Tester::MAX_HISTORY_SIZE),
      component("DpDev", STest::Pick::any(), STest::Pick::any()),
      container1Buffer(this->container1Data, DpDev::CONTAINER_1_SIZE),
      container2Buffer(this->container2Data, DpDev::CONTAINER_2_SIZE) {
    memset(this->container1Data, 0, sizeof this->container1Data);
    memset(this->container2Data, 0, sizeof this->container2Data);
    this->initComponents();
    this->connectPorts();
    this->component.setIdBase(ID_BASE);
}

Tester ::~Tester() {}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void Tester ::schedIn_OK() {
    this->invoke_to_schedIn(0, 0);
    this->component.doDispatch();
    ASSERT_FROM_PORT_HISTORY_SIZE(2);
    ASSERT_from_productRequestOut_SIZE(2);
    ASSERT_from_productRequestOut(0, ID_BASE + DpDev::ContainerId::Container1,
                                  FwDpBuffSizeType(DpDev::CONTAINER_1_SIZE));
    ASSERT_from_productRequestOut(1, ID_BASE + DpDev::ContainerId::Container2,
                                  FwDpBuffSizeType(DpDev::CONTAINER_2_SIZE));
}

// ----------------------------------------------------------------------
// Handlers for typed from ports
// ----------------------------------------------------------------------

void Tester ::from_productRequestOut_handler(const NATIVE_INT_TYPE portNum, FwDpIdType id, FwDpBuffSizeType size) {
    this->pushFromPortEntry_productRequestOut(id, size);
}

void Tester ::from_productSendOut_handler(const NATIVE_INT_TYPE portNum, FwDpIdType id, const Fw::Buffer& buffer) {
    this->pushFromPortEntry_productSendOut(id, buffer);
}

}  // end namespace Svc
