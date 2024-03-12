// ======================================================================
// \title  BufferSendIn.hpp
// \author Rob Bocchino
// \brief  BufferSendIn class interface
//
// \copyright
// Copyright (C) 2024 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged. Any commercial use must be negotiated with the Office
// of Technology Transfer at the California Institute of Technology.
// ======================================================================

#ifndef Svc_BufferSendIn_HPP
#define Svc_BufferSendIn_HPP

#include "Svc/DpWriter/test/ut/Rules/Rules.hpp"
#include "Svc/DpWriter/test/ut/TestState/TestState.hpp"

namespace Svc {

  namespace BufferSendIn {

    class Tester {

      public:

        // ----------------------------------------------------------------------
        // Tests
        // ----------------------------------------------------------------------

        //! OK
        void OK();

        //! Invalid buffer
        void InvalidBuffer();

      public:

        // ----------------------------------------------------------------------
        // Rules
        // ----------------------------------------------------------------------

        //! Rule BufferSendIn::OK
        Rules::BufferSendIn::OK ruleOK;
        
        //! Rule BufferSendIn::InvalidBuffer
        Rules::BufferSendIn::InvalidBuffer ruleInvalidBuffer;

      public:

        // ----------------------------------------------------------------------
        // Public member variables
        // ----------------------------------------------------------------------

        //! Test state
        TestState testState;

    };

  }

}

#endif
