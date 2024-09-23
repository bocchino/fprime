// ======================================================================
//
// \title  Basic.hpp
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

#include "FppTest/state_machine/internal/state/Basic.hpp"
#include "STest/STest/Pick/Pick.hpp"

namespace FppTest {

namespace State {

Basic::Basic() : BasicStateMachineBase(), m_action_a_history() {}

void Basic::action_a(Signal signal) {
    this->m_action_a_history.push(signal);
}

void Basic::test() {
    this->m_action_a_history.clear();
    const FwEnumStoreType id = InternalSmUtil::pickStateMachineId();
    this->init(id);
    ASSERT_EQ(this->m_id, id);
    ASSERT_EQ(this->m_state, State::S);
    ASSERT_EQ(this->m_action_a_history.getSize(), 0);
}

}  // namespace State

}  // end namespace FppTest
