// ======================================================================
// \title  BasicTestAbsType.cpp
// \author bocchino
// \brief  cpp file for BasicTestAbsType component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/BasicTestAbsType.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

BasicTestAbsType ::BasicTestAbsType(const char* const compName)
    : BasicTestAbsTypeComponentBase(compName),
      m_smStateBasicTestAbsType_action_a_history(),
      m_smStateBasicTestAbsType_action_b_history() {}

BasicTestAbsType ::~BasicTestAbsType() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void BasicTestAbsType ::FppTest_SmState_BasicTestAbsType_action_a(SmId smId,
                                                                  FppTest_SmState_BasicTestAbsType::Signal signal) {
    this->m_smStateBasicTestAbsType_action_a_history.push(signal);
}

void BasicTestAbsType ::FppTest_SmState_BasicTestAbsType_action_b(SmId smId,
                                                                  FppTest_SmState_BasicTestAbsType::Signal signal,
                                                                  const SmHarness::TestAbsType& value) {
    this->m_smStateBasicTestAbsType_action_b_history.push(signal, SmHarness::TestAbsType(value));
}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void BasicTestAbsType::test() {
    this->m_smStateBasicTestAbsType_action_a_history.clear();
    this->m_smStateBasicTestAbsType_action_b_history.clear();
    this->init(queueDepth, instanceId);
    ASSERT_EQ(this->smStateBasicTestAbsType_getState(), SmState_BasicTestAbsType::State::S);
    ASSERT_EQ(this->m_smStateBasicTestAbsType_action_a_history.getSize(), 0);
    const SmHarness::TestAbsType value = SmHarness::Pick::testAbsType();
    this->smStateBasicTestAbsType_sendSignal_s(value);
    const auto status = this->doDispatch();
    ASSERT_EQ(status, MSG_DISPATCH_OK);
    ASSERT_EQ(this->smStateBasicTestAbsType_getState(), SmState_BasicTestAbsType::State::T);
    const FwSizeType expectedASize = 5;
    ASSERT_EQ(this->m_smStateBasicTestAbsType_action_a_history.getSize(), expectedASize);
    for (FwSizeType i = 0; i < expectedASize; i++) {
        ASSERT_EQ(this->m_smStateBasicTestAbsType_action_a_history.getItemAt(i), SmState_BasicTestAbsType::Signal::s);
    }
    ASSERT_EQ(this->m_smStateBasicTestAbsType_action_b_history.getSize(), 1);
    ASSERT_EQ(this->m_smStateBasicTestAbsType_action_b_history.getSignals().getItemAt(0),
              SmState_BasicTestAbsType::Signal::s);
    ASSERT_EQ(this->m_smStateBasicTestAbsType_action_b_history.getValues().getItemAt(0), value);
}

}  // namespace SmInstanceState

}  // namespace FppTest