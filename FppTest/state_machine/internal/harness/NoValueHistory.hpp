// ======================================================================
//
// \title  ValueHistory.hpp
// \author R. Bocchino
// \brief  Header for a history of calls with no values
//
// \copyright
// Copyright 2024, by the California Institute of Technology.
// ALL RIGHTS RESERVED. United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef FppTest_NoValueHistory_HPP
#define FppTest_NoValueHistory_HPP

#include <FpConfig.hpp>

namespace FppTest {

//! A history of calls with no values
class NoValueHistory {
  public:
    //! Clear the history
    void clear() { this->m_size = 0; }

    //! Check two histories for equality
    bool operator==(NoValueHistory& history  //!< The other history
    ) const {
        return (this->m_size == history.m_size);
    }

    //! Push an element on the history
    void pushElement() { this->m_size++; }

    //! Get the history size
    FwSizeType getSize() const { return this->m_size; }

  private:
    //! The history size
    FwSizeType m_size = 0;
};

}  // end namespace FppTest

#endif
