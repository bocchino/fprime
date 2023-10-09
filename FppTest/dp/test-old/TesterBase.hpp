// ======================================================================
// \title  DpTest/test/ut/TesterBase.hpp
// \author Auto-generated
// \brief  hpp file for DpTest component test harness base class
//
// NOTE: this file was automatically generated
//
// ======================================================================

#ifndef DpTest_TESTER_BASE_HPP
#define DpTest_TESTER_BASE_HPP

#include <FppTest/dp/DpTestComponentAc.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Comp/PassiveComponentBase.hpp>
#include <cstdio>
#include <Fw/Port/InputSerializePort.hpp>

namespace FppTest {

  //! \class DpTestTesterBase
  //! \brief Auto-generated base class for DpTest component test harness
  //!
  class DpTestTesterBase :
    public Fw::PassiveComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Initialization
      // ----------------------------------------------------------------------

      //! Initialize object DpTestTesterBase
      //!
      virtual void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

    public:

      // ----------------------------------------------------------------------
      // Connectors for 'to' ports
      // Connect these output ports to the input ports under test
      // ----------------------------------------------------------------------

      //! Connect productRecvIn to to_productRecvIn[portNum]
      //!
      void connect_to_productRecvIn(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::InputDpResponsePort *const productRecvIn /*!< The port*/
      );

      //! Connect schedIn to to_schedIn[portNum]
      //!
      void connect_to_schedIn(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Svc::InputSchedPort *const schedIn /*!< The port*/
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for 'from' ports
      // Connect these input ports to the output ports under test
      // ----------------------------------------------------------------------

      //! Get the port that receives input from productGetOut
      //!
      //! \return from_productGetOut[portNum]
      //!
      Fw::InputDpGetPort* get_from_productGetOut(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from productRequestOut
      //!
      //! \return from_productRequestOut[portNum]
      //!
      Fw::InputDpRequestPort* get_from_productRequestOut(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from productSendOut
      //!
      //! \return from_productSendOut[portNum]
      //!
      Fw::InputDpSendPort* get_from_productSendOut(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Get the port that receives input from timeGetOut
      //!
      //! \return from_timeGetOut[portNum]
      //!
      Fw::InputTimePort* get_from_timeGetOut(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object DpTestTesterBase
      //!
      DpTestTesterBase(
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
      );

      //! Destroy object DpTestTesterBase
      //!
      virtual ~DpTestTesterBase();

      // ----------------------------------------------------------------------
      // Test history
      // ----------------------------------------------------------------------

    protected:

      //! \class History
      //! \brief A history of port inputs
      //!
      template <typename T> class History {

        public:

          //! Create a History
          //!
          History(
              const U32 maxSize /*!< The maximum history size*/
          ) :
              numEntries(0),
              maxSize(maxSize)
          {
            this->entries = new T[maxSize];
          }

          //! Destroy a History
          //!
          ~History() {
            delete[] this->entries;
          }

          //! Clear the history
          //!
          void clear() { this->numEntries = 0; }

          //! Push an item onto the history
          //!
          void push_back(
              T entry /*!< The item*/
          ) {
            FW_ASSERT(this->numEntries < this->maxSize);
            entries[this->numEntries++] = entry;
          }

          //! Get an item at an index
          //!
          //! \return The item at index i
          //!
          T at(
              const U32 i /*!< The index*/
          ) const {
            FW_ASSERT(i < this->numEntries);
            return entries[i];
          }

          //! Get the number of entries in the history
          //!
          //! \return The number of entries in the history
          //!
          U32 size() const { return this->numEntries; }

        private:

          //! The number of entries in the history
          //!
          U32 numEntries;

          //! The maximum history size
          //!
          const U32 maxSize;

          //! The entries
          //!
          T *entries;

      };

      //! Clear all history
      //!
      void clearHistory();

    protected:

      // ----------------------------------------------------------------------
      // Handler prototypes for typed from ports
      // ----------------------------------------------------------------------

      //! Handler prototype for from_productGetOut
      //!
      virtual Fw::Success from_productGetOut_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwDpIdType id, /*!< 
      The container ID
      */
          FwSizeType size, /*!< 
      The size of the requested buffer
      */
          Fw::Buffer &buffer /*!< 
      The buffer
      */
      ) = 0;

      //! Handler base function for from_productGetOut
      //!
      Fw::Success from_productGetOut_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwDpIdType id, /*!< 
      The container ID
      */
          FwSizeType size, /*!< 
      The size of the requested buffer
      */
          Fw::Buffer &buffer /*!< 
      The buffer
      */
      );

      //! Handler prototype for from_productRequestOut
      //!
      virtual void from_productRequestOut_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwDpIdType id, /*!< 
      The container ID
      */
          FwSizeType size /*!< 
      The size of the requested buffer
      */
      ) = 0;

      //! Handler base function for from_productRequestOut
      //!
      void from_productRequestOut_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwDpIdType id, /*!< 
      The container ID
      */
          FwSizeType size /*!< 
      The size of the requested buffer
      */
      );

      //! Handler prototype for from_productSendOut
      //!
      virtual void from_productSendOut_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwDpIdType id, /*!< 
      The container ID
      */
          const Fw::Buffer &buffer /*!< 
      The buffer
      */
      ) = 0;

