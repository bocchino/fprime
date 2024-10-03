// ======================================================================
//
// \title  Basic.hpp
// \author R. Bocchino
// \brief  Test class for basic state machine with a junction (header)
//
// \copyright
// Copyright 2024, by the California Institute of Technology.
// ALL RIGHTS RESERVED. United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef FppTest_State_Basic_HPP
#define FppTest_State_Basic_HPP

#include "FppTest/state_machine/internal/harness/Harness.hpp"
#include "FppTest/state_machine/internal/junction/BasicStateMachineAc.hpp"

namespace FppTest {

namespace SmJunction {

//! A basic state machine with a junction
class Basic final : public BasicStateMachineBase {
  public:
    //! The history size
    static constexpr FwSizeType historySize = 10;

  public:
    //! Constructor
    Basic();

  private:
    //! Implementation of action a
    void action_a(Signal signal  //!< The signal
                  ) final;

    //! Implementation of action b
    void action_b(Signal signal  //!< The signal
                  ) final;

    //! Implementation of guard g
    bool guard_g(Signal signal  //!< The signal
                 ) const final;

  public:
    //! Run the test with the true guard
    void testTrue();

    //! Run the test with the false guard
    void testFalse();

  private:
    //! The history associated with action a
    SmHarness::History<Signal, historySize> m_action_a_history;

    //! The history associated with action b
    SmHarness::History<Signal, historySize> m_action_b_history;

    //! The guard g
    SmHarness::NoArgGuard<Signal, historySize> m_guard_g;
};

}  // namespace SmJunction

}  // end namespace FppTest

#endif
