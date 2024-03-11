// ======================================================================
// \title  AbstractState.cpp
// \author Rob Bocchino
// \brief  Implementation file for abstract state
//
// \copyright
// Copyright (C) 2024 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged. Any commercial use must be negotiated with the Office
// of Technology Transfer at the California Institute of Technology.
// ======================================================================

#include <limits>

#include "Fw/Types/Assert.hpp"
#include "STest/Pick/Pick.hpp"
#include "Svc/DpWriter/test/ut/AbstractState.hpp"

namespace Svc {

// ----------------------------------------------------------------------
// Public member functions
// ----------------------------------------------------------------------

//! Get a data product buffer backed by bufferData
//! \return The buffer
Fw::Buffer AbstractState::getDpBuffer() {
    // Generate the ID
    const FwDpIdType id =
        STest::Pick::lowerUpper(std::numeric_limits<FwDpIdType>::min(), std::numeric_limits<FwDpIdType>::max());
    // Get the data size
    const FwSizeType dataSize = this->getDataSize();
    const FwSizeType bufferSize = Fw::DpContainer::getPacketSizeForDataSize(dataSize);
    FW_ASSERT(bufferSize <= MAX_DATA_SIZE, static_cast<FwAssertArgType>(bufferSize),
              static_cast<FwAssertArgType>(MAX_DATA_SIZE));
    // Create the buffer
    Fw::Buffer buffer(this->bufferData, bufferSize);
    // Create the container
    Fw::DpContainer container(id, buffer);
    // Update the processing types
    Fw::DpCfg::ProcType::SerialType procTypes = 0;
    for (FwIndexType i = 0; i < Fw::DpCfg::ProcType::NUM_CONSTANTS; i++) {
      const bool selector = static_cast<bool>(STest::Pick::lowerUpper(0, 1));
      if (selector) {
        procTypes |= (1 << i);
      }
    }
    container.setProcTypes(procTypes);
    // Serialize the header and update the header hash
    container.serializeHeader();
    // Randomize the data
    U8 *const dataPtr = &this->bufferData[Fw::DpContainer::DATA_OFFSET];
    const FwSizeType dataUpperBound = Fw::DpContainer::DATA_OFFSET + dataSize;
    FW_ASSERT(dataUpperBound <= bufferSize, dataUpperBound, bufferSize);
    for (FwSizeType i = 0; i <= dataSize; i++) {
      dataPtr[i] = static_cast<U8>(STest::Pick::any());
    }
    // Update the data hash
    container.updateDataHash();
    // Return the buffer
    return buffer;
}

}  // namespace Svc
