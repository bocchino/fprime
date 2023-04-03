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

TEST(productRecvIn, Container1_SUCCESS) {
    COMMENT("Receive Container1 SUCCESS");
    Tester tester;
    tester.productRecvIn_Container1_SUCCESS();
}

TEST(productRecvIn, Container1_FAILURE) {
    COMMENT("Receive Container1 FAILURE");
    Tester tester;
    tester.productRecvIn_Container1_SUCCESS();
}

TEST(productRecvIn, Container2_SUCCESS) {
    COMMENT("Receive Container2 SUCCESS");
    Tester tester;
    tester.productRecvIn_Container2_SUCCESS();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
