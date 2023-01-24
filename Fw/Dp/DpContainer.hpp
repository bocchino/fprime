// ======================================================================
// \title  DpContainer.hpp
// \author bocchino
// \brief  hpp file for DpContainer
// ======================================================================

#ifndef Fw_DpContainer_HPP
#define Fw_DpContainer_HPP

#include "FpConfig.hpp"
#include "Fw/Buffer/Buffer.hpp"
#include "Fw/Com/ComPacket.hpp"
#include "Fw/Time/Time.hpp"
#include "Fw/Types/Assert.hpp"

namespace Fw {

//! A data product Container
struct DpContainer {
    // ----------------------------------------------------------------------
    // Types
    // ----------------------------------------------------------------------

    //! A DpContainer packet header
    struct Header {
        //! The packet descriptor offset
        static constexpr FwDpBuffSizeType PACKET_DESCRIPTOR_OFFSET = 0;
        //! The id offset
        static constexpr FwDpBuffSizeType ID_OFFSET = PACKET_DESCRIPTOR_OFFSET + sizeof(FwPacketDescriptorType);
        //! The priority
        static constexpr FwDpPriorityType PRIORITY_OFFSET = ID_OFFSET + sizeof(FwDpIdType);
        //! The time tag
        static constexpr FwDpBuffSizeType TIME_TAG_OFFSET = PRIORITY_OFFSET + sizeof(FwDpPriorityType);
        //! The data size offset
        static constexpr FwDpBuffSizeType DATA_SIZE_OFFSET = TIME_TAG_OFFSET + Fw::Time::SERIALIZED_SIZE;
        //! The header size
        static constexpr FwDpBuffSizeType SIZE = DATA_SIZE_OFFSET + sizeof(FwDpBuffSizeType);
    };

    // ----------------------------------------------------------------------
    // Constructor
    // ----------------------------------------------------------------------

    //! Constructor
    DpContainer(FwDpIdType id,            //!< The container id
                const Fw::Buffer& buffer  //!< The buffer
                )
        : id(id), priority(0), dataSize(0), buffer(buffer) {
        // Move the serialization index to the end of the header
        const auto status = this->moveSerializationToOffset(Header::SIZE);
        FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);
    }

    // ----------------------------------------------------------------------
    // Member functions
    // ----------------------------------------------------------------------

    //! Move the packet serialization to the specified offset
    //! \return The serialize status
    Fw::SerializeStatus moveSerializationToOffset(FwDpBuffSizeType offset  //!< The offset
    ) {
        auto& serializeRepr = this->buffer.getSerializeRepr();
        // Reset serialization
        serializeRepr.resetSer();
        // Advance to offset
        return serializeRepr.serializeSkip(offset);
    }

    //! Write the packet header
    //! \return The serialize status
    Fw::SerializeStatus writeHeader() {
        auto& serializeRepr = this->buffer.getSerializeRepr();
        // Reset serialization
        serializeRepr.resetSer();
        // Store the packet type
        auto status = serializeRepr.serialize(static_cast<FwPacketDescriptorType>(Fw::ComPacket::FW_PACKET_DP));
        // Store the container id
        if (status == Fw::FW_SERIALIZE_OK) {
            status = serializeRepr.serialize(this->id);
        }
        // Store the priority
        if (status == Fw::FW_SERIALIZE_OK) {
            status = serializeRepr.serialize(this->priority);
        }
        // Store the time tag
        // TODO
        if (status == Fw::FW_SERIALIZE_OK) {
            status = serializeRepr.serialize(this->timeTag);
        }
        // Store the data size
        if (status == Fw::FW_SERIALIZE_OK) {
            status = serializeRepr.serialize(this->dataSize);
        }
        return status;
    }

    //! Get the packet size corresponding to the data size
    FwDpBuffSizeType getPacketSize() { return Header::SIZE + this->dataSize; }

    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The container id
    const FwDpIdType id;

    //! The priority
    FwDpPriorityType priority;

    //! The time tag
    Fw::Time timeTag;

    //! The data size
    FwDpBuffSizeType dataSize;

    //! The packet buffer
    Fw::Buffer buffer;
};

}  // end namespace Fw

#endif
