// ======================================================================
//
// \title  NoArgSmGuard.hpp
// \author R. Bocchino
// \brief  Class for test implementation of a state machine guard
//         with no argument value
//
// \copyright
// Copyright 2024, by the California Institute of Technology.
// ALL RIGHTS RESERVED. United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef FppTest_NoArgSmGuard_HPP
#define FppTest_NoArgSmGuard_HPP

#include "FppTest/state_machine/internal/harness/NoValueHistory.hpp"

namespace FppTest {

//! Test implementation of a state machine guard with no argument value
class NoArgSmGuard {
  public:
    //! Constructor
    NoArgSmGuard() : m_callHistory() {}

    //! Reset the guard to the initial state
    void reset() {
        this->m_callHistory.clear();
        this->m_returnValue = false;
    }

    //! Clear the call history but keep the return value
    void clearCallHistory() { this->m_callHistory.clear(); }

    //! Call the guard
    bool call() {
        this->m_callHistory.pushElement();
        return this->m_returnValue;
    }

    //! Set the return value
    void setReturnValue(bool returnValue  //!< The return value
    ) {
        this->m_returnValue = returnValue;
    }

    //! Get the call history
    const NoValueHistory& getCallHistory() const { return this->m_callHistory; }

  private:
    //! The return value
    bool m_returnValue = false;

    //! The call history
    NoValueHistory m_callHistory;
};

}  // end namespace FppTest

#endif