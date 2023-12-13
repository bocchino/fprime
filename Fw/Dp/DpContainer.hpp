// ======================================================================
// \title  DpContainer.hpp
// \author bocchino
// \brief  hpp file for DpContainer
// ======================================================================

#ifndef Fw_DpContainer_HPP
#define Fw_DpContainer_HPP

#include "Fw/Buffer/Buffer.hpp"
#include "Fw/Dp/DpStateEnumAc.hpp"
#include "Fw/Time/Time.hpp"
#include "Utils/Hash/Hash.hpp"
#include "config/FppConstantsAc.hpp"
#include "config/ProcTypeEnumAc.hpp"

namespace Fw {

//! A data product Container
class DpContainer {
  public:
    // ----------------------------------------------------------------------
    // Types
    // ----------------------------------------------------------------------

    //! A DpContainer packet header
    struct Header {
        //! The type of user data
        using UserData = U8[DpCfg::CONTAINER_USER_DATA_SIZE];
        //! The offset for the packet descriptor field
        static constexpr FwSizeType PACKET_DESCRIPTOR_OFFSET = 0;
        //! The offset for the id field
        static constexpr FwSizeType ID_OFFSET = PACKET_DESCRIPTOR_OFFSET + sizeof(FwPacketDescriptorType);
        //! The offset for the priority field
        static constexpr FwDpPriorityType PRIORITY_OFFSET = ID_OFFSET + sizeof(FwDpIdType);
        //! The offset for the time tag field
        static constexpr FwSizeType TIME_TAG_OFFSET = PRIORITY_OFFSET + sizeof(FwDpPriorityType);
        //! The offset for the processing types field
        static constexpr FwSizeType PROC_TYPES_OFFSET = TIME_TAG_OFFSET + Time::SERIALIZED_SIZE;
        //! The offset for the user data field
        static constexpr FwSizeType USER_DATA_OFFSET = PROC_TYPES_OFFSET + sizeof(DpCfg::ProcType::SerialType);
        //! The offset of the data product state field
        static constexpr FwSizeType DP_STATE_OFFSET = USER_DATA_OFFSET + DpCfg::CONTAINER_USER_DATA_SIZE;
        //! The offset for the data size field
        static constexpr FwSizeType DATA_SIZE_OFFSET = DP_STATE_OFFSET + DpState::SERIALIZED_SIZE;
        //! The header size
        static constexpr FwSizeType SIZE = DATA_SIZE_OFFSET + sizeof(FwSizeType);
    };

    //! The header hash offset
    static constexpr FwSizeType HEADER_HASH_OFFSET = Header::SIZE;
    //! The data offset
    //! FIXME: This should be HEADER_HASH_OFFSET + HASH_DIGEST_LENGTH
    static constexpr FwSizeType DATA_OFFSET = HEADER_HASH_OFFSET;

  public:
    // ----------------------------------------------------------------------
    // Constructor
    // ----------------------------------------------------------------------

    //! Constructor for initialized container
    DpContainer(FwDpIdType id,            //!< The container id
                const Fw::Buffer& buffer  //!< The buffer
    );

    //! Constructor for container with default initialization
    DpContainer();

  public:
    // ----------------------------------------------------------------------
    // Public member functions
    // ----------------------------------------------------------------------

    //! Get the container id
    //! \return The id
    FwDpIdType getId() const { return this->id; }

    //! Get the data size
    //! \return The data size
    FwSizeType getDataSize() const { return this->dataSize; }

    //! Get the packet buffer
    //! \return The buffer
    Fw::Buffer getBuffer() const { return this->buffer; }

    //! Get the packet size corresponding to the data size
    // FIXME: This should be augmented by 2 * HASH_DIGEST_LENGTH
    FwSizeType getPacketSize() const { return Header::SIZE + this->dataSize; }

    //! Get the priority
    //! \return The priority
    FwDpPriorityType getPriority() const { return this->priority; }

    //! Get the time tag
    //! \return The time tag
    Fw::Time getTimeTag() const { return this->timeTag; }

    //! Get the processing types
    //! \return The processing types
    DpCfg::ProcType::SerialType getProcTypes() const { return this->procTypes; }

    //! Move the packet serialization to the specified offset
    //! \return The serialize status
    Fw::SerializeStatus moveSerToOffset(FwSizeType offset  //!< The offset
    );

    //! Serialize the header into the packet buffer
    //! \return The serialize status
    Fw::SerializeStatus serializeHeader();

    //! Set the id
    void setId(FwDpIdType id  //!< The id
    ) {
        this->id = id;
    }

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

    //! Set the processing types bit mask
    void setProcTypes(DpCfg::ProcType::SerialType procTypes  //!< The processing types
    ) {
        this->procTypes = procTypes;
    }

    //! Set the data product state
    void setDpState(DpState dpState  //!< The data product state
    ) {
        this->dpState = dpState;
    }

    //! Set the packet buffer
    void setBuffer(const Buffer& buffer  //!< The buffer
    );

  public:
    // ----------------------------------------------------------------------
    // Public static functions
    // ----------------------------------------------------------------------

    //! Get the packet size for a given data size
    static constexpr FwSizeType getPacketSizeForDataSize(FwSizeType dataSize  //!< The data size
    ) {
        return Header::SIZE + dataSize + 2 * HASH_DIGEST_LENGTH;
    }

  PRIVATE:
    // ----------------------------------------------------------------------
    // Private member functions
    // ----------------------------------------------------------------------

    //! Initialize the user data field
    void initUserDataField();

  public:
    // ----------------------------------------------------------------------
    // Public member variables
    // ----------------------------------------------------------------------

    //! The user data
    Header::UserData userData;

  PROTECTED:
    // ----------------------------------------------------------------------
    // Protected member variables
    // ----------------------------------------------------------------------

    //! The container id
    //! This is a system-global id (component-local id + component base id)
    FwDpIdType id;

    //! The priority
    FwDpPriorityType priority;

    //! The time tag
    Time timeTag;

    //! The processing types
    DpCfg::ProcType::SerialType procTypes;

    //! The data product state
    DpState dpState;

    //! The data size
    FwSizeType dataSize;

    //! The packet buffer
    Buffer buffer;
};

}  // end namespace Fw

#endif
