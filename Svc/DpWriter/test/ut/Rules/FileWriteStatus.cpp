// ======================================================================
// \title  FileWriteStatus.cpp
// \author Rob Bocchino
// \brief  FileWriteStatus class implementation
//
// \copyright
// Copyright (C) 2024 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged. Any commercial use must be negotiated with the Office
// of Technology Transfer at the California Institute of Technology.
// ======================================================================

#include "Svc/DpWriter/test/ut/Rules/FileWriteStatus.hpp"
#include "Svc/DpWriter/test/ut/Rules/Testers.hpp"

namespace Svc {

// ----------------------------------------------------------------------
// Rule definitions
// ----------------------------------------------------------------------

bool TestState ::precondition__FileWriteStatus__OK() const {
    bool result = (this->abstractState.fileWriteStatus != Os::File::Status::OP_OK);
    return result;
}

void TestState ::action__FileWriteStatus__OK() {
    this->abstractState.fileWriteStatus = Os::File::Status::OP_OK;
}

bool TestState ::precondition__FileWriteStatus__Error() const {
    bool result = (this->abstractState.fileWriteStatus == Os::File::Status::OP_OK);
    return result;
}

void TestState ::action__FileWriteStatus__Error() {
    this->abstractState.fileWriteStatus = DpWriterTester::pickOsFileError();
}

namespace FileWriteStatus {

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void Tester::OK() {
    this->ruleError.apply(this->testState);
    this->ruleOK.apply(this->testState);
}

void Tester::Error() {
    this->ruleError.apply(this->testState);
}

}  // namespace FileWriteStatus

}  // namespace Svc
