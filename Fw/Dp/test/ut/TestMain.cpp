// ----------------------------------------------------------------------
// TestMain.cpp
// ----------------------------------------------------------------------

#include "gtest/gtest.h"

#include "Fw/Dp/DpContainer.hpp"
#include "Fw/Dp/test/util/DpContainerHeader.hpp"
#include "Fw/Test/UnitTest.hpp"
#include "STest/Pick/Pick.hpp"
#include "STest/Random/Random.hpp"

using namespace Fw;

constexpr FwDpBuffSizeType BUFFER_SIZE = 100;
U8 bufferData[BUFFER_SIZE];

TEST(Header, OK) {
    COMMENT("Test header serialization");
    // Create a buffer
    Fw::Buffer buffer(bufferData, sizeof bufferData);
    // Use the buffer to create a container
    const FwDpIdType id = STest::Pick::lowerUpper(0, FpLimits::FwDpIdType_MAX);
    DpContainer container(id, buffer);
    // Check the packet size
    // Packet size should be header size because there is no data
    const auto headerSize = DpContainer::Header::SIZE;
    ASSERT_EQ(container.getPacketSize(), headerSize);
    // Set the priority
    const FwDpPriorityType priority =
        STest::Pick::lowerUpper(0, FpLimits::FwDpPriorityType_MAX);
    container.setPriority(priority);
    // Set the time tag
    const U32 seconds = STest::Pick::any();
    const U32 useconds = STest::Pick::startLength(0, 1000000);
    Fw::Time timeTag(seconds, useconds);
    container.setTimeTag(timeTag);
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
    // Check the data size
    // Data size should be zero because there is no data
    ASSERT_EQ(0, header.dataSize);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
