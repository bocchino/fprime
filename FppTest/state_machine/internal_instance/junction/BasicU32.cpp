// ======================================================================
// \title  BasicU32.cpp
// \author bocchino
// \brief  cpp file for BasicU32 component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/junction/BasicU32.hpp"
#include "Fw/Types/Assert.hpp"

namespace FppTest {

namespace SmInstanceJunction {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

BasicU32 ::BasicU32(const char* const compName)
    : BasicU32ComponentBase(compName),
      m_smJunctionBasicU32_action_a_history(),
      m_smJunctionBasicU32_action_b_history(),
      m_smJunctionBasicU32_guard_g() {}

BasicU32 ::~BasicU32() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void BasicU32 ::FppTest_SmJunction_BasicU32_action_a(SmId smId, FppTest_SmJunction_BasicU32::Signal signal, U32 value) {
    ASSERT_EQ(smId, SmId::smJunctionBasicU32);
    this->m_smJunctionBasicU32_action_a_history.push(signal, value);
}

void BasicU32 ::FppTest_SmJunction_BasicU32_action_b(SmId smId, FppTest_SmJunction_BasicU32::Signal signal) {
    ASSERT_EQ(smId, SmId::smJunctionBasicU32);
    this->m_smJunctionBasicU32_action_b_history.push(signal);
}

// ----------------------------------------------------------------------
// Implementations for internal state machine guards
// ----------------------------------------------------------------------

bool BasicU32 ::FppTest_SmJunction_BasicU32_guard_g(SmId smId,
                                                    FppTest_SmJunction_BasicU32::Signal signal,
                                                    U32 value) const {
    FW_ASSERT(smId == SmId::smJunctionBasicU32, static_cast<FwAssertArgType>(smId));
    return this->m_smJunctionBasicU32_guard_g.call(signal, value);
}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void BasicU32::testTrue() {
    this->m_smJunctionBasicU32_action_a_history.clear();
    this->m_smJunctionBasicU32_action_b_history.clear();
    this->m_smJunctionBasicU32_guard_g.reset();
    this->m_smJunctionBasicU32_guard_g.setReturnValue(true);
    this->init(queueDepth, instanceId);
    ASSERT_EQ(this->smJunctionBasicU32_getState(), SmJunction_BasicU32::State::S1);
    ASSERT_EQ(this->m_smJunctionBasicU32_guard_g.getCallHistory().getSize(), 0);
    ASSERT_EQ(this->m_smJunctionBasicU32_action_a_history.getSize(), 0);
    ASSERT_EQ(this->m_smJunctionBasicU32_action_b_history.getSize(), 0);
    const U32 value = STest::Pick::any();
    this->smJunctionBasicU32_sendSignal_s(value);
    const auto status = this->doDispatch();
    ASSERT_EQ(status, MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_smJunctionBasicU32_guard_g.getCallHistory().getSize(), 1);
    ASSERT_EQ(this->m_smJunctionBasicU32_guard_g.getCallHistory().getSignals().getItemAt(0), SmJunction_BasicU32::Signal::s);
    ASSERT_EQ(this->m_smJunctionBasicU32_guard_g.getCallHistory().getValues().getItemAt(0), value);
    ASSERT_EQ(this->m_smJunctionBasicU32_action_a_history.getSize(), 1);
    ASSERT_EQ(this->m_smJunctionBasicU32_action_a_history.getSignals().getItemAt(0), SmJunction_BasicU32::Signal::s);
    ASSERT_EQ(this->m_smJunctionBasicU32_action_a_history.getValues().getItemAt(0), value);
    ASSERT_EQ(this->m_smJunctionBasicU32_action_b_history.getSize(), 0);
    ASSERT_EQ(this->smJunctionBasicU32_getState(), SmJunction_BasicU32::State::S2);
}

void BasicU32::testFalse() {
    this->m_smJunctionBasicU32_action_a_history.clear();
    this->m_smJunctionBasicU32_action_b_history.clear();
    this->m_smJunctionBasicU32_guard_g.reset();
    this->init(queueDepth, instanceId);
    ASSERT_EQ(this->smJunctionBasicU32_getState(), SmJunction_BasicU32::State::S1);
    ASSERT_EQ(this->m_smJunctionBasicU32_guard_g.getCallHistory().getSize(), 0);
    ASSERT_EQ(this->m_smJunctionBasicU32_action_a_history.getSize(), 0);
    ASSERT_EQ(this->m_smJunctionBasicU32_action_b_history.getSize(), 0);
    const U32 value = STest::Pick::any();
    this->smJunctionBasicU32_sendSignal_s(value);
    const auto status = this->doDispatch();
    ASSERT_EQ(status, MSG_DISPATCH_OK);
    ASSERT_EQ(this->m_smJunctionBasicU32_guard_g.getCallHistory().getSize(), 1);
    ASSERT_EQ(this->m_smJunctionBasicU32_guard_g.getCallHistory().getSignals().getItemAt(0), SmJunction_BasicU32::Signal::s);
    ASSERT_EQ(this->m_smJunctionBasicU32_guard_g.getCallHistory().getValues().getItemAt(0), value);
    ASSERT_EQ(this->m_smJunctionBasicU32_action_a_history.getSize(), 0);
    ASSERT_EQ(this->m_smJunctionBasicU32_action_b_history.getSize(), 1);
    ASSERT_EQ(this->m_smJunctionBasicU32_action_b_history.getItemAt(0), SmJunction_BasicU32::Signal::s);
    ASSERT_EQ(this->smJunctionBasicU32_getState(), SmJunction_BasicU32::State::S3);
}

}  // namespace SmInstanceJunction

}  // namespace FppTest