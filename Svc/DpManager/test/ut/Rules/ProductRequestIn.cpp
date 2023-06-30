// ======================================================================
// \title  ProductRequestIn.cpp
// \author Rob Bocchino
// \brief  ProductRequestIn class implementation
//
// \copyright
// Copyright (C) 2023 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged. Any commercial use must be negotiated with the Office
// of Technology Transfer at the California Institute of Technology.
// ======================================================================

#include "STest/Pick/Pick.hpp"
#include "Svc/DpManager/test/ut/Rules/ProductRequestIn.hpp"
#include "Svc/DpManager/test/ut/Rules/Testers.hpp"

namespace Svc {

// ----------------------------------------------------------------------
// Rule definitions
// ----------------------------------------------------------------------

bool TestState::precondition__ProductRequestIn__BufferValid() const {
    return true;
}

void TestState::action__ProductRequestIn__BufferValid() {
    // TODO
}

bool TestState::precondition__ProductRequestIn__BufferInvalid() const {
    return true;
}

void TestState ::action__ProductRequestIn__BufferInvalid() {
    // TODO
}

namespace ProductRequestIn {

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void Tester ::BufferValid() {
    // TODO
}

void Tester ::BufferInvalid() {
    // TODO
}

}  // namespace ProductRequestIn

}  // namespace Svc
