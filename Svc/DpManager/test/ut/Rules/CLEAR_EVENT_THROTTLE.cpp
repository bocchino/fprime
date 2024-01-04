// ======================================================================
// \title  CLEAR_EVENT_THROTTLE.cpp
// \author Rob Bocchino
// \brief  CLEAR_EVENT_THROTTLE class implementation
//
// \copyright
// Copyright (C) 2023 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged. Any commercial use must be negotiated with the Office
// of Technology Transfer at the California Institute of Technology.
// ======================================================================

#include "STest/Pick/Pick.hpp"
#include "Svc/DpManager/test/ut/Rules/CLEAR_EVENT_THROTTLE.hpp"
#include "Svc/DpManager/test/ut/Rules/Testers.hpp"

namespace Svc {

// ----------------------------------------------------------------------
// Rule definitions
// ----------------------------------------------------------------------

bool TestState ::precondition__CLEAR_EVENT_THROTTLE__OK() const {
    return true;
}

void TestState ::action__CLEAR_EVENT_THROTTLE__OK() {
    // Clear history
    this->clearHistory();
    // TODO
}

namespace CLEAR_EVENT_THROTTLE {

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void Tester ::OK() {
    // TODO
}

}  // namespace CLEAR_EVENT_THROTTLE

}  // namespace Svc
