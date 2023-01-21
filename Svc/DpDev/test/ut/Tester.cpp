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
    ASSERT_from_productRequestOut(0, DpDev::ContainerId::Container1, FwDpBuffSizeType(DpDev::CONTAINER_1_SIZE));
    ASSERT_from_productRequestOut(1, DpDev::ContainerId::Container2, FwDpBuffSizeType(DpDev::CONTAINER_2_SIZE));
}

void Tester ::productRecvIn_Container1OK() {
    // Invoke the productRecvIn port
    this->invoke_to_productRecvIn(0, DpDev::ContainerId::Container1, this->container1Buffer);
    this->component.doDispatch();
    // Check the port history size
    ASSERT_FROM_PORT_HISTORY_SIZE(1);
    ASSERT_from_productSendOut_SIZE(1);
    // Get the history entry
    const auto entry = this->fromPortHistory_productSendOut->at(0);
    // Check the container id
    ASSERT_EQ(entry.id, DpDev::ContainerId::Container1);
    // Check the buffer size
    auto entryBuffer = entry.buffer;
    const auto bufferSize = this->container1Buffer.getSize();
    ASSERT_EQ(bufferSize, FwDpBuffSizeType(DpDev::CONTAINER_1_SIZE));
    // Get the data size
    auto& serialRepr = entryBuffer.getSerializeRepr();
    serialRepr.setBuffLen(bufferSize);
    FwDpBuffSizeType dataSize = 0;
    auto status = serialRepr.deserialize(dataSize);
    ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
    // Check the data size
    const FwDpBuffSizeType eltSize = sizeof(FwDpIdType) + sizeof(U32);
    const auto expectedNumElts = (bufferSize - sizeof(FwDpBuffSizeType)) / eltSize;
    const auto expectedDataSize = expectedNumElts * eltSize;
    ASSERT_EQ(dataSize, expectedDataSize);
    // Check the data
    for (FwDpBuffSizeType i = 0; i < expectedNumElts; ++i) {
      // TODO
    }
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
