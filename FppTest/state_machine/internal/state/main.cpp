// ----------------------------------------------------------------------
// main.cpp
// ----------------------------------------------------------------------

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal/state/Basic.hpp"
#include "FppTest/state_machine/internal/state/BasicSelf.hpp"
#include "STest/STest/Random/Random.hpp"

TEST(Basic, Test) {
  FppTest::SmState::Basic basic;
  basic.test();
}

TEST(BasicSelf, Test) {
  FppTest::SmState::BasicSelf basicSelf;
  basicSelf.test();
}

// ----------------------------------------------------------------------
// Main function
// ----------------------------------------------------------------------

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
