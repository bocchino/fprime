// ----------------------------------------------------------------------
// TestMain.cpp
// ----------------------------------------------------------------------

#include <cstring>
#include <limits>

#include "gtest/gtest.h"

#include "Fw/Dp/DpContainer.hpp"
#include "Fw/Dp/test/util/DpContainerHeader.hpp"
#include "Fw/Test/UnitTest.hpp"
#include "STest/Pick/Pick.hpp"
#include "STest/Random/Random.hpp"

using namespace Fw;

U8 bufferData[Fw::DpContainer::MIN_PACKET_SIZE];
DpContainer::Header::UserData userData;

void checkHeader(FwDpIdType id, Fw::Buffer& buffer, DpContainer& container) {
    // Check the packet size
    const FwSizeType expectedPacketSize = Fw::DpContainer::MIN_PACKET_SIZE;
    ASSERT_EQ(container.getPacketSize(), expectedPacketSize);
    // Set the priority
    const FwDpPriorityType priority = STest::Pick::lowerUpper(0, std::numeric_limits<FwDpPriorityType>::max());
    container.setPriority(priority);
    // Set the time tag
    const U32 seconds = STest::Pick::any();
    const U32 useconds = STest::Pick::startLength(0, 1000000);
    Fw::Time timeTag(seconds, useconds);
    container.setTimeTag(timeTag);
    // Set the processing types
    const FwSizeType numProcTypeStates = 1 << DpCfg::ProcType::NUM_CONSTANTS;
    const DpCfg::ProcType::SerialType procTypes = STest::Pick::startLength(0, numProcTypeStates);
    container.setProcTypes(procTypes);
    // Set the user data
    for (U8& data : userData) {
        data = static_cast<U8>(STest::Pick::any());
    }
    FW_ASSERT(sizeof userData == sizeof container.userData);
    (void)::memcpy(container.userData, userData, sizeof container.userData);
    // Set the DP state
    const DpState dpState(static_cast<DpState::T>(STest::Pick::startLength(0, DpState::NUM_CONSTANTS)));
    container.setDpState(dpState);
    // Serialize and deserialize the header
    Fw::SerializeStatus status = container.serializeHeader();
    ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
    TestUtil::DpContainerHeader header;
    // Deserialize the header
    header.deserialize(__FILE__, __LINE__, buffer);
    // Check the deserialized header fields
    // Data size should be zero because there is no data
    header.check(__FILE__, __LINE__, buffer, id, priority, timeTag, procTypes, userData, dpState, 0);
}

void checkBuffers(DpContainer& container, FwSizeType bufferSize) {
  // Check the packet buffer
  ASSERT_EQ(container.buffer.getSize(), bufferSize);
  // Check the data buffer
  U8 *const buffPtr = container.buffer.getData();
  U8 *const dataPtr = &buffPtr[Fw::DpContainer::DATA_OFFSET];
  const FwSizeType dataCapacity = container.buffer.getSize() - Fw::DpContainer::MIN_PACKET_SIZE;
  ASSERT_EQ(container.dataBuffer.getBuffAddr(), dataPtr);
  ASSERT_EQ(container.dataBuffer.getBuffCapacity(), dataCapacity);
}

TEST(Header, BufferInConstructor) {
    COMMENT("Test header serialization with buffer in constructor");
    // Create a buffer
    Fw::Buffer buffer(bufferData, sizeof bufferData);
    // Use the buffer to create a container
    const FwDpIdType id = STest::Pick::lowerUpper(0, std::numeric_limits<FwDpIdType>::max());
    DpContainer container(id, buffer);
    // Check the header
    checkHeader(id, buffer, container);
    // Check the buffers
    checkBuffers(container, sizeof bufferData);
}

TEST(Header, BufferSet) {
    COMMENT("Test header serialization with buffer set");
    // Create a buffer
    Fw::Buffer buffer(bufferData, sizeof bufferData);
    // Use the buffer to create a container
    const FwDpIdType id = STest::Pick::lowerUpper(0, std::numeric_limits<FwDpIdType>::max());
    DpContainer container;
    container.setId(id);
    container.setBuffer(buffer);
    // Check the header
    checkHeader(id, buffer, container);
    // Check the buffers
    checkBuffers(container, sizeof bufferData);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
