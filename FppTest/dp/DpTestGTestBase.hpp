// ======================================================================
// \title  DpTestGTestBase.hpp
// \author Generated by fpp-to-cpp
// \brief  hpp file for DpTest component Google Test harness base class
// ======================================================================

#ifndef FppTest_DpTestGTestBase_HPP
#define FppTest_DpTestGTestBase_HPP

#include "FppTest/dp/DpTestTesterBase.hpp"
#include "gtest/gtest.h"

// ----------------------------------------------------------------------
// Macros for product get assertions
// ----------------------------------------------------------------------

#define ASSERT_PRODUCT_GET_SIZE(size) \
  this->assertProductGet_size(__FILE__, __LINE__, size)

#define ASSERT_PRODUCT_GET(index, id, size) \
  this->assertProductGet(__FILE__, __LINE__, index, id, size)

// ----------------------------------------------------------------------
// Macros for product request assertions
// ----------------------------------------------------------------------

#define ASSERT_PRODUCT_REQUEST_SIZE(size) \
  this->assertProductRequest_size(__FILE__, __LINE__, size)

#define ASSERT_PRODUCT_REQUEST(index, id, size) \
  this->assertProductRequest(__FILE__, __LINE__, index, id, size)

// ----------------------------------------------------------------------
// Macros for product send assertions
// ----------------------------------------------------------------------

#define ASSERT_PRODUCT_SEND_SIZE(size) \
  this->assertProductSend_size(__FILE__, __LINE__, size)

#define ASSERT_PRODUCT_SEND(index, id, buffer) \
  this->assertProductSend(__FILE__, __LINE__, index, id, buffer)

namespace FppTest {

  //! \class DpTestGTestBase
  //! \brief Auto-generated base for DpTest component Google Test harness
  class DpTestGTestBase :
    public DpTestTesterBase
  {

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object DpTestGTestBase
      DpTestGTestBase(
          const char* const compName, //!< The component name
          const U32 maxHistorySize //!< The maximum size of each history
      );

      //! Destroy object DpTestGTestBase
      ~DpTestGTestBase();

    protected:

      // ----------------------------------------------------------------------
      // Data Product Get
      // ----------------------------------------------------------------------

      //! Assert size of product get history
      void assertProductGet_size(
          const char* const __callSiteFileName, //!< The name of the file containing the call site
          const U32 __callSiteLineNumber, //!< The line number of the call site
          const U32 size //!< The asserted size
      ) const;

      //! Assert the product get history at index
      void assertProductGet(
          const char* const __callSiteFileName, //!< The name of the file containing the call site
          const U32 __callSiteLineNumber, //!< The line number of the call site
          const U32 __index, //!< The index
          FwOpcodeType opCode, //!< The opcode
          U32 cmdSeq, //!< The command sequence number
          FwDpIdType id, //!< The container ID
          FwSizeType size //!< The size of the requested buffer
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Data Product Request
      // ----------------------------------------------------------------------

      //! Assert size of product request history
      void assertProductRequest_size(
          const char* const __callSiteFileName, //!< The name of the file containing the call site
          const U32 __callSiteLineNumber, //!< The line number of the call site
          const U32 size //!< The asserted size
      ) const;

      //! Assert the product request history at index
      void assertProductRequest(
          const char* const __callSiteFileName, //!< The name of the file containing the call site
          const U32 __callSiteLineNumber, //!< The line number of the call site
          const U32 __index, //!< The index
          FwOpcodeType opCode, //!< The opcode
          U32 cmdSeq, //!< The command sequence number
          FwDpIdType id, //!< The container ID
          FwSizeType size //!< The size of the requested buffer
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // Data Product Send
      // ----------------------------------------------------------------------

      //! Assert size of product send history
      void assertProductSend_size(
          const char* const __callSiteFileName, //!< The name of the file containing the call site
          const U32 __callSiteLineNumber, //!< The line number of the call site
          const U32 size //!< The asserted size
      ) const;

      //! Assert the product send history at index
      void assertProductSend(
          const char* const __callSiteFileName, //!< The name of the file containing the call site
          const U32 __callSiteLineNumber, //!< The line number of the call site
          const U32 __index, //!< The index
          FwOpcodeType opCode, //!< The opcode
          U32 cmdSeq, //!< The command sequence number
          FwDpIdType id, //!< The container ID
          Fw::Buffer buffer //!< The buffer
      ) const;

  };

}

#endif
