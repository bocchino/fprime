// ======================================================================
//
// \title  StateToState.hpp
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

#include "FppTest/state_machine/internal/state/StateToState.hpp"
#include "STest/STest/Pick/Pick.hpp"

namespace FppTest {

namespace SmState {

StateToState::StateToState() : StateToStateStateMachineBase() {}

void StateToState::action_exitS1(Signal signal) {
    // TODO
}

void StateToState::action_exitS2(Signal signal) {
    // TODO
}

void StateToState::action_exitS3(Signal signal) {
    // TODO
}

void StateToState::action_a(Signal signal) {
    // TODO
}

void StateToState::action_enterS1(Signal signal) {
    // TODO
}

void StateToState::action_enterS2(Signal signal) {
    // TODO
}

void StateToState::action_enterS3(Signal signal) {
    // TODO
}

void StateToState::action_enterS4(Signal signal) {
    // TODO
}

void StateToState::action_enterS5(Signal signal) {
    // TODO
}

void StateToState::test() {
    const FwEnumStoreType id = SmHarness::Pick::stateMachineId();
    this->init(id);
    ASSERT_EQ(this->m_id, id);
    // TODO
}

}  // namespace SmState

}  // end namespace FppTest
