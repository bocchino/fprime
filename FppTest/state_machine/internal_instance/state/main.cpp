// ----------------------------------------------------------------------
// main.cpp
// ----------------------------------------------------------------------

#include <gtest/gtest.h>

#include "FppTest/state_machine/internal_instance/state/Basic.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuard.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuardString.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuardTestAbsType.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuardTestArray.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuardTestEnum.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuardTestStruct.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicGuardU32.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicInternal.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicSelf.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicString.hpp"
#include "FppTest/state_machine/internal_instance/state/BasicTestAbsType.hpp"
#include "STest/STest/Random/Random.hpp"

TEST(Basic, Test) {
    FppTest::SmInstanceState::Basic basic("basic");
    basic.test();
}

TEST(BasicGuard, False) {
    FppTest::SmInstanceState::BasicGuard basicGuard("basicGuard");
    basicGuard.testFalse();
}

TEST(BasicGuard, True) {
    FppTest::SmInstanceState::BasicGuard basicGuard("basicGuard");
    basicGuard.testTrue();
}

TEST(BasicGuardString, False) {
    FppTest::SmInstanceState::BasicGuardString basicGuardString("basicGuardString");
    basicGuardString.testFalse();
}

TEST(BasicGuardString, True) {
    FppTest::SmInstanceState::BasicGuardString basicGuardString("basicGuardString");
    basicGuardString.testTrue();
}

TEST(BasicGuardTestAbsType, False) {
    FppTest::SmInstanceState::BasicGuardTestAbsType basicGuardTestAbsType("basicGuardTestAbsType");
    basicGuardTestAbsType.testFalse();
}

TEST(BasicGuardTestAbsType, Overflow) {
    FppTest::SmInstanceState::BasicGuardTestAbsType basicGuardTestAbsType("basicGuardTestAbsType");
    basicGuardTestAbsType.testOverflow();
}

TEST(BasicGuardTestAbsType, True) {
    FppTest::SmInstanceState::BasicGuardTestAbsType basicGuardTestAbsType("basicGuardTestAbsType");
    basicGuardTestAbsType.testTrue();
}

TEST(BasicGuardTestArray, False) {
    FppTest::SmInstanceState::BasicGuardTestArray basicGuardTestArray("basicGuardTestArray");
    basicGuardTestArray.testFalse();
}

TEST(BasicGuardTestArray, True) {
    FppTest::SmInstanceState::BasicGuardTestArray basicGuardTestArray("basicGuardTestArray");
    basicGuardTestArray.testTrue();
}

TEST(BasicGuardTestEnum, False) {
    FppTest::SmInstanceState::BasicGuardTestEnum basicGuardTestEnum("basicGuardTestEnum");
    basicGuardTestEnum.testFalse();
}

TEST(BasicGuardTestEnum, True) {
    FppTest::SmInstanceState::BasicGuardTestEnum basicGuardTestEnum("basicGuardTestEnum");
    basicGuardTestEnum.testTrue();
}

TEST(BasicGuardTestStruct, False) {
    FppTest::SmInstanceState::BasicGuardTestStruct basicGuardTestStruct("basicGuardTestStruct");
    basicGuardTestStruct.testFalse();
}

TEST(BasicGuardTestStruct, True) {
    FppTest::SmInstanceState::BasicGuardTestStruct basicGuardTestStruct("basicGuardTestStruct");
    basicGuardTestStruct.testTrue();
}

TEST(BasicGuardU32, False) {
    FppTest::SmInstanceState::BasicGuardU32 basicGuardU32("basicGuardU32");
    basicGuardU32.testFalse();
}

TEST(BasicGuardU32, True) {
    FppTest::SmInstanceState::BasicGuardU32 basicGuardU32("basicGuardU32");
    basicGuardU32.testTrue();
}

TEST(BasicInternal, Test) {
    FppTest::SmInstanceState::BasicInternal basicInternal("basicInternal");
    basicInternal.test();
}

TEST(BasicSelf, Test) {
    FppTest::SmInstanceState::BasicSelf basicSelf("basicSelf");
    basicSelf.test();
}

TEST(BasicString, Test) {
    FppTest::SmInstanceState::BasicString basicString("basicString");
    basicString.test();
}

TEST(BasicTestAbsType, Test) {
    FppTest::SmInstanceState::BasicTestAbsType basicTestAbsType("basicTestAbsType");
    basicTestAbsType.test();
}

// ----------------------------------------------------------------------
// Main function
// ----------------------------------------------------------------------

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
