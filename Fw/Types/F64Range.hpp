// ======================================================================
// @file   F64Range.hpp
// @author Rob Bocchino
// @brief  A wrapper type representing an F64 range
// ======================================================================

#ifndef FW_F64_RANGE
#define FW_F64_RANGE

#include <limits>

#include <Fw/Types/Assert.hpp>
#include <Fw/Types/BoundType.hpp>

namespace Fw {

//! The type of an F64 range argument. The real type is not supported by C++14.
using F64_RANGE_ARG_TYPE = U64;

static_assert(std::numeric_limits<F64>::is_iec559 && (std::numeric_limits<F64>::digits == 53) &&
                  (sizeof(F64) == sizeof(F64_RANGE_ARG_TYPE)),
              "F64 must be an IEEE 754 binary64 type, and F64_RANGE_ARG_TYPE must have the same size");

//! \brief Bit cast F64 to F64_RANGE_ARG_TYPE
//!
//! C++14 has no constexpr bit cast, so this function works by arithmetic: it splits
//! the value into a sign, an exponent, and a mantissa, using only scalings by powers
//! of two. Each scaling is exact, so the result has the same bits as a memcpy of the
//! value, with two exceptions:
//! 1. Every NaN becomes the quiet NaN 0x7FF8000000000000. The payload and sign are lost.
//! 2. Negative zero becomes positive zero. The two compare equal, so a range
//!    cannot tell them apart.
//!
//! The function is intended for constant expressions. At run time it may give
//! different results for subnormal values if the processor flushes them to zero.
constexpr F64_RANGE_ARG_TYPE F64_RANGE_ARG(F64 f64) {
    constexpr F64_RANGE_ARG_TYPE SIGN_BIT = 0x8000000000000000ULL;
    constexpr F64_RANGE_ARG_TYPE INFINITY_BITS = 0x7FF0000000000000ULL;
    constexpr F64_RANGE_ARG_TYPE QUIET_NAN_BITS = 0x7FF8000000000000ULL;
    constexpr I32 MANTISSA_BITS = 52;
    constexpr F64 MANTISSA_SCALE = 4503599627370496.0;  // 2^52
    constexpr I32 EXPONENT_BIAS = 1023;
    constexpr I32 MIN_NORMAL_EXPONENT = -1022;
    constexpr I32 MIN_SUBNORMAL_EXPONENT = -1074;  // The smallest positive F64 is 2^-1074
    // Upper bounds on the number of scalings below
    constexpr I32 MAX_SCALE_DOWN = 1024;
    constexpr I32 MAX_SCALE_UP = 1075;

    F64_RANGE_ARG_TYPE result = 0;
    if (f64 != f64) {
        // NaN
        result = QUIET_NAN_BITS;
    } else {
        F64_RANGE_ARG_TYPE sign = 0;
        F64 magnitude = f64;
        if (f64 < 0.0) {
            sign = SIGN_BIT;
            magnitude = -f64;
        }
        if (magnitude > std::numeric_limits<F64>::max()) {
            // Infinity
            result = sign | INFINITY_BITS;
        } else if (magnitude > 0.0) {
            // Scale the magnitude into the interval [1, 2), counting the powers of two
            I32 exponent = 0;
            for (I32 i = 0; (i < MAX_SCALE_DOWN) && (magnitude >= 2.0); i++) {
                magnitude *= 0.5;
                exponent++;
            }
            for (I32 i = 0; (i < MAX_SCALE_UP) && (magnitude < 1.0); i++) {
                magnitude *= 2.0;
                exponent--;
            }
            if (exponent >= MIN_NORMAL_EXPONENT) {
                // Normal: the value is (1 + mantissa / 2^52) * 2^exponent
                const F64_RANGE_ARG_TYPE exponentField = static_cast<F64_RANGE_ARG_TYPE>(exponent + EXPONENT_BIAS);
                const F64_RANGE_ARG_TYPE mantissa = static_cast<F64_RANGE_ARG_TYPE>((magnitude - 1.0) * MANTISSA_SCALE);
                result = sign | (exponentField << MANTISSA_BITS) | mantissa;
            } else {
                // Subnormal: the exponent field is zero, and the value is mantissa * 2^-1074.
                // So the mantissa is magnitude * 2^(exponent + 1074), which is an integer.
                for (I32 i = 0; i < exponent - MIN_SUBNORMAL_EXPONENT; i++) {
                    magnitude *= 2.0;
                }
                result = sign | static_cast<F64_RANGE_ARG_TYPE>(magnitude);
            }
        }
        // Otherwise the value is zero, and the result is zero
    }
    return result;
}

//! \brief Bit cast F64_RANGE_ARG_TYPE to F64
//!
//! This function is the inverse of F64_RANGE_ARG. It works by arithmetic, for the
//! reasons given there. The result has the same bits as a memcpy of the argument, with
//! one exception: every NaN bit pattern gives a quiet NaN, but the payload and sign
//! are not specified.
constexpr F64 F64_RANGE_ARG_TYPE_TO_F64(F64_RANGE_ARG_TYPE f64_range_arg) {
    constexpr F64_RANGE_ARG_TYPE SIGN_BIT = 0x8000000000000000ULL;
    constexpr F64_RANGE_ARG_TYPE MANTISSA_MASK = 0x000FFFFFFFFFFFFFULL;
    constexpr I32 MANTISSA_BITS = 52;
    constexpr F64 MANTISSA_SCALE = 4503599627370496.0;  // 2^52
    constexpr F64_RANGE_ARG_TYPE EXPONENT_FIELD_MASK = 0x7FFU;
    constexpr I32 EXPONENT_BIAS = 1023;
    constexpr I32 SUBNORMAL_SCALE_STEPS = 1074;  // The smallest positive F64 is 2^-1074

    const F64_RANGE_ARG_TYPE exponentField = (f64_range_arg >> MANTISSA_BITS) & EXPONENT_FIELD_MASK;
    const F64_RANGE_ARG_TYPE mantissa = f64_range_arg & MANTISSA_MASK;
    F64 magnitude = 0.0;
    if (exponentField == EXPONENT_FIELD_MASK) {
        // Infinity or NaN
        magnitude = (mantissa == 0) ? std::numeric_limits<F64>::infinity() : std::numeric_limits<F64>::quiet_NaN();
    } else if (exponentField == 0) {
        // Zero or subnormal: the value is mantissa * 2^-1074
        magnitude = static_cast<F64>(mantissa);
        for (I32 i = 0; i < SUBNORMAL_SCALE_STEPS; i++) {
            magnitude *= 0.5;
        }
    } else {
        // Normal: the value is (1 + mantissa / 2^52) * 2^exponent
        magnitude = 1.0 + static_cast<F64>(mantissa) / MANTISSA_SCALE;
        const I32 exponent = static_cast<I32>(exponentField) - EXPONENT_BIAS;
        for (I32 i = 0; i < exponent; i++) {
            magnitude *= 2.0;
        }
        for (I32 i = 0; i > exponent; i--) {
            magnitude *= 0.5;
        }
    }
    return ((f64_range_arg & SIGN_BIT) != 0) ? -magnitude : magnitude;
}

//! \brief Get the next F64 value above a given value
//!
//! This function is constexpr and does not depend on std::nextafter, which is
//! not constexpr in C++14. It steps the bit pattern of the value by one. The
//! result is intended to be the same as std::nextafter(f64, +infinity).
//!
//! The next value above zero (of either sign) is the smallest positive
//! subnormal value. The next value above the largest finite value is
//! +infinity. There is no next value above +infinity or NaN, so the result is
//! the argument.
//!
//! @return The next value above f64
constexpr F64 f64NextAbove(F64 f64) {
    F64 result = f64;
    if (f64 == f64) {
        // Not NaN
        if (f64 == 0.0) {
            // The smallest positive subnormal value has the bit pattern 1
            result = F64_RANGE_ARG_TYPE_TO_F64(1U);
        } else if (f64 < 0.0) {
            // For a negative value, the magnitude decreases as the bit pattern decreases
            result = F64_RANGE_ARG_TYPE_TO_F64(F64_RANGE_ARG(f64) - 1U);
        } else if (f64 < std::numeric_limits<F64>::infinity()) {
            // For a finite positive value, the magnitude increases as the bit pattern increases
            result = F64_RANGE_ARG_TYPE_TO_F64(F64_RANGE_ARG(f64) + 1U);
        }
    }
    return result;
}

//! \brief Get the next F64 value below a given value
//!
//! This function is the mirror image of f64NextAbove. There is no next value
//! below -infinity or NaN, so the result is the argument.
//!
//! @return The next value below f64
constexpr F64 f64NextBelow(F64 f64) {
    return -f64NextAbove(-f64);
}

//! \brief An F64 range parameterized by a lower bound and an upper bound
//!
//! Each of the lower bound and upper bound is expressed as F64_RANGE_ARG_TYPE because F64
//! template parameters are not allowed in C++14. If and when we move to C++20, we
//! can change F64_RANGE_ARG_TYPE to F64 and change F64_RANGE_ARG_TYPE_TO_F64 to
//! the identity function.
template <BoundType LBT, F64_RANGE_ARG_TYPE LBV, BoundType UBT, F64_RANGE_ARG_TYPE UBV>
class F64Range {
  public:
    // ----------------------------------------------------------------------
    // Constructors and destructors
    // ----------------------------------------------------------------------

