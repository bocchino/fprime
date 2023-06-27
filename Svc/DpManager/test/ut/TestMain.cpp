// ======================================================================
// TestMain.cpp
// ======================================================================

#include "Fw/Test/UnitTest.hpp"
#include "STest/Random/Random.hpp"
#include "Svc/DpManager/test/ut/Rules/Testers.hpp"

namespace Svc {

  TEST(BufferGetStatus, Invalid) {
    BufferGetStatus::Tester tester;
    tester.Invalid();
  }

  TEST(BufferGetStatus, Valid) {
    BufferGetStatus::Tester tester;
    tester.Valid();
  }

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
