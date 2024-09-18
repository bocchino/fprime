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

Junction::Junction() : JunctionStateMachineBase(), m_action_a_history(), m_guard_g() {}

void Junction::action_a() {
    this->m_action_a_history.pushElement();
}

bool Junction::guard_g() {
    return m_guard_g.call();
}

void Junction::testFalse() {
    this->m_action_a_history.clear();
    this->m_guard_g.reset();
    const FwEnumStoreType id = InternalSmUtil::pickStateMachineId();
    this->init(id);
    ASSERT_EQ(this->m_id, id);
    ASSERT_EQ(this->m_state, State::T);
    ASSERT_EQ(this->m_action_a_history.getSize(), 5);
    ASSERT_EQ(this->m_guard_g.getCallHistory().getSize(), 1);
}

void Junction::testTrue() {
    this->m_action_a_history.clear();
    this->m_guard_g.reset();
    this->m_guard_g.setReturnValue(true);
    const FwEnumStoreType id = InternalSmUtil::pickStateMachineId();
    this->init(id);
    ASSERT_EQ(this->m_id, id);
    ASSERT_EQ(this->m_state, State::S);
    ASSERT_EQ(this->m_action_a_history.getSize(), 3);
    ASSERT_EQ(this->m_guard_g.getCallHistory().getSize(), 1);
}

}  // end namespace FppTest
