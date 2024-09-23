// ----------------------------------------------------------------------
// main.cpp
// ----------------------------------------------------------------------

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal/initial/Basic.hpp"
#include "FppTest/state_machine/internal/initial/Junction.hpp"
#include "FppTest/state_machine/internal/initial/Nested.hpp"
#include "STest/STest/Random/Random.hpp"

TEST(Basic, Test) {
  FppTest::SmInitial::Basic basic;
  basic.test();
}

TEST(Junction, False) {
  FppTest::SmInitial::Junction junction;
  junction.testFalse();
}

TEST(Junction, True) {
  FppTest::SmInitial::Junction junction;
  junction.testTrue();
}

TEST(Nested, Test) {
  FppTest::SmInitial::Nested nested;
  nested.test();
}

// ----------------------------------------------------------------------
// Main function
// ----------------------------------------------------------------------

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
