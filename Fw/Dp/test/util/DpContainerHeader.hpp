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
    static void moveDeserToOffset(Buffer& buffer,          //!< The buffer
                                            FwDpBuffSizeType offset  //!< The offset
    ) {
        auto& serializeRepr = buffer.getSerializeRepr();
        const auto status = serializeRepr.moveDeserToOffset(offset);
        ASSERT_EQ(status, FW_SERIALIZE_OK);
    }

    //! Deserialize a header from a packet buffer
    //! \return The serialize status
    void deserialize(Fw::Buffer& buffer  //!< The packet buffer
    ) {
        auto& serializeRepr = buffer.getSerializeRepr();
        // Deserialize the packet descriptor
        FwPacketDescriptorType packetDescriptor = Fw::ComPacket::FW_PACKET_UNKNOWN;
        // Reset deserialization
        serializeRepr.setBuffLen(buffer.getSize());
        // Deserialize the packet descriptor
        DpContainerHeader::moveDeserToOffset(buffer, DpContainer::Header::PACKET_DESCRIPTOR_OFFSET);
        auto status = serializeRepr.deserialize(packetDescriptor);
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

    //! The container id
    FwDpIdType id;

    //! The priority
    FwDpPriorityType priority;

    //! The time tag
    Fw::Time timeTag;

    //! The data size
    FwDpBuffSizeType dataSize;
};

}  // namespace TestUtil

}  // end namespace Fw

#endif