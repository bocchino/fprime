// ======================================================================
// \title  DpWriterTestMain.cpp
// \author bocchino
// \brief  cpp file for DpWriter component test main function
// ======================================================================

#include "Svc/DpWriter/test/ut/DpWriterTester.hpp"

TEST(Nominal, toDo) {
    Svc::DpWriterTester tester;
    tester.toDo();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
