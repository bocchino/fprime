// ======================================================================
// \title  AbstractState.hpp
// \author Rob Bocchino
// \brief  Header file for abstract state
//
// \copyright
// Copyright (C) 2024 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged. Any commercial use must be negotiated with the Office
// of Technology Transfer at the California Institute of Technology.
// ======================================================================

#ifndef Svc_AbstractState_HPP
#define Svc_AbstractState_HPP

#include <cstring>

#include "Fw/Types/Assert.hpp"
#include "STest/Pick/Pick.hpp"
#include "Svc/DpWriter/DpWriter.hpp"
#include "TestUtils/OnChangeChannel.hpp"
#include "TestUtils/Option.hpp"

namespace Svc {

class AbstractState {
  public:
    // ----------------------------------------------------------------------
    // Constants
    // ----------------------------------------------------------------------

    //! The maximum data size
    static constexpr FwSizeType MAX_DATA_SIZE = 1024;

    //! The maximum buffer size
    static constexpr FwSizeType MAX_BUFFER_SIZE = Fw::DpContainer::getPacketSizeForDataSize(MAX_DATA_SIZE);

  public:
    // ----------------------------------------------------------------------
    // Constructors
    // ----------------------------------------------------------------------

    //! Construct an AbstractState object
    AbstractState() {}

  public:
    // ----------------------------------------------------------------------
    // Public state variables
    // ----------------------------------------------------------------------

    //! The number of buffers received
    TestUtils::OnChangeChannel<U32> NumBuffersReceived = 0;

};

}  // namespace Svc

#endif
