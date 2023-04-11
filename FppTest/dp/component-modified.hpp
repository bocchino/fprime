// ======================================================================
// \title  DpTestComponentAc.hpp
// \author Generated by fpp-to-cpp
// \brief  hpp file for DpTest component base class
// ======================================================================

#ifndef FppTest_DpTestComponentAc_HPP
#define FppTest_DpTestComponentAc_HPP

#include "FpConfig.hpp"
#include "FppTest/dp/DpTest_DataSerializableAc.hpp"
#include "Fw/Comp/ActiveComponentBase.hpp"
#include "Fw/Dp/DpRequestPortAc.hpp"
#include "Fw/Dp/DpResponsePortAc.hpp"
#include "Fw/Dp/DpSendPortAc.hpp"
#include "Fw/Port/InputSerializePort.hpp"
#include "Fw/Port/OutputSerializePort.hpp"
#include "Fw/Time/TimePortAc.hpp"
#include "Svc/Sched/SchedPortAc.hpp"

namespace FppTest {

  //! \class DpTestComponentBase
  //! \brief Auto-generated base for DpTest component
  //!
  //! A component for testing  data product code gen
  class DpTestComponentBase :
    public Fw::ActiveComponentBase
  {

      // ----------------------------------------------------------------------
      // Friend classes
      // ----------------------------------------------------------------------

      //! Friend class for white-box testing
      friend class DpTestComponentBaseFriend;

    PROTECTED:

      // ----------------------------------------------------------------------
      // Constants
      // ----------------------------------------------------------------------

      //! Enumerations for numbers of special input ports
      enum {
        NUM_PRODUCTRECVIN_INPUT_PORTS = 1,
      };

      //! Enumerations for numbers of typed input ports
      enum {
        NUM_SCHEDIN_INPUT_PORTS = 1,
      };

      //! Enumerations for numbers of special output ports
      enum {
        NUM_PRODUCTREQUESTOUT_OUTPUT_PORTS = 1,
        NUM_PRODUCTSENDOUT_OUTPUT_PORTS = 1,
        NUM_TIMEGETOUT_OUTPUT_PORTS = 1,
      };

    public:

      // ----------------------------------------------------------------------
      // Component initialization
      // ----------------------------------------------------------------------

      //! Initialize DpTestComponentBase object
      void init(
          NATIVE_INT_TYPE queueDepth, //!< The queue depth
          NATIVE_INT_TYPE instance = 0 //!< The instance number
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for special input ports
      // ----------------------------------------------------------------------

      //! Get special input port at index
      //!
      //! \return productRecvIn[portNum]
      Fw::InputDpResponsePort* get_productRecvIn_InputPort(
          NATIVE_INT_TYPE portNum //!< The port number
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for typed input ports
      // ----------------------------------------------------------------------

      //! Get typed input port at index
      //!
      //! \return schedIn[portNum]
      Svc::InputSchedPort* get_schedIn_InputPort(
          NATIVE_INT_TYPE portNum //!< The port number
      );

    public:

      // ----------------------------------------------------------------------
      // Connect input ports to special output ports
      // ----------------------------------------------------------------------

      //! Connect port to productRequestOut[portNum]
      void set_productRequestOut_OutputPort(
          NATIVE_INT_TYPE portNum, //!< The port number
          Fw::InputDpRequestPort* port //!< The input port
      );

      //! Connect port to productSendOut[portNum]
      void set_productSendOut_OutputPort(
          NATIVE_INT_TYPE portNum, //!< The port number
          Fw::InputDpSendPort* port //!< The input port
      );

      //! Connect port to timeGetOut[portNum]
      void set_timeGetOut_OutputPort(
          NATIVE_INT_TYPE portNum, //!< The port number
          Fw::InputTimePort* port //!< The input port
      );

#if FW_PORT_SERIALIZATION

    public:

      // ----------------------------------------------------------------------
      // Connect serial input ports to special output ports
      // ----------------------------------------------------------------------

      //! Connect port to productRequestOut[portNum]
      void set_productRequestOut_OutputPort(
          NATIVE_INT_TYPE portNum, //!< The port number
          Fw::InputSerializePort* port //!< The port
      );

      //! Connect port to productSendOut[portNum]
      void set_productSendOut_OutputPort(
          NATIVE_INT_TYPE portNum, //!< The port number
          Fw::InputSerializePort* port //!< The port
      );

      //! Connect port to timeGetOut[portNum]
      void set_timeGetOut_OutputPort(
          NATIVE_INT_TYPE portNum, //!< The port number
          Fw::InputSerializePort* port //!< The port
      );

#endif

    PROTECTED:

      // ----------------------------------------------------------------------
      // Component construction and destruction
      // ----------------------------------------------------------------------

      //! Construct DpTestComponentBase object
      DpTestComponentBase(
          const char* compName = "" //!< The component name
      );

      //! Destroy DpTestComponentBase object
      virtual ~DpTestComponentBase();

    PROTECTED:

      // ----------------------------------------------------------------------
      // Getters for numbers of special input ports
      // ----------------------------------------------------------------------

      //! Get the number of productRecvIn input ports
      //!
      //! \return The number of productRecvIn input ports
      NATIVE_INT_TYPE getNum_productRecvIn_InputPorts();

    PROTECTED:

      // ----------------------------------------------------------------------
      // Getters for numbers of typed input ports
      // ----------------------------------------------------------------------

      //! Get the number of schedIn input ports
      //!
      //! \return The number of schedIn input ports
      NATIVE_INT_TYPE getNum_schedIn_InputPorts();

    PROTECTED:

      // ----------------------------------------------------------------------
      // Getters for numbers of special output ports
      // ----------------------------------------------------------------------

      //! Get the number of productRequestOut output ports
      //!
      //! \return The number of productRequestOut output ports
      NATIVE_INT_TYPE getNum_productRequestOut_OutputPorts();

      //! Get the number of productSendOut output ports
      //!
      //! \return The number of productSendOut output ports
      NATIVE_INT_TYPE getNum_productSendOut_OutputPorts();

      //! Get the number of timeGetOut output ports
      //!
      //! \return The number of timeGetOut output ports
      NATIVE_INT_TYPE getNum_timeGetOut_OutputPorts();

    PROTECTED:

      // ----------------------------------------------------------------------
      // Connection status queries for special output ports
      // ----------------------------------------------------------------------

      //! Check whether port productRequestOut is connected
      //!
      //! \return Whether port productRequestOut is connected
      bool isConnected_productRequestOut_OutputPort(
          NATIVE_INT_TYPE portNum //!< The port number
      );

      //! Check whether port productSendOut is connected
      //!
      //! \return Whether port productSendOut is connected
      bool isConnected_productSendOut_OutputPort(
          NATIVE_INT_TYPE portNum //!< The port number
      );

      //! Check whether port timeGetOut is connected
      //!
      //! \return Whether port timeGetOut is connected
      bool isConnected_timeGetOut_OutputPort(
          NATIVE_INT_TYPE portNum //!< The port number
      );

    PROTECTED:

      // ----------------------------------------------------------------------
      // Handlers to implement for special input ports
      // ----------------------------------------------------------------------

      //! Handler for input port productRecvIn
      virtual void productRecvIn_handler(
          NATIVE_INT_TYPE portNum, //!< The port number
          FwDpIdType id, //!< The container ID
          const Fw::Buffer &buffer, //!< The buffer
          const Fw::Success &status //!< The status
      ) = 0;

    PROTECTED:

      // ----------------------------------------------------------------------
      // Handlers to implement for typed input ports
      // ----------------------------------------------------------------------

      //! Handler for input port schedIn
      virtual void schedIn_handler(
          NATIVE_INT_TYPE portNum, //!< The port number
          NATIVE_UINT_TYPE context //!< The call order
      ) = 0;

    PROTECTED:

      // ----------------------------------------------------------------------
      // Port handler base-class functions for special input ports
      //
      // Call these functions directly to bypass the corresponding ports
      // ----------------------------------------------------------------------

      //! Handler base-class function for input port productRecvIn
      void productRecvIn_handlerBase(
          NATIVE_INT_TYPE portNum, //!< The port number
          FwDpIdType id, //!< The container ID
          const Fw::Buffer &buffer, //!< The buffer
          const Fw::Success &status //!< The status
      );

    PROTECTED:

      // ----------------------------------------------------------------------
      // Port handler base-class functions for typed input ports
      //
      // Call these functions directly to bypass the corresponding ports
      // ----------------------------------------------------------------------

      //! Handler base-class function for input port schedIn
      void schedIn_handlerBase(
          NATIVE_INT_TYPE portNum, //!< The port number
          NATIVE_UINT_TYPE context //!< The call order
      );

    PROTECTED:

      // ----------------------------------------------------------------------
      // Pre-message hooks for special async input ports
      //
      // Each of these functions is invoked just before processing a message
      // on the corresponding port. By default, they do nothing. You can
      // override them to provide specific pre-message behavior.
      // ----------------------------------------------------------------------

      //! Pre-message hook for async input port productRecvIn
      //!
      virtual void productRecvIn_preMsgHook(
          NATIVE_INT_TYPE portNum, //!< The port number
          FwDpIdType id, //!< The container ID
          const Fw::Buffer &buffer, //!< The buffer
          const Fw::Success &status //!< The status
      );

    PROTECTED:

      // ----------------------------------------------------------------------
      // Pre-message hooks for typed async input ports
      //
      // Each of these functions is invoked just before processing a message
      // on the corresponding port. By default, they do nothing. You can
      // override them to provide specific pre-message behavior.
      // ----------------------------------------------------------------------

      //! Pre-message hook for async input port schedIn
      virtual void schedIn_preMsgHook(
          NATIVE_INT_TYPE portNum, //!< The port number
          NATIVE_UINT_TYPE context //!< The call order
      );

    PROTECTED:

      // ----------------------------------------------------------------------
      // Invocation functions for typed output ports
      // ----------------------------------------------------------------------

      //! Invoke output port productRequestOut
      //!
      void productRequestOut_out(
          NATIVE_INT_TYPE portNum, //!< The port number
          FwDpIdType id, //!< The container ID
          FwSizeType size //!< The size of the requested buffer
      );

      //! Invoke output port productSendOut
      //!
      void productSendOut_out(
          NATIVE_INT_TYPE portNum, //!< The port number
          FwDpIdType id, //!< The container ID
          const Fw::Buffer &buffer //!< The buffer
      );

    PROTECTED:

      // ----------------------------------------------------------------------
      // Time
      // ----------------------------------------------------------------------

      //!  Get the time
      //!
      //! \\return The current time
      Fw::Time getTime();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Message dispatch functions
      // ----------------------------------------------------------------------

      //! Called in the message loop to dispatch a message from the queue
      virtual MsgDispatchStatus doDispatch();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Calls for messages received on special input ports
      // ----------------------------------------------------------------------

      //! Callback for port productRecvIn
      static void m_p_productRecvIn_in(
          Fw::PassiveComponentBase* callComp, //!< The component instance
          NATIVE_INT_TYPE portNum, //!< The port number
          FwDpIdType id, //!< The container ID
          const Fw::Buffer &buffer, //!< The buffer
          const Fw::Success &status //!< The status
      );
      
    PRIVATE:

      // ----------------------------------------------------------------------
      // Calls for messages received on typed input ports
      // ----------------------------------------------------------------------

      //! Callback for port schedIn
      static void m_p_schedIn_in(
          Fw::PassiveComponentBase* callComp, //!< The component instance
          NATIVE_INT_TYPE portNum, //!< The port number
          NATIVE_UINT_TYPE context //!< The call order
      );

    PRIVATE:

      // ----------------------------------------------------------------------
      // Special input ports
      // ----------------------------------------------------------------------

      //! Input port productRecvIn
      Fw::InputDpResponsePort m_productRecvIn_InputPort[NUM_PRODUCTRECVIN_INPUT_PORTS];

    PRIVATE:

      // ----------------------------------------------------------------------
      // Typed input ports
      // ----------------------------------------------------------------------

      //! Input port schedIn
      Svc::InputSchedPort m_schedIn_InputPort[NUM_SCHEDIN_INPUT_PORTS];

    PRIVATE:

      // ----------------------------------------------------------------------
      // Special output ports
      // ----------------------------------------------------------------------

      //! Output port productRequestOut
      Fw::OutputDpRequestPort m_productRequestOut_OutputPort[NUM_PRODUCTREQUESTOUT_OUTPUT_PORTS];

      //! Output port productSendOut
      Fw::OutputDpSendPort m_productSendOut_OutputPort[NUM_PRODUCTSENDOUT_OUTPUT_PORTS];

      //! Output port timeGetOut
      Fw::OutputTimePort m_timeGetOut_OutputPort[NUM_TIMEGETOUT_OUTPUT_PORTS];

  };

}

#endif
