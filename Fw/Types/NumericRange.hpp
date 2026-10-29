// ======================================================================
// @file   NumericRange.hpp
// @author Rob Bocchino
// @brief  A wrapper type representing a numeric range
// ======================================================================

#ifndef FW_NUMERIC_RANGE
#define FW_NUMERIC_RANGE

#include <type_traits>

#include <Fw/FPrimeBasicTypes.hpp>
#include <Fw/Types/Assert.hpp>

namespace Fw {

//! The type of a bound
enum class BoundType {
    NONE,       //!< No bound
    INCLUSIVE,  //!< An inclusive bound
    EXCLUSIVE   //!< An exclusive bound
};

//! An integer range parameterized by a type, a lower bound, and an upper bound
template <typename T, BoundType LBT, T LBV, BoundType UBT, T UBV>
class IntRange {
    static_assert(std::is_integral<T>::value, "The base type of an integer range must be an integral type");

  public:
    // ----------------------------------------------------------------------
    // Constructors and destructors
    // ----------------------------------------------------------------------

    //! Construct an integer range with a default value
    constexpr IntRange() { *this = LBV; }

    //! Construct an integer range from a numeric value
    constexpr IntRange(T intValue) { *this = intValue; }

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

  private:
    // ----------------------------------------------------------------------
    // Private member variables
    // ----------------------------------------------------------------------

    //! The integer value within the range
    T m_intValue = {};
};

//! Convenience alias for an IntRange range type with lower bound only
template <typename T, BoundType LBT, T LB>
using IntRangeLower = IntRange<T, LBT, LB, BoundType::NONE, T{}>;

//! Convenience alias for an IntRange type with upper bound only
template <typename T, BoundType UBT, T UB>
using IntRangeUpper = IntRange<T, BoundType::NONE, T{}, UBT, UB>;

}  // namespace Fw

#endif
