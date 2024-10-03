// ----------------------------------------------------------------------
// main.cpp
// ----------------------------------------------------------------------

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal/junction/Basic.hpp"
#include "FppTest/state_machine/internal/junction/BasicU32.hpp"
#include "FppTest/state_machine/internal/junction/Sequence.hpp"
#include "STest/STest/Random/Random.hpp"

TEST(Basic, True) {
  FppTest::SmJunction::Basic basic;
  basic.testTrue();
}

TEST(Basic, False) {
  FppTest::SmJunction::Basic basic;
  basic.testFalse();
}

TEST(BasicU32, True) {
  FppTest::SmJunction::BasicU32 basicU32;
  basicU32.testTrue();
}

TEST(BasicU32, False) {
  FppTest::SmJunction::BasicU32 basicU32;
  basicU32.testFalse();
}

TEST(Sequence, G1True) {
  FppTest::SmJunction::Sequence sequence;
  sequence.testG1True();
}

TEST(Sequence, G1FalseG2True) {
  FppTest::SmJunction::Sequence sequence;
  sequence.testG1FalseG2True();
}

TEST(Sequence, G1FalseG2False) {
  FppTest::SmJunction::Sequence sequence;
  sequence.testG1FalseG2False();
}

// ----------------------------------------------------------------------
// Main function
// ----------------------------------------------------------------------

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
