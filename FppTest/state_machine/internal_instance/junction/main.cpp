// ----------------------------------------------------------------------
// main.cpp
// ----------------------------------------------------------------------

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/junction/Basic.hpp"
#include "FppTest/state_machine/internal_instance/junction/BasicU32.hpp"
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

TEST(BasicU32, True) {
  FppTest::SmInstanceJunction::BasicU32 basicU32("basicU32");
  basicU32.testTrue();
}

TEST(BasicU32, False) {
  FppTest::SmInstanceJunction::BasicU32 basicU32("basicU32");
  basicU32.testFalse();
}

// ----------------------------------------------------------------------
// Main function
// ----------------------------------------------------------------------

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