    //! Construct an F64 range with the default value
    constexpr F64Range() {}

    //! Construct an F64 range from an F64 value
    constexpr F64Range(F64 f64Value) { *this = f64Value; }

  public:
    // ----------------------------------------------------------------------
    // User-defined operators
    // ----------------------------------------------------------------------

    //! Convert an F64 range to an F64 value
    constexpr operator F64() const { return m_f64Value; }

    //! Assignment from a value of the base type. If the assertion fails, the
    //! arguments reported are the high and low halves of the bit pattern of the
    //! value, not the value converted to an integer: that conversion is
    //! undefined for a value that is out of the integer range, NaN, or
    //! infinite, and those are the values that are likely to fail the
    //! assertion. The bit pattern has 64 bits, and FwAssertArgType may have
    //! only 32, so the pattern is reported as two arguments.
    constexpr F64Range& operator=(F64 f64Value) {
        FW_ASSERT(F64Range::isValid(f64Value), static_cast<FwAssertArgType>(F64_RANGE_ARG(f64Value) >> 32),
                  static_cast<FwAssertArgType>(F64_RANGE_ARG(f64Value) & 0xFFFFFFFFU));
        this->m_f64Value = f64Value;
        return *this;
    }

  public:
    // ----------------------------------------------------------------------
    // Static member functions
    // ----------------------------------------------------------------------

