// ======================================================================
// \title  DpTestComponentAc.cpp
// \author Generated by fpp-to-cpp
// \brief  cpp file for DpTest component base class
// ======================================================================

#include <cstdio>

#include "Fw/Types/ByteArray.hpp"
#include "FppTest/dp/DpTestComponentAc.hpp"
#include "Fw/Types/Assert.hpp"
#if FW_ENABLE_TEXT_LOGGING
#include "Fw/Types/String.hpp"
#endif

namespace FppTest {

  namespace {
    enum MsgTypeEnum {
      DPTEST_COMPONENT_EXIT = Fw::ActiveComponentBase::ACTIVE_COMPONENT_EXIT,
      PRODUCTRECVIN_DPRESPONSE,
      SCHEDIN_SCHED,
    };

    // Get the max size by constructing a union of the async input, command, and
    // internal port serialization sizes
    union BuffUnion {
      BYTE productRecvInPortSize[Fw::InputDpResponsePort::SERIALIZED_SIZE];
      BYTE schedInPortSize[Svc::InputSchedPort::SERIALIZED_SIZE];
    };

    // Define a message buffer class large enough to handle all the
    // asynchronous inputs to the component
    class ComponentIpcSerializableBuffer :
      public Fw::SerializeBufferBase
    {

      public:

        enum {
          // Max. message size = size of data + message id + port
          SERIALIZATION_SIZE =
            sizeof(BuffUnion) +
            sizeof(NATIVE_INT_TYPE) +
            sizeof(NATIVE_INT_TYPE)
        };

        NATIVE_UINT_TYPE getBuffCapacity() const {
          return sizeof(m_buff);
        }

        U8* getBuffAddr() {
          return m_buff;
        }

        const U8* getBuffAddr() const {
          return m_buff;
        }

      private:
        // Should be the max of all the input ports serialized sizes...
        U8 m_buff[SERIALIZATION_SIZE];

    };
  }

  // ----------------------------------------------------------------------
  // Types for data products
  // ----------------------------------------------------------------------

  DpTestComponentBase::DpContainer ::
    DpContainer(
        FwDpIdType id,
        const Fw::Buffer& buffer,
        FwDpIdType baseId
    ) :
      Fw::DpContainer(id, buffer),
      baseId(baseId)
  {

  }

  DpTestComponentBase::DpContainer ::
    DpContainer() :
      Fw::DpContainer(),
      baseId(0)
  {

  }

