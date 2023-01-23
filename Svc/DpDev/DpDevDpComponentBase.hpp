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
#include "Fw/Dp/DpContainer.hpp"
#include "Svc/DpDev/DpDevComponentAc.hpp"
#include "Svc/DpDev/DpDev_PriorityEnumAc.hpp"

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
    struct DpContainer : public Fw::DpContainer {
        //! Constructor
        DpContainer(FwDpIdType id,              //!< The container id
                    const Fw::Buffer& buffer,   //!< The packet buffer
                    FwDpIdType baseId           //!< The component base id
                    )
            : Fw::DpContainer(id, buffer), baseId(baseId) {}

        //! Serialize a U32Record into the packet
        //! \return The serialize status
        Fw::SerializeStatus serializeRecord_U32Record(U32 elt  //! The element
        ) {
            auto& serializeRepr = buffer.getSerializeRepr();
            const FwDpIdType id = this->baseId + RecordId::U32Record;
            auto status = serializeRepr.serialize(id);
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
            const FwDpIdType id = this->baseId + RecordId::DataRecord;
            auto status = serializeRepr.serialize(id);
            if (status == Fw::FW_SERIALIZE_OK) {
                status = serializeRepr.serialize(elt);
            }
            if (status == Fw::FW_SERIALIZE_OK) {
                this->dataSize += sizeof(FwDpIdType);
                this->dataSize += sizeof elt;
            }
            return status;
        }

      PRIVATE:
        //! The component base id
        FwDpIdType baseId;
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

    //! Receive a container of type Container1
    //! \return Serialize status
    virtual void Dp_Recv_Container1_handler(DpContainer& container  //!< The container
                                            ) = 0;

    //! Receive a container of type Container2
    //! \return Serialize status
    virtual void Dp_Recv_Container2_handler(DpContainer& container  //!< The container
                                            ) = 0;

  PROTECTED:
    //! ----------------------------------------------------------------------
    //! Functions for managing data products
    //! ----------------------------------------------------------------------

    //! Request a data product container
    void Dp_Request(ContainerId::T containerId,  //!< The container id
                    FwDpBuffSizeType size        //!< The buffer size
    );

    //! Send a data product
    void Dp_Send(DpContainer& container  //!< The data product packet
    );

  PRIVATE:
    // ----------------------------------------------------------------------
    // Private Dp handling functions
    // ----------------------------------------------------------------------

    //! Handler implementation for productRecvIn
    //!
    void productRecvIn_handler(const NATIVE_INT_TYPE portNum,  //!< The port number
                               FwDpIdType id,                  //!< The container ID
                               const Fw::Buffer& buffer        //!< The buffer
                               ) override;

    //! The handler for receiving a data product buffer
    void Dp_Recv_handler(DpContainer& container  //!< The data product packet
    ) {
        // Convert global id to local id
        const auto idBase = this->getIdBase();
        FW_ASSERT(container.id >= idBase);
        const auto localId = container.id - idBase;
        // Switch on the local id
        switch (localId) {
            case ContainerId::Container1:
                // Set the priority
                container.priority = DpDev_Priority::Container1;
                // Call the handler
                this->Dp_Recv_Container1_handler(container);
                break;
            case ContainerId::Container2:
                // Set the priority
                container.priority = DpDev_Priority::Container2;
                // Call the handler
                this->Dp_Recv_Container2_handler(container);
                break;
            default:
                FW_ASSERT(0);
                break;
        }
    }
};

}  // end namespace Svc

#endif
