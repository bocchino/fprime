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

    //! A container
    struct Container {
        //! Constructor
        Container(ContainerId::T id,        //!< The container id
                  const Fw::Buffer& buffer  //!< The buffer
                  )
            : id(id), buffer(buffer) {}
        //! Serialize a U32Record into the container
        //! \return The serialize status
        Fw::SerializeStatus serializeRecord_U32Record(U32 elt  //! The element
        ) {
            auto& serializeRepr = buffer.getSerializeRepr();
            auto status = serializeRepr.serialize(static_cast<FwDpIdType>(RecordId::U32Record));
            if (status == Fw::FW_SERIALIZE_OK) {
                status = serializeRepr.serialize(elt);
            }
            return status;
        }
        //! Serialize a DataRecord into the container
        //! \return The serialize status
        Fw::SerializeStatus serializeRecord_DataRecord(const DpDev_Data& elt  //! The element
        ) {
            auto& serializeRepr = buffer.getSerializeRepr();
            auto status = serializeRepr.serialize(static_cast<FwDpIdType>(RecordId::DataRecord));
            if (status == Fw::FW_SERIALIZE_OK) {
                status = serializeRepr.serialize(elt);
            }
            return status;
        }
        //! The container id
        const ContainerId::T id;
        //! The buffer
        Fw::Buffer buffer;
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
    virtual void Dp_Recv_handler(Container& container  //!< The container
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
    void Dp_Write(Container& container  //!< The container
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
