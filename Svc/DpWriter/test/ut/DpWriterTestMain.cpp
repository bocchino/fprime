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

TEST(BufferSendIn, InvalidBuffer) {
    COMMENT("Invoke bufferSendIn with an invalid buffer.");
    REQUIREMENT("SVC-DPMANAGER-001");
    BufferSendIn::Tester tester;
    tester.InvalidBuffer();
}

TEST(BufferSendIn, BufferTooSmallForPacket) {
    COMMENT("Invoke bufferSendIn with a buffer that is too small to hold a data product packet.");
    REQUIREMENT("SVC-DPMANAGER-001");
    BufferSendIn::Tester tester;
    tester.BufferTooSmallForPacket();
}

TEST(BufferSendIn, OK) {
    COMMENT("Invoke bufferSendIn with nominal input.");
    REQUIREMENT("SVC-DPMANAGER-001");
    REQUIREMENT("SVC-DPMANAGER-002");
    REQUIREMENT("SVC-DPMANAGER-003");
    REQUIREMENT("SVC-DPMANAGER-004");
    REQUIREMENT("SVC-DPMANAGER-005");
    BufferSendIn::Tester tester;
    tester.OK();
}

TEST(FileOpenStatus, OK) {
    COMMENT("Set the file open status to OP_OK.");
    FileOpenStatus::Tester tester;
    tester.OK();
}

TEST(FileOpenStatus, Error) {
    COMMENT("Set the file open status to an error value.");
    FileOpenStatus::Tester tester;
    tester.Error();
}

TEST(FileWriteStatus, OK) {
    COMMENT("Set the file write status to OP_OK.");
    FileWriteStatus::Tester tester;
    tester.OK();
}

TEST(FileWriteStatus, Error) {
    COMMENT("Set the file write status to an error value.");
    FileWriteStatus::Tester tester;
    tester.Error();
}

TEST(SchedIn, OK) {
  COMMENT("Invoke schedIn with nominal input.");
  REQUIREMENT("SVC-DPMANAGER-006");
  SchedIn::Tester tester;
  tester.OK();
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
