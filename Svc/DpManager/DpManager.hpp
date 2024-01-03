// ======================================================================
// \title  DpManager.hpp
// \author bocchino
// \brief  hpp file for DpManager component implementation class
// ======================================================================

#ifndef Svc_DpManager_HPP
#define Svc_DpManager_HPP

#include <atomic>

#include "Svc/DpManager/DpManagerComponentAc.hpp"
#include "config/FppConstantsAc.hpp"

namespace Svc {

class DpManager : public DpManagerComponentBase {

  public:
    // ----------------------------------------------------------------------
    // Construction, initialization, and destruction
    // ----------------------------------------------------------------------

    //! Construct a DpManager
    explicit DpManager(const char* const compName  //!< The component name
    );

    //! Destroy the DpManager
    ~DpManager() final;

  PRIVATE:
    // ----------------------------------------------------------------------
    // Handler implementations for user-defined typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for productGetIn
    Fw::Success productGetIn_handler(const NATIVE_INT_TYPE portNum,  //!< The port number
                                     FwDpIdType id,                  //!< The container ID
                                     FwSizeType size,                //!< The size of the requested buffer
                                     Fw::Buffer& buffer              //!< The buffer
                                     ) final;

    //! Handler implementation for productRequestIn
    void productRequestIn_handler(const NATIVE_INT_TYPE portNum,  //!< The port number
                                  FwDpIdType id,                  //!< The container ID
                                  FwSizeType size                 //!< The size of the requested buffer
                                  ) final;

    //! Handler implementation for productSendIn
    void productSendIn_handler(const NATIVE_INT_TYPE portNum,  //!< The port number
                               FwDpIdType id,                  //!< The container ID
                               const Fw::Buffer& buffer        //!< The buffer
                               ) final;

    //! Handler implementation for schedIn
    void schedIn_handler(const NATIVE_INT_TYPE portNum,  //!< The port number
                         NATIVE_UINT_TYPE context        //!< The call order
                         ) final;

  PRIVATE:
    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command CLEAR_THROTTLE
    //!
    //! Clear throttling
    void CLEAR_THROTTLE_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                                   U32 cmdSeq            //!< The command sequence number
                                   ) override;

  PRIVATE:
    // ----------------------------------------------------------------------
    // Private helper functions
    // ----------------------------------------------------------------------

    //! Get a buffer
    //! \return Status
    Fw::Success getBuffer(FwIndexType portNum,  //!< The port number
                          FwDpIdType id,        //!< The container ID (input)
                          FwSizeType size,      //!< The requested size (input)
                          Fw::Buffer& buffer    //!< The buffer (output)
    );

  PRIVATE:
    // ----------------------------------------------------------------------
    // Private member variables
    // ----------------------------------------------------------------------

    //! The number of successful buffer allocations
    std::atomic<U32> numSuccessfulAllocations;

    //! The number of failed buffer allocations
    std::atomic<U32> numFailedAllocations;

    //! The number of data products handled
    U32 numDataProducts;

    //! The number of bytes handled
    U64 numBytes;
};

}  // end namespace Svc

#endif
