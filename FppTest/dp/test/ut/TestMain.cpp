// ----------------------------------------------------------------------
// TestMain.cpp
// ----------------------------------------------------------------------

#include "FppTest/dp/test/ut/Tester.hpp"
#include "Fw/Test/UnitTest.hpp"
#include "STest/Random/Random.hpp"

using namespace FppTest;

TEST(schedIn, OK) {
    COMMENT("schedIn OK");
    Tester tester;
    tester.schedIn_OK();
}

TEST(productRecvIn, Container1_OK) {
    COMMENT("Receive Container1 OK");
    Tester tester;
    tester.productRecvIn_Container1_OK();
}

TEST(productRecvIn, Container2_OK) {
    COMMENT("Receive Container2 OK");
    Tester tester;
    tester.productRecvIn_Container2_OK();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
