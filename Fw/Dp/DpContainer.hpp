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
class DpContainer {
  public:
    // ----------------------------------------------------------------------
    // Types
    // ----------------------------------------------------------------------

    //! A DpContainer packet header
    struct Header {
        //! The offset for the packet descriptor field
        static constexpr FwDpBuffSizeType PACKET_DESCRIPTOR_OFFSET = 0;
        //! The offset for the id field
        static constexpr FwDpBuffSizeType ID_OFFSET = PACKET_DESCRIPTOR_OFFSET + sizeof(FwPacketDescriptorType);
        //! The offset for the priority field
        static constexpr FwDpPriorityType PRIORITY_OFFSET = ID_OFFSET + sizeof(FwDpIdType);
        //! The offset for the time tag field
        static constexpr FwDpBuffSizeType TIME_TAG_OFFSET = PRIORITY_OFFSET + sizeof(FwDpPriorityType);
        //! The offset for the data size field
        static constexpr FwDpBuffSizeType DATA_SIZE_OFFSET = TIME_TAG_OFFSET + Fw::Time::SERIALIZED_SIZE;
        //! The header size
        static constexpr FwDpBuffSizeType SIZE = DATA_SIZE_OFFSET + sizeof(FwDpBuffSizeType);
    };

  public:
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

  public:
    // ----------------------------------------------------------------------
    // Public member functions
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

    //! Serialize the header into the packet buffer
    //! \return The serialize status
    Fw::SerializeStatus serializeHeader() {
        auto& serializeRepr = this->buffer.getSerializeRepr();
        // Reset serialization
        serializeRepr.resetSer();
        // Serialize the packet type
        auto status = serializeRepr.serialize(static_cast<FwPacketDescriptorType>(Fw::ComPacket::FW_PACKET_DP));
        // Serialize the container id
        if (status == Fw::FW_SERIALIZE_OK) {
            status = serializeRepr.serialize(this->id);
        }
        // Serialize the priority
        if (status == Fw::FW_SERIALIZE_OK) {
            status = serializeRepr.serialize(this->priority);
        }
        // Serialize the time tag
        if (status == Fw::FW_SERIALIZE_OK) {
            status = serializeRepr.serialize(this->timeTag);
        }
        // Serialize the data size
        if (status == Fw::FW_SERIALIZE_OK) {
            status = serializeRepr.serialize(this->dataSize);
        }
        return status;
    }

    //! Get the packet size corresponding to the data size
    FwDpBuffSizeType getPacketSize() { return Header::SIZE + this->dataSize; }

    //! Get the container id
    //! \return The id
    FwDpIdType getId() { return this->id; }

    //! Get the priority
    //! \return The priority
    FwDpPriorityType getPriority() { return this->priority; }

    //! Set the priority
    void setPriority(FwDpPriorityType priority  //!< The priority
    ) {
        this->priority = priority;
    }

    //! Set the time tag
    void setTimeTag(Fw::Time timeTag  //!< The time tag
    ) {
        this->timeTag = timeTag;
    }

    //! Get the time tag
    //! \return The time tag
    Fw::Time getTimeTag() { return this->timeTag; }

    //! Get the data size
    //! \return The data size
    FwDpBuffSizeType getDataSize() { return this->dataSize; }

    //! Get the packet buffer
    //! \return The buffer
    Fw::Buffer getBuffer() { return this->buffer; }

  PROTECTED:
    // ----------------------------------------------------------------------
    // Protected member variables
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
