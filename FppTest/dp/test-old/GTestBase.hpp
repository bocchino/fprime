// ======================================================================
// \title  DpTest/test/ut/GTestBase.hpp
// \author Auto-generated
// \brief  hpp file for DpTest component Google Test harness base class
//
// NOTE: this file was automatically generated
//
// ======================================================================

#ifndef DpTest_GTEST_BASE_HPP
#define DpTest_GTEST_BASE_HPP

#include "TesterBase.hpp"
#include "gtest/gtest.h"

// ----------------------------------------------------------------------
// Macros for typed user from port history assertions
// ----------------------------------------------------------------------

#define ASSERT_FROM_PORT_HISTORY_SIZE(size) \
  this->assertFromPortHistory_size(__FILE__, __LINE__, size)

#define ASSERT_from_productGetOut_SIZE(size) \
  this->assert_from_productGetOut_size(__FILE__, __LINE__, size)

#define ASSERT_from_productGetOut(index, _id, _size, _buffer) \
  { \
    ASSERT_GT(this->fromPortHistory_productGetOut->size(), static_cast<U32>(index)) \
    << "\n" \
    << __FILE__ << ":" << __LINE__ << "\n" \
    << "  Value:    Index into history of from_productGetOut\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_productGetOut->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_productGetOut& _e = \
      this->fromPortHistory_productGetOut->at(index); \
    ASSERT_EQ(_id, _e.id) \
    << "\n" \
    << __FILE__ << ":" << __LINE__ << "\n" \
    << "  Value:    Value of argument id at index " \
    << index \
    << " in history of from_productGetOut\n" \
    << "  Expected: " << _id << "\n" \
    << "  Actual:   " << _e.id << "\n"; \
    ASSERT_EQ(_size, _e.size) \
    << "\n" \
    << __FILE__ << ":" << __LINE__ << "\n" \
    << "  Value:    Value of argument size at index " \
    << index \
    << " in history of from_productGetOut\n" \
    << "  Expected: " << _size << "\n" \
    << "  Actual:   " << _e.size << "\n"; \
    ASSERT_EQ(_buffer, _e.buffer) \
    << "\n" \
    << __FILE__ << ":" << __LINE__ << "\n" \
    << "  Value:    Value of argument buffer at index " \
    << index \
    << " in history of from_productGetOut\n" \
    << "  Expected: " << _buffer << "\n" \
    << "  Actual:   " << _e.buffer << "\n"; \
  }

#define ASSERT_from_productRequestOut_SIZE(size) \
  this->assert_from_productRequestOut_size(__FILE__, __LINE__, size)

#define ASSERT_from_productRequestOut(index, _id, _size) \
  { \
    ASSERT_GT(this->fromPortHistory_productRequestOut->size(), static_cast<U32>(index)) \
    << "\n" \
    << __FILE__ << ":" << __LINE__ << "\n" \
    << "  Value:    Index into history of from_productRequestOut\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_productRequestOut->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_productRequestOut& _e = \
      this->fromPortHistory_productRequestOut->at(index); \
    ASSERT_EQ(_id, _e.id) \
    << "\n" \
    << __FILE__ << ":" << __LINE__ << "\n" \
    << "  Value:    Value of argument id at index " \
    << index \
    << " in history of from_productRequestOut\n" \
    << "  Expected: " << _id << "\n" \
    << "  Actual:   " << _e.id << "\n"; \
    ASSERT_EQ(_size, _e.size) \
    << "\n" \
    << __FILE__ << ":" << __LINE__ << "\n" \
    << "  Value:    Value of argument size at index " \
    << index \
    << " in history of from_productRequestOut\n" \
    << "  Expected: " << _size << "\n" \
    << "  Actual:   " << _e.size << "\n"; \
  }

#define ASSERT_from_productSendOut_SIZE(size) \
  this->assert_from_productSendOut_size(__FILE__, __LINE__, size)

#define ASSERT_from_productSendOut(index, _id, _buffer) \
  { \
    ASSERT_GT(this->fromPortHistory_productSendOut->size(), static_cast<U32>(index)) \
    << "\n" \
    << __FILE__ << ":" << __LINE__ << "\n" \
    << "  Value:    Index into history of from_productSendOut\n" \
    << "  Expected: Less than size of history (" \
    << this->fromPortHistory_productSendOut->size() << ")\n" \
    << "  Actual:   " << index << "\n"; \
    const FromPortEntry_productSendOut& _e = \
      this->fromPortHistory_productSendOut->at(index); \
    ASSERT_EQ(_id, _e.id) \
    << "\n" \
    << __FILE__ << ":" << __LINE__ << "\n" \
    << "  Value:    Value of argument id at index " \
    << index \
    << " in history of from_productSendOut\n" \
    << "  Expected: " << _id << "\n" \
    << "  Actual:   " << _e.id << "\n"; \
    ASSERT_EQ(_buffer, _e.buffer) \
    << "\n" \
    << __FILE__ << ":" << __LINE__ << "\n" \
    << "  Value:    Value of argument buffer at index " \
    << index \
    << " in history of from_productSendOut\n" \
    << "  Expected: " << _buffer << "\n" \
    << "  Actual:   " << _e.buffer << "\n"; \
  }

namespace FppTest {

  //! \class DpTestGTestBase
  //! \brief Auto-generated base class for DpTest component Google Test harness
  //!
  class DpTestGTestBase :
    public DpTestTesterBase
  {

    protected:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct object DpTestGTestBase
      //!
      DpTestGTestBase(
          const char *const compName, /*!< The component name*/
          const U32 maxHistorySize /*!< The maximum size of each history*/
      );

      //! Destroy object DpTestGTestBase
      //!
      virtual ~DpTestGTestBase(void);

    protected:

      // ----------------------------------------------------------------------
      // From ports
      // ----------------------------------------------------------------------

      void assertFromPortHistory_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: productGetOut
      // ----------------------------------------------------------------------

      void assert_from_productGetOut_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: productRequestOut
      // ----------------------------------------------------------------------

      void assert_from_productRequestOut_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

    protected:

      // ----------------------------------------------------------------------
      // From port: productSendOut
      // ----------------------------------------------------------------------

      void assert_from_productSendOut_size(
          const char *const __callSiteFileName, /*!< The name of the file containing the call site*/
          const U32 __callSiteLineNumber, /*!< The line number of the call site*/
          const U32 size /*!< The asserted size*/
      ) const;

  };

} // end namespace FppTest

#endif
