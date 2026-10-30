// ======================================================================
// @file   F32Range.hpp
// @author Rob Bocchino
// @brief  A wrapper type representing a numeric range
// ======================================================================

#ifndef FW_F32_RANGE
#define FW_F32_RANGE

#include <limits>

#include <Fw/Types/Assert.hpp>
#include <Fw/Types/BoundType.hpp>

namespace Fw {

//! The type of an F32 range argument. The real type is not supported by C++14.
using F32_RANGE_ARG_TYPE = U32;

static_assert(std::numeric_limits<F32>::is_iec559 && (std::numeric_limits<F32>::digits == 24) &&
                  (sizeof(F32) == sizeof(F32_RANGE_ARG_TYPE)),
              "F32 must be an IEEE 754 binary32 type, and F32_RANGE_ARG_TYPE must have the same size");

//! \brief Bit cast F32 to F32_RANGE_ARG_TYPE
//!
//! C++14 has no constexpr bit cast, so this function works by arithmetic: it splits
//! the value into a sign, an exponent, and a mantissa, using only scalings by powers
//! of two. Each scaling is exact, so the result has the same bits as a memcpy of the
//! value, with two exceptions:
//! 1. Every NaN becomes the quiet NaN 0x7FC00000. The payload and sign are lost.
//! 2. Negative zero becomes positive zero. The two compare equal, so a range
//!    cannot tell them apart.
//!
//! The function is intended for constant expressions. At run time it may give
//! different results for subnormal values if the processor flushes them to zero.
constexpr F32_RANGE_ARG_TYPE F32_RANGE_ARG(F32 f32) {
    constexpr F32_RANGE_ARG_TYPE SIGN_BIT = 0x80000000U;
    constexpr F32_RANGE_ARG_TYPE INFINITY_BITS = 0x7F800000U;
    constexpr F32_RANGE_ARG_TYPE QUIET_NAN_BITS = 0x7FC00000U;
    constexpr I32 MANTISSA_BITS = 23;
    constexpr F32 MANTISSA_SCALE = 8388608.0f;  // 2^23
    constexpr I32 EXPONENT_BIAS = 127;
    constexpr I32 MIN_NORMAL_EXPONENT = -126;
    constexpr I32 MIN_SUBNORMAL_EXPONENT = -149;  // The smallest positive F32 is 2^-149
    // Upper bounds on the number of scalings below
    constexpr I32 MAX_SCALE_DOWN = 128;
    constexpr I32 MAX_SCALE_UP = 150;

    F32_RANGE_ARG_TYPE result = 0;
    if (f32 != f32) {
        // NaN
        result = QUIET_NAN_BITS;
    } else {
        F32_RANGE_ARG_TYPE sign = 0;
        F32 magnitude = f32;
        if (f32 < 0.0f) {
            sign = SIGN_BIT;
            magnitude = -f32;
        }
        if (magnitude > std::numeric_limits<F32>::max()) {
            // Infinity
            result = sign | INFINITY_BITS;
        } else if (magnitude > 0.0f) {
            // Scale the magnitude into the interval [1, 2), counting the powers of two
            I32 exponent = 0;
            for (I32 i = 0; (i < MAX_SCALE_DOWN) && (magnitude >= 2.0f); i++) {
                magnitude *= 0.5f;
                exponent++;
            }
            for (I32 i = 0; (i < MAX_SCALE_UP) && (magnitude < 1.0f); i++) {
                magnitude *= 2.0f;
                exponent--;
            }
            if (exponent >= MIN_NORMAL_EXPONENT) {
                // Normal: the value is (1 + mantissa / 2^23) * 2^exponent
                const F32_RANGE_ARG_TYPE exponentField = static_cast<F32_RANGE_ARG_TYPE>(exponent + EXPONENT_BIAS);
                const F32_RANGE_ARG_TYPE mantissa =
                    static_cast<F32_RANGE_ARG_TYPE>((magnitude - 1.0f) * MANTISSA_SCALE);
                result = sign | (exponentField << MANTISSA_BITS) | mantissa;
            } else {
                // Subnormal: the exponent field is zero, and the value is mantissa * 2^-149.
                // So the mantissa is magnitude * 2^(exponent + 149), which is an integer.
                for (I32 i = 0; i < exponent - MIN_SUBNORMAL_EXPONENT; i++) {
                    magnitude *= 2.0f;
                }
                result = sign | static_cast<F32_RANGE_ARG_TYPE>(magnitude);
            }
        }
        // Otherwise the value is zero, and the result is zero
    }
    return result;
}

//! \brief Bit cast F32_RANGE_ARG_TYPE to F32
//!
//! This function is the inverse of F32_RANGE_ARG. It works by arithmetic, for the
//! reasons given there. The result has the same bits as a memcpy of the argument, with
//! one exception: every NaN bit pattern gives a quiet NaN, but the payload and sign
//! are not specified.
constexpr F32 F32_RANGE_ARG_TYPE_TO_F32(F32_RANGE_ARG_TYPE f32_range_arg) {
    constexpr F32_RANGE_ARG_TYPE SIGN_BIT = 0x80000000U;
    constexpr F32_RANGE_ARG_TYPE MANTISSA_MASK = 0x007FFFFFU;
    constexpr I32 MANTISSA_BITS = 23;
    constexpr F32 MANTISSA_SCALE = 8388608.0f;  // 2^23
    constexpr F32_RANGE_ARG_TYPE EXPONENT_FIELD_MASK = 0xFFU;
    constexpr I32 EXPONENT_BIAS = 127;
    constexpr I32 SUBNORMAL_SCALE_STEPS = 149;  // The smallest positive F32 is 2^-149

    const F32_RANGE_ARG_TYPE exponentField = (f32_range_arg >> MANTISSA_BITS) & EXPONENT_FIELD_MASK;
    const F32_RANGE_ARG_TYPE mantissa = f32_range_arg & MANTISSA_MASK;
    F32 magnitude = 0.0f;
    if (exponentField == EXPONENT_FIELD_MASK) {
        // Infinity or NaN
        magnitude = (mantissa == 0) ? std::numeric_limits<F32>::infinity() : std::numeric_limits<F32>::quiet_NaN();
    } else if (exponentField == 0) {
        // Zero or subnormal: the value is mantissa * 2^-149
        magnitude = static_cast<F32>(mantissa);
        for (I32 i = 0; i < SUBNORMAL_SCALE_STEPS; i++) {
            magnitude *= 0.5f;
        }
    } else {
        // Normal: the value is (1 + mantissa / 2^23) * 2^exponent
        magnitude = 1.0f + static_cast<F32>(mantissa) / MANTISSA_SCALE;
        const I32 exponent = static_cast<I32>(exponentField) - EXPONENT_BIAS;
        for (I32 i = 0; i < exponent; i++) {
            magnitude *= 2.0f;
        }
        for (I32 i = 0; i > exponent; i--) {
            magnitude *= 0.5f;
        }
    }
    return ((f32_range_arg & SIGN_BIT) != 0) ? -magnitude : magnitude;
}

//! \brief Get the next F32 value above a given value
//!
//! This function is constexpr and does not depend on std::nextafter, which is
//! not constexpr in C++14. It steps the bit pattern of the value by one. The
//! result is intended to be the same as std::nextafter(f32, +infinity).
//!
//! The next value above zero (of either sign) is the smallest positive
//! subnormal value. The next value above the largest finite value is
//! +infinity. There is no next value above +infinity or NaN, so the result is
//! the argument.
//!
//! @return The next value above f32
constexpr F32 f32NextAbove(F32 f32) {
    F32 result = f32;
    if (f32 == f32) {
        // Not NaN
        if (f32 == 0.0f) {
            // The smallest positive subnormal value has the bit pattern 1
            result = F32_RANGE_ARG_TYPE_TO_F32(1U);
        } else if (f32 < 0.0f) {
            // For a negative value, the magnitude decreases as the bit pattern decreases
            result = F32_RANGE_ARG_TYPE_TO_F32(F32_RANGE_ARG(f32) - 1U);
        } else if (f32 < std::numeric_limits<F32>::infinity()) {
            // For a finite positive value, the magnitude increases as the bit pattern increases
            result = F32_RANGE_ARG_TYPE_TO_F32(F32_RANGE_ARG(f32) + 1U);
        }
    }
    return result;
}

//! \brief Get the next F32 value below a given value
//!
//! This function is the mirror image of f32NextAbove. There is no next value
//! below -infinity or NaN, so the result is the argument.
//!
//! @return The next value below f32
constexpr F32 f32NextBelow(F32 f32) {
    return -f32NextAbove(-f32);
}

//! \brief An F32 range parameterized by a lower bound and an upper bound
//!
//! Each of the lower bound and upper bound is expressed as F32_RANGE_ARG_TYPE because F32
//! template parameters are not allowed in C++14. If and when we move to C++20, we
//! can change F32_RANGE_ARG_TYPE to F32 and change F32_RANGE_ARG_TYPE_TO_F32 to
//! the identity function.
template <BoundType LBT, F32_RANGE_ARG_TYPE LBV, BoundType UBT, F32_RANGE_ARG_TYPE UBV>
class F32Range {
  public:
    // ----------------------------------------------------------------------
    // Constructors and destructors
    // ----------------------------------------------------------------------

