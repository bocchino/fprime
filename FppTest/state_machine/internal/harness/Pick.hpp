// ======================================================================
//
// \title  Pick.hpp
// \author R. Bocchino
// \brief  Header file for picking state machine test values
//
// \copyright
// Copyright 2024, by the California Institute of Technology.
// ALL RIGHTS RESERVED. United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef FppTest_SmHarness_Pick_HPP
#define FppTest_SmHarness_Pick_HPP

#include <FpConfig.hpp>
#include <limits>

#include "FppTest/state_machine/internal/harness/TestAbsType.hpp"
#include "FppTest/state_machine/internal/harness/TestArrayArrayAc.hpp"
#include "FppTest/state_machine/internal/harness/TestEnumEnumAc.hpp"
#include "STest/STest/Pick/Pick.hpp"

namespace FppTest {

namespace SmHarness {

namespace Pick {

//! Pick a state machine ID
static inline FwEnumStoreType stateMachineId() {
    const U32 upper = FW_MIN(std::numeric_limits<FwEnumStoreType>::max(), std::numeric_limits<U32>::max());
    const U32 id = STest::Pick::lowerUpper(0, upper);
    return static_cast<FwEnumStoreType>(id);
}

//! Pick a TestAbsType value
static inline TestAbsType testAbsType() {
    const U32 data = STest::Pick::any();
    return TestAbsType(data);
}

//! Pick a TestEnum value
static inline TestEnum testEnum() {
    const U32 u32Value = STest::Pick::startLength(0, TestEnum::NUM_CONSTANTS);
    const TestEnum::T enumValue = static_cast<TestEnum::T>(u32Value);
    return TestEnum(enumValue);
}

//! Pick a TestArray value
static inline TestArray testArray() {
    TestArray result;
    for (FwIndexType i = 0; i < TestArray::SIZE; i++) {
        result[i] = STest::Pick::any();
    }
    return result;
}

}  // namespace Pick

}  // namespace SmHarness

}  // namespace FppTest

#endif
