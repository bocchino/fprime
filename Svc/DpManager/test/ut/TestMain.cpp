// ======================================================================
// TestMain.cpp
// ======================================================================

#include "Fw/Test/UnitTest.hpp"
#include "STest/Random/Random.hpp"
#include "Svc/DpManager/test/ut/Rules/Testers.hpp"
#include "Svc/DpManager/test/ut/Scenarios/Random.hpp"

namespace Svc {

  TEST(BufferGetStatus, Invalid) {
    COMMENT("Set the buffer get status to INVALID.");
    BufferGetStatus::Tester tester;
    tester.Invalid();
  }

  TEST(BufferGetStatus, Valid) {
    COMMENT("Set the buffer get status to VALID.");
    BufferGetStatus::Tester tester;
    tester.Valid();
  }

  TEST(ProductRequestIn, BufferInvalid) {
    COMMENT("Invoke productRequestIn in a state where the test harness returns an invalid buffer.");
    REQUIREMENT("SVC-DPMANAGER-001");
    REQUIREMENT("SVC-DPMANAGER-003");
    ProductRequestIn::Tester tester;
    tester.BufferInvalid();
  }

  TEST(ProductRequestIn, BufferValid) {
    COMMENT("Invoke productRequestIn in a state where the test harness returns a valid buffer.");
    REQUIREMENT("SVC-DPMANAGER-001");
    REQUIREMENT("SVC-DPMANAGER-003");
    ProductRequestIn::Tester tester;
    tester.BufferValid();
  }

  TEST(ProductSendIn, OK) {
    COMMENT("Invoke productSendIn with nominal input.");
    REQUIREMENT("SVC-DPMANAGER-002");
    REQUIREMENT("SVC-DPMANAGER-003");
    ProductSendIn::Tester tester;
    tester.OK();
  }

  TEST(SchedIn, OK) {
    COMMENT("Invoke schedIn with nominal input.");
    REQUIREMENT("SVC-DPMANAGER-003");
    SchedIn::Tester tester;
    tester.OK();
  }

  TEST(Scenarios, Random) {
    COMMENT("Random scenario with all rules.");
    REQUIREMENT("SVC-DPMANAGER-001");
    REQUIREMENT("SVC-DPMANAGER-002");
    REQUIREMENT("SVC-DPMANAGER-003");
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
