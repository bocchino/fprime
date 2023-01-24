// ======================================================================
// \title  DpContainerHeader.hpp
// \author bocchino
// \brief  hpp file for DpContainer header
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

    //! Deserialize a header from a packet buffer
    //! \return The serialize status
    void deserialize(Fw::Buffer& buffer  //!< The packet buffer
    ) {
        auto& serializeRepr = buffer.getSerializeRepr();
        // Reset deserialization
        serializeRepr.setBuffLen(buffer.getSize());
        serializeRepr.resetDeser();
        // Deserialize the packet descriptor
        FwPacketDescriptorType packetDescriptor = Fw::ComPacket::FW_PACKET_UNKNOWN;
        auto status = serializeRepr.deserialize(packetDescriptor);
        ASSERT_EQ(status, FW_SERIALIZE_OK);
        ASSERT_EQ(packetDescriptor, Fw::ComPacket::FW_PACKET_DP);
        // Deserialize the container id
        status = serializeRepr.deserialize(this->id);
        ASSERT_EQ(status, FW_SERIALIZE_OK);
        // Deserialize the priority
        status = serializeRepr.deserialize(this->priority);
        ASSERT_EQ(status, FW_SERIALIZE_OK);
        // Deserialize the time tag
        status = serializeRepr.deserialize(this->timeTag);
        ASSERT_EQ(status, FW_SERIALIZE_OK);
        // Deserialize the data size
        status = serializeRepr.deserialize(this->dataSize);
        ASSERT_EQ(status, FW_SERIALIZE_OK);
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
