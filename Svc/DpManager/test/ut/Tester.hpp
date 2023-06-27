// ======================================================================
// \title  DpManager/test/ut/Tester.hpp
// \author bocchino
// \brief  hpp file for DpManager test harness implementation class
// ======================================================================

#ifndef TESTER_HPP
#define TESTER_HPP

#include "GTestBase.hpp"
#include "Svc/DpManager/DpManager.hpp"
#include "Svc/DpManager/test/ut/AbstractState.hpp"

namespace Svc {

  class Tester :
    public DpManagerGTestBase
  {

      // ----------------------------------------------------------------------
      // Constants
      // ----------------------------------------------------------------------

    private:
      
      //! The maximum buffer size
      static constexpr FwSizeType MAX_BUFFER_SIZE = 1024;

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

    public:
      // Maximum size of histories storing events, telemetry, and port outputs
      static const NATIVE_INT_TYPE MAX_HISTORY_SIZE = 10;
      // Instance ID supplied to the component instance under test
      static const NATIVE_INT_TYPE TEST_INSTANCE_ID = 0;
      // Queue depth supplied to component instance under test
      static const NATIVE_INT_TYPE TEST_INSTANCE_QUEUE_DEPTH = 10;

      //! Construct object Tester
      Tester();

      //! Destroy object Tester
      ~Tester();

    public:

      // ----------------------------------------------------------------------
      // Tests
      // ----------------------------------------------------------------------

      //! To do
      void toDo();

    private:

      // ----------------------------------------------------------------------
      // Handlers for typed from ports
      // ----------------------------------------------------------------------

      //! Handler for from_bufferGetOut
      Fw::Buffer from_bufferGetOut_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          U32 size //!< The size
      );

      //! Handler for from_productResponseOut
      void from_productResponseOut_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          FwDpIdType id, //!< The container ID
          const Fw::Buffer &buffer //!< The buffer
      );

      //! Handler for from_productSendOut
      void from_productSendOut_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          Fw::Buffer &fwBuffer //!< The buffer
      );

    private:

      // ----------------------------------------------------------------------
      // Helper methods
      // ----------------------------------------------------------------------

      //! Connect ports
      void connectPorts();

      //! Initialize components
      void initComponents();

    private:

      // ----------------------------------------------------------------------
      // Variables
      // ----------------------------------------------------------------------

      //! The abstract state
      AbstractState abstractState;

      //! The component under test
      DpManager component;

      //! Data for buffers
      U8 bufferData[MAX_BUFFER_SIZE];

  };

} // end namespace Svc

#endif