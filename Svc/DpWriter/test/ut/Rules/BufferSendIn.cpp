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

#include <string>

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
    // Clear the history
    this->clearHistory();
    // Reset the saved proc types
    // These are updated in the from_procBufferSendOut handler
    this->abstractState.procTypes = 0;
    // Reset the file pointer in the stub file implementation
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
    // Check processing types
    FwIndexType expectedNumProcTypes = 0;
    const Fw::DpCfg::ProcType::SerialType procTypes = container.getProcTypes();
    for (FwIndexType i = 0; i < Fw::DpCfg::ProcType::NUM_CONSTANTS; i++) {
        if (procTypes & (1 << i)) {
            ++expectedNumProcTypes;
        }
    }
    ASSERT_from_procBufferSendOut_SIZE(expectedNumProcTypes);
    ASSERT_EQ(container.getProcTypes(), this->abstractState.procTypes);
    // Check DP notification
    ASSERT_from_dpWrittenOut_SIZE(1);
    ASSERT_from_dpWrittenOut(0, fileName, container.getPriority(), buffer.getSize());
    // Check deallocation
    ASSERT_from_deallocBufferSendOut_SIZE(1);
    ASSERT_from_deallocBufferSendOut(0, buffer);
    // Check file write
    ASSERT_EQ(buffer.getSize(), Os::Stub::File::Test::StaticData::data.pointer);
    ASSERT_EQ(0, ::memcmp(buffer.getData(), Os::Stub::File::Test::StaticData::data.writeResult, buffer.getSize()));
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
