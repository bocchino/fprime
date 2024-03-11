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
#include "Os/File.hpp"
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
    AbstractState()
        : NumBuffersReceived(0), NumBytesWritten(0), NumFailedWrites(0), NumSuccessfulWrites(0), NumErrors(0) {}

  public:
    // ----------------------------------------------------------------------
    // Public state variables
    // ----------------------------------------------------------------------

    //! The number of buffers received
    TestUtils::OnChangeChannel<U32> NumBuffersReceived;

    //! The number of bytes written
    TestUtils::OnChangeChannel<U64> NumBytesWritten;

    //! The number of failed writes
    TestUtils::OnChangeChannel<U32> NumFailedWrites;

    //! The number of successful writes
    TestUtils::OnChangeChannel<U32> NumSuccessfulWrites;

    //! The number of errors
    TestUtils::OnChangeChannel<U32> NumErrors;

    //! The number of buffer invalid events since the last throttle clear
    FwSizeType invalidBufferEventCount = 0;

    //! The number of buffer too small events since the last throttle clear
    FwSizeType bufferTooSmallEventCount = 0;

    //! The number of file open error events since the last throttle clear
    FwSizeType fileOpenErrorEventCount = 0;

    //! The status returned by Os::File::open in the test harness
    Os::File::Status fileOpenStatus = Os::File::OP_OK;

    //! The number of file write error events since the last throttle clear
    FwSizeType fileWriteErrorEventCount = 0;

    //! The status returned by Os::File::write in the test harness
    Os::File::Status fileWriteStatus = Os::File::OP_OK;

    //! The number of invalid packet descriptor events since the last throttle clear
    FwSizeType invalidPacketDescriptorEventCount = 0;
};

}  // namespace Svc

#endif
