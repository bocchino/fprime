// ======================================================================
// \title  DpDevDpComponentBase.hpp
// \author bocchino
// \brief  hpp file for DpDev Dp component base (to be auto-generated)
// ======================================================================

#ifndef Svc_DpDevDpComponentBase_HPP
#define Svc_DpDevDpComponentBase_HPP

#include "FpConfig.hpp"
#include "Fw/Buffer/Buffer.hpp"
#include "Fw/Com/ComPacket.hpp"
#include "Svc/DpDev/DpDevComponentAc.hpp"

namespace Svc {

class DpDevDpComponentBase : public DpDevComponentBase {
  PROTECTED:
    // ----------------------------------------------------------------------
    // Types
    // ----------------------------------------------------------------------

    //! The container ids
    struct ContainerId {
        enum T : FwDpIdType {
            Container1 = 0,
            Container2 = 1,
        };
    };

    //! The record ids
    struct RecordId {
        enum T : FwDpIdType {
            U32Record = 0,
            DataRecord = 1,
        };
    };

    //! A data product packet
    struct DpPacket {
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

        //! Constructor
        DpPacket(ContainerId::T id,        //!< The container id
                 const Fw::Buffer& buffer  //!< The buffer
                 )
            : isValid(false), id(id), buffer(buffer), dataSize(0) {
            // Check buffer for validity
            if ((this->buffer.getData()) != nullptr && (this->buffer.getSize() > 0)) {
                // Write the packet header
                const auto status = this->writeHeader();
                if (status == Fw::FW_SERIALIZE_OK) {
                    this->isValid = true;
                }
            }
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
            // Store the data size
            if (status == Fw::FW_SERIALIZE_OK) {
                status = serializeRepr.serialize(this->dataSize);
            }
            return status;
        }

        //! Serialize a U32Record into the packet
        //! \return The serialize status
        Fw::SerializeStatus serializeRecord_U32Record(U32 elt  //! The element
        ) {
            auto& serializeRepr = buffer.getSerializeRepr();
            auto status = serializeRepr.serialize(static_cast<FwDpIdType>(RecordId::U32Record));
            if (status == Fw::FW_SERIALIZE_OK) {
                status = serializeRepr.serialize(elt);
            }
            if (status == Fw::FW_SERIALIZE_OK) {
                this->dataSize += sizeof(FwDpIdType);
                this->dataSize += sizeof elt;
            }
            return status;
        }

        //! Serialize a DataRecord into the packet
        //! \return The serialize status
        Fw::SerializeStatus serializeRecord_DataRecord(const DpDev_Data& elt  //! The element
        ) {
            auto& serializeRepr = buffer.getSerializeRepr();
            auto status = serializeRepr.serialize(static_cast<FwDpIdType>(RecordId::DataRecord));
            if (status == Fw::FW_SERIALIZE_OK) {
                status = serializeRepr.serialize(elt);
            }
            if (status == Fw::FW_SERIALIZE_OK) {
                this->dataSize += sizeof(FwDpIdType);
                this->dataSize += sizeof elt;
            }
            return status;
        }

        //! Get the buffer size corresponding to the data size
        FwDpBuffSizeType getBufferSize() {
          return Header::SIZE + this->dataSize;
        }

        //! Whether the packet is valid
        bool isValid;

        //! The container id
        const FwDpIdType id;

        //! The buffer
        Fw::Buffer buffer;

        //! The data size
        FwDpBuffSizeType dataSize;
    };

  public:
    // ----------------------------------------------------------------------
    // Construction, initialization, and destruction
    // ----------------------------------------------------------------------

    //! Construct object DpDevDpComponentBase
    //!
    DpDevDpComponentBase(const char* const compName  //!< The component name
    );

    //! Destroy object DpDevDpComponentBase
    //!
    virtual ~DpDevDpComponentBase();

  PROTECTED:
    //! ----------------------------------------------------------------------
    //! Pure virtual functions to implement
    //! ----------------------------------------------------------------------

    //! The handler for receiving a data product buffer
    virtual void Dp_Recv_handler(DpPacket& dpPacket  //!< The data product packet
                                 ) = 0;

  PROTECTED:
    //! ----------------------------------------------------------------------
    //! Functions for managing data products
    //! ----------------------------------------------------------------------

    //! Request a data product buffer
    void Dp_Request(ContainerId::T containerId,  //!< The container id
                    FwDpBuffSizeType size        //!< The buffer size
    );

    //! Write a data product. Typically this function is called in the
    //! user-implemented Dp_RecvBuffer_handler.
    //! \return The status after serializing the data length
    Fw::SerializeStatus Dp_Write(DpPacket& dpPacket  //!< The data product packet
    );

  PRIVATE:
    // ----------------------------------------------------------------------
    // Private Dp handling functions
    // ----------------------------------------------------------------------

    //! Handler implementation for productRecvIn
    //!
    void productRecvIn_handler(const NATIVE_INT_TYPE portNum,  //!< The port number
                               FwDpIdType id,                  //!< The buffer ID. Matches the container ID.
                               const Fw::Buffer& buffer        //!< The buffer
                               ) override;
};

}  // end namespace Svc

#endif
