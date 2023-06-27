// ======================================================================
// \title  Rules.hpp
// \author Rob Bocchino
// \brief  Rules for testing DpManager
//
// \copyright
// Copyright (C) 2023 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged. Any commercial use must be negotiated with the Office
// of Technology Transfer at the California Institute of Technology.
// ======================================================================

#ifndef Svc_Rules_HPP
#define Svc_Rules_HPP

#include "STest/Rule/Rule.hpp"

#include "Svc/DpManager/test/ut/TestState/TestState.hpp"

#define DEF_RULE(GROUP_NAME, RULE_NAME)                                                                         \
    namespace GROUP_NAME {                                                                                      \
                                                                                                                \
    struct RULE_NAME : public STest::Rule<TestState> {                                                          \
        RULE_NAME(void) : Rule<TestState>(#GROUP_NAME "." #RULE_NAME) {}                                        \
                                                                                                                \
        bool precondition(const TestState& state) { return state.precondition__##GROUP_NAME##__##RULE_NAME(); } \
                                                                                                                \
        void action(TestState& state) { state.action__##GROUP_NAME##__##RULE_NAME(); }                          \
    };                                                                                                          \
    }

namespace Svc {

namespace Rules {

namespace BufferGetStatus {

struct Invalid : public STest::Rule<TestState> {
    Invalid(void) : Rule<TestState>("BufferGetStatus.Invalid") {}

    bool precondition(const TestState& state) { return state.precondition__BufferGetStatus__Invalid(); }

    void action(TestState& state) { state.action__BufferGetStatus__Invalid(); }
};

}  // namespace BufferGetStatus

namespace BufferGetStatus {

struct Valid : public STest::Rule<TestState> {
    Valid(void) : Rule<TestState>("BufferGetStatus.Valid") {}

    bool precondition(const TestState& state) { return state.precondition__BufferGetStatus__Valid(); }

    void action(TestState& state) { state.action__BufferGetStatus__Valid(); }
};

}  // namespace BufferGetStatus

}  // namespace Rules

}  // namespace Svc

#endif
