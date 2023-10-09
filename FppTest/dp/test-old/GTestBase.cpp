// ======================================================================
// \title  DpTest/test/ut/GTestBase.cpp
// \author Auto-generated
// \brief  cpp file for DpTest component Google Test harness base class
//
// NOTE: this file was automatically generated
//
// ======================================================================

#include "GTestBase.hpp"

namespace FppTest {

  // ----------------------------------------------------------------------
  // Construction and destruction
  // ----------------------------------------------------------------------

  DpTestGTestBase ::
    DpTestGTestBase(
        const char *const compName,
        const U32 maxHistorySize
    ) :
        DpTestTesterBase (
            compName,
            maxHistorySize
        )
  {

  }

  DpTestGTestBase ::
    ~DpTestGTestBase()
  {

  }

  // ----------------------------------------------------------------------
  // From ports
  // ----------------------------------------------------------------------

  void DpTestGTestBase ::
    assertFromPortHistory_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistorySize)
      << "\n"
      << __callSiteFileName << ":" << __callSiteLineNumber << "\n"
      << "  Value:    Total size of all from port histories\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistorySize << "\n";
  }

  // ----------------------------------------------------------------------
  // From port: productGetOut
  // ----------------------------------------------------------------------

  void DpTestGTestBase ::
    assert_from_productGetOut_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistory_productGetOut->size())
      << "\n"
      << __callSiteFileName << ":" << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_productGetOut\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistory_productGetOut->size() << "\n";
  }

  // ----------------------------------------------------------------------
  // From port: productRequestOut
  // ----------------------------------------------------------------------

  void DpTestGTestBase ::
    assert_from_productRequestOut_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistory_productRequestOut->size())
      << "\n"
      << __callSiteFileName << ":" << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_productRequestOut\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistory_productRequestOut->size() << "\n";
  }

  // ----------------------------------------------------------------------
  // From port: productSendOut
  // ----------------------------------------------------------------------

  void DpTestGTestBase ::
    assert_from_productSendOut_size(
        const char *const __callSiteFileName,
        const U32 __callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistory_productSendOut->size())
      << "\n"
      << __callSiteFileName << ":" << __callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_productSendOut\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistory_productSendOut->size() << "\n";
  }

} // end namespace FppTest
