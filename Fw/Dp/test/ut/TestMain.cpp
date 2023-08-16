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

constexpr FwSizeType BUFFER_SIZE = 100;
U8 bufferData[BUFFER_SIZE];
U8 userData[DpCfg::CONTAINER_USER_DATA_SIZE];

void checkHeader(FwDpIdType id, Fw::Buffer& buffer, DpContainer& container) {
    // Check the packet size
    // Packet size should be header size because there is no data
    const auto headerSize = DpContainer::Header::SIZE;
    ASSERT_EQ(container.getPacketSize(), headerSize);
    // Set the priority
    const FwDpPriorityType priority = STest::Pick::lowerUpper(0, std::numeric_limits<FwDpPriorityType>::max());
    container.setPriority(priority);
    // Set the time tag
    const U32 seconds = STest::Pick::any();
    const U32 useconds = STest::Pick::startLength(0, 1000000);
    Fw::Time timeTag(seconds, useconds);
    container.setTimeTag(timeTag);
    // Set the processor ID
    const DpCfg::ProcId procId(
        static_cast<DpCfg::ProcId::T>(STest::Pick::startLength(0, DpCfg::ProcId::NUM_CONSTANTS)));
    container.setProcId(procId);
    // Set the user data
    for (U8& data : userData) {
        data = static_cast<U8>(STest::Pick::any());
    }
    FW_ASSERT(sizeof userData == sizeof container.userData);
    (void)::memcpy(container.userData, userData, sizeof container.userData);
    // Serialize and deserialize the header
    auto status = container.serializeHeader();
    ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
    TestUtil::DpContainerHeader header;
    header.deserialize(buffer);
    // Check the deserialized id
    ASSERT_EQ(id, header.id);
    // Check the deserialized priority
    ASSERT_EQ(priority, header.priority);
    // Check the deserialized time tag
    ASSERT_EQ(timeTag, header.timeTag);
    // Check the deserialized processor id
    ASSERT_EQ(procId, header.procId);
    // Check the deserialized data
    for (FwSizeType i = 0; i < DpCfg::CONTAINER_USER_DATA_SIZE; ++i) {
        ASSERT_EQ(userData[i], header.userData[i]);
    }
    // Check the data size
    // Data size should be zero because there is no data
    ASSERT_EQ(0, header.dataSize);
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
}

TEST(Header, BufferSet) {
    COMMENT("Test header serialization with buffer set");
    // Create a buffer
    Fw::Buffer buffer(bufferData, sizeof bufferData);
    // Use the buffer to create a container
    const FwDpIdType id = STest::Pick::lowerUpper(0, std::numeric_limits<FwDpIdType>::max());
    DpContainer container(id);
    container.setBuffer(buffer);
    // Check the header
    checkHeader(id, buffer, container);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
