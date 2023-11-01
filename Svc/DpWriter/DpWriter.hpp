// ======================================================================
// \title  DpWriter.hpp
// \author bocchino
// \brief  hpp file for DpWriter component implementation class
// ======================================================================

#ifndef DpWriter_HPP
#define DpWriter_HPP

#include "Svc/DpWriter/DpWriterComponentAc.hpp"

namespace Svc {

class DpWriter : public DpWriterComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Construction, initialization, and destruction
    // ----------------------------------------------------------------------

    //! Construct object DpWriter
    //!
    DpWriter(const char* const compName /*!< The component name*/
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
    );

    //! Handler implementation for schedIn
    //!
    void schedIn_handler(const NATIVE_INT_TYPE portNum,  //!< The port number
                         NATIVE_UINT_TYPE context        //!< The call order
    );
};

}  // end namespace Svc

#endif
