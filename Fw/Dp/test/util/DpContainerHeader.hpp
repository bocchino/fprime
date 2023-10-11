// ======================================================================
// \title  DpContainerHeader.hpp
// \author bocchino
// \brief  hpp file for DpContainer header test utility
// ======================================================================

#ifndef Fw_TestUtil_DpContainerHeader_HPP
#define Fw_TestUtil_DpContainerHeader_HPP

#include "gtest/gtest.h"

#include "FpConfig.hpp"
#include "Fw/Com/ComPacket.hpp"
#include "Fw/Dp/DpContainer.hpp"

#define DP_CONTAINER_HEADER_ASSERT_MSG(actual, expected) \
    << file << ":" << line << "\n"                       \
    << "  Actual value is " << actual << "\n"            \
    << "  Expected value is " << expected
#define DP_CONTAINER_HEADER_ASSERT_EQ(actual, expected) \
    ASSERT_EQ(actual, expected) DP_CONTAINER_HEADER_ASSERT_MSG(actual, expected)
#define DP_CONTAINER_HEADER_ASSERT_GE(actual, expected) \
    ASSERT_GE(actual, expected) DP_CONTAINER_HEADER_ASSERT_MSG(actual, expected)

namespace Fw {
namespace TestUtil {

//! A container packet header for testing
struct DpContainerHeader {
    DpContainerHeader() : id(0), priority(0), dataSize(0) {}

    //! Move the buffer deserialization to the specified offset
    static void moveDeserToOffset(const char* const file,  //!< The call site file name
                                  const U32 line,          //!< The call site line number
                                  Buffer& buffer,          //!< The buffer
                                  FwSizeType offset        //!< The offset
    ) {
        auto& serializeRepr = buffer.getSerializeRepr();
        // Reset deserialization
        auto status = serializeRepr.setBuffLen(buffer.getSize());
        DP_CONTAINER_HEADER_ASSERT_EQ(status, FW_SERIALIZE_OK);
        status = serializeRepr.moveDeserToOffset(offset);
        DP_CONTAINER_HEADER_ASSERT_EQ(status, FW_SERIALIZE_OK);
    }

    //! Deserialize a header from a packet buffer
    //! Check that the serialization succeeded at every step
    void deserialize(const char* const file,  //!< The call site file name
                     const U32 line,          //!< The call site line number
                     Fw::Buffer& buffer       //!< The packet buffer
    ) {
        auto& serializeRepr = buffer.getSerializeRepr();
        // Deserialize the packet descriptor
        FwPacketDescriptorType packetDescriptor = Fw::ComPacket::FW_PACKET_UNKNOWN;
        // Deserialize the packet descriptor
        DpContainerHeader::moveDeserToOffset(file, line, buffer, DpContainer::Header::PACKET_DESCRIPTOR_OFFSET);
        auto status = serializeRepr.deserialize(packetDescriptor);
        DP_CONTAINER_HEADER_ASSERT_EQ(status, FW_SERIALIZE_OK);
        DP_CONTAINER_HEADER_ASSERT_EQ(packetDescriptor, Fw::ComPacket::FW_PACKET_DP);
        // Deserialize the container id
        DpContainerHeader::moveDeserToOffset(file, line, buffer, DpContainer::Header::ID_OFFSET);
        status = serializeRepr.deserialize(this->id);
        DP_CONTAINER_HEADER_ASSERT_EQ(status, FW_SERIALIZE_OK);
        // Deserialize the priority
        DpContainerHeader::moveDeserToOffset(file, line, buffer, DpContainer::Header::PRIORITY_OFFSET);
        status = serializeRepr.deserialize(this->priority);
        DP_CONTAINER_HEADER_ASSERT_EQ(status, FW_SERIALIZE_OK);
        // Deserialize the time tag
        DpContainerHeader::moveDeserToOffset(file, line, buffer, DpContainer::Header::TIME_TAG_OFFSET);
        status = serializeRepr.deserialize(this->timeTag);
        DP_CONTAINER_HEADER_ASSERT_EQ(status, FW_SERIALIZE_OK);
        // Deserialize the processing type
        DpContainerHeader::moveDeserToOffset(file, line, buffer, DpContainer::Header::PROC_ID_OFFSET);
        status = serializeRepr.deserialize(procType);
        DP_CONTAINER_HEADER_ASSERT_EQ(status, FW_SERIALIZE_OK);
        // Deserialize the user data
        DpContainerHeader::moveDeserToOffset(file, line, buffer, DpContainer::Header::USER_DATA_OFFSET);
        NATIVE_UINT_TYPE size = sizeof this->userData;
        const bool omitLength = true;
        status = serializeRepr.deserialize(this->userData, size, omitLength);
        DP_CONTAINER_HEADER_ASSERT_EQ(status, FW_SERIALIZE_OK);
        DP_CONTAINER_HEADER_ASSERT_EQ(size, sizeof this->userData);
        // Deserialize the data size
        DpContainerHeader::moveDeserToOffset(file, line, buffer, DpContainer::Header::DATA_SIZE_OFFSET);
        status = serializeRepr.deserialize(this->dataSize);
        DP_CONTAINER_HEADER_ASSERT_EQ(status, FW_SERIALIZE_OK);
        // After deserializing time, the deserialization index should match the
        // header size
        const auto buffLeft = serializeRepr.getBuffLeft();
        DpContainerHeader::moveDeserToOffset(file, line, buffer, DpContainer::Header::SIZE);
        DP_CONTAINER_HEADER_ASSERT_EQ(buffLeft, serializeRepr.getBuffLeft());
    }

    //! Check a packet header against a buffer
    void check(const char* const file,                         //!< The call site file name
               const U32 line,                                 //!< The call site line number
               const Fw::Buffer& buffer,                       //!< The buffer
               FwDpIdType id,                                  //!< The expected id
               FwDpPriorityType priority,                      //!< The expected priority
               const Fw::Time& timeTag,                        //!< The expected time tag
               DpCfg::ProcType procType,                       //!< The expected processing type
               const DpContainer::Header::UserData& userData,  //!< The expected user data
               FwSizeType dataSize                             //!< The expected data size
    ) const {
        // Check the buffer size
        const auto bufferSize = buffer.getSize();
        const auto minBufferSize = Fw::DpContainer::Header::SIZE + dataSize;
        DP_CONTAINER_HEADER_ASSERT_GE(bufferSize, minBufferSize);
        // Check the container id
        DP_CONTAINER_HEADER_ASSERT_EQ(this->id, id);
        // Check the priority
        DP_CONTAINER_HEADER_ASSERT_EQ(this->priority, priority);
        // Check the time tag
        DP_CONTAINER_HEADER_ASSERT_EQ(this->timeTag, timeTag);
        // Check the deserialized processor id
        DP_CONTAINER_HEADER_ASSERT_EQ(this->procType, procType);
        // Check the user data
        for (FwSizeType i = 0; i < DpCfg::CONTAINER_USER_DATA_SIZE; ++i) {
            DP_CONTAINER_HEADER_ASSERT_EQ(this->userData[i], userData[i]);
        }
        // Check the data size
        DP_CONTAINER_HEADER_ASSERT_EQ(this->dataSize, dataSize);
    }

    //! The container id
    FwDpIdType id;

    //! The priority
    FwDpPriorityType priority;

    //! The time tag
    Time timeTag;

    //! The processing type
    DpCfg::ProcType procType;

    //! The user data
    U8 userData[DpCfg::CONTAINER_USER_DATA_SIZE];

    //! The data size
    FwSizeType dataSize;
};

}  // namespace TestUtil

}  // end namespace Fw

#endif
