// ======================================================================
// @file   F32Range.hpp
// @author Rob Bocchino
// @brief  A wrapper type representing a numeric range
// ======================================================================

#ifndef FW_F32_RANGE
#define FW_F32_RANGE

#include <type_traits>

#include <Fw/Types/Assert.hpp>
#include <Fw/Types/RangeUtils.hpp>

namespace Fw {

//! \brief An F32 range parameterized by a lower bound and an upper bound
//!
//! Each of the lower bound and upper bound is expressed as RANGE_ARG because F32
//! template parameters are not allowed in C++14
template <BoundType LBT, RANGE_ARG LBV, BoundType UBT, RANGE_ARG UBV>
class F32Range {
  public:
    // ----------------------------------------------------------------------
    // Constants 
    // ----------------------------------------------------------------------

    //! The lower bound value
    static constexpr F32 lowerBoundValue = RANGE_ARG_TO_F32(LBV);

    //! The upper bound value
    static constexpr F32 upperBoundValue = RANGE_ARG_TO_F32(UBV);

  public:
    // ----------------------------------------------------------------------
    // Constructors and destructors
    // ----------------------------------------------------------------------

    //! Construct an F32 range with the default value
    constexpr F32Range() {
        static_assert(F32Range::isValid(F32Range::getDefaultValue()), "An F32 range must contain at least one valid value");
    }

    //! Construct an F32 range from an F32 value
    constexpr F32Range(F32 f32Value) { *this = f32Value; }

    //! Copy constructor
    template <BoundType LBT1, RANGE_ARG LBV1, BoundType UBT1, RANGE_ARG UBV1>
    constexpr F32Range(const F32Range<LBT1, LBV1, UBT1, UBV1>& rangeValue) {
        *this = rangeValue;
    }

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
        F32 defaultValue = RANGE_ARG_TO_F32(LBV);
        if (!F32Range::isValid(defaultValue)) {
            defaultValue += 2 * F32_EPSILON;
        }
        return defaultValue;
    }

  private:
    // ----------------------------------------------------------------------
    // Private member variables
    // ----------------------------------------------------------------------

    //! The F32 value within the range
    F32 m_f32Value = getDefaultValue();
};

// TODO

}  // namespace Fw

#endif
