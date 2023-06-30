// ======================================================================
// TestMain.cpp
// ======================================================================

#include "Fw/Test/UnitTest.hpp"
#include "STest/Random/Random.hpp"
#include "Svc/DpManager/test/ut/Rules/Testers.hpp"
#include "Svc/DpManager/test/ut/Scenarios/Random.hpp"

namespace Svc {

  TEST(BufferGetStatus, Invalid) {
    BufferGetStatus::Tester tester;
    tester.Invalid();
  }

  TEST(BufferGetStatus, Valid) {
    BufferGetStatus::Tester tester;
    tester.Valid();
  }

  TEST(ProductRequestIn, BufferInvalid) {
    ProductRequestIn::Tester tester;
    tester.BufferInvalid();
  }

  TEST(ProductRequestIn, BufferValid) {
    ProductRequestIn::Tester tester;
    tester.BufferValid();
  }

  TEST(SchedIn, OK) {
    SchedIn::Tester tester;
    tester.OK();
  }

  TEST(Scenarios, Random) {
    const FwSizeType numSteps = 10000;
    Scenarios::Random::Tester tester;
    tester.run(numSteps);
  }

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
