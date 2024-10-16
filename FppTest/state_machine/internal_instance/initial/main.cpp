// ----------------------------------------------------------------------
// main.cpp
// ----------------------------------------------------------------------

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/initial/Basic.hpp"
#include "FppTest/state_machine/internal_instance/initial/Junction.hpp"
#include "STest/STest/Random/Random.hpp"

TEST(Basic, Test) {
  FppTest::SmInstanceInitial::Basic basic("Basic");
  basic.test();
}

TEST(Junction, False) {
  FppTest::SmInstanceInitial::Junction junction("Junction");
  junction.testFalse();
}

TEST(Junction, True) {
  FppTest::SmInstanceInitial::Junction junction("Junction");
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