  Fw::SerializeStatus DpTestComponentBase::DpContainer ::
    serializeRecord_DataRecord(const FppTest::DpTest_Data& elt)
  {
    Fw::SerializeBufferBase& serializeRepr = this->buffer.getSerializeRepr();
    const FwSizeType newDataSize = dataSize +
      sizeof(FwDpIdType) +
      FppTest::DpTest_Data::SERIALIZED_SIZE;
    Fw::SerializeStatus status = Fw::FW_SERIALIZE_OK;
    if (DpContainer::Header::SIZE + newDataSize <= serializeRepr.getBuffCapacity()) {
      const FwDpIdType id = this->baseId + RecordId::DataRecord;
      status = serializeRepr.serialize(id);
      FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);
      status = serializeRepr.serialize(elt);
      FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);
      this->dataSize = newDataSize;
    }
    else {
      status = Fw::FW_SERIALIZE_NO_ROOM_LEFT;
    }
    return status;
  }

  Fw::SerializeStatus DpTestComponentBase::DpContainer ::
    serializeRecord_U32Record(U32 elt)
  {
    Fw::SerializeBufferBase& serializeRepr = this->buffer.getSerializeRepr();
    const FwDpIdType id = this->baseId + RecordId::U32Record;
    Fw::SerializeStatus status = serializeRepr.serialize(id);
    if (status == Fw::FW_SERIALIZE_OK) {
      status = serializeRepr.serialize(elt);
    }
    if (status == Fw::FW_SERIALIZE_OK) {
      this->dataSize += sizeof(FwDpIdType);
      this->dataSize += sizeof(U32);
    }
    return status;
  }

  Fw::SerializeStatus DpTestComponentBase::DpContainer ::
    serializeRecord_U8ArrayRecord(
        const U8* array,
        FwSizeType size
    )
  {
    FW_ASSERT(array != nullptr);
    Fw::SerializeBufferBase& serializeRepr = this->buffer.getSerializeRepr();
    const FwDpIdType id = this->baseId + RecordId::U8ArrayRecord;
    Fw::SerializeStatus status = serializeRepr.serialize(id);
    if (status == Fw::FW_SERIALIZE_OK) {
      status = serializeRepr.serialize(size);
    }
    if (status == Fw::FW_SERIALIZE_OK) {
      for (FwSizeType i = 0; i < size; i++) {
        status = serializeRepr.serialize(array[i]);
        if (status != Fw::FW_SERIALIZE_OK) {
          break;
        }
      }
    }
    if (status == Fw::FW_SERIALIZE_OK) {
      this->dataSize += sizeof(FwDpIdType);
      this->dataSize += sizeof(FwSizeType);
      this->dataSize += size * sizeof(U8);
    }
    return status;
  }

  // ----------------------------------------------------------------------
  // Component initialization
  // ----------------------------------------------------------------------

  void DpTestComponentBase ::
    init(
        NATIVE_INT_TYPE queueDepth,
        NATIVE_INT_TYPE instance
    )
  {
    // Initialize base class
    Fw::ActiveComponentBase::init(instance);

    // Connect input port productRecvIn
    for (
      PlatformIntType port = 0;
      port < static_cast<PlatformIntType>(this->getNum_productRecvIn_InputPorts());
      port++
    ) {
      this->m_productRecvIn_InputPort[port].init();
      this->m_productRecvIn_InputPort[port].addCallComp(
        this,
        m_p_productRecvIn_in
      );
      this->m_productRecvIn_InputPort[port].setPortNum(port);

#if FW_OBJECT_NAMES == 1
      char portName[120];
      (void) snprintf(
        portName,
        sizeof(portName),
        "%s_productRecvIn_InputPort[%" PRI_PlatformIntType "]",
        this->m_objName,
        port
      );
      this->m_productRecvIn_InputPort[port].setObjName(portName);
#endif
    }

    // Connect input port schedIn
    for (
      PlatformIntType port = 0;
      port < static_cast<PlatformIntType>(this->getNum_schedIn_InputPorts());
      port++
    ) {
      this->m_schedIn_InputPort[port].init();
      this->m_schedIn_InputPort[port].addCallComp(
        this,
        m_p_schedIn_in
      );
      this->m_schedIn_InputPort[port].setPortNum(port);

#if FW_OBJECT_NAMES == 1
      char portName[120];
      (void) snprintf(
        portName,
        sizeof(portName),
        "%s_schedIn_InputPort[%" PRI_PlatformIntType "]",
        this->m_objName,
        port
      );
      this->m_schedIn_InputPort[port].setObjName(portName);
#endif
    }

    // Connect output port productGetOut
    for (
      PlatformIntType port = 0;
      port < static_cast<PlatformIntType>(this->getNum_productGetOut_OutputPorts());
      port++
    ) {
      this->m_productGetOut_OutputPort[port].init();

#if FW_OBJECT_NAMES == 1
      char portName[120];
      (void) snprintf(
        portName,
        sizeof(portName),
        "%s_productGetOut_OutputPort[%" PRI_PlatformIntType "]",
        this->m_objName,
        port
      );
      this->m_productGetOut_OutputPort[port].setObjName(portName);
#endif
    }

    // Connect output port productRequestOut
    for (
      PlatformIntType port = 0;
      port < static_cast<PlatformIntType>(this->getNum_productRequestOut_OutputPorts());
      port++
    ) {
      this->m_productRequestOut_OutputPort[port].init();

#if FW_OBJECT_NAMES == 1
      char portName[120];
      (void) snprintf(
        portName,
        sizeof(portName),
        "%s_productRequestOut_OutputPort[%" PRI_PlatformIntType "]",
        this->m_objName,
        port
      );
      this->m_productRequestOut_OutputPort[port].setObjName(portName);
#endif
    }

    // Connect output port productSendOut
    for (
      PlatformIntType port = 0;
      port < static_cast<PlatformIntType>(this->getNum_productSendOut_OutputPorts());
      port++
    ) {
      this->m_productSendOut_OutputPort[port].init();

#if FW_OBJECT_NAMES == 1
      char portName[120];
      (void) snprintf(
        portName,
        sizeof(portName),
        "%s_productSendOut_OutputPort[%" PRI_PlatformIntType "]",
        this->m_objName,
        port
      );
      this->m_productSendOut_OutputPort[port].setObjName(portName);
#endif
    }

    // Connect output port timeGetOut
    for (
      PlatformIntType port = 0;
      port < static_cast<PlatformIntType>(this->getNum_timeGetOut_OutputPorts());
      port++
    ) {
      this->m_timeGetOut_OutputPort[port].init();

#if FW_OBJECT_NAMES == 1
      char portName[120];
      (void) snprintf(
        portName,
        sizeof(portName),
        "%s_timeGetOut_OutputPort[%" PRI_PlatformIntType "]",
        this->m_objName,
        port
      );
      this->m_timeGetOut_OutputPort[port].setObjName(portName);
#endif
    }

    Os::Queue::QueueStatus qStat = this->createQueue(
      queueDepth,
      ComponentIpcSerializableBuffer::SERIALIZATION_SIZE
    );
    FW_ASSERT(
      Os::Queue::QUEUE_OK == qStat,
      static_cast<FwAssertArgType>(qStat)
    );
  }

  // ----------------------------------------------------------------------
  // Getters for special input ports
  // ----------------------------------------------------------------------

  Fw::InputDpResponsePort* DpTestComponentBase ::
    get_productRecvIn_InputPort(NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(
      portNum < this->getNum_productRecvIn_InputPorts(),
      static_cast<FwAssertArgType>(portNum)
    );

    return &this->m_productRecvIn_InputPort[portNum];
  }

  // ----------------------------------------------------------------------
  // Getters for typed input ports
  // ----------------------------------------------------------------------

  Svc::InputSchedPort* DpTestComponentBase ::
    get_schedIn_InputPort(NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(
      portNum < this->getNum_schedIn_InputPorts(),
      static_cast<FwAssertArgType>(portNum)
    );

    return &this->m_schedIn_InputPort[portNum];
  }

  // ----------------------------------------------------------------------
  // Connect input ports to special output ports
  // ----------------------------------------------------------------------

  void DpTestComponentBase ::
    set_productGetOut_OutputPort(
        NATIVE_INT_TYPE portNum,
        Fw::InputDpGetPort* port
    )
  {
    FW_ASSERT(
      portNum < this->getNum_productGetOut_OutputPorts(),
      static_cast<FwAssertArgType>(portNum)
    );

    this->m_productGetOut_OutputPort[portNum].addCallPort(port);
  }

  void DpTestComponentBase ::
    set_productRequestOut_OutputPort(
        NATIVE_INT_TYPE portNum,
        Fw::InputDpRequestPort* port
    )
  {
    FW_ASSERT(
      portNum < this->getNum_productRequestOut_OutputPorts(),
      static_cast<FwAssertArgType>(portNum)
    );

    this->m_productRequestOut_OutputPort[portNum].addCallPort(port);
  }

  void DpTestComponentBase ::
    set_productSendOut_OutputPort(
        NATIVE_INT_TYPE portNum,
        Fw::InputDpSendPort* port
    )
  {
    FW_ASSERT(
      portNum < this->getNum_productSendOut_OutputPorts(),
      static_cast<FwAssertArgType>(portNum)
    );

    this->m_productSendOut_OutputPort[portNum].addCallPort(port);
  }

  void DpTestComponentBase ::
    set_timeGetOut_OutputPort(
        NATIVE_INT_TYPE portNum,
        Fw::InputTimePort* port
    )
  {
    FW_ASSERT(
      portNum < this->getNum_timeGetOut_OutputPorts(),
      static_cast<FwAssertArgType>(portNum)
    );

    this->m_timeGetOut_OutputPort[portNum].addCallPort(port);
  }

