// ======================================================================
// @file   RangeUtils.hpp
// @author Rob Bocchino
// @brief  Utilities for range types
// ======================================================================

#ifndef FW_RANGE_UTILS
#define FW_RANGE_UTILS

#include <Fw/FPrimeBasicTypes.hpp>

namespace Fw {

//! The type of a range argument, when the real type is not supported by C++14
using RANGE_ARG = U32;

//! The epsilon value for F32 floating point
constexpr F32 F32_EPSILON = 10e-6f;

//! The type of a bound
enum class BoundType {
    NONE,       //!< No bound
    INCLUSIVE,  //!< An inclusive bound
    EXCLUSIVE   //!< An exclusive bound
};

//! Bit cast F32 to U32
constexpr U32 F32_TO_ARG(F32 f) {
    if (f == 0.0f) {
        // Check for negative zero (-0.0f)
        return (1.0f / f < 0.0f) ? 0x80000000 : 0x00000000;
    }

    // Handle Special Cases
    if (f != f) return 0x7FC00000; // NaN
    if (f == 1.0f / 0.0f) return 0x7F800000; // Positive Infinity
    if (f == -1.0f / 0.0f) return 0xFF800000; // Negative Infinity

    U32 sign = 0;
    if (f < 0.0f) {
        sign = 0x80000000;
        f = -f;
    }

    // Binary search to find the exponent
    I32 exp = 0;
    F32 base = f;

    if (base >= 1.0f) {
        for (I32 i = 64; i > 0; i /= 2) {
            // Approximating 2^i statically without std::pow
            F32 p = 1.0f;
            for(I32 j=0; j<i; ++j) p *= 2.0f;
            if (base >= p) { base /= p; exp += i; }
        }
    } else {
        for (I32 i = 64; i > 0; i /= 2) {
            F32 p = 1.0f;
            for(I32 j=0; j<i; ++j) p *= 2.0f;
            if (base < 1.0f / p) { base *= p; exp -= i; }
        }
        if (base < 1.0f) { base *= 2.0f; exp -= 1; }
    }

    // Handle denormalized numbers
    if (exp < -126) {
        I32 shift = -126 - exp;
        if (shift >= 24) return sign;
        U32 mantissa = static_cast<U32>(base * 8388608.0f);
        return sign | (mantissa >> shift);
    }

    // Normalize exponent and mantissa
    U32 biased_exp = static_cast<U32>(exp + 127);
    U32 mantissa = static_cast<U32>((base - 1.0f) * 8388608.0f + 0.5f);

    return sign | (biased_exp << 23) | (mantissa & 0x7FFFFF);
}

//! Bit cast U32 to F32
constexpr F32 RANGE_ARG_TO_F32(U32 bits) {
    // Extract IEEE 754 fields
    U32 sign_bit = (bits >> 31) & 1;
    U32 exp_bits = (bits >> 23) & 0xFF;
    U32 mant_bits = bits & 0x7FFFFF;

    float sign = sign_bit ? -1.0f : 1.0f;

    // Special Case: Exponent is 255 (NaN or Infinity)
    if (exp_bits == 255) {
        if (mant_bits != 0) {
            return 0.0f / 0.0f; // NaN
        }
        return sign * (1.0f / 0.0f); // Infinity
    }

    // Special Case: Exponent is 0 (Zero or Subnormal/Denormalized)
    if (exp_bits == 0) {
        if (mant_bits == 0) {
            return sign * 0.0f; // Positive or Negative Zero
        }
        // Subnormal number: implicit leading bit is 0, exponent is fixed at -126
        float mantissa = static_cast<float>(mant_bits) / 8388608.0f;

        // Statically compute 2^-126
        float p = 1.0f;
        for (I32 i = 0; i < 126; ++i) p /= 2.0f;

        return sign * mantissa * p;
    }

    // Normal Case
    I32 exp = static_cast<I32>(exp_bits) - 127;
    float mantissa = 1.0f + (static_cast<float>(mant_bits) / 8388608.0f);

    // Statically compute 2^exp using a binary loop
    float pow2 = 1.0f;
    if (exp > 0) {
        for (I32 i = 0; i < exp; ++i) pow2 *= 2.0f;
    } else if (exp < 0) {
        for (I32 i = 0; i < -exp; ++i) pow2 /= 2.0f;
    }

    return sign * mantissa * pow2;
}

}

#endif
