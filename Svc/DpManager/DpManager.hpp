// ======================================================================
// \title  DpManager.hpp
// \author bocchino
// \brief  hpp file for DpManager component implementation class
// ======================================================================

#ifndef Svc_DpManager_HPP
#define Svc_DpManager_HPP

#include "Svc/DpManager/DpManagerComponentAc.hpp"

namespace Svc {

class DpManager : public DpManagerComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Construction, initialization, and destruction
    // ----------------------------------------------------------------------

    //! Construct object DpManager
    //!
    DpManager(const char* const compName  //!< The component name
    );

    //! Destroy object DpManager
    //!
    ~DpManager();

  PRIVATE:
    // ----------------------------------------------------------------------
    // Handler implementations for user-defined typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for productRequestIn
    //!
    void productRequestIn_handler(const NATIVE_INT_TYPE portNum,  //!< The port number
                                  FwDpIdType id,                  //!< The container ID
                                  FwSizeType size                 //!< The size of the requested buffer
                                  ) final;

    //! Handler implementation for productSendIn
    //!
    void productSendIn_handler(const NATIVE_INT_TYPE portNum,  //!< The port number
                               FwDpIdType id,                  //!< The container ID
                               const Fw::Buffer& buffer        //!< The buffer
                               ) final;

    //! Handler implementation for schedIn
    //!
    void schedIn_handler(const NATIVE_INT_TYPE portNum,  //!< The port number
                         NATIVE_UINT_TYPE context        //!< The call order
                         ) final;
};

}  // end namespace Svc

#endif
