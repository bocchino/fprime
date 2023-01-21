// ======================================================================
// \title  DpPacket.hpp
// \author bocchino
// \brief  hpp file for DpPacket
// ======================================================================

#ifndef Fw_DpPacket_HPP
#define Fw_DpPacket_HPP

#include "FpConfig.hpp"
#include "Fw/Buffer/Buffer.hpp"
#include "Fw/Com/ComPacket.hpp"

namespace Fw {

//! A data product packet
struct DpPacket {
    // ----------------------------------------------------------------------
    // Types
    // ----------------------------------------------------------------------

    //! A DpPacket header
    struct Header {
        //! The header size
        static constexpr FwDpBuffSizeType SIZE =
            sizeof(FwPacketDescriptorType) + sizeof(FwDpIdType) + sizeof(FwDpBuffSizeType);
        //! The packet descriptor offset
        static constexpr FwDpBuffSizeType PACKET_DESCRIPTOR_OFFSET = 0;
        //! The id offset
        static constexpr FwDpBuffSizeType ID_OFFSET = PACKET_DESCRIPTOR_OFFSET + sizeof(FwPacketDescriptorType);
        //! The data size offset
        static constexpr FwDpBuffSizeType DATA_SIZE_OFFSET = ID_OFFSET + sizeof(FwDpIdType);
    };

    // ----------------------------------------------------------------------
    // Constructor
    // ----------------------------------------------------------------------

    //! Constructor
    DpPacket(FwDpIdType id,            //!< The container id
             const Fw::Buffer& buffer  //!< The buffer
             )
        : id(id), buffer(buffer), dataSize(0) {
        // Write the packet header
        const auto status = this->writeHeader();
        FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);
    }

    // ----------------------------------------------------------------------
    // Member functions
    // ----------------------------------------------------------------------

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
        // Store the data size
        if (status == Fw::FW_SERIALIZE_OK) {
            status = serializeRepr.serialize(this->dataSize);
        }
        return status;
    }

    //! Get the buffer size corresponding to the data size
    FwDpBuffSizeType getBufferSize() { return Header::SIZE + this->dataSize; }

    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The container id
    const FwDpIdType id;

    //! The buffer
    Fw::Buffer buffer;

    //! The data size
    FwDpBuffSizeType dataSize;
};

}  // end namespace Fw

#endif
