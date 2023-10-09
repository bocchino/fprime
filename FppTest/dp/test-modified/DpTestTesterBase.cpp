// ======================================================================
// \title  DpTestTesterBase.cpp
// \author Generated by fpp-to-cpp
// \brief  cpp file for DpTest component test harness base class
// ======================================================================

#include <cstdlib>
#include <cstring>

#include "FppTest/dp/DpTestTesterBase.hpp"

namespace FppTest {

  // ----------------------------------------------------------------------
  // Component initialization
  // ----------------------------------------------------------------------

  void DpTestTesterBase ::
    init(NATIVE_INT_TYPE instance)
  {
    // Initialize base class
    Fw::PassiveComponentBase::init(instance);

    // Connect input port productGetOut
    for (
      PlatformIntType port = 0;
      port < static_cast<PlatformIntType>(this->getNum_from_productGetOut());
      port++
    ) {
      this->m_from_productGetOut[port].init();
      this->m_from_productGetOut[port].addCallComp(
        this,
        from_productGetOut_static
      );
      this->m_from_productGetOut[port].setPortNum(port);

#if FW_OBJECT_NAMES == 1
      char portName[120];
      (void) snprintf(
        portName,
        sizeof(portName),
        "%s_from_productGetOut[%" PRI_PlatformIntType "]",
        this->m_objName,
        port
      );
      this->m_from_productGetOut[port].setObjName(portName);
#endif
    }

    // Connect input port productRequestOut
    for (
      PlatformIntType port = 0;
      port < static_cast<PlatformIntType>(this->getNum_from_productRequestOut());
      port++
    ) {
      this->m_from_productRequestOut[port].init();
      this->m_from_productRequestOut[port].addCallComp(
        this,
        from_productRequestOut_static
      );
      this->m_from_productRequestOut[port].setPortNum(port);

#if FW_OBJECT_NAMES == 1
      char portName[120];
      (void) snprintf(
        portName,
        sizeof(portName),
        "%s_from_productRequestOut[%" PRI_PlatformIntType "]",
        this->m_objName,
        port
      );
      this->m_from_productRequestOut[port].setObjName(portName);
#endif
    }

    // Connect input port productSendOut
    for (
      PlatformIntType port = 0;
      port < static_cast<PlatformIntType>(this->getNum_from_productSendOut());
      port++
    ) {
      this->m_from_productSendOut[port].init();
      this->m_from_productSendOut[port].addCallComp(
        this,
        from_productSendOut_static
      );
      this->m_from_productSendOut[port].setPortNum(port);

#if FW_OBJECT_NAMES == 1
      char portName[120];
      (void) snprintf(
        portName,
        sizeof(portName),
        "%s_from_productSendOut[%" PRI_PlatformIntType "]",
        this->m_objName,
        port
      );
      this->m_from_productSendOut[port].setObjName(portName);
#endif
    }

    // Connect input port timeGetOut
    for (
      PlatformIntType port = 0;
      port < static_cast<PlatformIntType>(this->getNum_from_timeGetOut());
      port++
    ) {
      this->m_from_timeGetOut[port].init();
      this->m_from_timeGetOut[port].addCallComp(
        this,
        from_timeGetOut_static
      );
      this->m_from_timeGetOut[port].setPortNum(port);

#if FW_OBJECT_NAMES == 1
      char portName[120];
      (void) snprintf(
        portName,
        sizeof(portName),
        "%s_from_timeGetOut[%" PRI_PlatformIntType "]",
        this->m_objName,
        port
      );
      this->m_from_timeGetOut[port].setObjName(portName);
#endif
    }

    // Connect output port productRecvIn
    for (
      PlatformIntType port = 0;
      port < static_cast<PlatformIntType>(this->getNum_to_productRecvIn());
      port++
    ) {
      this->m_to_productRecvIn[port].init();

#if FW_OBJECT_NAMES == 1
      char portName[120];
      (void) snprintf(
        portName,
        sizeof(portName),
        "%s_to_productRecvIn[%" PRI_PlatformIntType "]",
        this->m_objName,
        port
      );
      this->m_to_productRecvIn[port].setObjName(portName);
#endif
    }

    // Connect output port schedIn
    for (
      PlatformIntType port = 0;
      port < static_cast<PlatformIntType>(this->getNum_to_schedIn());
      port++
    ) {
      this->m_to_schedIn[port].init();

#if FW_OBJECT_NAMES == 1
      char portName[120];
      (void) snprintf(
        portName,
        sizeof(portName),
        "%s_to_schedIn[%" PRI_PlatformIntType "]",
        this->m_objName,
        port
      );
      this->m_to_schedIn[port].setObjName(portName);
#endif
    }
  }