      //! Handler base function for from_productSendOut
      //!
      void from_productSendOut_handlerBase(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwDpIdType id, /*!< 
      The container ID
      */
          const Fw::Buffer &buffer /*!< 
      The buffer
      */
      );

    protected:

      // ----------------------------------------------------------------------
      // Histories for typed from ports
      // ----------------------------------------------------------------------

      //! Clear from port history
      //!
      void clearFromPortHistory();

      //! The total number of from port entries
      //!
      U32 fromPortHistorySize;

      //! Push an entry on the history for from_productGetOut
      void pushFromPortEntry_productGetOut(
          FwDpIdType id, /*!< 
      The container ID
      */
          FwSizeType size, /*!< 
      The size of the requested buffer
      */
          Fw::Buffer &buffer /*!< 
      The buffer
      */
      );

      //! A history entry for from_productGetOut
      //!
      typedef struct {
          FwDpIdType id;
          FwSizeType size;
          Fw::Buffer buffer;
      } FromPortEntry_productGetOut;

      //! The history for from_productGetOut
      //!
      History<FromPortEntry_productGetOut>
        *fromPortHistory_productGetOut;

      //! Push an entry on the history for from_productRequestOut
      void pushFromPortEntry_productRequestOut(
          FwDpIdType id, /*!< 
      The container ID
      */
          FwSizeType size /*!< 
      The size of the requested buffer
      */
      );

      //! A history entry for from_productRequestOut
      //!
      typedef struct {
          FwDpIdType id;
          FwSizeType size;
      } FromPortEntry_productRequestOut;

      //! The history for from_productRequestOut
      //!
      History<FromPortEntry_productRequestOut>
        *fromPortHistory_productRequestOut;

      //! Push an entry on the history for from_productSendOut
      void pushFromPortEntry_productSendOut(
          FwDpIdType id, /*!< 
      The container ID
      */
          const Fw::Buffer &buffer /*!< 
      The buffer
      */
      );

      //! A history entry for from_productSendOut
      //!
      typedef struct {
          FwDpIdType id;
          Fw::Buffer buffer;
      } FromPortEntry_productSendOut;

      //! The history for from_productSendOut
      //!
      History<FromPortEntry_productSendOut>
        *fromPortHistory_productSendOut;

    protected:

      // ----------------------------------------------------------------------
      // Invocation functions for to ports
      // ----------------------------------------------------------------------

