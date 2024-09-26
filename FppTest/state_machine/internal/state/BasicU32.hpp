// ======================================================================
//
// \title  BasicU32.hpp
// \author R. Bocchino
// \brief  Test class for basic state machine with U32 actions (header)
//
// \copyright
// Copyright 2024, by the California Institute of Technology.
// ALL RIGHTS RESERVED. United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef FppTest_State_BasicU32_HPP
#define FppTest_State_BasicU32_HPP

#include "FppTest/state_machine/internal/harness/InternalSmHarness.hpp"
#include "FppTest/state_machine/internal/state/BasicU32StateMachineAc.hpp"

namespace FppTest {

namespace SmState {

//! A basic state machine with U32 actions
class BasicU32 final : public BasicU32StateMachineBase {
  public:
    //! The history size
    static constexpr FwSizeType historySize = 10;

  public:
    //! Constructor
    BasicU32();

  private:
    //! Implementation of action a
    void action_a(Signal signal  //!< The signal
                  ) final;

    //! Implementation of action b
    void action_b(Signal signal,  //!< The signal
                  U32 value //!< The value
                  ) final;

  public:
    //! Run the test
    void test();

  private:
    //! The history associated with action a
    NoValueHistory<Signal, historySize> m_action_a_history;

    //! The history associated with action b
    History<Signal, U32, historySize> m_action_b_history;
};

}  // namespace SmState

}  // end namespace FppTest

#endif
