// ======================================================================
// \title  DpDevDpComponentBase.cpp
// \author bocchino
// \brief  cpp file for DpDev Dp component base (to be auto-generated)
// ======================================================================

#include "FpConfig.hpp"
#include "Svc/DpDev/DpDevDpComponentBase.hpp"

namespace Svc {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  DpDevDpComponentBase ::
    DpDevDpComponentBase(
        const char *const compName
    ) : DpDevComponentBase(compName)
  {

  }

  void DpDevDpComponentBase ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    DpDevComponentBase::init(queueDepth, instance);
  }

  DpDevDpComponentBase ::
    ~DpDevDpComponentBase()
  {

  }

  // ----------------------------------------------------------------------
  // Private Dp handling functions
  // ----------------------------------------------------------------------

  void DpDevDpComponentBase ::
    productRecvIn_handler(
        const NATIVE_INT_TYPE portNum,
        FwDpIdType id,
        const Fw::Buffer &buffer
    )
  {
    // TODO
  }

} // end namespace Svc
