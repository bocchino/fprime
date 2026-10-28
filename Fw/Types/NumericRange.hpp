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
    static_assert(std::is_arithmetic<T>::value, "The type of a numeric range must be a numeric type");

  public:
    // ----------------------------------------------------------------------
    // Constructors and destructors
    // ----------------------------------------------------------------------

    //! Construct a numeric range with a default value
    NumericRange() {}

    //! Construct a numeric range from a value of the base type
    NumericRange(T value) {
        FW_ASSERT(NumericRange::isValid(value), static_cast<FwAssertArgType>(value));
        m_value = value;
    }

    //! Copy constructor
    template <typename T1, BoundType LBT1, T LBV1, BoundType UBT1, T UBV1>
    NumericRange(const NumericRange<T1, LBT1, LBV1, UBT1, UBV1>& range) {
        FW_ASSERT(NumericRange::isValid(range.m_value), static_cast<FwAssertArgType>(range.m_value));
        this->m_value = range.m_value;
    }

  public:
    // ----------------------------------------------------------------------
    // User-defined operators
    // ----------------------------------------------------------------------

    //! Convert a numeric range to a value of the base type
    operator T() const { return m_value; }

    //! Assignment
    // TODO

    //! Equality
    // TODO

    //! Inequality
    // TODO

  public:
    // ----------------------------------------------------------------------
    // Static member functions
    // ----------------------------------------------------------------------

    //! Check whether a value of the base type is valid for the range type
    //! @return The result
    static bool isValid(T value  //!< The value
    ) {
        bool result = true;
        if ((LBT == BoundType::INCLUSIVE) && (value < LBV)) {
            result = false;
        } else if ((LBT == BoundType::EXCLUSIVE) && (value <= LBV)) {
            result = false;
        } else if ((UBT == BoundType::INCLUSIVE) && (value > UBV)) {
            result =  false;
        } else if ((UBT == BoundType::EXCLUSIVE) && (value >= UBV)) {
            result = false;
        }
        return result;
    }

  private:
    // ----------------------------------------------------------------------
    // Private member variables
    // ----------------------------------------------------------------------

    //! The value of base type
    T m_value = {};
};

//! Convenience alias for a range type with lower bound only
template <typename T, BoundType LBT, T LB>
using NumericRangeLower = NumericRange<T, LBT, LB, BoundType::NONE, T{}>;

//! Convenience alias for a range type with upper bound only
template <typename T, BoundType UBT, T UB>
using NumericRangeUpper = NumericRange<T, BoundType::NONE, T{}, UBT, UB>;

}  // namespace Fw

#endif
