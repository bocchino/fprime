// ======================================================================
// \title  ProductSendIn.cpp
// \author Rob Bocchino
// \brief  ProductSendIn class implementation
//
// \copyright
// Copyright (C) 2023 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged. Any commercial use must be negotiated with the Office
// of Technology Transfer at the California Institute of Technology.
// ======================================================================

#include "STest/Pick/Pick.hpp"
#include "Svc/DpManager/test/ut/Rules/ProductSendIn.hpp"
#include "Svc/DpManager/test/ut/Rules/Testers.hpp"

namespace Svc {

// ----------------------------------------------------------------------
// Rule definitions
// ----------------------------------------------------------------------

bool TestState ::precondition__ProductSendIn__OK() const {
    return true;
}

void TestState ::action__ProductSendIn__OK() {
    // TODO
}

namespace ProductSendIn {

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void Tester ::OK() {
    this->ruleOK.apply(this->testState);
}

}  // namespace ProductSendIn

}  // namespace Svc
