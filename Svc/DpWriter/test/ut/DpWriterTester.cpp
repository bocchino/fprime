// ======================================================================
// \title  DpWriterTester.cpp
// \author bocchino
// \brief  cpp file for DpWriter component test harness implementation class
// ======================================================================

#include "DpWriterTester.hpp"
#include "Os/Stub/test/File.hpp"

namespace Svc {

// ----------------------------------------------------------------------
// Construction and destruction
// ----------------------------------------------------------------------

DpWriterTester ::DpWriterTester()
    : DpWriterGTestBase("DpWriterTester", DpWriterTester::MAX_HISTORY_SIZE), component("DpWriter") {
    this->initComponents();
    this->connectPorts();
    Os::Stub::File::Test::StaticData::data.setNextStatus(Os::File::OP_OK);
}

DpWriterTester ::~DpWriterTester() {}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void DpWriterTester ::toDo() {
    // TODO
}

// ----------------------------------------------------------------------
// Handlers for typed from ports
// ----------------------------------------------------------------------

void DpWriterTester ::from_deallocBufferSendOut_handler(NATIVE_INT_TYPE portNum, Fw::Buffer& fwBuffer) {
    // TODO
}

void DpWriterTester ::from_dpWrittenOut_handler(NATIVE_INT_TYPE portNum,
                                                const Svc::DpWrittenPortStrings::StringSize256& fileName,
                                                FwDpPriorityType priority,
                                                FwSizeType size) {
    // TODO
}

void DpWriterTester ::from_procBufferSendOut_handler(NATIVE_INT_TYPE portNum, Fw::Buffer& fwBuffer) {
    // TODO
}

// ----------------------------------------------------------------------
// Protected helper functions 
// ----------------------------------------------------------------------

Os::File::Status DpWriterTester::pickOsFileError() {
    U32 u32Status = STest::Pick::lowerUpper(
        Os::File::OP_OK + 1,
        Os::File::MAX_STATUS - 1
    );
    return static_cast<Os::File::Status>(u32Status);
}

#define TESTER_CHECK_CHANNEL(NAME)                                       \
    {                                                                    \
        const auto changeStatus = this->abstractState.NAME.updatePrev(); \
        if (changeStatus == TestUtils::OnChangeStatus::CHANGED) {        \
            ASSERT_TLM_##NAME##_SIZE(1);                                 \
            ASSERT_TLM_##NAME(0, this->abstractState.NAME.value);        \
        } else {                                                         \
            ASSERT_TLM_##NAME##_SIZE(0);                                 \
        }                                                                \
    }

void DpWriterTester::checkTelemetry() {
    TESTER_CHECK_CHANNEL(NumBuffersReceived);
    // TODO
}

}  // namespace Svc
