// ======================================================================
//
// \title  SignalValueHistory.hpp
// \author R. Bocchino
// \brief  Template for a history of calls with signals and values
//
// \copyright
// Copyright 2024, by the California Institute of Technology.
// ALL RIGHTS RESERVED. United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef FppTest_SmHarness_SignalValueHistory_HPP
#define FppTest_SmHarness_SignalValueHistory_HPP

#include <FpConfig.hpp>
#include <array>

#include "FppTest/state_machine/internal/harness/SignalHistory.hpp"
#include "Fw/Types/Assert.hpp"

namespace FppTest {

namespace SmHarness {

//! A history with signals and values
template <typename Signal, typename T, FwSizeType size>
class SignalValueHistory {
  public:
    //! The signal history type
    using SignalHistory = SmHarness::SignalHistory<Signal, size>;

    //! Constructor
    SignalValueHistory() : m_signals(), m_values() {}

    //! Clear the history
    void clear() {
        this->m_size = 0;
        this->m_signals.clear();
    }

    //! Check two histories for equality
    bool operator==(SignalValueHistory& history  //!< The other history
    ) const {
        bool result = (this->m_size == history.m_size);
        if (result) {
            FW_ASSERT(this->m_size < size);
            for (FwSizeType i = 0; i < this->m_size; ++i) {
                if (this->m_values[i] != history.m_values[i]) {
                    result = false;
                    break;
                }
            }
        }
        return result;
    }

    //! Push an item on the history
    void push(Signal signal,  //!< The signal
              const T& value  //!< The value
    ) {
        FW_ASSERT(this->m_size < size, static_cast<FwAssertArgType>(this->m_size));
        this->m_signals.push(signal);
        this->m_values[this->m_size] = value;
        this->m_size++;
    }

    //! Get the history size
    FwSizeType getSize() const { return this->m_size; }

    //! Get the signal history
    const SignalHistory& getSignals() const { return this->m_signals; }

    //! Get the value at an index
    const T& getValueAt(FwIndexType index  //!< The index
    ) const {
        FW_ASSERT(index < this->m_size);
        return this->m_values[index];
    }

  private:
    //! The size of the history
    FwSizeType m_size = 0;

    //! The signal history
    SignalHistory m_signals;

    //! The values in the history
    std::array<T, size> m_values = {};
};

}  // namespace SmHarness

}  // end namespace FppTest

#endif
