// ----------------------------------------------------------------------
// TestMain.cpp
// ----------------------------------------------------------------------

#include "FppTest/state_machine/external/test/ut/Tester.hpp"
#include "Fw/Test/UnitTest.hpp"
#include "STest/Random/Random.hpp"

using namespace FppTest;

TEST(schedIn, OK) {
    COMMENT("schedIn OK");
    Tester tester;
    tester.schedIn_OK();
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
