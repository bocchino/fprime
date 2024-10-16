// ======================================================================
// \title  Basic.cpp
// \author bocchino
// \brief  cpp file for Basic component implementation class
// ======================================================================

#include "FppTest/state_machine/internal_instance/state/Basic.hpp"

namespace FppTest {

namespace SmInstanceState {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

Basic ::Basic(const char* const compName) : BasicComponentBase(compName) {}

Basic ::~Basic() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void Basic ::FppTest_SmInstanceState_Basic_Basic_action_a(SmId smId,
                                                          FppTest_SmInstanceState_Basic_Basic::Signal signal) {
    // TODO
}

void Basic ::FppTest_SmState_Basic_action_a(SmId smId, FppTest_SmState_Basic::Signal signal) {
    // TODO
}

}  // namespace SmInstanceState

}  // namespace FppTest
