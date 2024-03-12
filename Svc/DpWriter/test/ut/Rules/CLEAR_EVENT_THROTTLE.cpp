// ======================================================================
// \title  CLEAR_EVENT_THROTTLE.cpp
// \author Rob Bocchino
// \brief  CLEAR_EVENT_THROTTLE class implementation
//
// \copyright
// Copyright (C) 2024 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged. Any commercial use must be negotiated with the Office
// of Technology Transfer at the California Institute of Technology.
// ======================================================================

#include "STest/Pick/Pick.hpp"
#include "Svc/DpWriter/test/ut/Rules/CLEAR_EVENT_THROTTLE.hpp"
#include "Svc/DpWriter/test/ut/Rules/Testers.hpp"

namespace Svc {

// ----------------------------------------------------------------------
// Rule definitions
// ----------------------------------------------------------------------

bool TestState ::precondition__CLEAR_EVENT_THROTTLE__OK() const {
    return true;
}

void TestState ::action__CLEAR_EVENT_THROTTLE__OK() {
#if 0
    // Clear history
    this->clearHistory();
    // Invoke schedIn port
    const U32 context = STest::Pick::any();
    this->invoke_to_schedIn(0, context);
    this->component.doDispatch();
    // Check telemetry
    this->checkTelemetry();
#endif
}

namespace CLEAR_EVENT_THROTTLE {

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void Tester ::OK() {
#if 0
    this->ruleOK.apply(this->testState);
#endif
}

}  // namespace CLEAR_EVENT_THROTTLE

}  // namespace Svc
