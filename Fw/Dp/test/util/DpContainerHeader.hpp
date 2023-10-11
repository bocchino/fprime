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

namespace Fw {

namespace TestUtil {

//! A container packet header for testing
struct DpContainerHeader {
    DpContainerHeader() : id(0), priority(0), dataSize(0) {}

    //! Move the buffer deserialization to the specified offset
    static void moveDeserToOffset(Buffer& buffer,    //!< The buffer
                                  FwSizeType offset  //!< The offset
    ) {
        auto& serializeRepr = buffer.getSerializeRepr();
        const auto status = serializeRepr.moveDeserToOffset(offset);
        ASSERT_EQ(status, FW_SERIALIZE_OK);
    }

    //! Deserialize a header from a packet buffer
    //! Check that the serialization succeeded at every step
    void deserialize(Fw::Buffer& buffer  //!< The packet buffer
    ) {
        auto& serializeRepr = buffer.getSerializeRepr();
        // Deserialize the packet descriptor
        FwPacketDescriptorType packetDescriptor = Fw::ComPacket::FW_PACKET_UNKNOWN;
        // Reset deserialization
        auto status = serializeRepr.setBuffLen(buffer.getSize());
        ASSERT_EQ(status, FW_SERIALIZE_OK);
        // Deserialize the packet descriptor
        DpContainerHeader::moveDeserToOffset(buffer, DpContainer::Header::PACKET_DESCRIPTOR_OFFSET);
        status = serializeRepr.deserialize(packetDescriptor);
        ASSERT_EQ(status, FW_SERIALIZE_OK);
        ASSERT_EQ(packetDescriptor, Fw::ComPacket::FW_PACKET_DP);
        // Deserialize the container id
        DpContainerHeader::moveDeserToOffset(buffer, DpContainer::Header::ID_OFFSET);
        status = serializeRepr.deserialize(this->id);
        ASSERT_EQ(status, FW_SERIALIZE_OK);
        // Deserialize the priority
        DpContainerHeader::moveDeserToOffset(buffer, DpContainer::Header::PRIORITY_OFFSET);
        status = serializeRepr.deserialize(this->priority);
        ASSERT_EQ(status, FW_SERIALIZE_OK);
        // Deserialize the time tag
        DpContainerHeader::moveDeserToOffset(buffer, DpContainer::Header::TIME_TAG_OFFSET);
        status = serializeRepr.deserialize(this->timeTag);
        ASSERT_EQ(status, FW_SERIALIZE_OK);
        // Deserialize the processing type
        DpContainerHeader::moveDeserToOffset(buffer, DpContainer::Header::PROC_ID_OFFSET);
        status = serializeRepr.deserialize(procType);
        ASSERT_EQ(status, FW_SERIALIZE_OK);
        // Deserialize the user data
        DpContainerHeader::moveDeserToOffset(buffer, DpContainer::Header::USER_DATA_OFFSET);
        NATIVE_UINT_TYPE size = sizeof this->userData;
        const bool omitLength = true;
        status = serializeRepr.deserialize(this->userData, size, omitLength);
        ASSERT_EQ(status, FW_SERIALIZE_OK);
        ASSERT_EQ(size, sizeof this->userData);
        // Deserialize the data size
        DpContainerHeader::moveDeserToOffset(buffer, DpContainer::Header::DATA_SIZE_OFFSET);
        status = serializeRepr.deserialize(this->dataSize);
        ASSERT_EQ(status, FW_SERIALIZE_OK);
        // After deserializing time, the deserialization index should match the
        // header size
        const auto buffLeft = serializeRepr.getBuffLeft();
        DpContainerHeader::moveDeserToOffset(buffer, DpContainer::Header::SIZE);
        ASSERT_EQ(buffLeft, serializeRepr.getBuffLeft());
    }

    //! Check a packet header against a buffer
    void check(const Fw::Buffer& buffer,                       //!< The buffer
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
        ASSERT_GE(bufferSize, minBufferSize);
        // Check the container id
        ASSERT_EQ(this->id, id);
        // Check the priority
        ASSERT_EQ(this->priority, priority);
        // Check the time tag
        ASSERT_EQ(this->timeTag, timeTag);
        // Check the deserialized processor id
        ASSERT_EQ(this->procType, procType);
        // Check the user data
        for (FwSizeType i = 0; i < DpCfg::CONTAINER_USER_DATA_SIZE; ++i) {
            ASSERT_EQ(this->userData[i], userData[i]);
        }
        // Check the data size
        ASSERT_EQ(this->dataSize, dataSize);
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
