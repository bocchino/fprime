// ======================================================================
// \title  DpDevDpComponentBase.hpp
// \author bocchino
// \brief  hpp file for DpDev Dp component base (to be auto-generated)
// ======================================================================

#ifndef Svc_DpDevDpComponentBase_HPP
#define Svc_DpDevDpComponentBase_HPP

#include "FpConfig.hpp"
#include "Fw/Buffer/Buffer.hpp"
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

        //! Constructor
        DpPacket(ContainerId::T id,        //!< The container id
                  const Fw::Buffer& buffer  //!< The buffer
                  )
            : id(id), buffer(buffer), dataSize(0)
        {
          // Reserve space to store the data size
          auto& serializeRepr = this->buffer.getSerializeRepr();
          (void) serializeRepr.serialize(static_cast<FwDpBuffSizeType>(0));
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

        //! The container id
        const ContainerId::T id;

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
