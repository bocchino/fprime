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
    constexpr IntRange() {}

    //! Construct an integer range from an integer value
    constexpr IntRange(T intValue) { *this = intValue; }

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

  public:
    // ----------------------------------------------------------------------
    // Static member functions
    // ----------------------------------------------------------------------

    //! Check whether an integer value is valid for the range
    //! @return The result
    static constexpr bool isValid(T intValue  //!< The integer value
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

    //! Get the default value for the type, checking that the range is
    //! non-empty. This check is run by every constructor, because every
    //! constructor initializes the member variable below with this function.
    //!
    //! The default value is chosen as follows:
    //! 1. If the range has neither a lower bound nor an upper bound, then zero.
    //! 2. Otherwise, if the range has a lower bound, then the lower bound if it
    //!    is valid, and otherwise the next greater value.
    //! 3. Otherwise, the range has only an upper bound. Then the upper bound
    //!    if it is valid, and otherwise the next lesser value.
    //!
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
        if ((LBT == BoundType::NONE) && (UBT == BoundType::NONE)) {
            // There are no bounds (the placeholder values LBV and UBV are
            // ignored): use zero
            defaultVal = T{};
        } else if (LBT != BoundType::NONE) {
            if (IntRange::isValid(LBV)) {
                defaultVal = LBV;
            } else {
                // LBV is not valid, so try the next value. If LBV is the
                // maximum value of T, there is no next value: stay at LBV, so
                // that the range is reported as empty. The conditional is what
                // prevents overflow, so do not replace it with LBV + 1. The
                // cast avoids a narrowing warning for types smaller than int.
                defaultVal = static_cast<T>(LBV + ((LBV < std::numeric_limits<T>::max()) ? 1 : 0));
            }
        } else {
            // There is only an upper bound (the placeholder LBV is ignored)
            if (IntRange::isValid(UBV)) {
                defaultVal = UBV;
            } else {
                // UBV is not valid, so try the previous value. If UBV is the
                // minimum value of T, there is no previous value: stay at UBV,
                // so that the range is reported as empty. As above, the
                // conditional is what prevents overflow.
                defaultVal = static_cast<T>(UBV - ((UBV > std::numeric_limits<T>::min()) ? 1 : 0));
            }
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
