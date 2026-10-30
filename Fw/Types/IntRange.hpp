// ======================================================================
// @file   IntRange.hpp
// @author Rob Bocchino
// @brief  A type representing an integer range
// ======================================================================

#ifndef FW_INT_RANGE
#define FW_INT_RANGE

#include <limits>
#include <type_traits>

#include <Fw/Types/Assert.hpp>
#include <Fw/Types/RangeUtils.hpp>

namespace Fw {

namespace IntRangeDetail {

//! Exact comparison a < b for two integers of the same signedness
template <typename A, typename B, bool IS_SIGNED>
constexpr bool lessThanImpl(A a,
                            B b,
                            std::integral_constant<bool, IS_SIGNED>,
                            std::integral_constant<bool, IS_SIGNED>) {
    return a < b;
}

//! Exact comparison a < b for a signed integer a and an unsigned integer b
template <typename A, typename B>
constexpr bool lessThanImpl(A a, B b, std::true_type, std::false_type) {
    return (a < 0) || (static_cast<typename std::make_unsigned<A>::type>(a) < b);
}

//! Exact comparison a < b for an unsigned integer a and a signed integer b
template <typename A, typename B>
constexpr bool lessThanImpl(A a, B b, std::false_type, std::true_type) {
    return (b >= 0) && (a < static_cast<typename std::make_unsigned<B>::type>(b));
}

//! Exact comparison a < b for two integers of any widths and signedness.
//! The comparison is performed on the mathematical values, so the result is
//! never affected by wraparound or sign conversion.
template <typename A, typename B>
constexpr bool lessThan(A a, B b) {
    return lessThanImpl(a, b, std::is_signed<A>(), std::is_signed<B>());
}

}  // namespace IntRangeDetail

//! An integer range parameterized by an integral type, a lower bound, and an
//! upper bound
template <typename T, BoundType LBT, T LBV, BoundType UBT, T UBV>
class IntRange {
    static_assert(std::is_integral<T>::value, "The base type of an integer range must be an integral type");

  public:
    // ----------------------------------------------------------------------
    // Constructors and destructors
    // ----------------------------------------------------------------------

    //! Construct an integer range with the default value
    constexpr IntRange() {}

    //! Construct an integer range from an integer value
    constexpr IntRange(T intValue) { *this = intValue; }

    //! Construct an integer range from another integer range, which may have
    //! a different base type and different bounds
    template <typename T1, BoundType LBT1, T1 LBV1, BoundType UBT1, T1 UBV1>
    constexpr IntRange(const IntRange<T1, LBT1, LBV1, UBT1, UBV1>& rangeValue) {
        *this = rangeValue;
    }

  public:
    // ----------------------------------------------------------------------
    // User-defined operators
    // ----------------------------------------------------------------------

    //! Convert an integer range to an integer value
    constexpr operator T() const { return m_intValue; }

    //! Assignment from a value of the base type
    constexpr IntRange& operator=(T intValue) {
        FW_ASSERT(IntRange::isValid(intValue), static_cast<FwAssertArgType>(intValue));
        this->m_intValue = intValue;
        return *this;
    }

    //! Assignment from an integer range. The source value is checked against
    //! the bounds of this range at the width and signedness of the source
    //! base type, and only then converted to the base type of this range.
    //! So a value that is out of range is never truncated into range.
    template <typename T1, BoundType LBT1, T1 LBV1, BoundType UBT1, T1 UBV1>
    constexpr IntRange& operator=(const IntRange<T1, LBT1, LBV1, UBT1, UBV1>& rangeValue) {
        const T1 intValue = static_cast<T1>(rangeValue);
        FW_ASSERT(IntRange::isValid(intValue), static_cast<FwAssertArgType>(intValue));
        this->m_intValue = static_cast<T>(intValue);
        return *this;
    }

  public:
    // ----------------------------------------------------------------------
    // Static member functions
    // ----------------------------------------------------------------------

