// ----------------------------------------------------------------------
// main.cpp
// ----------------------------------------------------------------------

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/Basic.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuard.hpp"
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

// ----------------------------------------------------------------------
// Main function
// ----------------------------------------------------------------------

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