    //! Check whether an F64 value is valid for the range. Each bound is
    //! checked by requiring that the comparison with the bound is true,
    //! not by rejecting a value for which the opposite comparison is true.
    //! So NaN, for which every comparison is false, is never valid for a
    //! range that has a lower bound or an upper bound.
    //! @return The result
    static constexpr bool isValid(F64 f64Value  //!< The F64 value
    ) {
        const bool lowerOK = (LBT == BoundType::NONE) ||
                             ((LBT == BoundType::INCLUSIVE) && (f64Value >= getLowerBoundValue())) ||
                             ((LBT == BoundType::EXCLUSIVE) && (f64Value > getLowerBoundValue()));
        const bool upperOK = (UBT == BoundType::NONE) ||
                             ((UBT == BoundType::INCLUSIVE) && (f64Value <= getUpperBoundValue())) ||
                             ((UBT == BoundType::EXCLUSIVE) && (f64Value < getUpperBoundValue()));
        return lowerOK && upperOK;
    }

    //! Get the lower bound value. If the range has no lower bound, the
    //! value is a placeholder and should be ignored.
    //! @return The lower bound value
    static constexpr F64 getLowerBoundValue() { return F64_RANGE_ARG_TYPE_TO_F64(LBV); }

    //! Get the upper bound value. If the range has no upper bound, the
    //! value is a placeholder and should be ignored.
    //! @return The upper bound value
    static constexpr F64 getUpperBoundValue() { return F64_RANGE_ARG_TYPE_TO_F64(UBV); }

