// ======================================================================
// \title  DpDev.cpp
// \author bocchino
// \brief  cpp file for DpDev component implementation class
// ======================================================================

#include "FpConfig.hpp"
#include "Svc/DpDev/DpDev.hpp"

namespace Svc {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  DpDev ::
    DpDev(
        const char *const compName
    ) : DpDevComponentBase(compName)
  {

  }

  void DpDev ::
    init(
        const NATIVE_INT_TYPE queueDepth,
        const NATIVE_INT_TYPE instance
    )
  {
    DpDevComponentBase::init(queueDepth, instance);
  }

  DpDev ::
    ~DpDev()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void DpDev ::
    productRecvIn_handler(
        const NATIVE_INT_TYPE portNum,
        FwDpIdType id,
        const Fw::Buffer &buffer
    )
  {
    // TODO
  }

} // end namespace Svc
