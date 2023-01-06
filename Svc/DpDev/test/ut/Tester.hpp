// ======================================================================
// \title  DpDev/test/ut/Tester.hpp
// \author bocchino
// \brief  hpp file for DpDev test harness implementation class
// ======================================================================

#ifndef TESTER_HPP
#define TESTER_HPP

#include "GTestBase.hpp"
#include "Svc/DpDev/DpDev.hpp"

namespace Svc {

  class Tester :
    public DpDevGTestBase
  {

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
      //!
      Tester();

      //! Destroy object Tester
      //!
      ~Tester();

    public:

      // ----------------------------------------------------------------------
      // Tests
      // ----------------------------------------------------------------------

      //! To do
      //!
      void toDo();

    private:

      // ----------------------------------------------------------------------
      // Handlers for typed from ports
      // ----------------------------------------------------------------------

      //! Handler for from_productRequestOut
      //!
      void from_productRequestOut_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwDpIdType id, /*!< 
      The buffer ID. Matches the container ID.
      */
          FwDpBuffSizeType size /*!< 
      The size of the requested buffer
      */
      );

      //! Handler for from_productSendOut
      //!
      void from_productSendOut_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwDpIdType id, /*!< 
      The buffer ID. Matches the container ID.
      */
          const Fw::Buffer &buffer /*!< 
      The buffer
      */
      );

    private:

      // ----------------------------------------------------------------------
      // Helper methods
      // ----------------------------------------------------------------------

      //! Connect ports
      //!
      void connectPorts();

      //! Initialize components
      //!
      void initComponents();

    private:

      // ----------------------------------------------------------------------
      // Variables
      // ----------------------------------------------------------------------

      //! The component under test
      //!
      DpDev component;

  };

} // end namespace Svc

#endif