    //! Check whether an integer value is valid for the range. The value may
    //! have any integral type. It is compared with the bounds as a
    //! mathematical integer, so the result does not depend on the width or
    //! signedness of the value type.
    //! @return The result
    template <typename U>
    static constexpr bool isValid(U intValue  //!< The integer value
    ) {
        static_assert(std::is_integral<U>::value, "The value checked against an integer range must be an integer");
        bool result = true;
        if ((LBT == BoundType::INCLUSIVE) && IntRangeDetail::lessThan(intValue, LBV)) {
            result = false;
        } else if ((LBT == BoundType::EXCLUSIVE) && !IntRangeDetail::lessThan(LBV, intValue)) {
            result = false;
        } else if ((UBT == BoundType::INCLUSIVE) && IntRangeDetail::lessThan(UBV, intValue)) {
            result = false;
        } else if ((UBT == BoundType::EXCLUSIVE) && !IntRangeDetail::lessThan(intValue, UBV)) {
            result = false;
        }
        return result;
    }

    //! Get the default value for the type, checking that the range is
    //! non-empty. This check is run by every constructor, because every
    //! constructor initializes the member variable below with this function.
    //! @return The default value
    static constexpr T getDefaultValue() {
        static_assert(IntRange::isValid(IntRange::computeDefaultValue()),
                      "An integer range must contain at least one valid value");
        return computeDefaultValue();
    }

  private:
    // ----------------------------------------------------------------------
    // Private helper functions
    // ----------------------------------------------------------------------

    //! Compute the default value for the type, without checking that it is valid
    //! @return The default value
    static constexpr T computeDefaultValue() {
        T defaultVal{};
        if (LBT == BoundType::NONE) {
            // There is no lower bound (the placeholder LBV is ignored): use the
            // smallest value of the base type
            defaultVal = std::numeric_limits<T>::min();
        } else if (IntRange::isValid(LBV)) {
            defaultVal = LBV;
        } else {
            // LBV is not valid, so try the next value. If LBV is the maximum
            // value of T, there is no next value: stay at LBV, so that the
            // range is reported as empty. The conditional is what prevents
            // overflow, so do not replace it with LBV + 1. The cast avoids a
            // narrowing warning for types smaller than int.
            defaultVal = static_cast<T>(LBV + ((LBV < std::numeric_limits<T>::max()) ? 1 : 0));
        }
        return defaultVal;
    }

  private:
    // ----------------------------------------------------------------------
    // Private member variables
    // ----------------------------------------------------------------------

    //! The integer value within the range
    T m_intValue = getDefaultValue();
};

//! Convenience alias for an IntRange type with inclusive bounds
template <typename T, T LBV, T UBV>
using IntRangeInclusive = IntRange<T, BoundType::INCLUSIVE, LBV, BoundType::INCLUSIVE, UBV>;

//! Convenience alias for an IntRange type with exclusive bounds
template <typename T, T LBV, T UBV>
using IntRangeExclusive = IntRange<T, BoundType::EXCLUSIVE, LBV, BoundType::EXCLUSIVE, UBV>;

//! Convenience alias for an IntRange type with inclusive and exclusive bounds
template <typename T, T LBV, T UBV>
using IntRangeInclusiveExclusive = IntRange<T, BoundType::INCLUSIVE, LBV, BoundType::EXCLUSIVE, UBV>;

//! Convenience alias for an IntRange type with exclusive and inclusive bounds
template <typename T, T LBV, T UBV>
using IntRangeExclusiveInclusive = IntRange<T, BoundType::EXCLUSIVE, LBV, BoundType::INCLUSIVE, UBV>;

//! Convenience alias for an IntRange type with an inclusive lower bound only
template <typename T, T LBV>
using IntLowerBoundInclusive = IntRange<T, BoundType::INCLUSIVE, LBV, BoundType::NONE, T{}>;

//! Convenience alias for an IntRange type with an exclusive lower bound only
template <typename T, T LBV>
using IntLowerBoundExclusive = IntRange<T, BoundType::EXCLUSIVE, LBV, BoundType::NONE, T{}>;

//! Convenience alias for an IntRange type with an inclusive upper bound only
template <typename T, T UBV>
using IntUpperBoundInclusive = IntRange<T, BoundType::NONE, T{}, BoundType::INCLUSIVE, UBV>;

//! Convenience alias for an IntRange type with an exclusive upper bound only
template <typename T, T UBV>
using IntUpperBoundExclusive = IntRange<T, BoundType::NONE, T{}, BoundType::EXCLUSIVE, UBV>;

}  // namespace Fw

#endif
