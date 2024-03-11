// ======================================================================
// \title  BufferSendIn.cpp
// \author Rob Bocchino
// \brief  BufferSendIn class implementation
//
// \copyright
// Copyright (C) 2024 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged. Any commercial use must be negotiated with the Office
// of Technology Transfer at the California Institute of Technology.
// ======================================================================

#include "Os/Stub/test/File.hpp"
#include "STest/Pick/Pick.hpp"
#include "Svc/DpWriter/test/ut/Rules/BufferSendIn.hpp"
#include "Svc/DpWriter/test/ut/Rules/Testers.hpp"

namespace Svc {

// ----------------------------------------------------------------------
// Rule definitions
// ----------------------------------------------------------------------

bool TestState ::precondition__BufferSendIn__OK() const {
    bool result = true;
    result &= (Os::Stub::File::Test::StaticData::data.openStatus == Os::File::Status::OP_OK);
    result &= (Os::Stub::File::Test::StaticData::data.writeStatus == Os::File::Status::OP_OK);
    return result;
}

void TestState ::action__BufferSendIn__OK() {
    // Clear history
    this->clearHistory();
    // Reset the file pointer
    Os::Stub::File::Test::StaticData::data.pointer = 0;
    // Update NumBuffersReceived
    this->abstractState.NumBuffersReceived.value++;
    // Construct a random buffer
    Fw::Buffer buffer = this->abstractState.getDpBuffer();
    // Send the buffer
    this->invoke_to_bufferSendIn(0, buffer);
    this->component.doDispatch();
    // Deserialize the container header
    Fw::DpContainer container;
    container.setBuffer(buffer);
    const Fw::SerializeStatus status = container.deserializeHeader();
    ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
    // Check events
    ASSERT_EVENTS_SIZE(1);
    this->printTextLogHistory(stdout);
    ASSERT_EVENTS_FileWritten_SIZE(1);
    Fw::FileNameString fileName;
    this->constructDpFileName(container.getId(), container.getTimeTag(), fileName);
    ASSERT_EVENTS_FileWritten(0, buffer.getSize(), fileName.toChar());
    // Check output ports
    // TODO
    // Check file write
    // TODO
    // Update NumBytesWritten
    this->abstractState.NumBytesWritten.value += buffer.getSize();
    // Update NumSuccessfulWrites
    this->abstractState.NumSuccessfulWrites.value++;
}

namespace BufferSendIn {

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void Tester ::OK() {
    this->ruleOK.apply(this->testState);
}

}  // namespace BufferSendIn

}  // namespace Svc
