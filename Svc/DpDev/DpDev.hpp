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
    // Data product handler implementations
    // ----------------------------------------------------------------------

    //! Receive a data product buffer
    void Dp_Recv_handler(DpPacket& dpPacket  //!< The data product packet
                         ) override;

    //! Receive a data product buffer for Container1
    //! \return Serialize status
    void Dp_Recv_Container1_handler(DpPacket& dpPacket  //!< The data product packet
    ) override;

    //! Receive a data product buffer for Container2
    //! \return Serialize status
    void Dp_Recv_Container2_handler(DpPacket& dpPacket  //!< The data product packet
    ) override;

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