#if FW_PORT_SERIALIZATION

  // ----------------------------------------------------------------------
  // Connect serial input ports to special output ports
  // ----------------------------------------------------------------------

  void DpTestComponentBase ::
    set_productRequestOut_OutputPort(
        NATIVE_INT_TYPE portNum,
        Fw::InputSerializePort* port
    )
  {
    FW_ASSERT(
      portNum < this->getNum_productRequestOut_OutputPorts(),
      static_cast<FwAssertArgType>(portNum)
    );

    this->m_productRequestOut_OutputPort[portNum].registerSerialPort(port);
  }

  void DpTestComponentBase ::
    set_productSendOut_OutputPort(
        NATIVE_INT_TYPE portNum,
        Fw::InputSerializePort* port
    )
  {
    FW_ASSERT(
      portNum < this->getNum_productSendOut_OutputPorts(),
      static_cast<FwAssertArgType>(portNum)
    );

    this->m_productSendOut_OutputPort[portNum].registerSerialPort(port);
  }

  void DpTestComponentBase ::
    set_timeGetOut_OutputPort(
        NATIVE_INT_TYPE portNum,
        Fw::InputSerializePort* port
    )
  {
    FW_ASSERT(
      portNum < this->getNum_timeGetOut_OutputPorts(),
      static_cast<FwAssertArgType>(portNum)
    );

    this->m_timeGetOut_OutputPort[portNum].registerSerialPort(port);
  }

