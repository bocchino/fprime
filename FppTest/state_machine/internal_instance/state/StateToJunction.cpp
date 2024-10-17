// ======================================================================
// \title  StateToJunction.cpp
// \author bocchino
// \brief  cpp file for StateToJunction component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/StateToJunction.hpp"
#include "Fw/Types/Assert.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

StateToJunction::StateToJunction(const char* const compName)
    : StateToJunctionComponentBase(compName),
      m_smStateStateToJunction_actionHistory(),
      m_smStateStateToJunction_guard_g() {}

StateToJunction::~StateToJunction() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void StateToJunction::FppTest_SmState_StateToJunction_action_exitS1(SmId smId,
                                                                    FppTest_SmState_StateToJunction::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToJunction);
    this->m_smStateStateToJunction_actionHistory.push(signal, ActionId::EXIT_S1);
}

void StateToJunction::FppTest_SmState_StateToJunction_action_exitS2(SmId smId,
                                                                    FppTest_SmState_StateToJunction::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToJunction);
    this->m_smStateStateToJunction_actionHistory.push(signal, ActionId::EXIT_S2);
}

void StateToJunction::FppTest_SmState_StateToJunction_action_exitS3(SmId smId,
                                                                    FppTest_SmState_StateToJunction::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToJunction);
    this->m_smStateStateToJunction_actionHistory.push(signal, ActionId::EXIT_S3);
}

void StateToJunction::FppTest_SmState_StateToJunction_action_a(SmId smId,
                                                               FppTest_SmState_StateToJunction::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToJunction);
    this->m_smStateStateToJunction_actionHistory.push(signal, ActionId::A);
}

void StateToJunction::FppTest_SmState_StateToJunction_action_enterS1(SmId smId,
                                                                     FppTest_SmState_StateToJunction::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToJunction);
    this->m_smStateStateToJunction_actionHistory.push(signal, ActionId::ENTER_S1);
}

void StateToJunction::FppTest_SmState_StateToJunction_action_enterS2(SmId smId,
                                                                     FppTest_SmState_StateToJunction::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToJunction);
    this->m_smStateStateToJunction_actionHistory.push(signal, ActionId::ENTER_S2);
}

void StateToJunction::FppTest_SmState_StateToJunction_action_enterS3(SmId smId,
                                                                     FppTest_SmState_StateToJunction::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToJunction);
    this->m_smStateStateToJunction_actionHistory.push(signal, ActionId::ENTER_S3);
}

void StateToJunction::FppTest_SmState_StateToJunction_action_enterS4(SmId smId,
                                                                     FppTest_SmState_StateToJunction::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateStateToJunction);
    this->m_smStateStateToJunction_actionHistory.push(signal, ActionId::ENTER_S4);
}

// ----------------------------------------------------------------------
// Implementations for internal state machine guards
// ----------------------------------------------------------------------

