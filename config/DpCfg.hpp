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

namespace DpCfg {
    //! The size in bytes of the user-configurable data in the container packet
    //! header
    constexpr FwSizeType CONTAINER_USER_DATA_SIZE = 32;
};

}  // namespace Fw

#endif  // DPCFG_HPP