#endif

  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  DpTestComponentBase ::
    DpTestComponentBase(const char* compName) :
      Fw::ActiveComponentBase(compName)
  {

  }

  DpTestComponentBase ::
    ~DpTestComponentBase()
  {

  }

  // ----------------------------------------------------------------------
  // Getters for numbers of special input ports
  // ----------------------------------------------------------------------

  NATIVE_INT_TYPE DpTestComponentBase ::
    getNum_productRecvIn_InputPorts() const
  {
    return static_cast<NATIVE_INT_TYPE>(FW_NUM_ARRAY_ELEMENTS(this->m_productRecvIn_InputPort));
  }

  // ----------------------------------------------------------------------
  // Getters for numbers of typed input ports
  // ----------------------------------------------------------------------

  NATIVE_INT_TYPE DpTestComponentBase ::
    getNum_schedIn_InputPorts() const
  {
    return static_cast<NATIVE_INT_TYPE>(FW_NUM_ARRAY_ELEMENTS(this->m_schedIn_InputPort));
  }

  // ----------------------------------------------------------------------
  // Getters for numbers of special output ports
  // ----------------------------------------------------------------------

  NATIVE_INT_TYPE DpTestComponentBase ::
    getNum_productGetOut_OutputPorts() const
  {
    return static_cast<NATIVE_INT_TYPE>(FW_NUM_ARRAY_ELEMENTS(this->m_productGetOut_OutputPort));
  }

  NATIVE_INT_TYPE DpTestComponentBase ::
    getNum_productRequestOut_OutputPorts() const
  {
    return static_cast<NATIVE_INT_TYPE>(FW_NUM_ARRAY_ELEMENTS(this->m_productRequestOut_OutputPort));
  }

  NATIVE_INT_TYPE DpTestComponentBase ::
    getNum_productSendOut_OutputPorts() const
  {
    return static_cast<NATIVE_INT_TYPE>(FW_NUM_ARRAY_ELEMENTS(this->m_productSendOut_OutputPort));
  }

  NATIVE_INT_TYPE DpTestComponentBase ::
    getNum_timeGetOut_OutputPorts() const
  {
    return static_cast<NATIVE_INT_TYPE>(FW_NUM_ARRAY_ELEMENTS(this->m_timeGetOut_OutputPort));
  }

  // ----------------------------------------------------------------------
  // Connection status queries for special output ports
  // ----------------------------------------------------------------------

  bool DpTestComponentBase ::
    isConnected_productGetOut_OutputPort(NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(
      portNum < this->getNum_productGetOut_OutputPorts(),
      static_cast<FwAssertArgType>(portNum)
    );

    return this->m_productGetOut_OutputPort[portNum].isConnected();
  }

  bool DpTestComponentBase ::
    isConnected_productRequestOut_OutputPort(NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(
      portNum < this->getNum_productRequestOut_OutputPorts(),
      static_cast<FwAssertArgType>(portNum)
    );

    return this->m_productRequestOut_OutputPort[portNum].isConnected();
  }

  bool DpTestComponentBase ::
    isConnected_productSendOut_OutputPort(NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(
      portNum < this->getNum_productSendOut_OutputPorts(),
      static_cast<FwAssertArgType>(portNum)
    );

    return this->m_productSendOut_OutputPort[portNum].isConnected();
  }

  bool DpTestComponentBase ::
    isConnected_timeGetOut_OutputPort(NATIVE_INT_TYPE portNum)
  {
    FW_ASSERT(
      portNum < this->getNum_timeGetOut_OutputPorts(),
      static_cast<FwAssertArgType>(portNum)
    );

    return this->m_timeGetOut_OutputPort[portNum].isConnected();
  }

  // ----------------------------------------------------------------------
  // Port handler base-class functions for special input ports
  //
  // Call these functions directly to bypass the corresponding ports
  // ----------------------------------------------------------------------

  void DpTestComponentBase ::
    productRecvIn_handlerBase(
        NATIVE_INT_TYPE portNum,
        FwDpIdType id,
        const Fw::Buffer& buffer,
        const Fw::Success& status
    )
  {
    // Make sure port number is valid
    FW_ASSERT(
      portNum < this->getNum_productRecvIn_InputPorts(),
      static_cast<FwAssertArgType>(portNum)
    );

    // Call pre-message hook
    productRecvIn_preMsgHook(
      portNum,
      id,
      buffer,
      status
    );
    ComponentIpcSerializableBuffer msg;
    Fw::SerializeStatus _status = Fw::FW_SERIALIZE_OK;

    // Serialize message ID
    _status = msg.serialize(
      static_cast<NATIVE_INT_TYPE>(PRODUCTRECVIN_DPRESPONSE)
    );
    FW_ASSERT(
      _status == Fw::FW_SERIALIZE_OK,
      static_cast<FwAssertArgType>(_status)
    );

    // Serialize port number
    _status = msg.serialize(portNum);
    FW_ASSERT(
      _status == Fw::FW_SERIALIZE_OK,
      static_cast<FwAssertArgType>(_status)
    );

    // Serialize argument id
    _status = msg.serialize(id);
    FW_ASSERT(
      _status == Fw::FW_SERIALIZE_OK,
      static_cast<FwAssertArgType>(_status)
    );

    // Serialize argument buffer
    _status = msg.serialize(buffer);
    FW_ASSERT(
      _status == Fw::FW_SERIALIZE_OK,
      static_cast<FwAssertArgType>(_status)
    );

    // Serialize argument status
    _status = msg.serialize(status);
    FW_ASSERT(
      _status == Fw::FW_SERIALIZE_OK,
      static_cast<FwAssertArgType>(_status)
    );

    // Send message
    Os::Queue::QueueBlocking _block = Os::Queue::QUEUE_NONBLOCKING;
    Os::Queue::QueueStatus qStatus = this->m_queue.send(msg, 0, _block);

    FW_ASSERT(
      qStatus == Os::Queue::QUEUE_OK,
      static_cast<FwAssertArgType>(qStatus)
    );
  }

  // ----------------------------------------------------------------------
  // Port handler base-class functions for typed input ports
  //
  // Call these functions directly to bypass the corresponding ports
  // ----------------------------------------------------------------------

  void DpTestComponentBase ::
    schedIn_handlerBase(
        NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    // Make sure port number is valid
    FW_ASSERT(
      portNum < this->getNum_schedIn_InputPorts(),
      static_cast<FwAssertArgType>(portNum)
    );

    // Call pre-message hook
    schedIn_preMsgHook(
      portNum,
      context
    );
    ComponentIpcSerializableBuffer msg;
    Fw::SerializeStatus _status = Fw::FW_SERIALIZE_OK;

    // Serialize message ID
    _status = msg.serialize(
      static_cast<NATIVE_INT_TYPE>(SCHEDIN_SCHED)
    );
    FW_ASSERT(
      _status == Fw::FW_SERIALIZE_OK,
      static_cast<FwAssertArgType>(_status)
    );

    // Serialize port number
    _status = msg.serialize(portNum);
    FW_ASSERT(
      _status == Fw::FW_SERIALIZE_OK,
      static_cast<FwAssertArgType>(_status)
    );

    // Serialize argument context
    _status = msg.serialize(context);
    FW_ASSERT(
      _status == Fw::FW_SERIALIZE_OK,
      static_cast<FwAssertArgType>(_status)
    );

    // Send message
    Os::Queue::QueueBlocking _block = Os::Queue::QUEUE_NONBLOCKING;
    Os::Queue::QueueStatus qStatus = this->m_queue.send(msg, 0, _block);

    FW_ASSERT(
      qStatus == Os::Queue::QUEUE_OK,
      static_cast<FwAssertArgType>(qStatus)
    );
  }

  // ----------------------------------------------------------------------
  // Pre-message hooks for special async input ports
  //
  // Each of these functions is invoked just before processing a message
  // on the corresponding port. By default, they do nothing. You can
  // override them to provide specific pre-message behavior.
  // ----------------------------------------------------------------------

  void DpTestComponentBase ::
    productRecvIn_preMsgHook(
        NATIVE_INT_TYPE portNum,
        FwDpIdType id,
        const Fw::Buffer& buffer,
        const Fw::Success& status
    )
  {
    // Default: no-op
  }

  // ----------------------------------------------------------------------
  // Pre-message hooks for typed async input ports
  //
  // Each of these functions is invoked just before processing a message
  // on the corresponding port. By default, they do nothing. You can
  // override them to provide specific pre-message behavior.
  // ----------------------------------------------------------------------

  void DpTestComponentBase ::
    schedIn_preMsgHook(
        NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    // Default: no-op
  }

  // ----------------------------------------------------------------------
  // Invocation functions for special output ports
  // ----------------------------------------------------------------------

  Fw::Success DpTestComponentBase ::
    productGetOut_out(
        NATIVE_INT_TYPE portNum,
        FwDpIdType id,
        FwSizeType size,
        Fw::Buffer& buffer
    )
  {
    FW_ASSERT(
      portNum < this->getNum_productGetOut_OutputPorts(),
      static_cast<FwAssertArgType>(portNum)
    );
    return this->m_productGetOut_OutputPort[portNum].invoke(
      id,
      size,
      buffer
    );
  }

  void DpTestComponentBase ::
    productRequestOut_out(
        NATIVE_INT_TYPE portNum,
        FwDpIdType id,
        FwSizeType size
    )
  {
    FW_ASSERT(
      portNum < this->getNum_productRequestOut_OutputPorts(),
      static_cast<FwAssertArgType>(portNum)
    );
    this->m_productRequestOut_OutputPort[portNum].invoke(
      id,
      size
    );
  }

  void DpTestComponentBase ::
    productSendOut_out(
        NATIVE_INT_TYPE portNum,
        FwDpIdType id,
        const Fw::Buffer& buffer
    )
  {
    FW_ASSERT(
      portNum < this->getNum_productSendOut_OutputPorts(),
      static_cast<FwAssertArgType>(portNum)
    );
    this->m_productSendOut_OutputPort[portNum].invoke(
      id,
      buffer
    );
  }

  // ----------------------------------------------------------------------
  // Functions for managing data products
  // ----------------------------------------------------------------------

  void DpTestComponentBase ::
    dpSend(
        DpContainer& container,
        Fw::Time timeTag
    )
  {
    // Update the time tag
    if (timeTag == Fw::ZERO_TIME) {
      // Get the time from the time port
      timeTag = this->getTime();
    }
    container.setTimeTag(timeTag);
    // Serialize the header into the packet
    Fw::SerializeStatus status = container.serializeHeader();
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);
    // Update the size of the buffer according to the data size
    const FwSizeType packetSize = container.getPacketSize();
    Fw::Buffer buffer = container.getBuffer();
    FW_ASSERT(packetSize <= buffer.getSize(), packetSize, buffer.getSize());
    buffer.setSize(packetSize);
    // Send the buffer
    this->productSendOut_out(0, container.getId(), buffer);
  }

  // ----------------------------------------------------------------------
  // Time
  // ----------------------------------------------------------------------

  Fw::Time DpTestComponentBase ::
    getTime()
  {
    if (this->m_timeGetOut_OutputPort[0].isConnected()) {
      Fw::Time _time;
      this->m_timeGetOut_OutputPort[0].invoke(_time);
      return _time;
    }
    else {
      return Fw::Time(TB_NONE, 0, 0);
    }
  }

  // ----------------------------------------------------------------------
  // Message dispatch functions
  // ----------------------------------------------------------------------

  Fw::QueuedComponentBase::MsgDispatchStatus DpTestComponentBase ::
    doDispatch()
  {
    ComponentIpcSerializableBuffer msg;
    NATIVE_INT_TYPE priority = 0;

    Os::Queue::QueueStatus msgStatus = this->m_queue.receive(
      msg,
      priority,
      Os::Queue::QUEUE_BLOCKING
    );
    FW_ASSERT(
      msgStatus == Os::Queue::QUEUE_OK,
      static_cast<FwAssertArgType>(msgStatus)
    );

    // Reset to beginning of buffer
    msg.resetDeser();

    NATIVE_INT_TYPE desMsg = 0;
    Fw::SerializeStatus deserStatus = msg.deserialize(desMsg);
    FW_ASSERT(
      deserStatus == Fw::FW_SERIALIZE_OK,
      static_cast<FwAssertArgType>(deserStatus)
    );

    MsgTypeEnum msgType = static_cast<MsgTypeEnum>(desMsg);

    if (msgType == DPTEST_COMPONENT_EXIT) {
      return MSG_DISPATCH_EXIT;
    }

    NATIVE_INT_TYPE portNum = 0;
    deserStatus = msg.deserialize(portNum);
    FW_ASSERT(
      deserStatus == Fw::FW_SERIALIZE_OK,
      static_cast<FwAssertArgType>(deserStatus)
    );

    switch (msgType) {
      // Handle async input port productRecvIn
      case PRODUCTRECVIN_DPRESPONSE: {
        // Deserialize argument id
        FwDpIdType id;
        deserStatus = msg.deserialize(id);
        FW_ASSERT(
          deserStatus == Fw::FW_SERIALIZE_OK,
          static_cast<FwAssertArgType>(deserStatus)
        );

        // Deserialize argument buffer
        Fw::Buffer buffer;
        deserStatus = msg.deserialize(buffer);
        FW_ASSERT(
          deserStatus == Fw::FW_SERIALIZE_OK,
          static_cast<FwAssertArgType>(deserStatus)
        );

        // Deserialize argument status
        Fw::Success status;
        deserStatus = msg.deserialize(status);
        FW_ASSERT(
          deserStatus == Fw::FW_SERIALIZE_OK,
          static_cast<FwAssertArgType>(deserStatus)
        );
        // Call handler function
        this->productRecvIn_handler(
          portNum,
          id,
          buffer,
          status
        );

        break;
      }

      // Handle async input port schedIn
      case SCHEDIN_SCHED: {
        // Deserialize argument context
        NATIVE_UINT_TYPE context;
        deserStatus = msg.deserialize(context);
        FW_ASSERT(
          deserStatus == Fw::FW_SERIALIZE_OK,
          static_cast<FwAssertArgType>(deserStatus)
        );
        // Call handler function
        this->schedIn_handler(
          portNum,
          context
        );

        break;
      }

      default:
        return MSG_DISPATCH_ERROR;
    }

    return MSG_DISPATCH_OK;
  }

  // ----------------------------------------------------------------------
  // Calls for messages received on special input ports
  // ----------------------------------------------------------------------

  void DpTestComponentBase ::
    m_p_productRecvIn_in(
        Fw::PassiveComponentBase* callComp,
        NATIVE_INT_TYPE portNum,
        FwDpIdType id,
        const Fw::Buffer& buffer,
        const Fw::Success& status
    )
  {
    FW_ASSERT(callComp);
    DpTestComponentBase* compPtr = static_cast<DpTestComponentBase*>(callComp);
    compPtr->productRecvIn_handlerBase(
      portNum,
      id,
      buffer,
      status
    );
  }

  // ----------------------------------------------------------------------
  // Calls for messages received on typed input ports
  // ----------------------------------------------------------------------

  void DpTestComponentBase ::
    m_p_schedIn_in(
        Fw::PassiveComponentBase* callComp,
        NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    FW_ASSERT(callComp);
    DpTestComponentBase* compPtr = static_cast<DpTestComponentBase*>(callComp);
    compPtr->schedIn_handlerBase(
      portNum,
      context
    );
  }

  // ----------------------------------------------------------------------
  // Private data product handling functions
  // ----------------------------------------------------------------------

  Fw::Success::T DpTestComponentBase ::
    dpGet(
        ContainerId::T containerId,
        FwSizeType size,
        DpContainer& container
    )
  {
    const FwDpIdType baseId = this->getIdBase();
    const FwDpIdType globalId = baseId + containerId;
    Fw::Buffer buffer;
    const Fw::Success::T status = this->productGetOut_out(0, globalId, size, buffer);
    if (status == Fw::Success::SUCCESS) {
      container.setId(globalId);
      container.setBuffer(buffer);
      container.setBaseId(baseId);
    }
    return status;
  }

  void DpTestComponentBase ::
    dpRequest(
        ContainerId::T containerId,
        FwSizeType size
    )
  {
    const FwDpIdType globalId = this->getIdBase() + containerId;
    this->productRequestOut_out(0, globalId, size);
  }

  void DpTestComponentBase ::
    productRecvIn_handler(
        const NATIVE_INT_TYPE portNum,
        FwDpIdType id,
        const Fw::Buffer& buffer,
        const Fw::Success& status
    )
  {
    DpContainer container(id, buffer, this->getIdBase());
    // Convert global id to local id
    const auto idBase = this->getIdBase();
    FW_ASSERT(id >= idBase, id, idBase);
    const auto localId = id - idBase;
    // Switch on the local id
    switch (localId) {
      case ContainerId::Container1:
        // Set the priority
        container.setPriority(ContainerPriority::Container1);
        // Call the handler
        this->dpRecv_Container1_handler(container, status.e);
        break;
      case ContainerId::Container2:
        // Set the priority
        container.setPriority(ContainerPriority::Container2);
        // Call the handler
        this->dpRecv_Container2_handler(container, status.e);
        break;
      case ContainerId::Container3:
        // Set the priority
        container.setPriority(ContainerPriority::Container3);
        // Call the handler
        this->dpRecv_Container3_handler(container, status.e);
        break;
      default:
        FW_ASSERT(0);
        break;
    }
  }

}
