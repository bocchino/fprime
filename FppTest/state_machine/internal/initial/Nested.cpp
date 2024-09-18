// ======================================================================
//
// \title  Nested.hpp
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

#include "FppTest/state_machine/internal/initial/Nested.hpp"
#include "STest/STest/Pick/Pick.hpp"

namespace FppTest {

Nested::Nested() : NestedStateMachineBase(), m_action_a_history() {}

void Nested::action_a() {
    this->m_action_a_history.pushElement();
}

void Nested::test() {
    this->m_action_a_history.clear();
    const FwEnumStoreType id = InternalSmUtil::pickStateMachineId();
    this->init(id);
    ASSERT_EQ(this->m_id, id);
    ASSERT_EQ(this->m_state, State::S_T);
    ASSERT_EQ(this->m_action_a_history.getSize(), 6);
}

}  // end namespace FppTest
