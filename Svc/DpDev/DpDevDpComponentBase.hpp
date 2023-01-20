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
  public:
    // ----------------------------------------------------------------------
    // Constants
    // ----------------------------------------------------------------------

    //! The container Ids
    struct ContainerId {
        enum T {
            Container1 = 0,
            Container2 = 1,
        };
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

    //! The user-implemented handler for writing data products
    virtual void Dp_Write_handler(ContainerId::T containerId,          //!< The container id
                                  Fw::Buffer& buffer,                  //!< The data product buffer
                                  Fw::SerializeBufferBase& serialRepr  //!< The serial representation of the buffer
                                  ) = 0;

  PROTECTED:
    //! ----------------------------------------------------------------------
    //! Functions for managing data products
    //! ----------------------------------------------------------------------

    //! Request a data product buffer.  On receipt of the buffer, call the
    //! user-implemented Dp_Write_handler
    void Dp_RequestBuffer(ContainerId::T containerId,  //!< The container id
                          FwSizeType size              //!< The buffer size
    );

    //! Write a data product.  Typically this function is called in the
    //! user-implemented Dp_Write_handler.
    void Dp_WriteProduct(ContainerId::T containerId,  //!< The container ID
                         Fw::Buffer& buffer           //!< The data product buffer
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

    // TODO
};

}  // end namespace Svc

#endif
