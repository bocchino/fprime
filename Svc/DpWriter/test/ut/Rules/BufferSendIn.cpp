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
    // TODO
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
