// ======================================================================
// \title  DpTest/test/ut/Tester.hpp
// \author bocchino
// \brief  hpp file for DpTest test harness implementation class
// ======================================================================

#ifndef FppTest_DpTest_Tester_HPP
#define FppTest_DpTest_Tester_HPP

#include "FppTest/dp/DpTest.hpp"
#include "Fw/Dp/test/util/DpContainerHeader.hpp"
#include "DpTestGTestBase.hpp"
#include "STest/Pick/Pick.hpp"

namespace FppTest {

class Tester : public DpTestGTestBase {
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

    //! productRecvIn with Container 1 (SUCCESS)
    void productRecvIn_Container1_SUCCESS();

    //! productRecvIn with Container 1 (FAILURE)
    void productRecvIn_Container1_FAILURE();

    //! productRecvIn with Container 2 (SUCCESS)
    void productRecvIn_Container2_SUCCESS();

    //! productRecvIn with Container 2 (FAILURE)
    void productRecvIn_Container2_FAILURE();

    //! productRecvIn with Container 3 (SUCCESS)
    void productRecvIn_Container3_SUCCESS();

    //! productRecvIn with Container 3 (FAILURE)
    void productRecvIn_Container3_FAILURE();

    //! productRecvIn with Container 4 (SUCCESS)
    void productRecvIn_Container4_SUCCESS();

    //! productRecvIn with Container 4 (FAILURE)
    void productRecvIn_Container4_FAILURE();

    //! productRecvIn with Container 5 (SUCCESS)
    void productRecvIn_Container5_SUCCESS();

    //! productRecvIn with Container 5 (FAILURE)
    void productRecvIn_Container5_FAILURE();

  PRIVATE:
    // ----------------------------------------------------------------------
    // Handlers for typed from ports
    // ----------------------------------------------------------------------

    Fw::Success::T from_productGetOut_handler(FwDpIdType id,                  //!< The container ID
                                              FwSizeType size,                //!< The size of the requested buffer
                                              Fw::Buffer& buffer              //!< The buffer
    ) override;

#if 0
    //! Handler for from_productSendOut
    //!
    void from_productSendOut_handler(const NATIVE_INT_TYPE portNum,  //!< The port number
                                     FwDpIdType id,                  //!< The container ID
                                     const Fw::Buffer& buffer        //!< The buffer
    ) override;
#endif

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

    //! Set and return a random time
    //! \return The time
    Fw::Time randomizeTestTime();

    //! Invoke productRecvIn and check header
    void productRecvIn_InvokeAndCheckHeader(FwDpIdType id,               //!< The container id
                                            FwSizeType dataEltSize,      //!< The data element size
                                            FwDpPriorityType priority,   //!< The priority
                                            Fw::Buffer inputBuffer,      //!< The buffer to send
                                            Fw::Buffer& outputBuffer,    //!< The buffer received (output)
                                            FwSizeType& expectedNumElts  //!< The expected number of elements (output)
    );

    //! Check received buffer with failure status
    void productRecvIn_CheckFailure(FwDpIdType id,     //!< The container id
                                    Fw::Buffer buffer  //!< The buffer
    );

  PRIVATE:
    // ----------------------------------------------------------------------
    // Variables
    // ----------------------------------------------------------------------

    //! Buffer data for Container 1
    U8 container1Data[DpTest::CONTAINER_1_SIZE];

    //! Buffer for Container 1
    const Fw::Buffer container1Buffer;

    //! Buffer data for Container 2
    U8 container2Data[DpTest::CONTAINER_2_SIZE];

    //! Buffer for Container 2
    const Fw::Buffer container2Buffer;

    //! Buffer data for Container 3
    U8 container3Data[DpTest::CONTAINER_3_SIZE];

    //! Buffer for Container 3
    const Fw::Buffer container3Buffer;

    //! Buffer data for Container 4
    U8 container4Data[DpTest::CONTAINER_4_SIZE];

    //! Buffer for Container 4
    const Fw::Buffer container4Buffer;

    //! Buffer data for Container 5
    U8 container5Data[DpTest::CONTAINER_5_SIZE];

    //! Buffer for Container 5
    const Fw::Buffer container5Buffer;

    //! Data for U8 array record
    DpTest::U8ArrayRecordData u8ArrayRecordData;

    //! Data for U32 array record
    DpTest::U32ArrayRecordData u32ArrayRecordData;

    //! Data for Data array record
    DpTest::DataArrayRecordData dataArrayRecordData;

    //! The component under test
    DpTest component;
};

}  // end namespace FppTest

#endif
