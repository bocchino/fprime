// ======================================================================
// \title  BasicGuardTestAbsType.cpp
// \author bocchino
// \brief  cpp file for BasicGuardTestAbsType component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/BasicGuardTestAbsType.hpp"
#include "Fw/Types/Assert.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

BasicGuardTestAbsType::BasicGuardTestAbsType(const char* const compName)
    : BasicGuardTestAbsTypeComponentBase(compName),
      m_smStateBasicGuardTestAbsType_action_a_history(),
      m_smStateBasicGuardTestAbsType_guard_g() {}

BasicGuardTestAbsType::~BasicGuardTestAbsType() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void BasicGuardTestAbsType::FppTest_SmState_BasicGuardTestAbsType_action_a(
    SmId smId,
    FppTest_SmState_BasicGuardTestAbsType::Signal signal,
    const SmHarness::TestAbsType& value) {
    ASSERT_EQ(smId, SmId::smStateBasicGuardTestAbsType);
    this->m_smStateBasicGuardTestAbsType_action_a_history.push(signal, value);
}

// ----------------------------------------------------------------------
// Implementations for internal state machine guards
// ----------------------------------------------------------------------

bool BasicGuardTestAbsType::FppTest_SmState_BasicGuardTestAbsType_guard_g(
    SmId smId,
    FppTest_SmState_BasicGuardTestAbsType::Signal signal,
    const SmHarness::TestAbsType& value) const {
    FW_ASSERT(smId == SmId::smStateBasicGuardTestAbsType, static_cast<FwAssertArgType>(smId));
    return this->m_smStateBasicGuardTestAbsType_guard_g.call(signal, value);
}

// ----------------------------------------------------------------------
// Overflow hook implementations for internal state machines
// ----------------------------------------------------------------------

void BasicGuardTestAbsType::smStateBasicGuardTestAbsType_stateMachineOverflowHook(SmId smId,
                                                                                  FwEnumStoreType signal,
                                                                                  Fw::SerializeBufferBase& buffer) {
    // TODO
}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void BasicGuardTestAbsType::testFalse() {
#if 0
    this->m_smStateBasicGuardTestAbsType_action_a_history.clear();
    this->m_smStateBasicGuardTestAbsType_guard_g.reset();
    this->init(queueDepth, instanceId);
    ASSERT_EQ(this->smStateBasicGuardTestAbsType_getState(), SmState_BasicGuardTestAbsType::State::S);
    ASSERT_EQ(this->m_smStateBasicGuardTestAbsType_action_a_history.getSize(), 0);
    ASSERT_EQ(this->m_smStateBasicGuardTestAbsType_guard_g.getCallHistory().getSize(), 0);
    Fw::TestAbsType value;
    SmHarness::Pick::string(value, SmState::basicGuardTestAbsTypeSize);
    this->smStateBasicGuardTestAbsType_sendSignal_s(value);
    this->doDispatch();
    ASSERT_EQ(this->smStateBasicGuardTestAbsType_getState(), SmState_BasicGuardTestAbsType::State::S);
    ASSERT_EQ(this->m_smStateBasicGuardTestAbsType_guard_g.getCallHistory().getSize(), 1);
    ASSERT_EQ(this->m_smStateBasicGuardTestAbsType_guard_g.getCallHistory().getSignals().getItemAt(0),
              SmState_BasicGuardTestAbsType::Signal::s);
    ASSERT_EQ(this->m_smStateBasicGuardTestAbsType_guard_g.getCallHistory().getValues().getItemAt(0), value);
    ASSERT_EQ(this->m_smStateBasicGuardTestAbsType_action_a_history.getSize(), 0);
#endif
}

void BasicGuardTestAbsType::testTrue() {
    // TODO
}

void BasicGuardTestAbsType::testOverflow() {
    // TODO
}

}  // namespace SmInstanceState

}  // namespace FppTest
