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

      //! Destroy object DpDev
      //!
      virtual ~DpDevDpComponentBase();

    PROTECTED:

      // ----------------------------------------------------------------------
      // Dp handling functions
      // ----------------------------------------------------------------------

      // TODO

    };

} // end namespace Svc

#endif
