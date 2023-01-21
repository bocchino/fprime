// ----------------------------------------------------------------------
// TestMain.cpp
// ----------------------------------------------------------------------

#include "STest/Random/Random.hpp"
#include "Svc/DpDev/test/ut/Tester.hpp"

using namespace Svc;

TEST(schedIn, OK) {
    Tester tester;
    tester.schedIn_OK();
}

TEST(productRecvIn, Container1OK) {
    Tester tester;
    tester.productRecvIn_Container1OK();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
