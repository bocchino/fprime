// ======================================================================
// \title  DpTestDpComponentBaseHc.hpp
// \author bocchino
// \brief  Hand-coded hpp file for DpTest Dp component base (to be auto-generated)
// ======================================================================

#ifndef FppTest_DpTestDpComponentBaseHc_HPP
#define FppTest_DpTestDpComponentBaseHc_HPP

#include "FpConfig.hpp"
#include "FppTest/dp/DpTestDpComponentAc.hpp"
#include "FppTest/dp/DpTest_PriorityEnumAc.hpp"
#include "Fw/Buffer/Buffer.hpp"
#include "Fw/Com/ComPacket.hpp"
#include "Fw/Dp/DpContainer.hpp"

namespace FppTest {

class DpTestDpComponentBaseHc : public DpTestDpComponentBase {
  PROTECTED:
    // ----------------------------------------------------------------------
    // Types
    // ----------------------------------------------------------------------

    //! A data product container
    class DpContainer : public Fw::DpContainer {

      public:
        //! Constructor
        DpContainer(FwDpIdType id,              //!< The container id
                    const Fw::Buffer& buffer,   //!< The packet buffer
                    FwDpIdType baseId           //!< The component base id
                    );

        //! Serialize a U32Record into the packet buffer
        //! \return The serialize status
        Fw::SerializeStatus serializeRecord_U32Record(U32 elt  //! The element
        );

        //! Serialize a DataRecord into the packet buffer
        //! \return The serialize status
        Fw::SerializeStatus serializeRecord_DataRecord(const DpTest_Data& elt  //! The element
        );

      PRIVATE:
        //! The component base id
        FwDpIdType baseId;
    };

  public:
    // ----------------------------------------------------------------------
    // Construction, initialization, and destruction
    // ----------------------------------------------------------------------

    //! Construct object DpTestDpComponentBaseHc
    //!
    DpTestDpComponentBaseHc(const char* const compName  //!< The component name
    );

    //! Destroy object DpTestDpComponentBaseHc
    //!
    virtual ~DpTestDpComponentBaseHc();

  PROTECTED:
    //! ----------------------------------------------------------------------
    //! Pure virtual functions to implement
    //! ----------------------------------------------------------------------

    //! Receive a data product container of type Container1
    //! \return Serialize status
    virtual void Dp_Recv_Container1_handler(DpContainer& container  //!< The container
                                            ) = 0;

    //! Receive a data product container of type Container2
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
    void Dp_Send(DpContainer& container  //!< The data product container
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
    void Dp_Recv_handler(DpContainer& container  //!< The data product container
    );
};

}  // end namespace FppTest

#endif
