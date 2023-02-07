// ======================================================================
// \title  DpTestDpComponentBaseHc.hpp
// \author bocchino
// \brief  Hand-coded hpp file for DpTest Dp component base (to be auto-generated)
// ======================================================================

#ifndef FppTest_DpTestDpComponentBaseHc_HPP
#define FppTest_DpTestDpComponentBaseHc_HPP

#include "FpConfig.hpp"
#include "FppTest/dp/DpTestDpComponentAc.hpp"
#include "Fw/Buffer/Buffer.hpp"

namespace FppTest {

class DpTestDpComponentBaseHc : public DpTestDpComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Construction, initialization, and destruction
    // ----------------------------------------------------------------------

    //! Construct object DpTestDpComponentBaseHc
    //!
    DpTestDpComponentBaseHc(const char* const compName  //!< The component name
    );

    //! Destroy object DpTestDpComponentBaseHc
    //!
    virtual ~DpTestDpComponentBaseHc();

};

}  // end namespace FppTest

#endif
