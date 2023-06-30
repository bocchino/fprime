// ====================================================================== 
// \title  Testers.hpp
// \author Rob Bocchino
// \brief  Testers class interface
//
// \copyright
// Copyright (C) 2023 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged. Any commercial use must be negotiated with the Office
// of Technology Transfer at the California Institute of Technology.
// ======================================================================

#ifndef Svc_Testers_HPP
#define Svc_Testers_HPP

#include "Svc/DpManager/test/ut/Rules/BufferGetStatus.hpp"
#include "Svc/DpManager/test/ut/Rules/ProductRequestIn.hpp"
#include "Svc/DpManager/test/ut/Rules/SchedIn.hpp"

namespace Svc {

  namespace Testers {
    
    extern BufferGetStatus::Tester bufferGetStatus;

    extern ProductRequestIn::Tester invalidBuffer;

    extern ProductRequestIn::Tester validBuffer;

    extern SchedIn::Tester schedIn;

    
  }

}

#endif
