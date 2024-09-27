// ======================================================================
//
// \title  Util.hpp
// \author R. Bocchino
// \brief  Header file for state machine test utilities
//
// \copyright
// Copyright 2024, by the California Institute of Technology.
// ALL RIGHTS RESERVED. United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef FppTest_SmHarness_Util_HPP
#define FppTest_SmHarness_Util_HPP

#include <FpConfig.hpp>

#include "FppTest/state_machine/internal/harness/TestAbsType.hpp"
#include "STest/STest/Pick/Pick.hpp"

namespace FppTest {

namespace SmHarness {

//! Pick a state machine ID
static inline FwEnumStoreType pickStateMachineId() {
    const U32 upper = FW_MIN(std::numeric_limits<FwEnumStoreType>::max(), std::numeric_limits<U32>::max());
    const U32 id = STest::Pick::lowerUpper(0, upper);
    return static_cast<FwEnumStoreType>(id);
}

//! Pick a TestAbsType value
static inline TestAbsType pickTestAbsType() {
    const U32 data = STest::Pick::any();
    return TestAbsType(data);
}

}  // namespace SmHarness

}  // namespace FppTest

#endif
