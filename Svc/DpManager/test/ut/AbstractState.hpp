// ======================================================================
// \title  AbstractState.hpp
// \author bocchino
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

  public:
    // ----------------------------------------------------------------------
    // Constructors
    // ----------------------------------------------------------------------

    //! Construct an AbstractState object
    AbstractState(void) : bufferGetStatus(BufferGetStatus::VALID) {}

  public:
    // ----------------------------------------------------------------------
    // State variables
    // ----------------------------------------------------------------------

    //! The buffer get status
    BufferGetStatus bufferGetStatus;
};

}  // namespace Svc

#endif
