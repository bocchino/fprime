// ======================================================================
// \title  TestState.hpp
// \author Rob Bocchino
// \brief  Test state for testing DpWriter
//
// \copyright
// Copyright (C) 2023 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged. Any commercial use must be negotiated with the Office
// of Technology Transfer at the California Institute of Technology.
// ======================================================================

#ifndef Svc_TestState_HPP
#define Svc_TestState_HPP

#include "Svc/DpWriter/test/ut/DpWriterTester.hpp"

#define TEST_STATE_DEF_RULE(GROUP_NAME, RULE_NAME)          \
    bool precondition__##GROUP_NAME##__##RULE_NAME() const; \
    void action__##GROUP_NAME##__##RULE_NAME();

namespace Svc {

class TestState : public DpWriterTester {
  public:
    // ----------------------------------------------------------------------
    // Rule definitions
    // ----------------------------------------------------------------------

    TEST_STATE_DEF_RULE(FileOpenStatus, OK)
    TEST_STATE_DEF_RULE(FileOpenStatus, Error)
};

}  // namespace Svc

#endif
