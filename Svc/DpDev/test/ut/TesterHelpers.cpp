// ======================================================================
// \title  DpDev/test/ut/TesterHelpers.cpp
// \author Auto-generated
// \brief  cpp file for DpDev component test harness base class
//
// NOTE: this file was automatically generated
//
// ======================================================================
#include "Tester.hpp"

namespace Svc {
  // ----------------------------------------------------------------------
  // Helper methods
  // ----------------------------------------------------------------------

  void Tester ::
    connectPorts()
  {

    // productRecvIn
    this->connect_to_productRecvIn(
        0,
        this->component.get_productRecvIn_InputPort(0)
    );

    // productRequestOut
    this->component.set_productRequestOut_OutputPort(
        0,
        this->get_from_productRequestOut(0)
    );

    // productSendOut
    this->component.set_productSendOut_OutputPort(
        0,
        this->get_from_productSendOut(0)
    );




  }

  void Tester ::
    initComponents()
  {
    this->init();
    this->component.init(
        Tester::TEST_INSTANCE_QUEUE_DEPTH, Tester::TEST_INSTANCE_ID
    );
  }

} // end namespace Svc