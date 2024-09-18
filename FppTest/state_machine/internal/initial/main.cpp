// ----------------------------------------------------------------------
// main.cpp
// ----------------------------------------------------------------------

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal/initial/Basic.hpp"
#include "FppTest/state_machine/internal/initial/Junction.hpp"
#include "STest/STest/Random/Random.hpp"

TEST(Basic, Test) {
  FppTest::Basic basic;
  basic.test();
}

TEST(Junction, False) {
  FppTest::Junction junction;
  junction.testFalse();
}

TEST(Junction, True) {
  FppTest::Junction junction;
  junction.testTrue();
}

// ----------------------------------------------------------------------
// Main function
// ----------------------------------------------------------------------

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
