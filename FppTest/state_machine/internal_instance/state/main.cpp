// ----------------------------------------------------------------------
// main.cpp
// ----------------------------------------------------------------------

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/Basic.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuard.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuardString.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuardTestAbsType.hpp"
#include "STest/STest/Random/Random.hpp"

TEST(Basic, Test) {
    FppTest::SmInstanceState::Basic basic("basic");
    basic.test();
}

TEST(BasicGuard, False) {
    FppTest::SmInstanceState::BasicGuard basicGuard("basicGuard");
    basicGuard.testFalse();
}

TEST(BasicGuard, True) {
    FppTest::SmInstanceState::BasicGuard basicGuard("basicGuard");
    basicGuard.testTrue();
}

TEST(BasicGuardString, False) {
    FppTest::SmInstanceState::BasicGuardString basicGuardString("basicGuardString");
    basicGuardString.testFalse();
}

TEST(BasicGuardString, True) {
    FppTest::SmInstanceState::BasicGuardString basicGuardString("basicGuardString");
    basicGuardString.testTrue();
}

TEST(BasicGuardTestAbsType, False) {
    FppTest::SmInstanceState::BasicGuardTestAbsType basicGuardTestAbsType("basicGuardTestAbsType");
    basicGuardTestAbsType.testFalse();
}

TEST(BasicGuardTestAbsType, Overflow) {
    FppTest::SmInstanceState::BasicGuardTestAbsType basicGuardTestAbsType("basicGuardTestAbsType");
    basicGuardTestAbsType.testOverflow();
}

TEST(BasicGuardTestAbsType, True) {
    FppTest::SmInstanceState::BasicGuardTestAbsType basicGuardTestAbsType("basicGuardTestAbsType");
    basicGuardTestAbsType.testTrue();
}

// ----------------------------------------------------------------------
// Main function
// ----------------------------------------------------------------------

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