bool StateToJunction ::FppTest_SmState_StateToJunction_guard_g(SmId smId,
                                                               FppTest_SmState_StateToJunction::Signal signal) const {
    FW_ASSERT(smId == SmId::smStateStateToJunction, static_cast<FwAssertArgType>(smId));
    return this->m_smStateStateToJunction_guard_g.call(signal);
}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void StateToJunction::testInit() {
    this->m_smStateStateToJunction_actionHistory.clear();
    this->init(queueDepth, instanceId);
    ASSERT_EQ(this->smStateStateToJunction_getState(), SmState_StateToJunction::State::S1_S2);
    const FwSizeType expectedSize = 2;
    ASSERT_EQ(this->m_smStateStateToJunction_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_smStateStateToJunction_actionHistory.getSignals();
    const auto& actions = this->m_smStateStateToJunction_actionHistory.getValues();
    for (FwSizeType i = 0; i < expectedSize; i++) {
        ASSERT_EQ(signals.getItemAt(i), SmState_StateToJunction::Signal::__FPRIME_AC_INITIAL_TRANSITION);
    }
    ASSERT_EQ(actions.getItemAt(0), ActionId::ENTER_S1);
    ASSERT_EQ(actions.getItemAt(1), ActionId::ENTER_S2);
}

void StateToJunction::testS2_to_J() {
    this->m_smStateStateToJunction_actionHistory.clear();
    this->m_smStateStateToJunction_guard_g.reset();
    this->m_smStateStateToJunction_guard_g.setReturnValue(true);
    this->init(queueDepth, instanceId);
    this->m_smStateStateToJunction_actionHistory.clear();
    this->smStateStateToJunction_sendSignal_S1_to_J();
    const auto status = this->doDispatch();
    ASSERT_EQ(status, MSG_DISPATCH_OK);
    ASSERT_EQ(this->smStateStateToJunction_getState(), SmState_StateToJunction::State::S4_S5);
    const FwSizeType expectedSize = 4;
    ASSERT_EQ(this->m_smStateStateToJunction_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_smStateStateToJunction_actionHistory.getSignals();
    const auto& actions = this->m_smStateStateToJunction_actionHistory.getValues();
    for (FwSizeType i = 0; i < expectedSize; i++) {
      ASSERT_EQ(signals.getItemAt(i), SmState_StateToJunction::Signal::S1_to_J);
    }
    ASSERT_EQ(actions.getItemAt(0), ActionId::EXIT_S2);
    ASSERT_EQ(actions.getItemAt(1), ActionId::EXIT_S1);
    ASSERT_EQ(actions.getItemAt(2), ActionId::A);
    ASSERT_EQ(actions.getItemAt(3), ActionId::ENTER_S4);
}

void StateToJunction::testS2_to_S3() {
    this->m_smStateStateToJunction_actionHistory.clear();
    this->init(queueDepth, instanceId);
    this->m_smStateStateToJunction_actionHistory.clear();
    this->smStateStateToJunction_sendSignal_S2_to_S3();
    const auto status = this->doDispatch();
    ASSERT_EQ(status, MSG_DISPATCH_OK);
    ASSERT_EQ(this->smStateStateToJunction_getState(), SmState_StateToJunction::State::S1_S3);
    const FwSizeType expectedSize = 2;
    ASSERT_EQ(this->m_smStateStateToJunction_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_smStateStateToJunction_actionHistory.getSignals();
    const auto& actions = this->m_smStateStateToJunction_actionHistory.getValues();
    for (FwSizeType i = 0; i < expectedSize; i++) {
      ASSERT_EQ(signals.getItemAt(i), SmState_StateToJunction::Signal::S2_to_S3);
    }
    ASSERT_EQ(actions.getItemAt(0), ActionId::EXIT_S2);
    ASSERT_EQ(actions.getItemAt(1), ActionId::ENTER_S3);
}

void StateToJunction::testS2_to_S4() {
    this->m_smStateStateToJunction_actionHistory.clear();
    this->m_smStateStateToJunction_guard_g.reset();
    this->m_smStateStateToJunction_guard_g.setReturnValue(true);
    this->init(queueDepth, instanceId);
    this->m_smStateStateToJunction_actionHistory.clear();
    this->smStateStateToJunction_sendSignal_S1_to_S4();
    const auto status = this->doDispatch();
    ASSERT_EQ(status, MSG_DISPATCH_OK);
    ASSERT_EQ(this->smStateStateToJunction_getState(), SmState_StateToJunction::State::S4_S5);
    const FwSizeType expectedSize = 4;
    ASSERT_EQ(this->m_smStateStateToJunction_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_smStateStateToJunction_actionHistory.getSignals();
    const auto& actions = this->m_smStateStateToJunction_actionHistory.getValues();
    for (FwSizeType i = 0; i < expectedSize; i++) {
      ASSERT_EQ(signals.getItemAt(i), SmState_StateToJunction::Signal::S1_to_S4);
    }
    ASSERT_EQ(actions.getItemAt(0), ActionId::EXIT_S2);
    ASSERT_EQ(actions.getItemAt(1), ActionId::EXIT_S1);
    ASSERT_EQ(actions.getItemAt(2), ActionId::A);
    ASSERT_EQ(actions.getItemAt(3), ActionId::ENTER_S4);
}

void StateToJunction::testS3_to_J() {
    this->m_smStateStateToJunction_actionHistory.clear();
    this->m_smStateStateToJunction_guard_g.reset();
    this->init(queueDepth, instanceId);
    {
        this->m_smStateStateToJunction_actionHistory.clear();
        this->smStateStateToJunction_sendSignal_S2_to_S3();
        const auto status = this->doDispatch();
        ASSERT_EQ(status, MSG_DISPATCH_OK);
    }
    {
        this->m_smStateStateToJunction_actionHistory.clear();
        this->smStateStateToJunction_sendSignal_S1_to_J();
        const auto status = this->doDispatch();
        ASSERT_EQ(status, MSG_DISPATCH_OK);
    }
    ASSERT_EQ(this->smStateStateToJunction_getState(), SmState_StateToJunction::State::S4_S6);
    const FwSizeType expectedSize = 4;
    ASSERT_EQ(this->m_smStateStateToJunction_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_smStateStateToJunction_actionHistory.getSignals();
    const auto& actions = this->m_smStateStateToJunction_actionHistory.getValues();
    for (FwSizeType i = 0; i < expectedSize; i++) {
      ASSERT_EQ(signals.getItemAt(i), SmState_StateToJunction::Signal::S1_to_J);
    }
    ASSERT_EQ(actions.getItemAt(0), ActionId::EXIT_S3);
    ASSERT_EQ(actions.getItemAt(1), ActionId::EXIT_S1);
    ASSERT_EQ(actions.getItemAt(2), ActionId::A);
    ASSERT_EQ(actions.getItemAt(3), ActionId::ENTER_S4);
}

void StateToJunction::testS3_to_S4() {
    this->m_smStateStateToJunction_actionHistory.clear();
    this->m_smStateStateToJunction_guard_g.reset();
    this->init(queueDepth, instanceId);
    {
        this->m_smStateStateToJunction_actionHistory.clear();
        this->smStateStateToJunction_sendSignal_S2_to_S3();
        const auto status = this->doDispatch();
        ASSERT_EQ(status, MSG_DISPATCH_OK);
    }
    {
        this->m_smStateStateToJunction_actionHistory.clear();
        this->smStateStateToJunction_sendSignal_S1_to_S4();
        const auto status = this->doDispatch();
        ASSERT_EQ(status, MSG_DISPATCH_OK);
    }
    ASSERT_EQ(this->smStateStateToJunction_getState(), SmState_StateToJunction::State::S4_S6);
    const FwSizeType expectedSize = 4;
    ASSERT_EQ(this->m_smStateStateToJunction_actionHistory.getSize(), expectedSize);
    const auto& signals = this->m_smStateStateToJunction_actionHistory.getSignals();
    const auto& actions = this->m_smStateStateToJunction_actionHistory.getValues();
    for (FwSizeType i = 0; i < expectedSize; i++) {
      ASSERT_EQ(signals.getItemAt(i), SmState_StateToJunction::Signal::S1_to_S4);
    }
    ASSERT_EQ(actions.getItemAt(0), ActionId::EXIT_S3);
    ASSERT_EQ(actions.getItemAt(1), ActionId::EXIT_S1);
    ASSERT_EQ(actions.getItemAt(2), ActionId::A);
    ASSERT_EQ(actions.getItemAt(3), ActionId::ENTER_S4);
}

}  // namespace SmInstanceState

}  // namespace FppTest
