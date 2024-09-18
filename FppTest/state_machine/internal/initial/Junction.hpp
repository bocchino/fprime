// ======================================================================
//
// \title  Junction.hpp
// \author R. Bocchino
// \brief  Test class for junction state machine (header)
//
// \copyright
// Copyright 2024, by the California Institute of Technology.
// ALL RIGHTS RESERVED. United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef FppTest_Junction_HPP
#define FppTest_Junction_HPP

#include "FppTest/state_machine/internal/initial/JunctionStateMachineAc.hpp"
#include "FppTest/state_machine/internal/harness/InternalSmHarness.hpp"

namespace FppTest {

//! Junction state machine
class Junction final : public JunctionStateMachineBase {
  public:
    //! Constructor
    Junction();

  private:
    //! Implementation of action a
    void action_a() final;

    //! Implementation of guard g
    bool guard_g();

  public:
    //! Test with true guard
    void testTrue();

    //! Test with false guard
    void testFalse();

  private:
    //! The history associated with action a
    NoValueHistory m_action_a_history;

    //! The guard g
    NoArgSmGuard m_guard_g;

};

}  // end namespace FppTest

#endif
