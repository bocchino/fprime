// ======================================================================
// \title  DpManager.hpp
// \author bocchino
// \brief  cpp file for DpManager test harness implementation class
// ======================================================================

#include "Tester.hpp"

namespace Svc {

  // ----------------------------------------------------------------------
  // Construction and destruction
  // ----------------------------------------------------------------------

  Tester ::
    Tester() :
      DpManagerGTestBase("Tester", Tester::MAX_HISTORY_SIZE),
      component("DpManager")
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

  Fw::Buffer Tester ::
    from_bufferGetOut_handler(
        const NATIVE_INT_TYPE portNum,
        U32 size
    )
  {
    this->pushFromPortEntry_bufferGetOut(size);
    Fw::Buffer buffer;
    switch (this->abstractState.bufferGetStatus) {
      case AbstractState::BufferGetStatus::VALID:
        // Construct a valid buffer
        buffer.setData(this->bufferData);
        FW_ASSERT(size <= MAX_BUFFER_SIZE);
        buffer.setSize(size);
        break;
      case AbstractState::BufferGetStatus::INVALID:
        // Leave buffer in invalid state
        break;
      default:
        FW_ASSERT(0);
        break;
    }
    return buffer;
  }

  void Tester ::
    from_productResponseOut_handler(
        const NATIVE_INT_TYPE portNum,
        FwDpIdType id,
        const Fw::Buffer &buffer
    )
  {
    this->pushFromPortEntry_productResponseOut(id, buffer);
  }

  void Tester ::
    from_productSendOut_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &fwBuffer
    )
  {
    this->pushFromPortEntry_productSendOut(fwBuffer);
  }


} // end namespace Svc
