// ----------------------------------------------------------------------
// main.cpp
// ----------------------------------------------------------------------

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/junction/Basic.hpp"
#include "STest/STest/Random/Random.hpp"

TEST(Basic, BasicTrue) {
  FppTest::SmInstanceJunction::Basic basic("basic");
  basic.testBasicTrue();
}

TEST(Basic, BasicFalse) {
  FppTest::SmInstanceJunction::Basic basic("basic");
  basic.testBasicFalse();
}

TEST(Basic, SmJunctionBasicTrue) {
  FppTest::SmInstanceJunction::Basic basic("basic");
  basic.testSmJunctionBasicTrue();
}

TEST(Basic, SmJunctionBasicFalse) {
  FppTest::SmInstanceJunction::Basic basic("basic");
  basic.testSmJunctionBasicFalse();
}

// ----------------------------------------------------------------------
// Main function
// ----------------------------------------------------------------------

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
