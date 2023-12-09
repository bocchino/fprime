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

U8 bufferData[DpContainer::Header::SIZE];
DpContainer::Header::UserData userData;

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
    // Set the processing type
    const DpCfg::ProcType procType(
        static_cast<DpCfg::ProcType::T>(STest::Pick::startLength(0, DpCfg::ProcType::NUM_CONSTANTS)));
    container.setProcType(procType);
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
    auto status = container.serializeHeader();
    ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
    TestUtil::DpContainerHeader header;
    // Deserialize the header
    header.deserialize(__FILE__, __LINE__, buffer);
    // Check the deserialized header fields
    // Data size should be zero because there is no data
    header.check(__FILE__, __LINE__, buffer, id, priority, timeTag, procType, userData, dpState, 0);
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
    DpContainer container;
    container.setId(id);
    container.setBuffer(buffer);
    // Check the header
    checkHeader(id, buffer, container);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
