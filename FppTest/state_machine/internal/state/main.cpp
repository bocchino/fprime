// ----------------------------------------------------------------------
// main.cpp
// ----------------------------------------------------------------------

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal/state/Basic.hpp"
#include "FppTest/state_machine/internal/state/BasicGuard.hpp"
#include "FppTest/state_machine/internal/state/BasicSelf.hpp"
#include "FppTest/state_machine/internal/state/BasicString.hpp"
#include "FppTest/state_machine/internal/state/BasicTestAbsType.hpp"
#include "FppTest/state_machine/internal/state/BasicTestArray.hpp"
#include "FppTest/state_machine/internal/state/BasicTestEnum.hpp"
#include "FppTest/state_machine/internal/state/BasicTestStruct.hpp"
#include "FppTest/state_machine/internal/state/BasicU32.hpp"
#include "FppTest/state_machine/internal/state/StateToState.hpp"
#include "STest/STest/Random/Random.hpp"

TEST(Basic, Test) {
  FppTest::SmState::Basic basic;
  basic.test();
}

TEST(BasicGuard, False) {
  FppTest::SmState::BasicGuard basicGuard;
  basicGuard.testFalse();
}

TEST(BasicGuard, True) {
  FppTest::SmState::BasicGuard basicGuard;
  basicGuard.testTrue();
}

TEST(BasicSelf, Test) {
  FppTest::SmState::BasicSelf basicSelf;
  basicSelf.test();
}

TEST(BasicString, Test) {
  FppTest::SmState::BasicString basicString;
  basicString.test();
}

TEST(BasicTestAbsType, Test) {
  FppTest::SmState::BasicTestAbsType basicTestAbsType;
  basicTestAbsType.test();
}

TEST(BasicTestArray, Test) {
  FppTest::SmState::BasicTestArray basicTestArray;
  basicTestArray.test();
}

TEST(BasicTestEnum, Test) {
  FppTest::SmState::BasicTestEnum basicTestEnum;
  basicTestEnum.test();
}

TEST(BasicTestStruct, Test) {
  FppTest::SmState::BasicTestStruct basicTestStruct;
  basicTestStruct.test();
}

TEST(BasicU32, Test) {
  FppTest::SmState::BasicU32 basicU32;
  basicU32.test();
}

TEST(StateToState, Init) {
  FppTest::SmState::StateToState stateToState;
  stateToState.testInit();
}

TEST(StateToState, S1_to_S4) {
  FppTest::SmState::StateToState stateToState;
  stateToState.testS2_to_S4();
}

// ----------------------------------------------------------------------
// Main function
// ----------------------------------------------------------------------

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
