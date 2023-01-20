// ----------------------------------------------------------------------
// TestMain.cpp
// ----------------------------------------------------------------------

#include "STest/Random/Random.hpp"
#include "Svc/DpDev/test/ut/Tester.hpp"

TEST(Nominal, ToDo) {
    Svc::Tester tester;
    tester.testSchedIn();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
