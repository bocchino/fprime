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
    tester.productRecvIn_Container1_FAILURE();
}

TEST(productRecvIn, Container2_SUCCESS) {
    COMMENT("Receive Container2 SUCCESS");
    Tester tester;
    tester.productRecvIn_Container2_SUCCESS();
}

TEST(productRecvIn, Container2_FAILURE) {
    COMMENT("Receive Container2 FAILURE");
    Tester tester;
    tester.productRecvIn_Container2_FAILURE();
}

TEST(productRecvIn, Container3_SUCCESS) {
    COMMENT("Receive Container3 SUCCESS");
    Tester tester;
    tester.productRecvIn_Container3_SUCCESS();
}

TEST(productRecvIn, Container3_FAILURE) {
    COMMENT("Receive Container3 FAILURE");
    Tester tester;
    tester.productRecvIn_Container3_FAILURE();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
