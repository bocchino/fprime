// ======================================================================
// \title  DpDev.hpp
// \author bocchino
// \brief  hpp file for DpDev component implementation class
// ======================================================================

#ifndef Svc_DpDev_HPP
#define Svc_DpDev_HPP

#include "Svc/DpDev/DpDevDpComponentBase.hpp"

namespace Svc {

class DpDev : public DpDevDpComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Construction, initialization, and destruction
    // ----------------------------------------------------------------------

    //! Construct object DpDev
    DpDev(const char* const compName  //!< The component name
    );

    //! Initialize object DpDev
    void init(const NATIVE_INT_TYPE queueDepth,   //!< The queue depth
              const NATIVE_INT_TYPE instance = 0  //!< The instance number
    );

    //! Destroy object DpDev
    ~DpDev();

  PRIVATE:
    // ----------------------------------------------------------------------
    // Handler implementations for user-defined typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for schedIn
    void schedIn_handler(const NATIVE_INT_TYPE portNum,  //!< The port number
                         NATIVE_UINT_TYPE context        //!< The call order
                         ) override;

  PRIVATE:
    // ----------------------------------------------------------------------
    // Implementation of the data product write handler
    // ----------------------------------------------------------------------

    //! Construct and write a data product
    void Dp_Write_handler(ContainerId::T containerId,          //!< The container Id
                          Fw::Buffer& buffer,                  //!< The data product buffer
                          Fw::SerializeBufferBase& serialRepr  //!< The serial representation of the buffer
                          ) override;

  PRIVATE:
    // ----------------------------------------------------------------------
    // Private member variables
    // ----------------------------------------------------------------------

    //! U32 data
    U32 u32Data;
};

}  // end namespace Svc

#endif
