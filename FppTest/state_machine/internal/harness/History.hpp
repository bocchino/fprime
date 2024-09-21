// ======================================================================
//
// \title  History.hpp
// \author R. Bocchino
// \brief  Template for a history of calls with values
//
// \copyright
// Copyright 2024, by the California Institute of Technology.
// ALL RIGHTS RESERVED. United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef FppTest_History_HPP
#define FppTest_History_HPP

#include <array>
#include <FpConfig.hpp>

#include "FppTest/state_machine/internal/harness/NoValueHistory.hpp"
#include "Fw/Types/Assert.hpp"

namespace FppTest {

//! A history with values
template <typename Signal, typename T, FwSizeType size>
class History {
  public:
    //! The signal history type
    using SignalHistory = NoValueHistory<Signal, size>;

    //! Constructor
    History() : m_signals(), m_values() {}

    //! Clear the history
    void clear() { 
      this->m_size = 0; 
      this->m_signals.clear();
    }

    //! Check two histories for equality
    bool operator==(History& history  //!< The other history
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

    //! Push a value on the history
    void pushValue(Signal signal, //!< The signal
                   const T& value  //!< The value
    ) {
        FW_ASSERT(this->m_size < size, static_cast<FwAssertArgType>(this->m_size));
        this->m_signals.pushElement(signal);
        this->m_values[this->m_size] = value;
        this->m_size++;
    }

    //! Get the history size
    FwSizeType getSize() const { return this->m_size; }

    //! Get the signal history
    const SignalHistory& getSignals() const {
        return this->m_signals;
    }

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

}  // end namespace FppTest

#endif
