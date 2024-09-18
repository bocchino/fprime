// ----------------------------------------------------------------------
// main.cpp
// ----------------------------------------------------------------------

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal/initial/Basic.hpp"
#include "STest/STest/Random/Random.hpp"

TEST(Initial, Basic) {
  FppTest::Basic basic;
  basic.test();
}

// ----------------------------------------------------------------------
// Main function
// ----------------------------------------------------------------------

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
