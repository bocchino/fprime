// ======================================================================
// \title  DpDev.hpp
// \author bocchino
// \brief  hpp file for DpDev component implementation class
// ======================================================================

#ifndef Svc_DpDev_HPP
#define Svc_DpDev_HPP

#include "Svc/DpDev/DpDevDpComponentBase.hpp"

namespace Svc {

  class DpDev :
    public DpDevDpComponentBase
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

      // TODO

    PRIVATE:

      // ---------------------------------------------------------------------- 
      // Implementations of data product handlers
      // ---------------------------------------------------------------------- 
 
      Fw::SerializeStatus Dp_Write_handler(
          ContainerId::t containerId, //!< The container Id
          Fw::Buffer& buffer //!< The data product buffer
      ) override;

  };

} // end namespace Svc

#endif