  // ----------------------------------------------------------------------
  // Connectors for to ports
  // ----------------------------------------------------------------------

  void DpTestTesterBase ::
    connect_to_productRecvIn(
        NATIVE_INT_TYPE portNum,
        Fw::InputDpResponsePort* port
    )
  {
    FW_ASSERT(
      portNum < this->getNum_to_productRecvIn(),
      static_cast<FwAssertArgType>(portNum)
    );

    this->m_to_productRecvIn[portNum].addCallPort(port);
  }

  void DpTestTesterBase ::
    connect_to_schedIn(
        NATIVE_INT_TYPE portNum,
        Svc::InputSchedPort* port
    )
  {
    FW_ASSERT(
      portNum < this->getNum_to_schedIn(),
      static_cast<FwAssertArgType>(portNum)
    );

    this->m_to_schedIn[portNum].addCallPort(port);
  }

  // ----------------------------------------------------------------------
  // Getters for from ports
  // ----------------------------------------------------------------------

  Fw::InputDpGetPort* DpTestTesterBase ::
    get_from_productGetOut(NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(
      portNum < this->getNum_from_productGetOut(),
      static_cast<FwAssertArgType>(portNum)
    );

    return &this->m_from_productGetOut[portNum];
  }

  Fw::InputDpRequestPort* DpTestTesterBase ::
    get_from_productRequestOut(NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(
      portNum < this->getNum_from_productRequestOut(),
      static_cast<FwAssertArgType>(portNum)
    );

    return &this->m_from_productRequestOut[portNum];
  }

  Fw::InputDpSendPort* DpTestTesterBase ::
    get_from_productSendOut(NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(
      portNum < this->getNum_from_productSendOut(),
      static_cast<FwAssertArgType>(portNum)
    );

    return &this->m_from_productSendOut[portNum];
  }

  Fw::InputTimePort* DpTestTesterBase ::
    get_from_timeGetOut(NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(
      portNum < this->getNum_from_timeGetOut(),
      static_cast<FwAssertArgType>(portNum)
    );

    return &this->m_from_timeGetOut[portNum];
  }

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  DpTestTesterBase ::
    DpTestTesterBase(
        const char* const compName,
        const U32 maxHistorySize
    ) :
      Fw::PassiveComponentBase(compName)
  {
    // Initialize data product get history
    this->productGetHistory = new History<DpGet>(maxHistorySize);

    // Initialize data product request history
    this->productRequestHistory = new History<DpRequest>(maxHistorySize);

    // Initialize data product send history
    this->productSendHistory = new History<DpSend>(maxHistorySize);

    // Clear history
    this->clearHistory();
  }

  DpTestTesterBase ::
    ~DpTestTesterBase()
  {
    // Destroy product request history
    delete this->productRequestHistory;

    // Destroy product send history
    delete this->productSendHistory;
  }

  // ----------------------------------------------------------------------
  // Invocation functions for to ports
  // ----------------------------------------------------------------------

  void DpTestTesterBase ::
    invoke_to_schedIn(
        NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    // Make sure port number is valid
    FW_ASSERT(
      portNum < this->getNum_to_schedIn(),
      static_cast<FwAssertArgType>(portNum)
    );
    this->m_to_schedIn[portNum].invoke(
      context
    );
  }

  void DpTestTesterBase ::
    invoke_to_productRecvIn(
        NATIVE_INT_TYPE portNum,
        FwDpIdType id,
        Fw::Buffer buffer,
        Fw::Success success
    )
  {
    // Make sure port number is valid
    FW_ASSERT(
      portNum < this->getNum_to_productRecvIn(),
      static_cast<FwAssertArgType>(portNum)
    );
    this->m_to_productRecvIn[portNum].invoke(
      id, buffer, success
    );
  }

  // ----------------------------------------------------------------------
  // Getters for port counts
  // ----------------------------------------------------------------------

  NATIVE_INT_TYPE DpTestTesterBase ::
    getNum_to_productRecvIn() const
  {
    return static_cast<NATIVE_INT_TYPE>(FW_NUM_ARRAY_ELEMENTS(this->m_to_productRecvIn));
  }

