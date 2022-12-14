// ======================================================================
// \title  DpDev.hpp
// \author bocchino
// \brief  hpp file for DpDev component implementation class
// ======================================================================

#ifndef Svc_DpDev_HPP
#define Svc_DpDev_HPP

#include "Svc/DpDev/DpDevComponentAc.hpp"

namespace Svc {

  class DpDev :
    public DpDevComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object DpDev
      //!
      DpDev(
          const char *const compName //!< The component name
      );

      //! Initialize object DpDev
      //!
      void init(
          const NATIVE_INT_TYPE queueDepth, //!< The queue depth
          const NATIVE_INT_TYPE instance = 0 //!< The instance number
      );

      //! Destroy object DpDev
      //!
      ~DpDev();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for productRecvIn
      //!
      void productRecvIn_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          FwDpIdType id, //!< The buffer ID. Matches the container ID.
          const Fw::Buffer &buffer //!< The buffer
      );

    };

} // end namespace Svc

#endif
