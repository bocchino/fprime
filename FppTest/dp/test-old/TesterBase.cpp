// ======================================================================
// \title  DpTest/test/ut/TesterBase.cpp
// \author Auto-generated
// \brief  cpp file for DpTest component test harness base class
//
// NOTE: this file was automatically generated
//
// ======================================================================

#include <cstdlib>
#include <cstring>
#include "TesterBase.hpp"

namespace FppTest {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  DpTestTesterBase ::
    DpTestTesterBase(
        const char *const compName,
        const U32 maxHistorySize
    ) :
      Fw::PassiveComponentBase(compName)
  {
    // Initialize histories for typed user output ports
    this->fromPortHistory_productGetOut =
      new History<FromPortEntry_productGetOut>(maxHistorySize);
    this->fromPortHistory_productRequestOut =
      new History<FromPortEntry_productRequestOut>(maxHistorySize);
    this->fromPortHistory_productSendOut =
      new History<FromPortEntry_productSendOut>(maxHistorySize);
    // Clear history
    this->clearHistory();
  }

  DpTestTesterBase ::
    ~DpTestTesterBase()
  {
    // Destroy port histories
    delete this->fromPortHistory_productGetOut;
    // Destroy port histories
    delete this->fromPortHistory_productRequestOut;
    // Destroy port histories
    delete this->fromPortHistory_productSendOut;
  }

  void DpTestTesterBase ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {

    // Initialize base class

		Fw::PassiveComponentBase::init(instance);

    // Attach input port productGetOut

    for (
        PlatformIntType _port = 0;
        _port < static_cast<PlatformIntType>(this->getNum_from_productGetOut());
        ++_port
    ) {

      this->m_from_productGetOut[_port].init();
      this->m_from_productGetOut[_port].addCallComp(
          this,
          from_productGetOut_static
      );
      this->m_from_productGetOut[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_productGetOut[%" PRI_PlatformIntType "]",
          this->m_objName,
          _port
      );
      this->m_from_productGetOut[_port].setObjName(_portName);
#endif

    }

    // Attach input port productRequestOut

    for (
        PlatformIntType _port = 0;
        _port < static_cast<PlatformIntType>(this->getNum_from_productRequestOut());
        ++_port
    ) {

      this->m_from_productRequestOut[_port].init();
      this->m_from_productRequestOut[_port].addCallComp(
          this,
          from_productRequestOut_static
      );
      this->m_from_productRequestOut[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_productRequestOut[%" PRI_PlatformIntType "]",
          this->m_objName,
          _port
      );
      this->m_from_productRequestOut[_port].setObjName(_portName);
#endif

    }

    // Attach input port productSendOut

    for (
        PlatformIntType _port = 0;
        _port < static_cast<PlatformIntType>(this->getNum_from_productSendOut());
        ++_port
    ) {

      this->m_from_productSendOut[_port].init();
      this->m_from_productSendOut[_port].addCallComp(
          this,
          from_productSendOut_static
      );
      this->m_from_productSendOut[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_productSendOut[%" PRI_PlatformIntType "]",
          this->m_objName,
          _port
      );
      this->m_from_productSendOut[_port].setObjName(_portName);
#endif

    }

    // Attach input port timeGetOut

    for (
        PlatformIntType _port = 0;
        _port < static_cast<PlatformIntType>(this->getNum_from_timeGetOut());
        ++_port
    ) {

      this->m_from_timeGetOut[_port].init();
      this->m_from_timeGetOut[_port].addCallComp(
          this,
          from_timeGetOut_static
      );
      this->m_from_timeGetOut[_port].setPortNum(_port);

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      (void) snprintf(
          _portName,
          sizeof(_portName),
          "%s_from_timeGetOut[%" PRI_PlatformIntType "]",
          this->m_objName,
          _port
      );
      this->m_from_timeGetOut[_port].setObjName(_portName);
#endif

    }

    // Initialize output port productRecvIn

    for (
        PlatformIntType _port = 0;
        _port < static_cast<PlatformIntType>(this->getNum_to_productRecvIn());
        ++_port
    ) {
      this->m_to_productRecvIn[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_productRecvIn[%" PRI_PlatformIntType "]",
          this->m_objName,
          _port
      );
      this->m_to_productRecvIn[_port].setObjName(_portName);
#endif

    }

    // Initialize output port schedIn

    for (
        PlatformIntType _port = 0;
        _port < static_cast<PlatformIntType>(this->getNum_to_schedIn());
        ++_port
    ) {
      this->m_to_schedIn[_port].init();

#if FW_OBJECT_NAMES == 1
      char _portName[120];
      snprintf(
          _portName,
          sizeof(_portName),
          "%s_to_schedIn[%" PRI_PlatformIntType "]",
          this->m_objName,
          _port
      );
      this->m_to_schedIn[_port].setObjName(_portName);
#endif

    }

  }

  // ----------------------------------------------------------------------
  // Getters for port counts
  // ----------------------------------------------------------------------

  NATIVE_INT_TYPE DpTestTesterBase ::
    getNum_from_productGetOut() const
  {
    return static_cast<NATIVE_INT_TYPE>(FW_NUM_ARRAY_ELEMENTS(this->m_from_productGetOut));
  }

