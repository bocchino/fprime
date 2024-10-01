// ----------------------------------------------------------------------
// main.cpp
// ----------------------------------------------------------------------

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal/junction/Basic.hpp"
#include "STest/STest/Random/Random.hpp"

TEST(Basic, True) {
  FppTest::SmJunction::Basic basic;
  basic.testTrue();
}

TEST(Basic, False) {
  FppTest::SmJunction::Basic basic;
  basic.testFalse();
}

// ----------------------------------------------------------------------
// Main function
// ----------------------------------------------------------------------

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
