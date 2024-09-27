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

#include "FppTest/state_machine/internal/harness/Harness.hpp"
#include "FppTest/state_machine/internal/initial/JunctionStateMachineAc.hpp"

namespace FppTest {

namespace SmInitial {

//! Junction state machine
class Junction final : public JunctionStateMachineBase {
  public:
    static constexpr FwSizeType historySize = 10;

  public:
    //! Constructor
    Junction();

  private:
    //! Implementation of action a
    void action_a(Signal signal  //!< The signal
                  ) final;

    //! Implementation of guard g
    bool guard_g(Signal signal  //!< The signal
    ) const;

  public:
    //! Test with true guard
    void testTrue();

    //! Test with false guard
    void testFalse();

  private:
    //! Helper function for checking actions and guards
    void checkActionsAndGuards(FwSizeType expectedActionSize,  //!< The expected action size
                               FwSizeType expectedGuardSize    //!< The expected guard size
    );

  private:
    //! The history associated with action a
    SmHarness::NoValueHistory<Signal, historySize> m_action_a_history;

    //! The guard g
    SmHarness::NoArgGuard<Signal, historySize> m_guard_g;
};

}  // namespace SmInitial

}  // end namespace FppTest

#endif