  NATIVE_INT_TYPE DpTestTesterBase ::
    getNum_to_productRecvIn() const
  {
    return static_cast<NATIVE_INT_TYPE>(FW_NUM_ARRAY_ELEMENTS(this->m_to_productRecvIn));
  }

  NATIVE_INT_TYPE DpTestTesterBase ::
    getNum_from_productRequestOut() const
  {
    return static_cast<NATIVE_INT_TYPE>(FW_NUM_ARRAY_ELEMENTS(this->m_from_productRequestOut));
  }

  NATIVE_INT_TYPE DpTestTesterBase ::
    getNum_from_productSendOut() const
  {
    return static_cast<NATIVE_INT_TYPE>(FW_NUM_ARRAY_ELEMENTS(this->m_from_productSendOut));
  }

  NATIVE_INT_TYPE DpTestTesterBase ::
    getNum_to_schedIn() const
  {
    return static_cast<NATIVE_INT_TYPE>(FW_NUM_ARRAY_ELEMENTS(this->m_to_schedIn));
  }

  NATIVE_INT_TYPE DpTestTesterBase ::
    getNum_from_timeGetOut() const
  {
    return static_cast<NATIVE_INT_TYPE>(FW_NUM_ARRAY_ELEMENTS(this->m_from_timeGetOut));
  }

  // ----------------------------------------------------------------------
  // Connectors for to ports
  // ----------------------------------------------------------------------

  void DpTestTesterBase ::
    connect_to_productRecvIn(
        const NATIVE_INT_TYPE portNum,
        Fw::InputDpResponsePort *const productRecvIn
    )
  {
    FW_ASSERT(portNum < this->getNum_to_productRecvIn(),static_cast<FwAssertArgType>(portNum));
    this->m_to_productRecvIn[portNum].addCallPort(productRecvIn);
  }

  void DpTestTesterBase ::
    connect_to_schedIn(
        const NATIVE_INT_TYPE portNum,
        Svc::InputSchedPort *const schedIn
    )
  {
    FW_ASSERT(portNum < this->getNum_to_schedIn(),static_cast<FwAssertArgType>(portNum));
    this->m_to_schedIn[portNum].addCallPort(schedIn);
  }


  // ----------------------------------------------------------------------
  // Invocation functions for to ports
  // ----------------------------------------------------------------------

  void DpTestTesterBase ::
    invoke_to_productRecvIn(
        const NATIVE_INT_TYPE portNum,
        FwDpIdType id,
        const Fw::Buffer &buffer,
        const Fw::Success &status
    )
  {
    FW_ASSERT(portNum < this->getNum_to_productRecvIn(),static_cast<FwAssertArgType>(portNum));
    FW_ASSERT(portNum < this->getNum_to_productRecvIn(),static_cast<FwAssertArgType>(portNum));
    this->m_to_productRecvIn[portNum].invoke(
        id, buffer, status
    );
  }

  void DpTestTesterBase ::
    invoke_to_schedIn(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    FW_ASSERT(portNum < this->getNum_to_schedIn(),static_cast<FwAssertArgType>(portNum));
    FW_ASSERT(portNum < this->getNum_to_schedIn(),static_cast<FwAssertArgType>(portNum));
    this->m_to_schedIn[portNum].invoke(
        context
    );
  }

  // ----------------------------------------------------------------------
  // Connection status for to ports
  // ----------------------------------------------------------------------

