// ======================================================================
//
// \title  Junction.hpp
// \author R. Bocchino
// \brief  Test class for basic state machine (implementation)
//
// \copyright
// Copyright 2024, by the California Institute of Technology.
// ALL RIGHTS RESERVED. United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include <gtest/gtest.h>
#include <limits>

#include "FppTest/state_machine/internal/initial/Junction.hpp"
#include "STest/STest/Pick/Pick.hpp"

namespace FppTest {

namespace SmInitial {

Junction::Junction() : JunctionStateMachineBase(), m_action_a_history(), m_guard_g() {}

void Junction::action_a(Signal signal) {
    this->m_action_a_history.push(signal);
}

bool Junction::guard_g(Signal signal) const {
    return m_guard_g.call(signal);
}

void Junction::testFalse() {
    this->m_action_a_history.clear();
    this->m_guard_g.reset();
    const FwEnumStoreType id = InternalSmUtil::pickStateMachineId();
    this->init(id);
    ASSERT_EQ(this->m_id, id);
    ASSERT_EQ(this->m_state, State::T);
    const FwSizeType expectedActionSize = 5;
    const FwSizeType expectedGuardSize = 1;
    this->checkActionsAndGuards(expectedActionSize, expectedGuardSize);
}

void Junction::testTrue() {
    this->m_action_a_history.clear();
    this->m_guard_g.reset();
    this->m_guard_g.setReturnValue(true);
    const FwEnumStoreType id = InternalSmUtil::pickStateMachineId();
    this->init(id);
    ASSERT_EQ(this->m_id, id);
    ASSERT_EQ(this->m_state, State::S);
    const FwSizeType expectedActionSize = 3;
    const FwSizeType expectedGuardSize = 1;
    this->checkActionsAndGuards(expectedActionSize, expectedGuardSize);
}

void Junction::checkActionsAndGuards(FwSizeType expectedActionSize, FwSizeType expectedGuardSize) {
    for (FwSizeType i = 0; i < expectedActionSize; i++) {
        ASSERT_EQ(this->m_action_a_history.getSignalAt(i), Signal::__FPRIME_AC_INITIAL_TRANSITION);
    }
    ASSERT_EQ(this->m_action_a_history.getSize(), expectedActionSize);
    for (FwSizeType i = 0; i < expectedGuardSize; i++) {
        ASSERT_EQ(this->m_guard_g.getCallHistory().getSignalAt(i), Signal::__FPRIME_AC_INITIAL_TRANSITION);
    }
    ASSERT_EQ(this->m_guard_g.getCallHistory().getSize(), expectedGuardSize);
}

}  // namespace SmInitial

}  // end namespace FppTest
