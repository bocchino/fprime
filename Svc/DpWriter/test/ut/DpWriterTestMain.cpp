// ======================================================================
// \title  DpWriterTestMain.cpp
// \author bocchino
// \brief  cpp file for DpWriter component test main function
// ======================================================================

#include "Fw/Test/UnitTest.hpp"
#include "STest/Random/Random.hpp"
#include "Svc/DpWriter/test/ut/Rules/Testers.hpp"
#include "Svc/DpWriter/test/ut/Scenarios/Random.hpp"

namespace Svc {

TEST(FileOpenStatus, Invalid) {
    COMMENT("Set the file open status to OP_OK.");
    FileOpenStatus::Tester tester;
    tester.OK();
}

TEST(FileOpenStatus, Valid) {
    COMMENT("Set the file open status to an error value.");
    FileOpenStatus::Tester tester;
    tester.Error();
}

TEST(Scenarios, Random) {
    COMMENT("Random scenario with all rules.");
    REQUIREMENT("SVC-DPMANAGER-001");
    REQUIREMENT("SVC-DPMANAGER-002");
    REQUIREMENT("SVC-DPMANAGER-003");
    REQUIREMENT("SVC-DPMANAGER-004");
    REQUIREMENT("SVC-DPMANAGER-005");
    REQUIREMENT("SVC-DPMANAGER-006");
    const FwSizeType numSteps = 10000;
    Scenarios::Random::Tester tester;
    tester.run(numSteps);
}

}  // namespace Svc

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
