// ======================================================================
// @file   F32Range.hpp
// @author Rob Bocchino
// @brief  A wrapper type representing a numeric range
// ======================================================================

#ifndef FW_F32_RANGE
#define FW_F32_RANGE

#include <type_traits>

#include <Fw/Types/Assert.hpp>
#include <Fw/Types/BoundType.hpp>

namespace Fw {

//! The type of an F32 range argument. The real type is not supported by C++14.
using F32_RANGE_ARG_TYPE = U32;

//! The epsilon value for F32
constexpr F32 FW_F32_EPSILON = 10e-6f;

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
    // Constants
    // ----------------------------------------------------------------------

    //! The lower bound value
    static constexpr F32 lowerBoundValue = F32_RANGE_ARG_TYPE_TO_F32(LBV);

    //! The upper bound value
    static constexpr F32 upperBoundValue = F32_RANGE_ARG_TYPE_TO_F32(UBV);

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
    operator F32() const { return m_f32Value; }

    //! Assignment from a value of the base type
    F32Range& operator=(F32 f32Value) {
        FW_ASSERT(F32Range::isValid(f32Value), static_cast<FwAssertArgType>(f32Value));
        this->m_f32Value = f32Value;
        return *this;
    }

    //! Assignment from an F32 range
    template <BoundType LBT1, U32 LBV1, BoundType UBT1, U32 UBV1>
    F32Range& operator=(const F32Range<LBT1, LBV1, UBT1, UBV1>& rangeValue) {
        *this = static_cast<F32>(rangeValue);
        return *this;
    }

  public:
    // ----------------------------------------------------------------------
    // Static member functions
    // ----------------------------------------------------------------------

    //! Check whether an F32 value is valid for the range
    //! @return The result
    static constexpr bool isValid(F32 f32Value  //!< The F32 value
    ) {
        bool result = true;
        if ((LBT == BoundType::INCLUSIVE) && (f32Value < lowerBoundValue)) {
            result = false;
        } else if ((LBT == BoundType::EXCLUSIVE) && (f32Value <= lowerBoundValue)) {
            result = false;
        } else if ((UBT == BoundType::INCLUSIVE) && (f32Value > upperBoundValue)) {
            result = false;
        } else if ((UBT == BoundType::EXCLUSIVE) && (f32Value >= upperBoundValue)) {
            result = false;
        }
        return result;
    }

    //! Get the default value for the type.
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
            if (F32Range::isValid(F32Range::lowerBoundValue)) {
                defaultVal = F32Range::lowerBoundValue;
            } else {
                defaultVal = F32Range::lowerBoundValue + FW_F32_EPSILON;
            }
        } else if (UBT != BoundType::NONE) {
            if (F32Range::isValid(upperBoundValue)) {
                defaultVal = F32Range::upperBoundValue;
            } else {
                defaultVal = F32Range::upperBoundValue - FW_F32_EPSILON;
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
#define FW_F32_RANGE_INCLUSIVE(LBV, UBV) F32RangeInclusive<F32_RANGE_ARG(LBV), F32_RANGE_ARG(UBV)>

//! Convenience alias for an F32Range type with exclusive bounds
template <F32_RANGE_ARG_TYPE LBV, F32_RANGE_ARG_TYPE UBV>
using F32RangeExclusive = F32Range<BoundType::EXCLUSIVE, LBV, BoundType::EXCLUSIVE, UBV>;

// Convenience macro that hides F32_RANGE_ARG_TYPE
#define FW_F32_RANGE_EXCLUSIVE(LBV, UBV) F32RangeExclusive<F32_RANGE_ARG(LBV), F32_RANGE_ARG(UBV)>

//! Convenience alias for an F32Range type with inclusive and exclusive bounds
template <F32_RANGE_ARG_TYPE LBV, F32_RANGE_ARG_TYPE UBV>
using F32RangeInclusiveExclusive = F32Range<BoundType::INCLUSIVE, LBV, BoundType::EXCLUSIVE, UBV>;

// Convenience macro that hides F32_RANGE_ARG_TYPE
#define FW_F32_RANGE_INCLUSIVE_EXCLUSIVE(LBV, UBV) F32RangeInclusiveExclusive<F32_RANGE_ARG(LBV), F32_RANGE_ARG(UBV)>

//! Convenience alias for an F32Range type with exclusive and inclusive bounds
template <F32_RANGE_ARG_TYPE LBV, F32_RANGE_ARG_TYPE UBV>
using F32RangeExclusiveInclusive = F32Range<BoundType::EXCLUSIVE, LBV, BoundType::INCLUSIVE, UBV>;

// Convenience macro that hides F32_RANGE_ARG_TYPE
#define FW_F32_RANGE_EXCLUSIVE_INCLUSIVE(LBV, UBV) F32RangeExclusiveInclusive<F32_RANGE_ARG(LBV), F32_RANGE_ARG(UBV)>

//! Convenience alias for an F32Range type with an inclusive lower bound only
template <F32_RANGE_ARG_TYPE LBV>
using F32LowerBoundInclusive = F32Range<BoundType::INCLUSIVE, LBV, BoundType::NONE, F32_RANGE_ARG(0.0)>;

// Convenience macro that hides F32_RANGE_ARG_TYPE
#define FW_F32_LOWER_BOUND_INCLUSIVE(LBV) F32LowerBoundInclusive<F32_RANGE_ARG(LBV)>

//! Convenience alias for an F32Range type with an exclusive lower bound only
template <F32_RANGE_ARG_TYPE LBV>
using F32LowerBoundExclusive = F32Range<BoundType::EXCLUSIVE, LBV, BoundType::NONE, F32_RANGE_ARG(0.0)>;

// Convenience macro that hides F32_RANGE_ARG_TYPE
#define FW_F32_LOWER_BOUND_EXCLUSIVE(LBV) F32LowerBoundExclusive<F32_RANGE_ARG(LBV)>

//! Convenience alias for an F32Range type with an inclusive upper bound only
template <F32_RANGE_ARG_TYPE UBV>
using F32UpperBoundInclusive = F32Range<BoundType::NONE, F32_RANGE_ARG(0.0), BoundType::INCLUSIVE, UBV>;

// Convenience macro that hides F32_RANGE_ARG_TYPE
#define FW_F32_UPPER_BOUND_INCLUSIVE(UBV) F32UpperBoundInclusive<F32_RANGE_ARG(UBV)>

//! Convenience alias for an F32Range type with an exclusive upper bound only
template <F32_RANGE_ARG_TYPE UBV>
using F32UpperBoundExclusive = F32Range<BoundType::NONE, F32_RANGE_ARG(0.0), BoundType::EXCLUSIVE, UBV>;

// Convenience macro that hides F32_RANGE_ARG_TYPE
#define FW_F32_UPPER_BOUND_EXCLUSIVE(UBV) F32UpperBoundExclusive<F32_RANGE_ARG(UBV)>

}  // namespace Fw

#endif
