// ======================================================================
// \title  AbstractState.hpp
// \author Rob Bocchino
// \brief  Header file for abstract state
//
// \copyright
// Copyright (C) 2023 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged. Any commercial use must be negotiated with the Office
// of Technology Transfer at the California Institute of Technology.
// ======================================================================

#ifndef Svc_AbstractState_HPP
#define Svc_AbstractState_HPP

#include <cstring>

#include "Fw/Types/Assert.hpp"
#include "Svc/DpManager/DpManager.hpp"

namespace Svc {

class AbstractState {
  public:
    // ----------------------------------------------------------------------
    // Types
    // ----------------------------------------------------------------------

    //! The type of the buffer get status
    enum class BufferGetStatus {
        //! Valid
        VALID,
        //! Invalid
        INVALID
    };

    //! Change status
    enum class ChangeStatus { CHANGED, NOT_CHANGED };

    //! An optional value
    template <typename T>
    class Option {
      private:
        enum class State { VALUE, NO_VALUE };

      public:
        Option<T>(T value) : state(State::VALUE), value(value) {}
        Option<T>() : state(State::NO_VALUE) { ::memset(&this->value, 0, sizeof this->value); }

      public:
        static Option<T> some(T value) { return Option(value); }
        static constexpr Option<T> none() { return Option(); }

      public:
        bool hasValue() const { return this->state == State::VALUE; }
        void set(T value) {
            this->state = State::VALUE;
            this->value = value;
        }
        T get() const {
            FW_ASSERT(this->hasValue());
            return this->value;
        }
        T getOrElse(T value) const {
            T result = value;
            if (this->hasValue()) {
                result = this->value;
            }
            return result;
        }

      private:
        State state;
        T value;
    };

    //! A model of an on-change telemetry channel
    template <typename T>
    class OnChangeChannel {
      public:
        OnChangeChannel(T value) : value(value) {}
        ChangeStatus updatePrev() {
            const auto status = ((!this->prev.hasValue()) || (this->value != this->prev.get()))
                                    ? ChangeStatus::CHANGED
                                    : ChangeStatus::NOT_CHANGED;
            this->prev.set(this->value);
            return status;
        }

      public:
        T value;

      private:
        Option<T> prev;
    };

  public:
    // ----------------------------------------------------------------------
    // Constructors
    // ----------------------------------------------------------------------

    //! Construct an AbstractState object
    AbstractState(void)
        : bufferGetStatus(BufferGetStatus::VALID),
          numSuccessfulAllocations(0),
          numFailedAllocations(0),
          numDataProducts(0),
          numBytes(0) {}

  public:
    // ----------------------------------------------------------------------
    // State variables
    // ----------------------------------------------------------------------

    //! The buffer get status
    BufferGetStatus bufferGetStatus;

    //! The number of successful buffer allocations
    OnChangeChannel<U32> numSuccessfulAllocations;

    //! The number of failed buffer allocations
    OnChangeChannel<U32> numFailedAllocations;

    //! The number of data products handled
    OnChangeChannel<U32> numDataProducts;

    //! The number of bytes handled
    OnChangeChannel<U32> numBytes;
};

}  // namespace Svc

#endif
