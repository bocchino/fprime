// ======================================================================
// \title  DpWriterTester.cpp
// \author bocchino
// \brief  cpp file for DpWriter component test harness implementation class
// ======================================================================

#include "DpWriterTester.hpp"

namespace Svc {

// ----------------------------------------------------------------------
// Construction and destruction
// ----------------------------------------------------------------------

DpWriterTester ::DpWriterTester()
    : DpWriterGTestBase("DpWriterTester", DpWriterTester::MAX_HISTORY_SIZE), component("DpWriter") {
    this->initComponents();
    this->connectPorts();
}

DpWriterTester ::~DpWriterTester() {}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void DpWriterTester ::toDo() {
    // TODO
}

// ----------------------------------------------------------------------
// Handlers for typed from ports
// ----------------------------------------------------------------------

void DpWriterTester ::from_deallocBufferSendOut_handler(NATIVE_INT_TYPE portNum, Fw::Buffer& fwBuffer) {
    // TODO
}

void DpWriterTester ::from_dpWrittenOut_handler(NATIVE_INT_TYPE portNum,
                                                const Svc::DpWrittenPortStrings::StringSize256& fileName,
                                                FwDpPriorityType priority,
                                                FwSizeType size) {
    // TODO
}

void DpWriterTester ::from_procBufferSendOut_handler(NATIVE_INT_TYPE portNum, Fw::Buffer& fwBuffer) {
    // TODO
}

}  // namespace Svc
