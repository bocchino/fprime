// ======================================================================
// \title  DpDev.cpp
// \author bocchino
// \brief  cpp file for DpDev component implementation class
// ======================================================================

#include "Svc/DpDev/DpDev.hpp"

namespace Svc {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  DpDev ::
    DpDev(const char *const compName) :
      DpDevDpComponentBase(compName)
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

  // TODO


} // end namespace Svc
