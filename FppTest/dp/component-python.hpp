// ======================================================================
// \title  DpTestComponentAc.hpp
// \author Auto-generated
// \brief  hpp file for DpTest component base class
//
// NOTE: this file was automatically generated
//
// ======================================================================

#ifndef FPPTEST_DPTEST_COMP_HPP_
#define FPPTEST_DPTEST_COMP_HPP_

#include <FpConfig.hpp>
#include <Fw/Port/InputSerializePort.hpp>
#include <Fw/Port/OutputSerializePort.hpp>
#include <Fw/Comp/ActiveComponentBase.hpp>
#include <Fw/Types/SuccessEnumAc.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Time/Time.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Buffer/Buffer.hpp>
#include <Fw/Time/Time.hpp>
#include <Fw/Dp/DpRequestPortAc.hpp>
#include <Fw/Dp/DpResponsePortAc.hpp>
#include <Fw/Dp/DpSendPortAc.hpp>
#include <Fw/Time/TimePortAc.hpp>
#include <Svc/Sched/SchedPortAc.hpp>
#include <FppTest/dp/DpTest_DataSerializableAc.hpp>

namespace FppTest {

  //! \class DpTestComponentBase
  //! \brief Auto-generated base for DpTest component
  //!
  class DpTestComponentBase :
    public Fw::ActiveComponentBase
  {

    // ----------------------------------------------------------------------
    // Friend classes
    // ----------------------------------------------------------------------

    //! Friend class for white-box testing
    //!
    friend class DpTestComponentBaseFriend;

  public:

    // ----------------------------------------------------------------------
    // Getters for typed input ports
    // ----------------------------------------------------------------------

    //! Get input port at index
    //!
    //! \return productRecvIn[portNum]
    //!
    Fw::InputDpResponsePort* get_productRecvIn_InputPort(
        NATIVE_INT_TYPE portNum /*!< The port number*/
    );

    //! Get input port at index
    //!
    //! \return schedIn[portNum]
    //!
    Svc::InputSchedPort* get_schedIn_InputPort(
        NATIVE_INT_TYPE portNum /*!< The port number*/
    );

  public:

    // ----------------------------------------------------------------------
    // Connect typed input ports to typed output ports
    // ----------------------------------------------------------------------

    //! Connect port to productRequestOut[portNum]
    //!
    void set_productRequestOut_OutputPort(
        NATIVE_INT_TYPE portNum, /*!< The port number*/
        Fw::InputDpRequestPort *port /*!< The port*/
    );

    //! Connect port to productSendOut[portNum]
    //!
    void set_productSendOut_OutputPort(
        NATIVE_INT_TYPE portNum, /*!< The port number*/
        Fw::InputDpSendPort *port /*!< The port*/
    );

    //! Connect port to timeGetOut[portNum]
    //!
    void set_timeGetOut_OutputPort(
        NATIVE_INT_TYPE portNum, /*!< The port number*/
        Fw::InputTimePort *port /*!< The port*/
    );

#if FW_PORT_SERIALIZATION

  public:

    // ----------------------------------------------------------------------
    // Connect serialization input ports to typed output ports
    // ----------------------------------------------------------------------

    //! Connect port to productRequestOut[portNum]
    //!
    void set_productRequestOut_OutputPort(
        NATIVE_INT_TYPE portNum, /*!< The port number*/
        Fw::InputSerializePort *port /*!< The port*/
    );

    //! Connect port to productSendOut[portNum]
    //!
    void set_productSendOut_OutputPort(
        NATIVE_INT_TYPE portNum, /*!< The port number*/
        Fw::InputSerializePort *port /*!< The port*/
    );

    //! Connect port to timeGetOut[portNum]
    //!
    void set_timeGetOut_OutputPort(
        NATIVE_INT_TYPE portNum, /*!< The port number*/
        Fw::InputSerializePort *port /*!< The port*/
    );

#endif

  PROTECTED:

    // ----------------------------------------------------------------------
    // Component construction, initialization, and destruction
    // ----------------------------------------------------------------------

    //! Construct a DpTestComponentBase object
    //!
    DpTestComponentBase(
        const char* compName = "" /*!< Component name*/
    );

  public:
    //! Initialize a DpTestComponentBase object
    //!
    void init(
        NATIVE_INT_TYPE queueDepth, /*!< The queue depth*/
        NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
    );

  PROTECTED:
    //! Destroy a DpTestComponentBase object
    //!
    virtual ~DpTestComponentBase();

  PROTECTED:

    // ----------------------------------------------------------------------
    // Handlers to implement for typed input ports
    // ----------------------------------------------------------------------

    //! Handler for input port productRecvIn
    //
    virtual void productRecvIn_handler(
        NATIVE_INT_TYPE portNum, /*!< The port number*/
        FwDpIdType id, /*!< 
      The container ID
      */
        const Fw::Buffer &buffer, /*!< 
      The buffer
      */
        const Fw::Success &status /*!< 
      The status
      */
    ) = 0;

    //! Handler for input port schedIn
    //
    virtual void schedIn_handler(
        NATIVE_INT_TYPE portNum, /*!< The port number*/
        NATIVE_UINT_TYPE context /*!< 
      The call order
      */
    ) = 0;

  PROTECTED:

    // ----------------------------------------------------------------------
    // Port handler base-class functions for typed input ports.
    // ----------------------------------------------------------------------
    // Call these functions directly to bypass the corresponding ports.
    // ----------------------------------------------------------------------

    //! Handler base-class function for input port productRecvIn
    //!
    void productRecvIn_handlerBase(
        NATIVE_INT_TYPE portNum, /*!< The port number*/
        FwDpIdType id, /*!< 
      The container ID
      */
        const Fw::Buffer &buffer, /*!< 
      The buffer
      */
        const Fw::Success &status /*!< 
      The status
      */
    );

    //! Handler base-class function for input port schedIn
    //!
    void schedIn_handlerBase(
        NATIVE_INT_TYPE portNum, /*!< The port number*/
        NATIVE_UINT_TYPE context /*!< 
      The call order
      */
    );

  PROTECTED:

    // ----------------------------------------------------------------------
    // Pre-message hooks for typed async input ports.
    // ----------------------------------------------------------------------
    // Each of these functions is invoked just before processing a message
    // on the corresponding port. By default they do nothing. You can
    // override them to provide specific pre-message behavior.
    // ----------------------------------------------------------------------

    //! Pre-message hook for async input port productRecvIn
    //!
    virtual void productRecvIn_preMsgHook(
        NATIVE_INT_TYPE portNum, /*!< The port number*/
        FwDpIdType id, /*!< 
      The container ID
      */
        const Fw::Buffer &buffer, /*!< 
      The buffer
      */
        const Fw::Success &status /*!< 
      The status
      */
    );

    //! Pre-message hook for async input port schedIn
    //!
    virtual void schedIn_preMsgHook(
        NATIVE_INT_TYPE portNum, /*!< The port number*/
        NATIVE_UINT_TYPE context /*!< 
      The call order
      */
    );

  PROTECTED:

    // ----------------------------------------------------------------------
    // Invocation functions for typed output ports
    // ----------------------------------------------------------------------

    //! Invoke output port productRequestOut
    //!
    void productRequestOut_out(
        NATIVE_INT_TYPE portNum, /*!< The port number*/
        FwDpIdType id, /*!< 
      The container ID
      */
        FwSizeType size /*!< 
      The size of the requested buffer
      */
    );

    //! Invoke output port productSendOut
    //!
    void productSendOut_out(
        NATIVE_INT_TYPE portNum, /*!< The port number*/
        FwDpIdType id, /*!< 
      The container ID
      */
        const Fw::Buffer &buffer /*!< 
      The buffer
      */
    );

  PROTECTED:

    // ----------------------------------------------------------------------
    // Getters for numbers of input ports
    // ----------------------------------------------------------------------

    //! Get the number of productRecvIn input ports
    //!
    //! \return The number of productRecvIn input ports
    //!
    NATIVE_INT_TYPE getNum_productRecvIn_InputPorts();

    //! Get the number of schedIn input ports
    //!
    //! \return The number of schedIn input ports
    //!
    NATIVE_INT_TYPE getNum_schedIn_InputPorts();


    // ----------------------------------------------------------------------
    // Enumerations for number of ports
    // ----------------------------------------------------------------------

    enum {
       NUM_PRODUCTRECVIN_INPUT_PORTS = 1,
       NUM_SCHEDIN_INPUT_PORTS = 1,
    };

  PROTECTED:

    // ----------------------------------------------------------------------
    // Getters for numbers of output ports
    // ----------------------------------------------------------------------

    //! Get the number of productRequestOut output ports
    //!
    //! \return The number of productRequestOut output ports
    //!
    NATIVE_INT_TYPE getNum_productRequestOut_OutputPorts();

    //! Get the number of productSendOut output ports
    //!
    //! \return The number of productSendOut output ports
    //!
    NATIVE_INT_TYPE getNum_productSendOut_OutputPorts();

    //! Get the number of timeGetOut output ports
    //!
    //! \return The number of timeGetOut output ports
    //!
    NATIVE_INT_TYPE getNum_timeGetOut_OutputPorts();


    enum {
       NUM_PRODUCTREQUESTOUT_OUTPUT_PORTS = 1,
       NUM_PRODUCTSENDOUT_OUTPUT_PORTS = 1,
       NUM_TIMEGETOUT_OUTPUT_PORTS = 1,
    };

  PROTECTED:

    // ----------------------------------------------------------------------
    // Connection status queries for output ports
    // ----------------------------------------------------------------------

    //! Check whether port productRequestOut is connected
    //!
    //! \return Whether port productRequestOut is connected
    //!
    bool isConnected_productRequestOut_OutputPort(
        NATIVE_INT_TYPE portNum /*!< The port number*/
    );

    //! Check whether port productSendOut is connected
    //!
    //! \return Whether port productSendOut is connected
    //!
    bool isConnected_productSendOut_OutputPort(
        NATIVE_INT_TYPE portNum /*!< The port number*/
    );

    //! Check whether port timeGetOut is connected
    //!
    //! \return Whether port timeGetOut is connected
    //!
    bool isConnected_timeGetOut_OutputPort(
        NATIVE_INT_TYPE portNum /*!< The port number*/
    );

  PROTECTED:

    // ----------------------------------------------------------------------
    // Event logging functions
    // ----------------------------------------------------------------------

  PROTECTED:

    // ----------------------------------------------------------------------
    // Time
    // ----------------------------------------------------------------------

    //! Get the time
    //!
    //! \return The current time
    //!
    Fw::Time getTime();



  PRIVATE:

    // ----------------------------------------------------------------------
    // Typed input ports
    // ----------------------------------------------------------------------

    //! Input port productRecvIn
    //!
    Fw::InputDpResponsePort m_productRecvIn_InputPort[NUM_PRODUCTRECVIN_INPUT_PORTS];

    //! Input port schedIn
    //!
    Svc::InputSchedPort m_schedIn_InputPort[NUM_SCHEDIN_INPUT_PORTS];

  PRIVATE:

    // ----------------------------------------------------------------------
    // Typed output ports
    // ----------------------------------------------------------------------

    //! Output port productRequestOut
    //!
    Fw::OutputDpRequestPort m_productRequestOut_OutputPort[NUM_PRODUCTREQUESTOUT_OUTPUT_PORTS];

    //! Output port productSendOut
    //!
    Fw::OutputDpSendPort m_productSendOut_OutputPort[NUM_PRODUCTSENDOUT_OUTPUT_PORTS];

    //! Output port timeGetOut
    //!
    Fw::OutputTimePort m_timeGetOut_OutputPort[NUM_TIMEGETOUT_OUTPUT_PORTS];

  PRIVATE:

    // ----------------------------------------------------------------------
    // Calls for messages received on typed input ports
    // ----------------------------------------------------------------------

    //! Callback for port productRecvIn
    //!
    static void m_p_productRecvIn_in(
        Fw::PassiveComponentBase* callComp, /*!< The component instance*/
        NATIVE_INT_TYPE portNum, /*!< The port number*/
        FwDpIdType id, /*!< 
      The container ID
      */
        const Fw::Buffer &buffer, /*!< 
      The buffer
      */
        const Fw::Success &status /*!< 
      The status
      */
    );

    //! Callback for port schedIn
    //!
    static void m_p_schedIn_in(
        Fw::PassiveComponentBase* callComp, /*!< The component instance*/
        NATIVE_INT_TYPE portNum, /*!< The port number*/
        NATIVE_UINT_TYPE context /*!< 
      The call order
      */
    );

  PRIVATE:

    // ----------------------------------------------------------------------
    // Message dispatch functions
    // ----------------------------------------------------------------------

    //! Called in the message loop to dispatch a message from the queue
    //!
    virtual MsgDispatchStatus doDispatch();



  };

} // end namespace FppTest
#endif
