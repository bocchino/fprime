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
    constexpr IntRange() {
        static_assert(IntRange::isValid(IntRange::getDefaultValue()), "An integer range must contain at least one valid value");
    }

    //! Construct an integer range from a numeric value
    IntRange(T intValue) { *this = intValue; }

    //! Copy constructor
    template <typename T1, BoundType LBT1, T LBV1, BoundType UBT1, T UBV1>
    constexpr IntRange(const IntRange<T1, LBT1, LBV1, UBT1, UBV1>& rangeValue) {
        *this = rangeValue;
    }

  public:
    // ----------------------------------------------------------------------
    // User-defined operators
    // ----------------------------------------------------------------------

    //! Convert a numeric range to a numeric value
    operator T() const { return m_intValue; }

    //! Assignment from a value of the base type
    IntRange& operator=(T intValue) {
        FW_ASSERT(IntRange::isValid(intValue), static_cast<FwAssertArgType>(intValue));
        this->m_intValue = intValue;
        return *this;
    }

    //! Assignment from an integer range
    template <typename T1, BoundType LBT1, T LBV1, BoundType UBT1, T UBV1>
    IntRange& operator=(const IntRange<T1, LBT1, LBV1, UBT1, UBV1>& rangeValue) {
        *this = static_cast<T>(rangeValue);
        return *this;
    }

  public:
    // ----------------------------------------------------------------------
    // Static member functions
    // ----------------------------------------------------------------------

    //! Check whether an integer value is valid for the range
    //! @return The result
    static constexpr bool isValid(T intValue  //!< The numeric value
    ) {
        bool result = true;
        if ((LBT == BoundType::INCLUSIVE) && (intValue < LBV)) {
            result = false;
        } else if ((LBT == BoundType::EXCLUSIVE) && (intValue <= LBV)) {
            result = false;
        } else if ((UBT == BoundType::INCLUSIVE) && (intValue > UBV)) {
            result = false;
        } else if ((UBT == BoundType::EXCLUSIVE) && (intValue >= UBV)) {
            result = false;
        }
        return result;
    }

    //! Get the default value for the type.
    //! @return The default value
    static constexpr T getDefaultValue() {
        T defaultVal{};
        if (IntRange::isValid(LBV)) {
            defaultVal = LBV;
        } else if (LBV == std::numeric_limits<T>::max()) {
            defaultVal = LBV;
        } else {
            defaultVal = LBV + 1;
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

//! Convenience alias for an IntRange type with an exclusve lower bound only
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
