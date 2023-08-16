// ======================================================================
// \title  DpContainer.hpp
// \author bocchino
// \brief  hpp file for DpContainer
// ======================================================================

#ifndef Fw_DpContainer_HPP
#define Fw_DpContainer_HPP

#include "DpCfg.hpp"
#include "config/ProcIdEnumAc.hpp"
#include "Fw/Buffer/Buffer.hpp"
#include "Fw/Time/Time.hpp"

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
        static constexpr FwSizeType PACKET_DESCRIPTOR_OFFSET = 0;
        //! The offset for the id field
        static constexpr FwSizeType ID_OFFSET = PACKET_DESCRIPTOR_OFFSET + sizeof(FwPacketDescriptorType);
        //! The offset for the priority field
        static constexpr FwDpPriorityType PRIORITY_OFFSET = ID_OFFSET + sizeof(FwDpIdType);
        //! The offset for the time tag field
        static constexpr FwSizeType TIME_TAG_OFFSET = PRIORITY_OFFSET + sizeof(FwDpPriorityType);
        //! The offset for the processing ID field
        static constexpr FwSizeType PROC_ID_OFFSET = TIME_TAG_OFFSET + Time::SERIALIZED_SIZE;
        //! The offset for the user data field
        static constexpr FwSizeType USER_DATA_OFFSET = PROC_ID_OFFSET + sizeof(DpCfg::ProcId::SerialType);
        //! The offset for the data size field
        static constexpr FwSizeType DATA_SIZE_OFFSET = USER_DATA_OFFSET + DpCfg::CONTAINER_USER_DATA_SIZE;
        //! The header size
        static constexpr FwSizeType SIZE = DATA_SIZE_OFFSET + sizeof(FwSizeType);
    };

  public:
    // ----------------------------------------------------------------------
    // Constructor
    // ----------------------------------------------------------------------

    //! Constructor with buffer
    DpContainer(FwDpIdType id,            //!< The container id
                const Fw::Buffer& buffer  //!< The buffer
    );

    //! Constructor without buffer
    DpContainer(FwDpIdType id  //!< The container id
    );

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
    FwSizeType getPacketSize() const { return Header::SIZE + this->dataSize; }

    //! Get the priority
    //! \return The priority
    FwDpPriorityType getPriority() const { return this->priority; }

    //! Get the time tag
    //! \return The time tag
    Fw::Time getTimeTag() const { return this->timeTag; }

    //! Get the processor ID
    //! \return The processor ID
    DpCfg::ProcId::T getProcId() const { return this->procId; }

    //! Move the packet serialization to the specified offset
    //! \return The serialize status
    Fw::SerializeStatus moveSerToOffset(FwSizeType offset  //!< The offset
    );

    //! Serialize the header into the packet buffer
    //! \return The serialize status
    Fw::SerializeStatus serializeHeader();

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

    //! Set the processor ID
    void setProcId(DpCfg::ProcId::T procId  //!< The processor ID
    ) {
        this->procId = procId;
    }

    //! Set the packet buffer
    void setBuffer(const Buffer& buffer  //!< The buffer
    );

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

    //! The container id
    const FwDpIdType id;

    //! The user data
    U8 userData[DpCfg::CONTAINER_USER_DATA_SIZE];

  PROTECTED:
    // ----------------------------------------------------------------------
    // Protected member variables
    // ----------------------------------------------------------------------

    //! The priority
    FwDpPriorityType priority;

    //! The time tag
    Time timeTag;

    //! The processor ID
    DpCfg::ProcId::T procId;

    //! The data size
    FwSizeType dataSize;

    //! The packet buffer
    Buffer buffer;
};

}  // end namespace Fw

#endif
