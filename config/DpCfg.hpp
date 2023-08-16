// ======================================================================
// \title  DpCfg.hpp
// \author Rob Bocchino
// \brief  hpp file for data products configuration
//
// \copyright
// Copyright 2023, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef DPCFG_HPP
#define DPCFG_HPP

#include "FpConfig.hpp"

namespace Fw {

class DpCfg {
    //! The type of the identifier for the kind of processing to perform on
    //! a container before writing it to disk.
    enum class ProcId : U8 {
        NONE = 255  //!< No processing
    };

    //! The size in bytes of the user-configurable data in the container packet
    //! header
    static constexpr FwSizeType CONTAINER_DATA_SIZE = 32;
};

}  // namespace Fw

#endif  // DPCFG_HPP
