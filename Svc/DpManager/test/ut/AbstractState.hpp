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

    //! A model of an on-change telemetry channel
    template <typename T>
    class OnChangeChannel {
      public:
        OnChangeChannel(T value) : isValid(false), value(value) {}
        bool valueChanged(T newValue) const { return (!this->isValid) || (newValue != this->value); }
        void update(T newValue) {
            this->value = newValue;
            this->isValid = true;
        }

      PRIVATE:
        bool isValid;
        T value;
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
