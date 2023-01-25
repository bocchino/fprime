// ======================================================================
// \title  DpTest/test/ut/Tester.hpp
// \author bocchino
// \brief  hpp file for DpTest test harness implementation class
// ======================================================================

#ifndef FppTest_DpTest_Tester_HPP
#define FppTest_DpTest_Tester_HPP

#include "FppTest/dp/DpTest.hpp"
#include "Fw/Dp/test/util/DpContainerHeader.hpp"
#include "GTestBase.hpp"
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

    //! productRecvIn with Container 1 OK
    void productRecvIn_Container1_OK() {
        Fw::Buffer buffer;
        FwSizeType expectedNumElts;
        // Invoke the port and check the header
        this->productRecvIn_InvokeAndCheckHeader(DpTest::ContainerId::Container1, sizeof(U32), buffer, expectedNumElts);
        // Check the data
        auto& serialRepr = buffer.getSerializeRepr();
        for (FwDpBuffSizeType i = 0; i < expectedNumElts; ++i) {
            FwDpIdType id;
            U32 elt;
            auto status = serialRepr.deserialize(id);
            ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
            const FwDpIdType expectedId = this->component.getIdBase() + DpTest::RecordId::U32Record;
            ASSERT_EQ(id, expectedId);
            status = serialRepr.deserialize(elt);
            ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
            ASSERT_EQ(elt, this->component.u32RecordData);
        }
    }

    //! productRecvIn with Container 2 OK
    void productRecvIn_Container2_OK() {
        Fw::Buffer buffer;
        FwSizeType expectedNumElts;
        // Invoke the port and check the header
        this->productRecvIn_InvokeAndCheckHeader(DpTest::ContainerId::Container2, DpTest_Data::SERIALIZED_SIZE, buffer,
                                                 expectedNumElts);
        // Check the data
        auto& serialRepr = buffer.getSerializeRepr();
        for (FwDpBuffSizeType i = 0; i < expectedNumElts; ++i) {
            FwDpIdType id;
            DpTest_Data elt;
            auto status = serialRepr.deserialize(id);
            ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
            const FwDpIdType expectedId = this->component.getIdBase() + DpTest::RecordId::DataRecord;
            ASSERT_EQ(id, expectedId);
            status = serialRepr.deserialize(elt);
            ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
            ASSERT_EQ(elt.getu16Field(), this->component.dataRecordData);
        }
    }

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

    //! Set and return a random time
    //! \return The time
    Fw::Time randomizeTestTime();

    //! Invoke productRecvIn and check header
    void productRecvIn_InvokeAndCheckHeader(FwDpIdType id,               //!< The container id
                                            FwSizeType dataEltSize,      //!< The data element size
                                            Fw::Buffer& buffer,          //!< The buffer received
                                            FwSizeType& expectedNumElts  //!< The expected number of elements
    );

  PRIVATE:
    // ----------------------------------------------------------------------
    // Variables
    // ----------------------------------------------------------------------

    //! The component under test
    //!
    DpTest component;

    //! Buffer data for Container 1
    U8 container1Data[DpTest::CONTAINER_1_SIZE];

    //! Buffer for Container 1
    const Fw::Buffer container1Buffer;

    //! Buffer data for Container 2
    U8 container2Data[DpTest::CONTAINER_2_SIZE];

    //! Buffer for Container 2
    const Fw::Buffer container2Buffer;
};

}  // end namespace FppTest

#endif
