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

    void productRecvIn_InvokeAndCheckHeader(FwDpIdType id,
                                            FwSizeType dataEltSize,
                                            Fw::Buffer& buffer,
                                            FwSizeType& expectedNumElts) {
        const auto containerId = ID_BASE + DpTest::ContainerId::Container1;
        // Set the test time
        const Fw::Time timeTag = this->randomizeTestTime();
        // Invoke the productRecvIn port
        this->invoke_to_productRecvIn(0, containerId, this->container1Buffer);
        this->component.doDispatch();
        // Check the port history size
        ASSERT_FROM_PORT_HISTORY_SIZE(1);
        ASSERT_from_productSendOut_SIZE(1);
        // Get the history entry
        const auto entry = this->fromPortHistory_productSendOut->at(0);
        // Check the container id
        ASSERT_EQ(entry.id, containerId);
        // Check the buffer size
        buffer = entry.buffer;
        const auto bufferSize = buffer.getSize();
        ASSERT_GE(bufferSize, FwDpBuffSizeType(DpTest::DpContainer::Header::SIZE));
        // Deserialize the packet header
        Fw::TestUtil::DpContainerHeader header;
        header.deserialize(buffer);
        // Check the container id
        ASSERT_EQ(header.id, containerId);
        // Check the priority
        ASSERT_EQ(header.priority, DpTest_Priority::Container1);
        // Check the time tag
        ASSERT_EQ(header.timeTag, timeTag);
        // Check the data size
        const auto dataCapacity = bufferSize - DpTest::DpContainer::Header::SIZE;
        const auto eltSize = sizeof(FwDpIdType) + dataEltSize;
        expectedNumElts = dataCapacity / eltSize;
        const auto expectedDataSize = expectedNumElts * eltSize;
        ASSERT_EQ(header.dataSize, expectedDataSize);
        // Check the buffer size
        const auto expectedBufferSize = DpTest::DpContainer::Header::SIZE + expectedDataSize;
        ASSERT_EQ(bufferSize, expectedBufferSize);
    }

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
        this->productRecvIn_InvokeAndCheckHeader(DpTest::ContainerId::Container2, DpTest_Data::SERIALIZED_SIZE, buffer, expectedNumElts);
#if 0
    // Check the data
    auto& serialRepr = entryBuffer.getSerializeRepr();
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
#endif
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
