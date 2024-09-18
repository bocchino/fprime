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
#include <limits>

#include "FppTest/state_machine/internal/initial/Basic.hpp"
#include "STest/STest/Pick/Pick.hpp"

namespace FppTest {

Basic::Basic() : BasicStateMachineBase(), m_action_a_history() {}

void Basic::action_a() {
    this->m_action_a_history.pushElement();
}

void Basic::test() {
    this->m_action_a_history.clear();
    const U32 upper = FW_MIN(
        std::numeric_limits<FwEnumStoreType>::max(),
        std::numeric_limits<U32>::max()
    );
    const U32 id = STest::Pick::lowerUpper(0, upper);
    this->init(static_cast<FwEnumStoreType>(id));
    ASSERT_EQ(this->m_id, id);
    ASSERT_EQ(this->m_state, State::S);
    ASSERT_EQ(this->m_action_a_history.getSize(), 3);
}

}  // end namespace FppTest
