// ======================================================================
// \title  Basic.cpp
// \author bocchino
// \brief  cpp file for Basic component implementation class
// ======================================================================

#include "FppTest/state_machine/internal_instance/initial/Basic.hpp"

namespace FppTest {

namespace SmInstanceInitial {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

Basic ::Basic(const char* const compName) : BasicComponentBase(compName) {}

Basic ::~Basic() {}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void Basic ::FppTest_SmInitial_Basic_action_a(SmId smId, FppTest_SmInitial_Basic::Signal signal) {
    // TODO
}

void Basic ::FppTest_SmInstanceInitial_Basic_Basic_action_a(SmId smId,
                                                            FppTest_SmInstanceInitial_Basic_Basic::Signal signal) {
    // TODO
}

}  // namespace SmInstanceInitial

}  // namespace FppTest
