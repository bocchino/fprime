// ======================================================================
// \title  FileOpenStatus.cpp
// \author Rob Bocchino
// \brief  FileOpenStatus class implementation
//
// \copyright
// Copyright (C) 2024 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged. Any commercial use must be negotiated with the Office
// of Technology Transfer at the California Institute of Technology.
// ======================================================================

#include "Svc/DpWriter/test/ut/Rules/FileOpenStatus.hpp"
#include "Svc/DpWriter/test/ut/Rules/Testers.hpp"

namespace Svc {

// ----------------------------------------------------------------------
// Rule definitions
// ----------------------------------------------------------------------

bool TestState ::precondition__FileOpenStatus__OK() const {
    bool result = (this->abstractState.fileOpenStatus != Os::File::Status::OP_OK);
    return result;
}

void TestState ::action__FileOpenStatus__OK() {
    this->abstractState.fileOpenStatus = Os::File::Status::OP_OK;
}

bool TestState ::precondition__FileOpenStatus__Error() const {
    bool result = (this->abstractState.fileOpenStatus == Os::File::Status::OP_OK);
    return result;
}

void TestState ::action__FileOpenStatus__Error() {
    this->abstractState.fileOpenStatus = DpWriterTester::pickOsFileError();
}

namespace FileOpenStatus {

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

}  // namespace FileOpenStatus

}  // namespace Svc