    //! Get the default value for the type, and statically check
    //! that the value is valid. Choose the default value as follows:
    //! 1. If the range has no lower bound and no upper bound, then use zero.
    //! 2. Otherwise, if the range has a lower bound, then
    //!    a. If the lower bound is in range, then use it.
    //!    b. Otherwise use the next F64 value above the lower bound.
    //! 3. Otherwise, the range has only an upper bound. In this case
    //!    a. If the upper bound is in range, then use it.
    //!    b. Otherwise use the next F64 value below the upper bound.
    //!
    //! If the lower bound is +infinity, then there is no next value above it,
    //! and the default value is the lower bound, which is not in range. Likewise
    //! if the upper bound is -infinity. In either case the range is empty and
    //! the static assertion fails.
    //!
    //! @return The default value
    static constexpr F64 getDefaultValue() {
        constexpr F64 defaultValue = computeDefaultValue();
        static_assert(F64Range::isValid(defaultValue), "An F64 range must contain at least one valid value");
        return defaultValue;
    }

  private:
    // ----------------------------------------------------------------------
    // Private helper functions
    // ----------------------------------------------------------------------

    //! Compute the default value for the range type.
    //! @return The default value
    static constexpr F64 computeDefaultValue() {
        F64 defaultVal{};
        if (LBT != BoundType::NONE) {
            if (F64Range::isValid(getLowerBoundValue())) {
                defaultVal = getLowerBoundValue();
            } else {
                // The lower bound is not valid, so try the next value above it.
                // If the lower bound is +infinity, the next value is the lower
                // bound, so the range is reported as empty.
                defaultVal = f64NextAbove(getLowerBoundValue());
            }
        } else if (UBT != BoundType::NONE) {
            // There is only an upper bound (the placeholder LBV is ignored)
            if (F64Range::isValid(getUpperBoundValue())) {
                defaultVal = getUpperBoundValue();
            } else {
                // The upper bound is not valid, so try the next value below it.
                // If the upper bound is -infinity, the next value is the upper
                // bound, so the range is reported as empty.
                defaultVal = f64NextBelow(getUpperBoundValue());
            }
        }
        return defaultVal;
    }

  private:
    // ----------------------------------------------------------------------
    // Private member variables
    // ----------------------------------------------------------------------

