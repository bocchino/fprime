// ======================================================================
//
// \title  InternalSmUtil.hpp
// \author R. Bocchino
// \brief  Header file for internal state machine test utilities
//
// \copyright
// Copyright 2024, by the California Institute of Technology.
// ALL RIGHTS RESERVED. United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef FppTest_InternalSmUtil_HPP
#define FppTest_InternalSmUtil_HPP

#include <FpConfig.hpp>

#include "STest/STest/Pick/Pick.hpp"

namespace FppTest {

namespace InternalSmUtil {

//! Pick a state machine ID
static inline FwEnumStoreType pickStateMachineId() {
    const U32 upper = FW_MIN(std::numeric_limits<FwEnumStoreType>::max(), std::numeric_limits<U32>::max());
    const U32 id = STest::Pick::lowerUpper(0, upper);
    return static_cast<FwEnumStoreType>(id);
}

}  // namespace InternalSmUtil

}  // namespace FppTest

#endif
