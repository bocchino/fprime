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

  class DpDevDpComponentBase :
    public DpDevComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Constants 
      // ----------------------------------------------------------------------

      //! The container Ids
      struct ContainerId {
        enum t {
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
      DpDevDpComponentBase(
          const char *const compName //!< The component name
      );

      //! Destroy object DpDevDpComponentBase
      //!
      virtual ~DpDevDpComponentBase();

    PROTECTED:

      //! ---------------------------------------------------------------------- 
      //! Pure virtual functions to implement
      //! ---------------------------------------------------------------------- 

      virtual Fw::SerializeStatus Dp_Write_handler(
          ContainerId::t containerId, //!< The container Id
          Fw::Buffer& buffer //!< The data product buffer
      ) = 0;

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
