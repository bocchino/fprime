// ======================================================================
// @file   RangeUtils.hpp
// @author Rob Bocchino
// @brief  Utilities for range types
// ======================================================================

#ifndef FW_RANGE_UTILS
#define FW_RANGE_UTILS

#include <Fw/FPrimeBasicTypes.hpp>

namespace Fw {

//! The type of an F32 range argument, when the real type is not supported by C++14
using F32_RANGE_ARG_TYPE = U32;

//! The epsilon value for F32 floating point
constexpr F32 F32_EPSILON = 10e-6f;

//! The type of a bound
enum class BoundType {
    NONE,       //!< No bound
    INCLUSIVE,  //!< An inclusive bound
    EXCLUSIVE   //!< An exclusive bound
};

//! Bit cast F32 to F32_RANGE_ARG_TYPE
constexpr F32_RANGE_ARG_TYPE F32_RANGE_ARG(F32 f32) {
    // TODO
    return 0;
}

//! Bit cast F32_RANGE_ARG_TYPE to F32
constexpr F32 F32_RANGE_ARG_TYPE_TO_F32(F32_RANGE_ARG_TYPE f32_range_arg) {
    // TODO
    return 0.0;
}

}

#endif
