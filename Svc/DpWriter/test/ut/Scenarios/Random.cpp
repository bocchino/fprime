// ======================================================================
// \title  Random.hpp
// \author Rob Bocchino
// \brief  Random scenario
//
// \copyright
// Copyright (C) 2024 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged. Any commercial use must be negotiated with the Office
// of Technology Transfer at the California Institute of Technology.
// ======================================================================

#include "STest/Scenario/BoundedScenario.hpp"
#include "STest/Scenario/RandomScenario.hpp"
#include "Svc/DpWriter/test/ut/Rules/Rules.hpp"
#include "Svc/DpWriter/test/ut/Scenarios/Random.hpp"

namespace Svc {

namespace Scenarios {

namespace Random {

// ----------------------------------------------------------------------
// Rule definitions
// ----------------------------------------------------------------------

Rules::BufferSendIn::BufferTooSmallForPacket bufferSendInBufferTooSmallForPacket;
Rules::BufferSendIn::InvalidBuffer bufferSendInInvalidBuffer;
Rules::BufferSendIn::OK bufferSendInOK;
Rules::FileOpenStatus::Error fileOpenStatusError;
Rules::FileOpenStatus::OK fileOpenStatusOK;
Rules::FileWriteStatus::Error fileWriteStatusError;
Rules::FileWriteStatus::OK fileWriteStatusOK;
Rules::SchedIn::OK schedInOK;

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void Tester ::run(FwSizeType maxNumSteps) {
    STest::Rule<TestState>* rules[] = {&bufferSendInBufferTooSmallForPacket,
                                       &bufferSendInInvalidBuffer,
                                       &bufferSendInOK,
                                       &fileOpenStatusError,
                                       &fileOpenStatusOK,
                                       &fileWriteStatusError,
                                       &fileWriteStatusOK,
                                       &schedInOK};
    STest::RandomScenario<TestState> scenario("RandomScenario", rules,
                                              sizeof(rules) / sizeof(STest::RandomScenario<TestState>*));
    STest::BoundedScenario<TestState> boundedScenario("BoundedRandomScenario", scenario, maxNumSteps);
    const U32 numSteps = boundedScenario.run(this->testState);
    printf("Ran %u steps.\n", numSteps);
}

}  // namespace Random

}  // namespace Scenarios

}  // namespace Svc
