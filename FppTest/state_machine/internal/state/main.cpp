// ----------------------------------------------------------------------
// main.cpp
// ----------------------------------------------------------------------

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal/state/Basic.hpp"
#include "FppTest/state_machine/internal/state/BasicGuard.hpp"
#include "FppTest/state_machine/internal/state/BasicSelf.hpp"
#include "FppTest/state_machine/internal/state/BasicU32.hpp"
#include "STest/STest/Random/Random.hpp"

TEST(Basic, Test) {
  FppTest::SmState::Basic basic;
  basic.test();
}

TEST(BasicSelf, Test) {
  FppTest::SmState::BasicSelf basicSelf;
  basicSelf.test();
}

TEST(BasicGuard, False) {
  FppTest::SmState::BasicGuard basicGuard;
  basicGuard.testFalse();
}

TEST(BasicGuard, True) {
  FppTest::SmState::BasicGuard basicGuard;
  basicGuard.testTrue();
}

TEST(BasicU32, Test) {
  FppTest::SmState::BasicU32 basicU32;
  basicU32.test();
}

// ----------------------------------------------------------------------
// Main function
// ----------------------------------------------------------------------

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
