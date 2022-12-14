// ======================================================================
// \title  DpDevDpComponentBase.hpp
// \author bocchino
// \brief  hpp file for DpDev Dp component base (to be auto-generated)
// ======================================================================

#ifndef Svc_DpDevDpComponentBase_HPP
#define Svc_DpDevDpComponentBase_HPP

#include "FpConfig.hpp"
#include "Svc/DpDev/DpDevComponentAc.hpp"

namespace Svc {

  class DpDevDpComponentBase :
    public DpDevComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object DpDevDpComponentBase
      //!
      DpDevDpComponentBase(
          const char *const compName //!< The component name
      );

      //! Destroy object DpDevDpComponentBase
      //!
      virtual ~DpDevDpComponentBase();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Private Dp handling functions
      // ----------------------------------------------------------------------

      //! Handler implementation for productRecvIn
      //!
      void productRecvIn_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          FwDpIdType id, //!< The buffer ID. Matches the container ID.
          const Fw::Buffer &buffer //!< The buffer
      ) override;

      // TODO

    };

} // end namespace Svc

#endif