    //! The F64 value within the range
    F64 m_f64Value = getDefaultValue();
};

//! Convenience alias for an F64Range type with inclusive bounds
template <F64_RANGE_ARG_TYPE LBV, F64_RANGE_ARG_TYPE UBV>
using F64RangeInclusive = F64Range<BoundType::INCLUSIVE, LBV, BoundType::INCLUSIVE, UBV>;

// Convenience macro that hides F64_RANGE_ARG_TYPE
#define FW_F64_RANGE_INCLUSIVE(LBV, UBV) Fw::F64RangeInclusive<Fw::F64_RANGE_ARG(LBV), Fw::F64_RANGE_ARG(UBV)>

//! Convenience alias for an F64Range type with exclusive bounds
template <F64_RANGE_ARG_TYPE LBV, F64_RANGE_ARG_TYPE UBV>
using F64RangeExclusive = F64Range<BoundType::EXCLUSIVE, LBV, BoundType::EXCLUSIVE, UBV>;

// Convenience macro that hides F64_RANGE_ARG_TYPE
#define FW_F64_RANGE_EXCLUSIVE(LBV, UBV) Fw::F64RangeExclusive<Fw::F64_RANGE_ARG(LBV), Fw::F64_RANGE_ARG(UBV)>

//! Convenience alias for an F64Range type with inclusive and exclusive bounds
template <F64_RANGE_ARG_TYPE LBV, F64_RANGE_ARG_TYPE UBV>
using F64RangeInclusiveExclusive = F64Range<BoundType::INCLUSIVE, LBV, BoundType::EXCLUSIVE, UBV>;

// Convenience macro that hides F64_RANGE_ARG_TYPE
#define FW_F64_RANGE_INCLUSIVE_EXCLUSIVE(LBV, UBV) \
    Fw::F64RangeInclusiveExclusive<Fw::F64_RANGE_ARG(LBV), Fw::F64_RANGE_ARG(UBV)>

//! Convenience alias for an F64Range type with exclusive and inclusive bounds
template <F64_RANGE_ARG_TYPE LBV, F64_RANGE_ARG_TYPE UBV>
using F64RangeExclusiveInclusive = F64Range<BoundType::EXCLUSIVE, LBV, BoundType::INCLUSIVE, UBV>;

// Convenience macro that hides F64_RANGE_ARG_TYPE
#define FW_F64_RANGE_EXCLUSIVE_INCLUSIVE(LBV, UBV) \
    Fw::F64RangeExclusiveInclusive<Fw::F64_RANGE_ARG(LBV), Fw::F64_RANGE_ARG(UBV)>

//! Convenience alias for an F64Range type with an inclusive lower bound only
template <F64_RANGE_ARG_TYPE LBV>
using F64LowerBoundInclusive = F64Range<BoundType::INCLUSIVE, LBV, BoundType::NONE, F64_RANGE_ARG(0.0)>;

// Convenience macro that hides F64_RANGE_ARG_TYPE
#define FW_F64_LOWER_BOUND_INCLUSIVE(LBV) Fw::F64LowerBoundInclusive<Fw::F64_RANGE_ARG(LBV)>

//! Convenience alias for an F64Range type with an exclusive lower bound only
template <F64_RANGE_ARG_TYPE LBV>
using F64LowerBoundExclusive = F64Range<BoundType::EXCLUSIVE, LBV, BoundType::NONE, F64_RANGE_ARG(0.0)>;

// Convenience macro that hides F64_RANGE_ARG_TYPE
#define FW_F64_LOWER_BOUND_EXCLUSIVE(LBV) Fw::F64LowerBoundExclusive<Fw::F64_RANGE_ARG(LBV)>

//! Convenience alias for an F64Range type with an inclusive upper bound only
template <F64_RANGE_ARG_TYPE UBV>
using F64UpperBoundInclusive = F64Range<BoundType::NONE, F64_RANGE_ARG(0.0), BoundType::INCLUSIVE, UBV>;

// Convenience macro that hides F64_RANGE_ARG_TYPE
#define FW_F64_UPPER_BOUND_INCLUSIVE(UBV) Fw::F64UpperBoundInclusive<Fw::F64_RANGE_ARG(UBV)>

//! Convenience alias for an F64Range type with an exclusive upper bound only
template <F64_RANGE_ARG_TYPE UBV>
using F64UpperBoundExclusive = F64Range<BoundType::NONE, F64_RANGE_ARG(0.0), BoundType::EXCLUSIVE, UBV>;

// Convenience macro that hides F64_RANGE_ARG_TYPE
#define FW_F64_UPPER_BOUND_EXCLUSIVE(UBV) Fw::F64UpperBoundExclusive<Fw::F64_RANGE_ARG(UBV)>

}  // namespace Fw

#endif
