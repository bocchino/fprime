// ====================================================================== 
// \title  TestState.hpp
// \author Rob Bocchino
// \brief  Test state for testing DpManager
//
// \copyright
// Copyright (C) 2023 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged. Any commercial use must be negotiated with the Office
// of Technology Transfer at the California Institute of Technology.
// ======================================================================

#ifndef Svc_TestState_HPP
#define Svc_TestState_HPP

#include "Svc/DpManager/test/ut/Tester.hpp"

namespace Svc {

  class TestState :
    public Tester
  {

    public:

      // ----------------------------------------------------------------------
      // Rule definitions 
      // ----------------------------------------------------------------------
      
      bool precondition__BufferGetStatus__Invalid() const;
      void action__BufferGetStatus__Invalid();
      
      bool precondition__BufferGetStatus__Valid() const;
      void action__BufferGetStatus__Valid();
      
  };

}

#endif
