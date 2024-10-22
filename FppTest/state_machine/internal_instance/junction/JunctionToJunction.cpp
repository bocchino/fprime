// ======================================================================
// \title  JunctionToJunction.cpp
// \author bocchino
// \brief  cpp file for JunctionToJunction component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/junction/JunctionToJunction.hpp"
#include "Fw/Types/Assert.hpp"

namespace FppTest {

namespace SmInstanceJunction {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

JunctionToJunction ::JunctionToJunction(const char* const compName)
    : JunctionToJunctionComponentBase(compName),
      m_smJunctionJunctionToJunction_actionHistory(),
      m_smJunctionJunctionToJunction_guard_g1(),
      m_smJunctionJunctionToJunction_guard_g2() {}

JunctionToJunction ::~JunctionToJunction() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void JunctionToJunction ::FppTest_SmJunction_JunctionToJunction_action_exitS1(
    SmId smId,
    FppTest_SmJunction_JunctionToJunction::Signal signal) {
    ASSERT_EQ(smId, SmId::smJunctionJunctionToJunction);
    this->m_smJunctionJunctionToJunction_actionHistory.push(signal, ActionId::EXIT_S1);
}

void JunctionToJunction ::FppTest_SmJunction_JunctionToJunction_action_a(
    SmId smId,
    FppTest_SmJunction_JunctionToJunction::Signal signal) {
    ASSERT_EQ(smId, SmId::smJunctionJunctionToJunction);
    this->m_smJunctionJunctionToJunction_actionHistory.push(signal, ActionId::A);
}

void JunctionToJunction ::FppTest_SmJunction_JunctionToJunction_action_enterS2(
    SmId smId,
    FppTest_SmJunction_JunctionToJunction::Signal signal) {
    ASSERT_EQ(smId, SmId::smJunctionJunctionToJunction);
    this->m_smJunctionJunctionToJunction_actionHistory.push(signal, ActionId::ENTER_S2);
}

// ----------------------------------------------------------------------
// Implementations for internal state machine guards
// ----------------------------------------------------------------------

bool JunctionToJunction ::FppTest_SmJunction_JunctionToJunction_guard_g1(
    SmId smId,
    FppTest_SmJunction_JunctionToJunction::Signal signal) const {
    FW_ASSERT(smId == SmId::smJunctionJunctionToJunction, static_cast<FwAssertArgType>(smId));
    return this->m_smJunctionJunctionToJunction_guard_g1.call(signal);
}

bool JunctionToJunction ::FppTest_SmJunction_JunctionToJunction_guard_g2(
    SmId smId,
    FppTest_SmJunction_JunctionToJunction::Signal signal) const {
    FW_ASSERT(smId == SmId::smJunctionJunctionToJunction, static_cast<FwAssertArgType>(smId));
    return this->m_smJunctionJunctionToJunction_guard_g2.call(signal);
}

// ----------------------------------------------------------------------
// Overflow hook implementations for internal state machines
// ----------------------------------------------------------------------

void JunctionToJunction ::smJunctionJunctionToJunction_stateMachineOverflowHook(SmId smId,
                                                                                FwEnumStoreType signal,
                                                                                Fw::SerializeBufferBase& buffer) {
    this->m_hookCalled = true;
    ASSERT_EQ(smId, SmId::smJunctionJunctionToJunction);
    ASSERT_EQ(static_cast<SmJunction_JunctionToJunction::Signal>(signal), SmJunction_JunctionToJunction::Signal::s);
    ASSERT_EQ(buffer.getBuffLeft(), 0);
}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void JunctionToJunction::testG1True() {
    this->m_smJunctionJunctionToJunction_actionHistory.clear();
    this->m_smJunctionJunctionToJunction_guard_g1.reset();
    this->m_smJunctionJunctionToJunction_guard_g2.reset();
    this->m_smJunctionJunctionToJunction_guard_g1.setReturnValue(true);
    this->m_hookCalled = false;
    this->init(queueDepth, instanceId);
    ASSERT_EQ(this->smJunctionJunctionToJunction_getState(), SmJunction_JunctionToJunction::State::S1);
    ASSERT_EQ(this->m_smJunctionJunctionToJunction_guard_g1.getCallHistory().getSize(), 0);
    ASSERT_EQ(this->m_smJunctionJunctionToJunction_guard_g2.getCallHistory().getSize(), 0);
    ASSERT_EQ(this->m_smJunctionJunctionToJunction_actionHistory.getSize(), 0);
    this->smJunctionJunctionToJunction_sendSignal_s();
    const auto status = this->doDispatch();
    ASSERT_EQ(status, MSG_DISPATCH_OK);
    ASSERT_FALSE(this->m_hookCalled);
    ASSERT_EQ(this->m_smJunctionJunctionToJunction_guard_g1.getCallHistory().getSize(), 1);
    ASSERT_EQ(this->m_smJunctionJunctionToJunction_guard_g1.getCallHistory().getItemAt(0),
              SmJunction_JunctionToJunction::Signal::s);
    ASSERT_EQ(this->m_smJunctionJunctionToJunction_guard_g2.getCallHistory().getSize(), 0);
    const FwIndexType expectedSize = 3;
    ASSERT_EQ(this->m_smJunctionJunctionToJunction_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_smJunctionJunctionToJunction_actionHistory.getSignals();
    for (FwIndexType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(signals.getItemAt(i), SmJunction_JunctionToJunction::Signal::s);
    }
    const auto& values = this->m_smJunctionJunctionToJunction_actionHistory.getValues();
    ASSERT_EQ(values.getItemAt(0), ActionId::EXIT_S1);
    ASSERT_EQ(values.getItemAt(1), ActionId::A);
    ASSERT_EQ(values.getItemAt(2), ActionId::ENTER_S2);
    ASSERT_EQ(this->smJunctionJunctionToJunction_getState(), SmJunction_JunctionToJunction::State::S2_S3);
}

void JunctionToJunction::testG1FalseG2True() {
    this->m_smJunctionJunctionToJunction_actionHistory.clear();
    this->m_smJunctionJunctionToJunction_guard_g1.reset();
    this->m_smJunctionJunctionToJunction_guard_g2.reset();
    this->m_smJunctionJunctionToJunction_guard_g2.setReturnValue(true);
    this->m_hookCalled = false;
    this->init(queueDepth, instanceId);
    ASSERT_EQ(this->smJunctionJunctionToJunction_getState(), SmJunction_JunctionToJunction::State::S1);
    ASSERT_EQ(this->m_smJunctionJunctionToJunction_guard_g1.getCallHistory().getSize(), 0);
    ASSERT_EQ(this->m_smJunctionJunctionToJunction_guard_g2.getCallHistory().getSize(), 0);
    ASSERT_EQ(this->m_smJunctionJunctionToJunction_actionHistory.getSize(), 0);
    this->smJunctionJunctionToJunction_sendSignal_s();
    const auto status = this->doDispatch();
    ASSERT_EQ(status, MSG_DISPATCH_OK);
    ASSERT_FALSE(this->m_hookCalled);
    ASSERT_EQ(this->m_smJunctionJunctionToJunction_guard_g1.getCallHistory().getSize(), 1);
    ASSERT_EQ(this->m_smJunctionJunctionToJunction_guard_g1.getCallHistory().getItemAt(0),
              SmJunction_JunctionToJunction::Signal::s);
    ASSERT_EQ(this->m_smJunctionJunctionToJunction_guard_g2.getCallHistory().getSize(), 1);
    ASSERT_EQ(this->m_smJunctionJunctionToJunction_guard_g1.getCallHistory().getItemAt(0),
              SmJunction_JunctionToJunction::Signal::s);
    const FwIndexType expectedSize = 3;
    ASSERT_EQ(this->m_smJunctionJunctionToJunction_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_smJunctionJunctionToJunction_actionHistory.getSignals();
    for (FwIndexType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(signals.getItemAt(i), SmJunction_JunctionToJunction::Signal::s);
    }
    const auto& values = this->m_smJunctionJunctionToJunction_actionHistory.getValues();
    ASSERT_EQ(values.getItemAt(0), ActionId::EXIT_S1);
    ASSERT_EQ(values.getItemAt(1), ActionId::A);
    ASSERT_EQ(values.getItemAt(2), ActionId::ENTER_S2);
    ASSERT_EQ(this->smJunctionJunctionToJunction_getState(), SmJunction_JunctionToJunction::State::S2_S3);
}

void JunctionToJunction::testG1FalseG2False() {
    this->m_smJunctionJunctionToJunction_actionHistory.clear();
    this->m_smJunctionJunctionToJunction_guard_g1.reset();
    this->m_smJunctionJunctionToJunction_guard_g2.reset();
    this->m_hookCalled = false;
    this->init(queueDepth, instanceId);
    ASSERT_EQ(this->smJunctionJunctionToJunction_getState(), SmJunction_JunctionToJunction::State::S1);
    ASSERT_EQ(this->m_smJunctionJunctionToJunction_guard_g1.getCallHistory().getSize(), 0);
    ASSERT_EQ(this->m_smJunctionJunctionToJunction_guard_g2.getCallHistory().getSize(), 0);
    ASSERT_EQ(this->m_smJunctionJunctionToJunction_actionHistory.getSize(), 0);
    this->smJunctionJunctionToJunction_sendSignal_s();
    const auto status = this->doDispatch();
    ASSERT_EQ(status, MSG_DISPATCH_OK);
    ASSERT_FALSE(this->m_hookCalled);
    ASSERT_EQ(this->m_smJunctionJunctionToJunction_guard_g1.getCallHistory().getSize(), 1);
    ASSERT_EQ(this->m_smJunctionJunctionToJunction_guard_g1.getCallHistory().getItemAt(0),
              SmJunction_JunctionToJunction::Signal::s);
    ASSERT_EQ(this->m_smJunctionJunctionToJunction_guard_g2.getCallHistory().getSize(), 1);
    ASSERT_EQ(this->m_smJunctionJunctionToJunction_guard_g1.getCallHistory().getItemAt(0),
              SmJunction_JunctionToJunction::Signal::s);
    const FwIndexType expectedSize = 3;
    ASSERT_EQ(this->m_smJunctionJunctionToJunction_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_smJunctionJunctionToJunction_actionHistory.getSignals();
    for (FwIndexType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(signals.getItemAt(i), SmJunction_JunctionToJunction::Signal::s);
    }
    const auto& values = this->m_smJunctionJunctionToJunction_actionHistory.getValues();
    ASSERT_EQ(values.getItemAt(0), ActionId::EXIT_S1);
    ASSERT_EQ(values.getItemAt(1), ActionId::A);
    ASSERT_EQ(values.getItemAt(2), ActionId::ENTER_S2);
    ASSERT_EQ(this->smJunctionJunctionToJunction_getState(), SmJunction_JunctionToJunction::State::S2_S4);
}

void JunctionToJunction::testOverflow() {
    this->m_hookCalled = false;
    this->init(queueDepth, instanceId);
    for (FwSizeType i = 0; i < queueDepth; i++) {
        this->smJunctionJunctionToJunction_sendSignal_s();
        ASSERT_FALSE(this->m_hookCalled);
    }
    this->smJunctionJunctionToJunction_sendSignal_s();
    ASSERT_TRUE(this->m_hookCalled);
}

}  // namespace SmInstanceJunction

}  // namespace FppTest
