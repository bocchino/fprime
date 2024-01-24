// ======================================================================
// \title  DpWriterTester.hpp
// \author bocchino
// \brief  hpp file for DpWriter component test harness implementation class
// ======================================================================

#ifndef Svc_DpWriterTester_HPP
#define Svc_DpWriterTester_HPP

#include "Svc/DpWriter/DpWriter.hpp"
#include "Svc/DpWriter/DpWriterGTestBase.hpp"

namespace Svc {

class DpWriterTester : public DpWriterGTestBase {
  public:
    // ----------------------------------------------------------------------
    // Constants
    // ----------------------------------------------------------------------

    // Maximum size of histories storing events, telemetry, and port outputs
    static const NATIVE_INT_TYPE MAX_HISTORY_SIZE = 10;

    // Instance ID supplied to the component instance under test
    static const NATIVE_INT_TYPE TEST_INSTANCE_ID = 0;

    // Queue depth supplied to the component instance under test
    static const NATIVE_INT_TYPE TEST_INSTANCE_QUEUE_DEPTH = 10;

  public:
    // ----------------------------------------------------------------------
    // Construction and destruction
    // ----------------------------------------------------------------------

    //! Construct object DpWriterTester
    DpWriterTester();

    //! Destroy object DpWriterTester
    ~DpWriterTester();

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

    //! Handler implementation for deallocBufferSendOut
    void from_deallocBufferSendOut_handler(NATIVE_INT_TYPE portNum,  //!< The port number
                                           Fw::Buffer& fwBuffer      //!< The buffer
    );

    //! Handler implementation for dpWrittenOut
    void from_dpWrittenOut_handler(NATIVE_INT_TYPE portNum,                                   //!< The port number
                                   const Svc::DpWrittenPortStrings::StringSize256& fileName,  //!< The file name
                                   FwDpPriorityType priority,                                 //!< The priority
                                   FwSizeType size                                            //!< The file size
    );

    //! Handler implementation for procBufferSendOut
    void from_procBufferSendOut_handler(NATIVE_INT_TYPE portNum,  //!< The port number
                                        Fw::Buffer& fwBuffer      //!< The buffer
    );

  private:
    // ----------------------------------------------------------------------
    // Helper functions
    // ----------------------------------------------------------------------

    //! Connect ports
    void connectPorts();

    //! Initialize components
    void initComponents();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The component under test
    DpWriter component;
};

}  // namespace Svc

#endif
