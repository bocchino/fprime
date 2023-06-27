// ====================================================================== 
// \title  Rules.hpp
// \author bocchino
// \brief  Rules for testing DpManager
//
// \copyright
// Copyright (C) 2023 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged. Any commercial use must be negotiated with the Office
// of Technology Transfer at the California Institute of Technology.
// 
// This software may be subject to U.S. export control laws and
// regulations.  By accepting this document, the user agrees to comply
// with all U.S. export laws and regulations.  User has the
// responsibility to obtain export licenses, or other export authority
// as may be required before exporting such information to foreign
// countries or providing access to foreign persons.
// ======================================================================

#ifndef Svc_Rules_HPP
#define Svc_Rules_HPP

#include "STest/Rule/Rule.hpp"

#include "Svc/DpManager/test/ut/TestState/TestState.hpp"

namespace Svc {

  namespace Rules {
    
    namespace BufferGetStatus {
    
      struct Invalid :
        public STest::Rule<TestState>
      {
      
        Invalid(void) :
          Rule<TestState>("BufferGetStatus.Invalid")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__BufferGetStatus__Invalid();
        }
    
        void action(TestState& state) {
          state.action__BufferGetStatus__Invalid();
        }
      
      };
    
      struct Valid :
        public STest::Rule<TestState>
      {
      
        Valid(void) :
          Rule<TestState>("BufferGetStatus.Valid")
        {
    
        }
      
        bool precondition(const TestState& state) {
          return state.precondition__BufferGetStatus__Valid();
        }
    
        void action(TestState& state) {
          state.action__BufferGetStatus__Valid();
        }
      
      };
    
    }
    
  }

}

#endif
