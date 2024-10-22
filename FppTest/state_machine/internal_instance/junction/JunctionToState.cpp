// ======================================================================
// \title  JunctionToState.cpp
// \author bocchino
// \brief  cpp file for JunctionToState component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/junction/JunctionToState.hpp"
#include "Fw/Types/Assert.hpp"

namespace FppTest {

namespace SmInstanceJunction {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

JunctionToState::JunctionToState(const char* const compName)
    : JunctionToStateComponentBase(compName),
      m_smJunctionJunctionToState_actionHistory(),
      m_smJunctionJunctionToState_guard_g() {}

JunctionToState::~JunctionToState() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void JunctionToState::FppTest_SmJunction_JunctionToState_action_exitS1(
    SmId smId,
    FppTest_SmJunction_JunctionToState::Signal signal) {
    ASSERT_EQ(smId, SmId::smJunctionJunctionToState);
    this->m_smJunctionJunctionToState_actionHistory.push(signal, ActionId::EXIT_S1);
}

void JunctionToState::FppTest_SmJunction_JunctionToState_action_a(SmId smId,
                                                                  FppTest_SmJunction_JunctionToState::Signal signal) {
    ASSERT_EQ(smId, SmId::smJunctionJunctionToState);
    this->m_smJunctionJunctionToState_actionHistory.push(signal, ActionId::A);
}

void JunctionToState::FppTest_SmJunction_JunctionToState_action_enterS2(
    SmId smId,
    FppTest_SmJunction_JunctionToState::Signal signal) {
    ASSERT_EQ(smId, SmId::smJunctionJunctionToState);
    this->m_smJunctionJunctionToState_actionHistory.push(signal, ActionId::ENTER_S2);
}

void JunctionToState::FppTest_SmJunction_JunctionToState_action_enterS3(
    SmId smId,
    FppTest_SmJunction_JunctionToState::Signal signal) {
    ASSERT_EQ(smId, SmId::smJunctionJunctionToState);
    this->m_smJunctionJunctionToState_actionHistory.push(signal, ActionId::ENTER_S3);
}

// ----------------------------------------------------------------------
// Implementations for internal state machine guards
// ----------------------------------------------------------------------

bool JunctionToState::FppTest_SmJunction_JunctionToState_guard_g(
    SmId smId,
    FppTest_SmJunction_JunctionToState::Signal signal) const {
    FW_ASSERT(smId == SmId::smJunctionJunctionToState, static_cast<FwAssertArgType>(smId));
    return this->m_smJunctionJunctionToState_guard_g.call(signal);
}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void JunctionToState::testTrue() {
    this->m_smJunctionJunctionToState_actionHistory.clear();
    this->m_smJunctionJunctionToState_guard_g.reset();
    this->m_smJunctionJunctionToState_guard_g.setReturnValue(true);
    this->init(queueDepth, instanceId);
    ASSERT_EQ(this->smJunctionJunctionToState_getState(), SmJunction_JunctionToState::State::S1);
    ASSERT_EQ(this->m_smJunctionJunctionToState_guard_g.getCallHistory().getSize(), 0);
    ASSERT_EQ(this->m_smJunctionJunctionToState_actionHistory.getSize(), 0);
    this->smJunctionJunctionToState_sendSignal_s();
    const auto status = this->doDispatch();
    ASSERT_EQ(status, MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_smJunctionJunctionToState_guard_g.getCallHistory().getSize(), 1);
    ASSERT_EQ(this->m_smJunctionJunctionToState_guard_g.getCallHistory().getItemAt(0),
              SmJunction_JunctionToState::Signal::s);
    const FwIndexType expectedSize = 5;
    ASSERT_EQ(this->m_smJunctionJunctionToState_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_smJunctionJunctionToState_actionHistory.getSignals();
    for (FwIndexType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(signals.getItemAt(i), SmJunction_JunctionToState::Signal::s);
    }
    const auto& values = this->m_smJunctionJunctionToState_actionHistory.getValues();
    ASSERT_EQ(values.getItemAt(0), ActionId::EXIT_S1);
    ASSERT_EQ(values.getItemAt(1), ActionId::A);
    ASSERT_EQ(values.getItemAt(2), ActionId::ENTER_S2);
    ASSERT_EQ(values.getItemAt(3), ActionId::A);
    ASSERT_EQ(values.getItemAt(4), ActionId::ENTER_S3);
    ASSERT_EQ(this->smJunctionJunctionToState_getState(), SmJunction_JunctionToState::State::S2_S3);
}

void JunctionToState::testFalse() {
    this->m_smJunctionJunctionToState_actionHistory.clear();
    this->m_smJunctionJunctionToState_guard_g.reset();
    this->init(queueDepth, instanceId);
    ASSERT_EQ(this->smJunctionJunctionToState_getState(), SmJunction_JunctionToState::State::S1);
    ASSERT_EQ(this->m_smJunctionJunctionToState_guard_g.getCallHistory().getSize(), 0);
    ASSERT_EQ(this->m_smJunctionJunctionToState_actionHistory.getSize(), 0);
    this->smJunctionJunctionToState_sendSignal_s();
    const auto status = this->doDispatch();
    ASSERT_EQ(status, MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_smJunctionJunctionToState_guard_g.getCallHistory().getSize(), 1);
    ASSERT_EQ(this->m_smJunctionJunctionToState_guard_g.getCallHistory().getItemAt(0),
              SmJunction_JunctionToState::Signal::s);
    const FwIndexType expectedSize = 4;
    ASSERT_EQ(this->m_smJunctionJunctionToState_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_smJunctionJunctionToState_actionHistory.getSignals();
    for (FwIndexType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(signals.getItemAt(i), SmJunction_JunctionToState::Signal::s);
    }
    const auto& values = this->m_smJunctionJunctionToState_actionHistory.getValues();
    ASSERT_EQ(values.getItemAt(0), ActionId::EXIT_S1);
    ASSERT_EQ(values.getItemAt(1), ActionId::A);
    ASSERT_EQ(values.getItemAt(2), ActionId::ENTER_S2);
    ASSERT_EQ(values.getItemAt(3), ActionId::ENTER_S3);
    ASSERT_EQ(this->smJunctionJunctionToState_getState(), SmJunction_JunctionToState::State::S2_S3);
}

}  // namespace SmInstanceJunction

}  // namespace FppTest
