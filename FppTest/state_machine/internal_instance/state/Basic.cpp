// ======================================================================
// \title  Basic.cpp
// \author bocchino
// \brief  cpp file for Basic component implementation class
// ======================================================================

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/Basic.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

Basic ::Basic(const char* const compName)
    : BasicComponentBase(compName), m_basic_action_a_history(), m_smStateBasic_action_a_history() {}

Basic ::~Basic() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void Basic ::FppTest_SmInstanceState_Basic_Basic_action_a(SmId smId,
                                                          FppTest_SmInstanceState_Basic_Basic::Signal signal) {
    ASSERT_EQ(smId, SmId::basic);
    this->m_basic_action_a_history.push(signal);
}

void Basic ::FppTest_SmState_Basic_action_a(SmId smId, FppTest_SmState_Basic::Signal signal) {
    ASSERT_EQ(smId, SmId::smStateBasic);
    this->m_smStateBasic_action_a_history.push(signal);
}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void Basic::test() {
   // TODO
}

}  // namespace SmInstanceState

}  // namespace FppTest
