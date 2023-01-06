// ======================================================================
// \title  DpDev.hpp
// \author bocchino
// \brief  cpp file for DpDev test harness implementation class
// ======================================================================

#include "Tester.hpp"

namespace Svc {

  // ----------------------------------------------------------------------
  // Construction and destruction
  // ----------------------------------------------------------------------

  Tester ::
    Tester() :
      DpDevGTestBase("Tester", Tester::MAX_HISTORY_SIZE),
      component("DpDev")
  {
    this->initComponents();
    this->connectPorts();
  }

  Tester ::
    ~Tester()
  {

  }

  // ----------------------------------------------------------------------
  // Tests
  // ----------------------------------------------------------------------

  void Tester ::
    toDo()
  {
    // TODO
  }

  // ----------------------------------------------------------------------
  // Handlers for typed from ports
  // ----------------------------------------------------------------------

  void Tester ::
    from_productRequestOut_handler(
        const NATIVE_INT_TYPE portNum,
        FwDpIdType id,
        FwDpBuffSizeType size
    )
  {
    this->pushFromPortEntry_productRequestOut(id, size);
  }

  void Tester ::
    from_productSendOut_handler(
        const NATIVE_INT_TYPE portNum,
        FwDpIdType id,
        const Fw::Buffer &buffer
    )
  {
    this->pushFromPortEntry_productSendOut(id, buffer);
  }


} // end namespace Svc