  NATIVE_INT_TYPE DpTestTesterBase ::
    getNum_to_schedIn() const
  {
    return static_cast<NATIVE_INT_TYPE>(FW_NUM_ARRAY_ELEMENTS(this->m_to_schedIn));
  }

  NATIVE_INT_TYPE DpTestTesterBase ::
    getNum_from_productGetOut() const
  {
    return static_cast<NATIVE_INT_TYPE>(FW_NUM_ARRAY_ELEMENTS(this->m_from_productGetOut));
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
    getNum_from_timeGetOut() const
  {
    return static_cast<NATIVE_INT_TYPE>(FW_NUM_ARRAY_ELEMENTS(this->m_from_timeGetOut));
  }

  // ----------------------------------------------------------------------
  // Connection status queries for to ports
  // ----------------------------------------------------------------------

  bool DpTestTesterBase ::
    isConnected_to_productRecvIn(NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(
      portNum < this->getNum_to_productRecvIn(),
      static_cast<FwAssertArgType>(portNum)
    );

    return this->m_to_productRecvIn[portNum].isConnected();
  }

  bool DpTestTesterBase ::
    isConnected_to_schedIn(NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(
      portNum < this->getNum_to_schedIn(),
      static_cast<FwAssertArgType>(portNum)
    );

    return this->m_to_schedIn[portNum].isConnected();
  }

  // ----------------------------------------------------------------------
  // Functions to test time
  // ----------------------------------------------------------------------

  void DpTestTesterBase ::
    setTestTime(const Fw::Time& timeTag)
  {
    this->m_testTime = timeTag;
  }

  // ----------------------------------------------------------------------
  // Functions for testing data products
  // ----------------------------------------------------------------------

  Fw::Success::T DpTestTesterBase ::
    productGet_handler(
        FwDpIdType id,
        FwSizeType size,
        Fw::Buffer& buffer
    )
  {
    (void) buffer;
    DpGet e = { id, size };
    this->productGetHistory->push_back(e);
    // Default behavior: do not allocate a buffer and return FAILURE
    // Client code can override this behavior
    return Fw::Success::FAILURE;
  }

  void DpTestTesterBase ::
    productRequest_handler(
        FwDpIdType id,
        FwSizeType size
    )
  {
    DpRequest e = { id, size };
    this->productRequestHistory->push_back(e);
  }

  void DpTestTesterBase ::
    productSend_handler(
        FwDpIdType id,
        Fw::Buffer buffer
    )
  {
    DpSend e = { id, buffer };
    this->productSendHistory->push_back(e);
  }

  // ----------------------------------------------------------------------
  // History functions
  // ----------------------------------------------------------------------

  void DpTestTesterBase ::
    clearHistory()
  {
    this->productGetHistory->clear();
    this->productRequestHistory->clear();
    this->productSendHistory->clear();
  }

  // ----------------------------------------------------------------------
  // Static functions for output ports
  // ----------------------------------------------------------------------

  Fw::Success DpTestTesterBase ::
    from_productGetOut_static(
        Fw::PassiveComponentBase* const callComp,
        NATIVE_INT_TYPE portNum,
        FwDpIdType id,
        FwSizeType size,
        Fw::Buffer& buffer
    )
  {
    DpTestTesterBase* _testerBase = static_cast<DpTestTesterBase*>(callComp);
    return _testerBase->productGet_handler(id, size, buffer);
  }

  void DpTestTesterBase ::
    from_productRequestOut_static(
        Fw::PassiveComponentBase* const callComp,
        NATIVE_INT_TYPE portNum,
        FwDpIdType id,
        FwSizeType size
    )
  {
    DpTestTesterBase* _testerBase = static_cast<DpTestTesterBase*>(callComp);
    _testerBase->productRequest_handler(id, size);
  }

  void DpTestTesterBase ::
    from_productSendOut_static(
        Fw::PassiveComponentBase* const callComp,
        NATIVE_INT_TYPE portNum,
        FwDpIdType id,
        const Fw::Buffer& buffer
    )
  {
    DpTestTesterBase* _testerBase = static_cast<DpTestTesterBase*>(callComp);
    _testerBase->productSend_handler(id, buffer);
  }

  void DpTestTesterBase ::
    from_timeGetOut_static(
        Fw::PassiveComponentBase* const callComp,
        NATIVE_INT_TYPE portNum,
        Fw::Time& time
    )
  {
    DpTestTesterBase* _testerBase = static_cast<DpTestTesterBase*>(callComp);
    time = _testerBase->m_testTime;
  }

}