      //! Invoke the to port connected to productRecvIn
      //!
      void invoke_to_productRecvIn(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
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

      //! Invoke the to port connected to schedIn
      //!
      void invoke_to_schedIn(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< 
      The call order
      */
      );

    public:

      // ----------------------------------------------------------------------
      // Getters for port counts
      // ----------------------------------------------------------------------

      //! Get the number of from_productGetOut ports
      //!
      //! \return The number of from_productGetOut ports
      //!
      NATIVE_INT_TYPE getNum_from_productGetOut() const;

      //! Get the number of to_productRecvIn ports
      //!
      //! \return The number of to_productRecvIn ports
      //!
      NATIVE_INT_TYPE getNum_to_productRecvIn() const;

      //! Get the number of from_productRequestOut ports
      //!
      //! \return The number of from_productRequestOut ports
      //!
      NATIVE_INT_TYPE getNum_from_productRequestOut() const;

      //! Get the number of from_productSendOut ports
      //!
      //! \return The number of from_productSendOut ports
      //!
      NATIVE_INT_TYPE getNum_from_productSendOut() const;

      //! Get the number of to_schedIn ports
      //!
      //! \return The number of to_schedIn ports
      //!
      NATIVE_INT_TYPE getNum_to_schedIn() const;

      //! Get the number of from_timeGetOut ports
      //!
      //! \return The number of from_timeGetOut ports
      //!
      NATIVE_INT_TYPE getNum_from_timeGetOut() const;

    protected:

      // ----------------------------------------------------------------------
      // Connection status for to ports
      // ----------------------------------------------------------------------

      //! Check whether port is connected
      //!
      //! Whether to_productRecvIn[portNum] is connected
      //!
      bool isConnected_to_productRecvIn(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

      //! Check whether port is connected
      //!
      //! Whether to_schedIn[portNum] is connected
      //!
      bool isConnected_to_schedIn(
          const NATIVE_INT_TYPE portNum /*!< The port number*/
      );

    protected:

      // ----------------------------------------------------------------------
      // Test time
      // ----------------------------------------------------------------------

      //! Set the test time for events and telemetry
      //!
      void setTestTime(
          const Fw::Time& timeTag /*!< The time*/
      );

    private:

      // ----------------------------------------------------------------------
      // To ports
      // ----------------------------------------------------------------------

      //! To port connected to productRecvIn
      //!
      Fw::OutputDpResponsePort m_to_productRecvIn[1];

      //! To port connected to schedIn
      //!
      Svc::OutputSchedPort m_to_schedIn[1];

    private:

      // ----------------------------------------------------------------------
      // From ports
      // ----------------------------------------------------------------------

      //! From port connected to productGetOut
      //!
      Fw::InputDpGetPort m_from_productGetOut[1];

      //! From port connected to productRequestOut
      //!
      Fw::InputDpRequestPort m_from_productRequestOut[1];

      //! From port connected to productSendOut
      //!
      Fw::InputDpSendPort m_from_productSendOut[1];

      //! From port connected to timeGetOut
      //!
      Fw::InputTimePort m_from_timeGetOut[1];

    private:

      // ----------------------------------------------------------------------
      // Static functions for output ports
      // ----------------------------------------------------------------------

      //! Static function for port from_productGetOut
      //!
      static Fw::Success from_productGetOut_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwDpIdType id, /*!< 
      The container ID
      */
          FwSizeType size, /*!< 
      The size of the requested buffer
      */
          Fw::Buffer &buffer /*!< 
      The buffer
      */
      );

      //! Static function for port from_productRequestOut
      //!
      static void from_productRequestOut_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwDpIdType id, /*!< 
      The container ID
      */
          FwSizeType size /*!< 
      The size of the requested buffer
      */
      );

      //! Static function for port from_productSendOut
      //!
      static void from_productSendOut_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          FwDpIdType id, /*!< 
      The container ID
      */
          const Fw::Buffer &buffer /*!< 
      The buffer
      */
      );

      //! Static function for port from_timeGetOut
      //!
      static void from_timeGetOut_static(
          Fw::PassiveComponentBase *const callComp, /*!< The component instance*/
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Time &time /*!< 
      The U32 cmd argument
      */
      );

    private:

      // ----------------------------------------------------------------------
      // Test time
      // ----------------------------------------------------------------------

      //! Test time stamp
      //!
      Fw::Time m_testTime;

  };

} // end namespace FppTest

#endif
