// ======================================================================
// \title  Junction.cpp
// \author bocchino
// \brief  cpp file for Junction component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/initial/Junction.hpp"
#include "Fw/Types/Assert.hpp"

namespace FppTest {

namespace SmInstanceInitial {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

Junction::Junction(const char* const compName)
    : JunctionComponentBase(compName),
      m_junction_action_a_history(),
      m_smInitialJunction_action_a_history(),
      m_junction_guard_g(),
      m_smInitialJunction_guard_g() {}

Junction::~Junction() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void Junction::FppTest_SmInitial_Junction_action_a(SmId smId, FppTest_SmInitial_Junction::Signal signal) {
    ASSERT_EQ(smId, SmId::smInitialJunction);
    this->m_smInitialJunction_action_a_history.push(signal);
}

void Junction::FppTest_SmInstanceInitial_Junction_Junction_action_a(
    SmId smId,
    FppTest_SmInstanceInitial_Junction_Junction::Signal signal) {
    ASSERT_EQ(smId, SmId::junction);
    this->m_junction_action_a_history.push(signal);
}

// ----------------------------------------------------------------------
// Implementations for internal state machine guards
// ----------------------------------------------------------------------

bool Junction ::FppTest_SmInitial_Junction_guard_g(SmId smId, FppTest_SmInitial_Junction::Signal signal) const {
    FW_ASSERT(smId == SmId::smInitialJunction, static_cast<FwAssertArgType>(smId));
    return m_smInitialJunction_guard_g.call(signal);
}

bool Junction ::FppTest_SmInstanceInitial_Junction_Junction_guard_g(
    SmId smId,
    FppTest_SmInstanceInitial_Junction_Junction::Signal signal) const {
    FW_ASSERT(smId == SmId::junction, static_cast<FwAssertArgType>(smId));
    return m_junction_guard_g.call(signal);
}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void Junction::testFalse() {
    this->m_junction_action_a_history.clear();
    this->m_smInitialJunction_action_a_history.clear();
    this->m_junction_guard_g.reset();
    this->m_smInitialJunction_guard_g.reset();
    this->init(queueDepth, instanceId);
    ASSERT_EQ(this->junction_getState(), Junction_Junction::State::T);
    ASSERT_EQ(this->smInitialJunction_getState(), SmInitial_Junction::State::T);
    const FwSizeType expectedActionSize = 5;
    const FwSizeType expectedGuardSize = 1;
    this->checkActionsAndGuards(expectedActionSize, expectedGuardSize);
}

void Junction::testTrue() {
    this->m_junction_action_a_history.clear();
    this->m_smInitialJunction_action_a_history.clear();
    this->m_junction_guard_g.reset();
    this->m_smInitialJunction_guard_g.reset();
    this->m_junction_guard_g.setReturnValue(true);
    this->m_smInitialJunction_guard_g.setReturnValue(true);
    this->init(queueDepth, instanceId);
    ASSERT_EQ(this->junction_getState(), Junction_Junction::State::S);
    ASSERT_EQ(this->smInitialJunction_getState(), SmInitial_Junction::State::S);
    const FwSizeType expectedActionSize = 3;
    const FwSizeType expectedGuardSize = 1;
    this->checkActionsAndGuards(expectedActionSize, expectedGuardSize);
}

// ----------------------------------------------------------------------
// Helper functions
// ----------------------------------------------------------------------

void Junction::checkActionsAndGuards(FwSizeType expectedActionSize, FwSizeType expectedGuardSize) {
    ASSERT_EQ(this->m_junction_action_a_history.getSize(), expectedActionSize);
    ASSERT_EQ(this->m_smInitialJunction_action_a_history.getSize(), expectedActionSize);
    for (FwSizeType i = 0; i < expectedActionSize; i++) {
        ASSERT_EQ(this->m_junction_action_a_history.getItemAt(i),
                  Junction_Junction::Signal::__FPRIME_AC_INITIAL_TRANSITION);
        ASSERT_EQ(this->m_smInitialJunction_action_a_history.getItemAt(i),
                  SmInitial_Junction::Signal::__FPRIME_AC_INITIAL_TRANSITION);
    }
    ASSERT_EQ(this->m_junction_guard_g.getCallHistory().getSize(), expectedGuardSize);
    ASSERT_EQ(this->m_smInitialJunction_guard_g.getCallHistory().getSize(), expectedGuardSize);
    for (FwSizeType i = 0; i < expectedGuardSize; i++) {
        ASSERT_EQ(this->m_junction_guard_g.getCallHistory().getItemAt(i),
                  Junction_Junction::Signal::__FPRIME_AC_INITIAL_TRANSITION);
        ASSERT_EQ(this->m_smInitialJunction_guard_g.getCallHistory().getItemAt(i),
                  SmInitial_Junction::Signal::__FPRIME_AC_INITIAL_TRANSITION);
    }
}

}  // namespace SmInstanceInitial

}  // namespace FppTest