    //! Construct an F32 range with the default value
    constexpr F32Range() {}

    //! Construct an F32 range from an F32 value
    constexpr F32Range(F32 f32Value) { *this = f32Value; }

  public:
    // ----------------------------------------------------------------------
    // User-defined operators
    // ----------------------------------------------------------------------

    //! Convert an F32 range to an F32 value
    constexpr operator F32() const { return m_f32Value; }

    //! Assignment from a value of the base type. If the assertion fails, the
    //! argument reported is the bit pattern of the value, not the value
    //! converted to an integer: that conversion is undefined for a value that
    //! is out of the integer range, NaN, or infinite, and those are the values
    //! that are likely to fail the assertion.
    constexpr F32Range& operator=(F32 f32Value) {
        FW_ASSERT(F32Range::isValid(f32Value), static_cast<FwAssertArgType>(F32_RANGE_ARG(f32Value)));
        this->m_f32Value = f32Value;
        return *this;
    }

  public:
    // ----------------------------------------------------------------------
    // Static member functions
    // ----------------------------------------------------------------------

    //! Check whether an F32 value is valid for the range. Each bound is
    //! checked by requiring that the comparison with the bound is true,
    //! not by rejecting a value for which the opposite comparison is true.
    //! So NaN, for which every comparison is false, is never valid for a
    //! range that has a lower bound or an upper bound.
    //! @return The result
    static constexpr bool isValid(F32 f32Value  //!< The F32 value
    ) {
        const bool lowerOK = (LBT == BoundType::NONE) ||
                             ((LBT == BoundType::INCLUSIVE) && (f32Value >= getLowerBoundValue())) ||
                             ((LBT == BoundType::EXCLUSIVE) && (f32Value > getLowerBoundValue()));
        const bool upperOK = (UBT == BoundType::NONE) ||
                             ((UBT == BoundType::INCLUSIVE) && (f32Value <= getUpperBoundValue())) ||
                             ((UBT == BoundType::EXCLUSIVE) && (f32Value < getUpperBoundValue()));
        return lowerOK && upperOK;
    }

