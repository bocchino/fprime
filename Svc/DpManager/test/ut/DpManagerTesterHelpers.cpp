// ======================================================================
// \title  DpManager/test/ut/TesterHelpers.cpp
// \author Auto-generated
// \brief  cpp file for DpManager component test harness base class
//
// NOTE: this file was automatically generated
//
// ======================================================================
#include "DpManagerTester.hpp"

namespace Svc {
// ----------------------------------------------------------------------
// Helper methods
// ----------------------------------------------------------------------

void DpManagerTester ::connectPorts() {
    // productGetIn
    this->connect_to_productGetIn(0, this->component.get_productGetIn_InputPort(0));

    // productRequestIn
    this->connect_to_productRequestIn(0, this->component.get_productRequestIn_InputPort(0));

    // productSendIn
    this->connect_to_productSendIn(0, this->component.get_productSendIn_InputPort(0));

    // schedIn
    this->connect_to_schedIn(0, this->component.get_schedIn_InputPort(0));

    // bufferGetOut
    this->component.set_bufferGetOut_OutputPort(0, this->get_from_bufferGetOut(0));

    // eventOut
    this->component.set_eventOut_OutputPort(0, this->get_from_eventOut(0));

    // productResponseOut
    this->component.set_productResponseOut_OutputPort(0, this->get_from_productResponseOut(0));

    // productSendOut
    this->component.set_productSendOut_OutputPort(0, this->get_from_productSendOut(0));

    // textEventOut
    this->component.set_textEventOut_OutputPort(0, this->get_from_textEventOut(0));

    // timeGetOut
    this->component.set_timeGetOut_OutputPort(0, this->get_from_timeGetOut(0));

    // tlmOut
    this->component.set_tlmOut_OutputPort(0, this->get_from_tlmOut(0));
}

void DpManagerTester ::initComponents() {
    this->init();
    this->component.init(DpManagerTester::TEST_INSTANCE_QUEUE_DEPTH, DpManagerTester::TEST_INSTANCE_ID);
}

}  // end namespace Svc