  bool DpTestTesterBase ::
    isConnected_to_productRecvIn(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_productRecvIn(), static_cast<FwAssertArgType>(portNum));
    return this->m_to_productRecvIn[portNum].isConnected();
  }

  bool DpTestTesterBase ::
    isConnected_to_schedIn(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_to_schedIn(), static_cast<FwAssertArgType>(portNum));
    return this->m_to_schedIn[portNum].isConnected();
  }

  // ----------------------------------------------------------------------
  // Getters for from ports
  // ----------------------------------------------------------------------

  Fw::InputDpGetPort *DpTestTesterBase ::
    get_from_productGetOut(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_productGetOut(),static_cast<FwAssertArgType>(portNum));
    return &this->m_from_productGetOut[portNum];
  }

  Fw::InputDpRequestPort *DpTestTesterBase ::
    get_from_productRequestOut(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_productRequestOut(),static_cast<FwAssertArgType>(portNum));
    return &this->m_from_productRequestOut[portNum];
  }

  Fw::InputDpSendPort *DpTestTesterBase ::
    get_from_productSendOut(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_productSendOut(),static_cast<FwAssertArgType>(portNum));
    return &this->m_from_productSendOut[portNum];
  }

  Fw::InputTimePort *DpTestTesterBase ::
    get_from_timeGetOut(const NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(portNum < this->getNum_from_timeGetOut(),static_cast<FwAssertArgType>(portNum));
    return &this->m_from_timeGetOut[portNum];
  }

  // ----------------------------------------------------------------------
  // Static functions for from ports
  // ----------------------------------------------------------------------

  Fw::Success DpTestTesterBase ::
    from_productGetOut_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        FwDpIdType id,
        FwSizeType size,
        Fw::Buffer &buffer
    )
  {
    FW_ASSERT(callComp);
    DpTestTesterBase* _testerBase =
      static_cast<DpTestTesterBase*>(callComp);
    return _testerBase->from_productGetOut_handlerBase(
        portNum,
        id, size, buffer
    );
  }

  void DpTestTesterBase ::
    from_productRequestOut_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        FwDpIdType id,
        FwSizeType size
    )
  {
    FW_ASSERT(callComp);
    DpTestTesterBase* _testerBase =
      static_cast<DpTestTesterBase*>(callComp);
    _testerBase->from_productRequestOut_handlerBase(
        portNum,
        id, size
    );
  }

  void DpTestTesterBase ::
    from_productSendOut_static(
        Fw::PassiveComponentBase *const callComp,
        const NATIVE_INT_TYPE portNum,
        FwDpIdType id,
        const Fw::Buffer &buffer
    )
  {
    FW_ASSERT(callComp);
    DpTestTesterBase* _testerBase =
      static_cast<DpTestTesterBase*>(callComp);
    _testerBase->from_productSendOut_handlerBase(
        portNum,
        id, buffer
    );
  }

  void DpTestTesterBase ::
    from_timeGetOut_static(
        Fw::PassiveComponentBase *const component,
        const NATIVE_INT_TYPE portNum,
        Fw::Time& time
    )
  {
    DpTestTesterBase* _testerBase =
      static_cast<DpTestTesterBase*>(component);
    time = _testerBase->m_testTime;
  }

  // ----------------------------------------------------------------------
  // Histories for typed from ports
  // ----------------------------------------------------------------------

  void DpTestTesterBase ::
    clearFromPortHistory()
  {
    this->fromPortHistorySize = 0;
    this->fromPortHistory_productGetOut->clear();
    this->fromPortHistory_productRequestOut->clear();
    this->fromPortHistory_productSendOut->clear();
  }

  // ----------------------------------------------------------------------
  // From port: productGetOut
  // ----------------------------------------------------------------------

  void DpTestTesterBase ::
    pushFromPortEntry_productGetOut(
        FwDpIdType id,
        FwSizeType size,
        Fw::Buffer &buffer
    )
  {
    FromPortEntry_productGetOut _e = {
      id, size, buffer
    };
    this->fromPortHistory_productGetOut->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ----------------------------------------------------------------------
  // From port: productRequestOut
  // ----------------------------------------------------------------------

  void DpTestTesterBase ::
    pushFromPortEntry_productRequestOut(
        FwDpIdType id,
        FwSizeType size
    )
  {
    FromPortEntry_productRequestOut _e = {
      id, size
    };
    this->fromPortHistory_productRequestOut->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ----------------------------------------------------------------------
  // From port: productSendOut
  // ----------------------------------------------------------------------

  void DpTestTesterBase ::
    pushFromPortEntry_productSendOut(
        FwDpIdType id,
        const Fw::Buffer &buffer
    )
  {
    FromPortEntry_productSendOut _e = {
      id, buffer
    };
    this->fromPortHistory_productSendOut->push_back(_e);
    ++this->fromPortHistorySize;
  }

  // ----------------------------------------------------------------------
  // Handler base functions for from ports
  // ----------------------------------------------------------------------

  Fw::Success DpTestTesterBase ::
    from_productGetOut_handlerBase(
        const NATIVE_INT_TYPE portNum,
        FwDpIdType id,
        FwSizeType size,
        Fw::Buffer &buffer
    )
  {
    FW_ASSERT(portNum < this->getNum_from_productGetOut(),static_cast<FwAssertArgType>(portNum));
    return this->from_productGetOut_handler(
        portNum,
        id, size, buffer
    );
  }

  void DpTestTesterBase ::
    from_productRequestOut_handlerBase(
        const NATIVE_INT_TYPE portNum,
        FwDpIdType id,
        FwSizeType size
    )
  {
    FW_ASSERT(portNum < this->getNum_from_productRequestOut(),static_cast<FwAssertArgType>(portNum));
    this->from_productRequestOut_handler(
        portNum,
        id, size
    );
  }

  void DpTestTesterBase ::
    from_productSendOut_handlerBase(
        const NATIVE_INT_TYPE portNum,
        FwDpIdType id,
        const Fw::Buffer &buffer
    )
  {
    FW_ASSERT(portNum < this->getNum_from_productSendOut(),static_cast<FwAssertArgType>(portNum));
    this->from_productSendOut_handler(
        portNum,
        id, buffer
    );
  }

  // ----------------------------------------------------------------------
  // History
  // ----------------------------------------------------------------------

  void DpTestTesterBase ::
    clearHistory()
  {
    this->clearFromPortHistory();
  }

  // ----------------------------------------------------------------------
  // Time
  // ----------------------------------------------------------------------

  void DpTestTesterBase ::
    setTestTime(const Fw::Time& time)
  {
    this->m_testTime = time;
  }

} // end namespace FppTest
