// ======================================================================
// \title  DpTest.hpp
// \author bocchino
// \brief  hpp file for DpTest component implementation class
// ======================================================================

#ifndef FppTest_DpTest_HPP
#define FppTest_DpTest_HPP

#include "FppTest/dp/DpTestDpComponentBase.hpp"

namespace FppTest {

class DpTest : public DpTestDpComponentBaseHc {
  PRIVATE:
    // ----------------------------------------------------------------------
    // Constants
    // ----------------------------------------------------------------------

    static constexpr FwSizeType CONTAINER_1_SIZE = 100;
    static constexpr FwSizeType CONTAINER_2_SIZE = 1000;

  public:
    // ----------------------------------------------------------------------
    // Construction, initialization, and destruction
    // ----------------------------------------------------------------------

    //! Construct object DpTest
    DpTest(const char* const compName,  //!< The component name
          U32 u32RecordData,           //!< The U32Record data
          U16 dataRecordData           //!< The DataRecord data
    );

    //! Initialize object DpTest
    void init(const NATIVE_INT_TYPE queueDepth,   //!< The queue depth
              const NATIVE_INT_TYPE instance = 0  //!< The instance number
    );

    //! Destroy object DpTest
    ~DpTest();

  PRIVATE:
    // ----------------------------------------------------------------------
    // Handler implementations for user-defined typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for schedIn
    void schedIn_handler(const NATIVE_INT_TYPE portNum,  //!< The port number
                         NATIVE_UINT_TYPE context        //!< The call order
                         ) override;

  PRIVATE:
    // ----------------------------------------------------------------------
    // Data product handler implementations
    // ----------------------------------------------------------------------

    //! Receive a data product container of type Container1
    //! \return Serialize status
    void Dp_Recv_Container1_handler(DpContainer& container  //!< The container
                                    ) override;

    //! Receive a data product container of type Container2
    //! \return Serialize status
    void Dp_Recv_Container2_handler(DpContainer& container  //!< The container
                                    ) override;

  PRIVATE:
    // ----------------------------------------------------------------------
    // Private member variables
    // ----------------------------------------------------------------------

    //! U32Record data
    const U32 u32RecordData;

    //! DataRecord data
    const U16 dataRecordData;
};

}  // end namespace FppTest

#endif
