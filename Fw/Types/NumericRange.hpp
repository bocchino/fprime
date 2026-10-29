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

//! A numeric range parameterized by a type, a lower bound, and an upper bound
template <typename T, BoundType LBT, T LBV, BoundType UBT, T UBV>
class NumericRange {
    static_assert(std::is_arithmetic<T>::value, "The base type of a numeric range must be a numeric type");

  public:
    // ----------------------------------------------------------------------
    // Constructors and destructors
    // ----------------------------------------------------------------------

    //! Construct a numeric range with a default value
    constexpr NumericRange() {}

    //! Construct a numeric range from a numeric value
    constexpr NumericRange(T numericValue) { *this = numericValue; }

    //! Copy constructor
    template <typename T1, BoundType LBT1, T LBV1, BoundType UBT1, T UBV1>
    constexpr NumericRange(const NumericRange<T1, LBT1, LBV1, UBT1, UBV1>& rangeValue) {
        *this = rangeValue;
    }

  public:
    // ----------------------------------------------------------------------
    // User-defined operators
    // ----------------------------------------------------------------------

    //! Convert a numeric range to a numeric value
    operator T() const { return m_numericValue; }

    //! Assignment from a value of the base type
    NumericRange& operator=(T numericValue) {
        FW_ASSERT(NumericRange::isValid(numericValue), static_cast<FwAssertArgType>(numericValue));
        this->m_numericValue = numericValue;
        return *this;
    }

    //! Assignment from a numeric range
    template <typename T1, BoundType LBT1, T LBV1, BoundType UBT1, T UBV1>
    NumericRange& operator=(const NumericRange<T1, LBT1, LBV1, UBT1, UBV1>& rangeValue) {
        *this = rangeValue.m_numericValue;
        return *this;
    }

    //! Equality
    // TODO

    //! Inequality
    // TODO

  public:
    // ----------------------------------------------------------------------
    // Static member functions
    // ----------------------------------------------------------------------

    //! Check whether a numeric value is valid for the range
    //! @return The result
    static constexpr bool isValid(T numericValue  //!< The numeric value
    ) {
        bool result = true;
        if ((LBT == BoundType::INCLUSIVE) && (numericValue < LBV)) {
            result = false;
        } else if ((LBT == BoundType::EXCLUSIVE) && (numericValue <= LBV)) {
            result = false;
        } else if ((UBT == BoundType::INCLUSIVE) && (numericValue > UBV)) {
            result = false;
        } else if ((UBT == BoundType::EXCLUSIVE) && (numericValue >= UBV)) {
            result = false;
        }
        return result;
    }

  private:
    // ----------------------------------------------------------------------
    // Private member variables
    // ----------------------------------------------------------------------

    //! The numeric value within the range
    T m_numericValue = {};
};

//! Convenience alias for a range type with lower bound only
template <typename T, BoundType LBT, T LB>
using NumericRangeLower = NumericRange<T, LBT, LB, BoundType::NONE, T{}>;

//! Convenience alias for a range type with upper bound only
template <typename T, BoundType UBT, T UB>
using NumericRangeUpper = NumericRange<T, BoundType::NONE, T{}, UBT, UB>;

}  // namespace Fw

#endif