    //! Get the lower bound value. If the range has no lower bound, the
    //! value is a placeholder and should be ignored.
    //! @return The lower bound value
    static constexpr F32 getLowerBoundValue() { return F32_RANGE_ARG_TYPE_TO_F32(LBV); }

    //! Get the upper bound value. If the range has no upper bound, the
    //! value is a placeholder and should be ignored.
    //! @return The upper bound value
    static constexpr F32 getUpperBoundValue() { return F32_RANGE_ARG_TYPE_TO_F32(UBV); }

    //! Get the default value for the type, and statically check
    //! that the value is valid. Choose the default value as follows:
    //! 1. If the range has no lower bound and no upper bound, then use zero.
    //! 2. Otherwise, if the range has a lower bound, then
    //!    a. If the lower bound is in range, then use it.
    //!    b. Otherwise use the next F32 value above the lower bound.
    //! 3. Otherwise, the range has only an upper bound. In this case
    //!    a. If the upper bound is in range, then use it.
    //!    b. Otherwise use the next F32 value below the upper bound.
    //!
    //! If the lower bound is +infinity, then there is no next value above it,
    //! and the default value is the lower bound, which is not in range. Likewise
    //! if the upper bound is -infinity. In either case the range is empty and
    //! the static assertion fails.
    //!
    //! @return The default value
    static constexpr F32 getDefaultValue() {
        constexpr F32 defaultValue = computeDefaultValue();
        static_assert(F32Range::isValid(defaultValue), "An F32 range must contain at least one valid value");
        return defaultValue;
    }

  private:
    // ----------------------------------------------------------------------
    // Private helper functions
    // ----------------------------------------------------------------------

    //! Compute the default value for the range type.
    //! @return The default value
    static constexpr F32 computeDefaultValue() {
        F32 defaultVal{};
        if (LBT != BoundType::NONE) {
            if (F32Range::isValid(getLowerBoundValue())) {
                defaultVal = getLowerBoundValue();
            } else {
                // The lower bound is not valid, so try the next value above it.
                // If the lower bound is +infinity, the next value is the lower
                // bound, so the range is reported as empty.
                defaultVal = f32NextAbove(getLowerBoundValue());
            }
        } else if (UBT != BoundType::NONE) {
            // There is only an upper bound (the placeholder LBV is ignored)
            if (F32Range::isValid(getUpperBoundValue())) {
                defaultVal = getUpperBoundValue();
            } else {
                // The upper bound is not valid, so try the next value below it.
                // If the upper bound is -infinity, the next value is the upper
                // bound, so the range is reported as empty.
                defaultVal = f32NextBelow(getUpperBoundValue());
            }
        }
        return defaultVal;
    }

  private:
    // ----------------------------------------------------------------------
    // Private member variables
    // ----------------------------------------------------------------------

