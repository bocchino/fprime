// ======================================================================
// \title  DpDev.hpp
// \author bocchino
// \brief  hpp file for DpDev component implementation class
// ======================================================================

#ifndef Svc_DpDev_HPP
#define Svc_DpDev_HPP

#include "Svc/DpDev/DpDevDpComponentBase.hpp"

namespace Svc {

class DpDev : public DpDevDpComponentBase {
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

    //! Construct object DpDev
    DpDev(const char* const compName,  //!< The component name
          U32 u32RecordData,           //!< The U32Record data
          U32 dataRecordData           //!< The DataRecord data
    );

    //! Initialize object DpDev
    void init(const NATIVE_INT_TYPE queueDepth,   //!< The queue depth
              const NATIVE_INT_TYPE instance = 0  //!< The instance number
    );

    //! Destroy object DpDev
    ~DpDev();

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
    // Implementation of the data product write handler
    // ----------------------------------------------------------------------

    //! Receive a data product buffer
    void Dp_Recv_handler(DpPacket& dpPacket  //!< The data product packet
                         ) override;

  PRIVATE:
    // ----------------------------------------------------------------------
    // Private helper functions
    // ----------------------------------------------------------------------

    //! Fill a data product packet for Container 1
    //! \return Serialize status
    Fw::SerializeStatus fillContainer1(DpPacket& dpPacket  //!< The data product packet
    ) const;

    //! Fill a data product packet for Container 2
    //! \return Serialize status
    Fw::SerializeStatus fillContainer2(DpPacket& dpPacket  //!< The data product packet
    ) const;

  PRIVATE:
    // ----------------------------------------------------------------------
    // Private member variables
    // ----------------------------------------------------------------------

    //! U32Record data
    const U32 u32RecordData;

    //! DataRecord data
    const U32 dataRecordData;
};

}  // end namespace Svc

#endif
