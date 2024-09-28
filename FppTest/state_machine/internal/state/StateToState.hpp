// ======================================================================
//
// \title  StateToState.hpp
// \author R. Bocchino
// \brief  Test class for basic state machine (header)
//
// \copyright
// Copyright 2024, by the California Institute of Technology.
// ALL RIGHTS RESERVED. United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef FppTest_State_StateToState_HPP
#define FppTest_State_StateToState_HPP

#include "FppTest/state_machine/internal/harness/Harness.hpp"
#include "FppTest/state_machine/internal/state/StateToStateStateMachineAc.hpp"

namespace FppTest {

namespace SmState {

//! A basic state machine
class StateToState final : public StateToStateStateMachineBase {
  public:
    //! The history size
    static constexpr FwSizeType historySize = 10;

  public:
    //! Constructor
    StateToState();

  private:
    //! Exit S1
    void action_exitS1(Signal signal  //!< The signal
                       ) final;

    //! Exit S2
    void action_exitS2(Signal signal  //!< The signal
                       ) final;

    //! Exit S3
    void action_exitS3(Signal signal  //!< The signal
                       ) final;

    //! Action a
    void action_a(Signal signal  //!< The signal
                  ) final;

    //! Enter S1
    void action_enterS1(Signal signal  //!< The signal
                        ) final;

    //! Enter S2
    void action_enterS2(Signal signal  //!< The signal
                        ) final;

    //! Enter S3
    void action_enterS3(Signal signal  //!< The signal
                        ) final;

    //! Enter S4
    void action_enterS4(Signal signal  //!< The signal
                        ) final;

    //! Enter S5
    void action_enterS5(Signal signal  //!< The signal
                        ) final;

  public:
    //! Run the test
    void test();

  private:
    // TODO
};

}  // namespace SmState

}  // end namespace FppTest

#endif
