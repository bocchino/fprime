// ======================================================================
// \title  SchedIn.cpp
// \author Rob Bocchino
// \brief  SchedIn class implementation
//
// \copyright
// Copyright (C) 2023 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged. Any commercial use must be negotiated with the Office
// of Technology Transfer at the California Institute of Technology.
// ======================================================================

#include "Svc/DpManager/test/ut/Rules/SchedIn.hpp"
#include "Svc/DpManager/test/ut/Rules/Testers.hpp"

namespace Svc {

// ----------------------------------------------------------------------
// Rule definitions
// ----------------------------------------------------------------------

bool TestState ::precondition__SchedIn__OK() const {
    return true;
}

void TestState ::action__SchedIn__OK() {
    // TODO
}

namespace SchedIn {

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void Tester ::OK() {
    this->ruleOK.apply(this->testState);
}

}  // namespace SchedIn

}  // namespace Svc
