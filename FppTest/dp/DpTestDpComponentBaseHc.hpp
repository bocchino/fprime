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

#if 0
  PRIVATE:
    // ----------------------------------------------------------------------
    // Private Dp handling functions
    // ----------------------------------------------------------------------

    //! Handler implementation for productRecvIn
    //!
    void productRecvIn_handler(const NATIVE_INT_TYPE portNum,  //!< The port number
                               FwDpIdType id,                  //!< The container ID
                               const Fw::Buffer& buffer        //!< The buffer
                               ) override;
#endif

};

}  // end namespace FppTest

#endif
