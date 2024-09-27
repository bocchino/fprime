// ======================================================================
//
// \title  SignalHistory.hpp
// \author R. Bocchino
// \brief  Header for a history of signals
//
// \copyright
// Copyright 2024, by the California Institute of Technology.
// ALL RIGHTS RESERVED. United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef FppTest_SmHarness_SignalHistory_HPP
#define FppTest_SmHarness_SignalHistory_HPP

#include <FpConfig.hpp>
#include <array>

#include "Fw/Types/Assert.hpp"

namespace FppTest {

namespace SmHarness {

//! A history of calls with no values
template <typename Signal, FwSizeType size>
class SignalHistory {
  public:
    //! Constructor
    SignalHistory() {}

    //! Clear the history
    void clear() { this->m_size = 0; }

    //! Check two histories for equality
    bool operator==(SignalHistory& history  //!< The other history
    ) const {
        bool result = (this->m_size == history.m_size);
        if (result) {
            for (FwSizeType i = 0; i < this->m_size; i++) {
                if (this->m_signals[i] != history.m_signals[i]) {
                    result = false;
                    break;
                }
            }
        }
        return result;
    }

    //! Push an item on the history
    void push(Signal signal  //!< The signal
    ) {
        FW_ASSERT(m_size < size);
        this->m_signals[m_size] = signal;
        this->m_size++;
    }

    //! Get the history size
    FwSizeType getSize() const { return this->m_size; }

    //! Get the signal at an index
    Signal getSignalAt(FwIndexType index  //!< The index
    ) const {
        FW_ASSERT(index < this->m_size);
        return this->m_signals[index];
    }

  private:
    //! The history size
    FwSizeType m_size = 0;

    //! The signals in the history
    std::array<Signal, size> m_signals = {};
};

}  // namespace SmHarness

}  // end namespace FppTest

#endif