    //! The F32 value within the range
    F32 m_f32Value = getDefaultValue();
};

//! Convenience alias for an F32Range type with inclusive bounds
template <F32_RANGE_ARG_TYPE LBV, F32_RANGE_ARG_TYPE UBV>
using F32RangeInclusive = F32Range<BoundType::INCLUSIVE, LBV, BoundType::INCLUSIVE, UBV>;

// Convenience macro that hides F32_RANGE_ARG_TYPE
#define FW_F32_RANGE_INCLUSIVE(LBV, UBV) Fw::F32RangeInclusive<Fw::F32_RANGE_ARG(LBV), Fw::F32_RANGE_ARG(UBV)>

//! Convenience alias for an F32Range type with exclusive bounds
template <F32_RANGE_ARG_TYPE LBV, F32_RANGE_ARG_TYPE UBV>
using F32RangeExclusive = F32Range<BoundType::EXCLUSIVE, LBV, BoundType::EXCLUSIVE, UBV>;

// Convenience macro that hides F32_RANGE_ARG_TYPE
#define FW_F32_RANGE_EXCLUSIVE(LBV, UBV) Fw::F32RangeExclusive<Fw::F32_RANGE_ARG(LBV), Fw::F32_RANGE_ARG(UBV)>

//! Convenience alias for an F32Range type with inclusive and exclusive bounds
template <F32_RANGE_ARG_TYPE LBV, F32_RANGE_ARG_TYPE UBV>
using F32RangeInclusiveExclusive = F32Range<BoundType::INCLUSIVE, LBV, BoundType::EXCLUSIVE, UBV>;

// Convenience macro that hides F32_RANGE_ARG_TYPE
#define FW_F32_RANGE_INCLUSIVE_EXCLUSIVE(LBV, UBV) \
    Fw::F32RangeInclusiveExclusive<Fw::F32_RANGE_ARG(LBV), Fw::F32_RANGE_ARG(UBV)>

//! Convenience alias for an F32Range type with exclusive and inclusive bounds
template <F32_RANGE_ARG_TYPE LBV, F32_RANGE_ARG_TYPE UBV>
using F32RangeExclusiveInclusive = F32Range<BoundType::EXCLUSIVE, LBV, BoundType::INCLUSIVE, UBV>;

// Convenience macro that hides F32_RANGE_ARG_TYPE
#define FW_F32_RANGE_EXCLUSIVE_INCLUSIVE(LBV, UBV) \
    Fw::F32RangeExclusiveInclusive<Fw::F32_RANGE_ARG(LBV), Fw::F32_RANGE_ARG(UBV)>

//! Convenience alias for an F32Range type with an inclusive lower bound only
template <F32_RANGE_ARG_TYPE LBV>
using F32LowerBoundInclusive = F32Range<BoundType::INCLUSIVE, LBV, BoundType::NONE, F32_RANGE_ARG(0.0)>;

// Convenience macro that hides F32_RANGE_ARG_TYPE
#define FW_F32_LOWER_BOUND_INCLUSIVE(LBV) Fw::F32LowerBoundInclusive<Fw::F32_RANGE_ARG(LBV)>

//! Convenience alias for an F32Range type with an exclusive lower bound only
template <F32_RANGE_ARG_TYPE LBV>
using F32LowerBoundExclusive = F32Range<BoundType::EXCLUSIVE, LBV, BoundType::NONE, F32_RANGE_ARG(0.0)>;

// Convenience macro that hides F32_RANGE_ARG_TYPE
#define FW_F32_LOWER_BOUND_EXCLUSIVE(LBV) Fw::F32LowerBoundExclusive<Fw::F32_RANGE_ARG(LBV)>

//! Convenience alias for an F32Range type with an inclusive upper bound only
template <F32_RANGE_ARG_TYPE UBV>
using F32UpperBoundInclusive = F32Range<BoundType::NONE, F32_RANGE_ARG(0.0), BoundType::INCLUSIVE, UBV>;

// Convenience macro that hides F32_RANGE_ARG_TYPE
#define FW_F32_UPPER_BOUND_INCLUSIVE(UBV) Fw::F32UpperBoundInclusive<Fw::F32_RANGE_ARG(UBV)>

//! Convenience alias for an F32Range type with an exclusive upper bound only
template <F32_RANGE_ARG_TYPE UBV>
using F32UpperBoundExclusive = F32Range<BoundType::NONE, F32_RANGE_ARG(0.0), BoundType::EXCLUSIVE, UBV>;

// Convenience macro that hides F32_RANGE_ARG_TYPE
#define FW_F32_UPPER_BOUND_EXCLUSIVE(UBV) Fw::F32UpperBoundExclusive<Fw::F32_RANGE_ARG(UBV)>

}  // namespace Fw

#endif
