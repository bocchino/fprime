// ======================================================================
// \title  DpWriter.hpp
// \author bocchino
// \brief  hpp file for DpWriter component implementation class
// ======================================================================

#ifndef Svc_DpWriter_HPP
#define Svc_DpWriter_HPP

#include "Fw/Types/String.hpp"
#include "Fw/Types/SuccessEnumAc.hpp"
#include "Svc/DpWriter/DpWriterComponentAc.hpp"

namespace Svc {

class DpWriter : public DpWriterComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Construction, initialization, and destruction
    // ----------------------------------------------------------------------

    //! Construct object DpWriter
    //!
    DpWriter(const char* const compName  //!< The component name
    );

    //! Destroy object DpWriter
    //!
    ~DpWriter();

  PRIVATE:
    // ----------------------------------------------------------------------
    // Handler implementations for user-defined typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for bufferSendIn
    //!
    void bufferSendIn_handler(const NATIVE_INT_TYPE portNum,  //!< The port number
                              Fw::Buffer& fwBuffer            //!< The buffer
    ) override;

    //! Handler implementation for schedIn
    //!
    void schedIn_handler(const NATIVE_INT_TYPE portNum,  //!< The port number
                         NATIVE_UINT_TYPE context        //!< The call order
    ) override;

  PRIVATE:
    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command CLEAR_EVENT_THROTTLE
    //!
    //! Clear event throttling
    void CLEAR_EVENT_THROTTLE_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                                         U32 cmdSeq            //!< The command sequence number
                                         ) override;

  PRIVATE:
    // ----------------------------------------------------------------------
    // Private helper functions
    // ----------------------------------------------------------------------

    //! Validate an incoming packet packet buffer
    Fw::Success::T validatePacketBuffer(const Fw::Buffer& buffer  //!< The packet buffer
    );

    //! Perform processing on a packet buffer
    void performProcessing(Fw::Buffer& buffer //!< The packet buffer
    );

    //! Write the file
    void writeFile(const Fw::Buffer& buffer //!< The packet buffer
    );

    //! Send the DpWritten notification
    void sendNotification(const Fw::Buffer& buffer //!< The packet buffer
    );

    //! Update the telemetry values
    void updateTlmValues(const Fw::Buffer& buffer //!< The packet buffer
    );

  PRIVATE:
    // ----------------------------------------------------------------------
    // Private member variables
    // ----------------------------------------------------------------------

    //! The number of data products written
    U32 m_numDataProducts = 0;

    //! The number of bytes written
    U64 m_numBytes = 0;

};

}  // end namespace Svc

#endif
