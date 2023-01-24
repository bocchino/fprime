// ======================================================================
// \title  DpDev/test/ut/Tester.hpp
// \author bocchino
// \brief  hpp file for DpDev test harness implementation class
// ======================================================================

#ifndef Svc_DpDev_Tester_HPP
#define Svc_DpDev_Tester_HPP

#include "Fw/Dp/test/util/DpContainerHeader.hpp"
#include "GTestBase.hpp"
#include "STest/Pick/Pick.hpp"
#include "Svc/DpDev/DpDev.hpp"

namespace Svc {

class Tester : public DpDevGTestBase {
    // ----------------------------------------------------------------------
    // Construction and destruction
    // ----------------------------------------------------------------------

  public:
    // Maximum size of histories storing events, telemetry, and port outputs
    static constexpr FwSizeType MAX_HISTORY_SIZE = 10;
    // Instance ID supplied to the component instance under test
    static constexpr FwSizeType TEST_INSTANCE_ID = 0;
    // Queue depth supplied to component instance under test
    static constexpr FwSizeType TEST_INSTANCE_QUEUE_DEPTH = 10;
    // The component id base
    static constexpr FwDpIdType ID_BASE = 100;

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

    //! schedIn OK
    void schedIn_OK();

    //! productRecvIn with Container 1 OK
    void productRecvIn_Container1_OK();

  PRIVATE:
    // ----------------------------------------------------------------------
    // Handlers for typed from ports
    // ----------------------------------------------------------------------

    //! Handler for from_productRequestOut
    //!
    void from_productRequestOut_handler(const NATIVE_INT_TYPE portNum,  //!< The port number
                                        FwDpIdType id,                  //!< The container ID
                                        FwDpBuffSizeType size           //!< The size of the requested buffer
    );

    //! Handler for from_productSendOut
    //!
    void from_productSendOut_handler(const NATIVE_INT_TYPE portNum,  //!< The port number
                                     FwDpIdType id,                  //!< The container ID
                                     const Fw::Buffer& buffer        //!< The buffer
    );

  PRIVATE:
    // ----------------------------------------------------------------------
    // Helper methods
    // ----------------------------------------------------------------------

    //! Connect ports
    //!
    void connectPorts();

    //! Initialize components
    //!
    void initComponents();

  PRIVATE:
    // ----------------------------------------------------------------------
    // Variables
    // ----------------------------------------------------------------------

    //! The component under test
    //!
    DpDev component;

    //! Buffer data for Container 1
    U8 container1Data[DpDev::CONTAINER_1_SIZE];

    //! Buffer for Container 1
    const Fw::Buffer container1Buffer;

    //! Buffer data for Container 2
    U8 container2Data[DpDev::CONTAINER_2_SIZE];

    //! Buffer for Container 2
    const Fw::Buffer container2Buffer;
};

}  // end namespace Svc

#endif
