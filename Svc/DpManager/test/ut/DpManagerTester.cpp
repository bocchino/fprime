// ======================================================================
// \title  DpManager.hpp
// \author Rob Bocchino
// \brief  cpp file for DpManager test harness implementation
// ======================================================================

#include "Svc/DpManager/test/ut/DpManagerTester.hpp"

namespace Svc {

// ----------------------------------------------------------------------
// Construction and destruction
// ----------------------------------------------------------------------

Tester ::Tester() : DpManagerGTestBase("Tester", Tester::MAX_HISTORY_SIZE), component("DpManager") {
    this->initComponents();
    this->connectPorts();
}

Tester ::~Tester() {}

// ----------------------------------------------------------------------
// Handlers for typed from ports
// ----------------------------------------------------------------------

Fw::Buffer Tester ::from_bufferGetOut_handler(const NATIVE_INT_TYPE portNum, U32 size) {
    this->pushFromPortEntry_bufferGetOut(size);
    Fw::Buffer buffer;
    switch (this->abstractState.bufferGetStatus) {
        case AbstractState::BufferGetStatus::VALID:
            // Construct a valid buffer
            buffer.setData(this->abstractState.bufferData);
            FW_ASSERT(size <= AbstractState::MAX_BUFFER_SIZE);
            buffer.setSize(size);
            break;
        case AbstractState::BufferGetStatus::INVALID:
            // Leave buffer in invalid state
            break;
        default:
            FW_ASSERT(0);
            break;
    }
    return buffer;
}

void Tester ::from_productResponseOut_handler(const NATIVE_INT_TYPE portNum,
                                              FwDpIdType id,
                                              const Fw::Buffer& buffer,
                                              const Fw::Success& status) {
    this->pushFromPortEntry_productResponseOut(id, buffer, status);
}

void Tester ::from_productSendOut_handler(const NATIVE_INT_TYPE portNum, Fw::Buffer& fwBuffer) {
    this->pushFromPortEntry_productSendOut(fwBuffer);
}

// ----------------------------------------------------------------------
// Helper methods
// ----------------------------------------------------------------------

#define TESTER_CHECK_CHANNEL(NAME)                                       \
    {                                                                    \
        const auto changeStatus = this->abstractState.NAME.updatePrev(); \
        if (changeStatus == AbstractState::ChangeStatus::CHANGED) {      \
            ASSERT_TLM_##NAME##_SIZE(1);                                 \
            ASSERT_TLM_##NAME(0, this->abstractState.NAME.value);        \
        } else {                                                         \
            ASSERT_TLM_##NAME##_SIZE(0);                                 \
        }                                                                \
    }

void Tester::checkTelemetry() {
    TESTER_CHECK_CHANNEL(NumSuccessfulAllocations);
    TESTER_CHECK_CHANNEL(NumFailedAllocations);
    TESTER_CHECK_CHANNEL(NumDataProducts);
    TESTER_CHECK_CHANNEL(NumBytes);
}

}  // end namespace Svc
