// ======================================================================
//
// \title  SmGuard.hpp
// \author R. Bocchino
// \brief  Template for test implementation of a state machine guard
//
// \copyright
// Copyright 2024, by the California Institute of Technology.
// ALL RIGHTS RESERVED. United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef FppTest_SmGuard_HPP
#define FppTest_SmGuard_HPP

#include <FpConfig.hpp>
#include "FppTest/state_machine/internal/harness/History.hpp"

namespace FppTest {

//! Test implementation of a state machine guard with a value argument
template <typename T, FwSizeType size>
class SmGuard {
  public:
    //! Constructor
    SmGuard(T initialValue  //!< The initial value
            )
        : history(initialValue) {}

  private:
    //! The return value
    bool m_returnValue = false;

    //! The call history
    History m_callHistory;
};

}  // end namespace FppTest

#endif
