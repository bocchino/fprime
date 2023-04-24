// ======================================================================
// \title  DpTestDpComponentAc.hpp
// \author Generated by fpp-to-cpp
// \brief  hpp file for Data product base class for DpTest component
// ======================================================================

#ifndef FppTest_DpTestDpComponentAc_HPP
#define FppTest_DpTestDpComponentAc_HPP

#include "FpConfig.hpp"
#include "FppTest/dp/DpTestComponentAc.hpp"
#include "FppTest/dp/DpTest_DataSerializableAc.hpp"
#include "Fw/Com/ComPacket.hpp"
#include "Fw/Dp/DpContainer.hpp"
#include "Fw/Dp/DpRequestPortAc.hpp"
#include "Fw/Dp/DpResponsePortAc.hpp"
#include "Fw/Dp/DpSendPortAc.hpp"
#include "Fw/Time/TimePortAc.hpp"
#include "Svc/Sched/SchedPortAc.hpp"

namespace FppTest {

  //! \class DpTestDpComponentBase
  //! \brief Auto-generated data product base class for DpTest component
  //!
  //! A component for testing  data product code gen
  class DpTestDpComponentBase :
    public DpTestComponentBase
  {

    PROTECTED:

      // ----------------------------------------------------------------------
      // Construction and destruction
      // ----------------------------------------------------------------------

      //! Construct DpTestDpComponentBase object
      DpTestDpComponentBase(
          const char* compName = "" //!< The component name
      );

      //! Destroy DpTestDpComponentBase object
      virtual ~DpTestDpComponentBase();

    PROTECTED:

      // ----------------------------------------------------------------------
      // Functions for managing data products
      // ----------------------------------------------------------------------

      //! Request a data product container
      void Dp_Request(
          ContainerId::T containerId, //!< The container id
          FwSizeType size //!< The buffer size
      );

      //! Send a data product
      void Dp_Send(
          DpContainer& container, //!< The data product container
          Fw::Time timeTag = Fw::ZERO_TIME //!< The time tag
      );

    PRIVATE:

      // ----------------------------------------------------------------------
      // Private data product handling functions
      // ----------------------------------------------------------------------

      //! Handler implementation for productRecvIn
      void productRecvIn_handler(
          const NATIVE_INT_TYPE portNum, //!< The port number
          FwDpIdType id, //!< The container id
          const Fw::Buffer& buffer, //!< The buffer
          const Fw::Success& status //!< The buffer status
      ) override;

  };

}

#endif
