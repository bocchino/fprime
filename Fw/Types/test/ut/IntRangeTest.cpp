// ======================================================================
// @file   IntRangeTest.cpp
// @brief  Unit tests for the integer range types
//
// Not covered here: rejection of empty ranges, e.g., IntRangeInclusive<U32, 1, 0>.
// That check is a static_assert, so a violation is a compile error, which a
// gtest test cannot observe.
// ======================================================================

#include <gtest/gtest.h>
#include <limits>

#include <Fw/Types/Assert.hpp>
#include <Fw/Types/IntRange.hpp>

namespace {

//! Construct a range of type R from a value, discarding the result
template <typename R, typename T>
void constructFrom(T value) {
    R range(value);
    (void)range;
}

//! Check the default value of a range that contains only the maximum value of T
//! and of a range with an exclusive lower bound just below it. These are the
//! cases in which computing the default value must not overflow.
template <typename T>
void checkRangesAtMaximum() {
    constexpr T maxValue = std::numeric_limits<T>::max();
    Fw::IntRangeInclusive<T, maxValue, maxValue> single;
    ASSERT_EQ(static_cast<T>(single), maxValue);
    Fw::IntLowerBoundExclusive<T, static_cast<T>(maxValue - 1)> exclusive;
    ASSERT_EQ(static_cast<T>(exclusive), maxValue);
}

//! Check the default value of a range that contains only the minimum value of T
//! and of a range with an exclusive upper bound just above it. These are the
//! cases in which computing the default value must not underflow.
template <typename T>
void checkRangesAtMinimum() {
    constexpr T minValue = std::numeric_limits<T>::min();
    Fw::IntRangeInclusive<T, minValue, minValue> single;
    ASSERT_EQ(static_cast<T>(single), minValue);
    Fw::IntUpperBoundInclusive<T, minValue> upperInclusive;
    ASSERT_EQ(static_cast<T>(upperInclusive), minValue);
    Fw::IntUpperBoundExclusive<T, static_cast<T>(minValue + 1)> upperExclusive;
    ASSERT_EQ(static_cast<T>(upperExclusive), minValue);
}

}  // namespace

TEST(IntRangeTest, Construction) {
    Fw::IntRangeExclusiveInclusive<U32, 0, 10> rangeDefault;
    ASSERT_EQ(rangeDefault, 1U);
    Fw::IntRangeInclusiveExclusive<U32, 0, 10> range(1);
    ASSERT_EQ(range, 1U);
    Fw::IntLowerBoundExclusive<U32, 0> rangeLower(2);
    ASSERT_EQ(rangeLower, 2U);
    Fw::IntUpperBoundExclusive<U32, 10> rangeUpper(3);
    ASSERT_EQ(rangeUpper, 3U);
}

// ----------------------------------------------------------------------
// Default values
// ----------------------------------------------------------------------

TEST(IntRangeTest, DefaultValueWithLowerBound) {
    // The lower bound, if it is valid
    using Inclusive = Fw::IntRangeInclusive<U32, 5, 10>;
    ASSERT_EQ(Inclusive(), 5U);
    using NegativeInclusive = Fw::IntLowerBoundInclusive<I32, -5>;
    ASSERT_EQ(NegativeInclusive(), -5);
    // Otherwise the next value
    using Exclusive = Fw::IntRangeExclusive<I32, -3, 3>;
    ASSERT_EQ(Exclusive(), -2);
    using ExclusiveAtMaxMinusOne = Fw::IntLowerBoundExclusive<U8, 254>;
    ASSERT_EQ(ExclusiveAtMaxMinusOne(), std::numeric_limits<U8>::max());
}

TEST(IntRangeTest, DefaultValueWithUpperBoundOnly) {
    // The upper bound, if it is valid
    using SignedInclusive = Fw::IntUpperBoundInclusive<I32, -5>;
    ASSERT_EQ(SignedInclusive(), -5);
    using UnsignedInclusive = Fw::IntUpperBoundInclusive<U32, 7>;
    ASSERT_EQ(UnsignedInclusive(), 7U);
    // Otherwise the previous value
    using SignedExclusive = Fw::IntUpperBoundExclusive<I32, 0>;
    ASSERT_EQ(SignedExclusive(), -1);
    using UnsignedExclusive = Fw::IntUpperBoundExclusive<U32, 7>;
    ASSERT_EQ(UnsignedExclusive(), 6U);
    using ExclusiveAtMinPlusOne = Fw::IntUpperBoundExclusive<I8, -127>;
    ASSERT_EQ(ExclusiveAtMinPlusOne(), std::numeric_limits<I8>::min());
}

TEST(IntRangeTest, DefaultValueWithoutBounds) {
    // Zero, whatever the placeholder values of the bounds are
    using Unsigned = Fw::IntRange<U32, Fw::BoundType::NONE, 0, Fw::BoundType::NONE, 0>;
    ASSERT_EQ(Unsigned(), 0U);
    using Signed = Fw::IntRange<I32, Fw::BoundType::NONE, 0, Fw::BoundType::NONE, 0>;
    ASSERT_EQ(Signed(), 0);
    using SignedWithPlaceholders = Fw::IntRange<I32, Fw::BoundType::NONE, 5, Fw::BoundType::NONE, -5>;
    ASSERT_EQ(SignedWithPlaceholders(), 0);
}

TEST(IntRangeTest, DefaultValueAtMaximum) {
    checkRangesAtMaximum<U8>();
    checkRangesAtMaximum<I8>();
    checkRangesAtMaximum<U16>();
    checkRangesAtMaximum<I16>();
    checkRangesAtMaximum<U32>();
    checkRangesAtMaximum<I32>();
    checkRangesAtMaximum<U64>();
    checkRangesAtMaximum<I64>();
}

TEST(IntRangeTest, DefaultValueAtMinimum) {
    checkRangesAtMinimum<U8>();
    checkRangesAtMinimum<I8>();
    checkRangesAtMinimum<U16>();
    checkRangesAtMinimum<I16>();
    checkRangesAtMinimum<U32>();
    checkRangesAtMinimum<I32>();
    checkRangesAtMinimum<U64>();
    checkRangesAtMinimum<I64>();
}

// ----------------------------------------------------------------------
// Constant expressions
// ----------------------------------------------------------------------

TEST(IntRangeTest, Constexpr) {
    using Range = Fw::IntRangeInclusive<U32, 5, 10>;
    constexpr Range defaultValue = Range();
    static_assert(static_cast<U32>(defaultValue) == 5, "The default value must be a constant expression");
    constexpr Range value(7);
    static_assert(static_cast<U32>(value) == 7, "Construction must be a constant expression");
}

// ----------------------------------------------------------------------
// isValid
// ----------------------------------------------------------------------

TEST(IntRangeTest, IsValidBounds) {
    using Inclusive = Fw::IntRangeInclusive<U32, 3, 5>;
    ASSERT_FALSE(Inclusive::isValid(2U));
    ASSERT_TRUE(Inclusive::isValid(3U));
    ASSERT_TRUE(Inclusive::isValid(5U));
    ASSERT_FALSE(Inclusive::isValid(6U));

    using Exclusive = Fw::IntRangeExclusive<U32, 3, 5>;
    ASSERT_FALSE(Exclusive::isValid(3U));
    ASSERT_TRUE(Exclusive::isValid(4U));
    ASSERT_FALSE(Exclusive::isValid(5U));

    using InclusiveExclusive = Fw::IntRangeInclusiveExclusive<U32, 3, 5>;
    ASSERT_TRUE(InclusiveExclusive::isValid(3U));
    ASSERT_FALSE(InclusiveExclusive::isValid(5U));

    using ExclusiveInclusive = Fw::IntRangeExclusiveInclusive<U32, 3, 5>;
    ASSERT_FALSE(ExclusiveInclusive::isValid(3U));
    ASSERT_TRUE(ExclusiveInclusive::isValid(5U));
}

TEST(IntRangeTest, IsValidOneSidedBounds) {
    constexpr I32 minValue = std::numeric_limits<I32>::min();
    constexpr I32 maxValue = std::numeric_limits<I32>::max();

    using LowerInclusive = Fw::IntLowerBoundInclusive<I32, -5>;
    ASSERT_FALSE(LowerInclusive::isValid(-6));
    ASSERT_TRUE(LowerInclusive::isValid(-5));
    ASSERT_TRUE(LowerInclusive::isValid(maxValue));

    using LowerExclusive = Fw::IntLowerBoundExclusive<I32, -5>;
    ASSERT_FALSE(LowerExclusive::isValid(-5));
    ASSERT_TRUE(LowerExclusive::isValid(-4));
    ASSERT_TRUE(LowerExclusive::isValid(maxValue));

    using UpperInclusive = Fw::IntUpperBoundInclusive<I32, 5>;
    ASSERT_TRUE(UpperInclusive::isValid(minValue));
    ASSERT_TRUE(UpperInclusive::isValid(5));
    ASSERT_FALSE(UpperInclusive::isValid(6));

    using UpperExclusive = Fw::IntUpperBoundExclusive<I32, 5>;
    ASSERT_TRUE(UpperExclusive::isValid(minValue));
    ASSERT_TRUE(UpperExclusive::isValid(4));
    ASSERT_FALSE(UpperExclusive::isValid(5));
}

#if FW_ASSERT_LEVEL != FW_NO_ASSERT

// ----------------------------------------------------------------------
// Assertions
// ----------------------------------------------------------------------

// In the tests below, a value that is out of range must cause an assertion
// failure, and the assertion failure aborts the process. The statement inside
// each ASSERT_DEATH contains only the operation under test. Any other values
// are constructed outside the statement, so that they cannot cause the death.

TEST(IntRangeTest, ValueOutOfRange) {
    using Inclusive = Fw::IntRangeInclusive<U32, 3, 5>;
    ASSERT_DEATH(constructFrom<Inclusive>(2U), ".*");
    ASSERT_EQ(Inclusive(3U), 3U);
    ASSERT_EQ(Inclusive(5U), 5U);
    ASSERT_DEATH(constructFrom<Inclusive>(6U), ".*");

    using Exclusive = Fw::IntRangeExclusive<U32, 3, 5>;
    ASSERT_DEATH(constructFrom<Exclusive>(3U), ".*");
    ASSERT_EQ(Exclusive(4U), 4U);
    ASSERT_DEATH(constructFrom<Exclusive>(5U), ".*");

    using InclusiveExclusive = Fw::IntRangeInclusiveExclusive<U32, 3, 5>;
    ASSERT_EQ(InclusiveExclusive(3U), 3U);
    ASSERT_DEATH(constructFrom<InclusiveExclusive>(5U), ".*");

    using ExclusiveInclusive = Fw::IntRangeExclusiveInclusive<U32, 3, 5>;
    ASSERT_DEATH(constructFrom<ExclusiveInclusive>(3U), ".*");
    ASSERT_EQ(ExclusiveInclusive(5U), 5U);

    using LowerInclusive = Fw::IntLowerBoundInclusive<I32, -5>;
    ASSERT_DEATH(constructFrom<LowerInclusive>(-6), ".*");
    ASSERT_EQ(LowerInclusive(-5), -5);
    ASSERT_EQ(LowerInclusive(std::numeric_limits<I32>::max()), std::numeric_limits<I32>::max());

    using LowerExclusive = Fw::IntLowerBoundExclusive<I32, -5>;
    ASSERT_DEATH(constructFrom<LowerExclusive>(-5), ".*");
    ASSERT_EQ(LowerExclusive(-4), -4);

    using UpperInclusive = Fw::IntUpperBoundInclusive<I32, 5>;
    ASSERT_EQ(UpperInclusive(std::numeric_limits<I32>::min()), std::numeric_limits<I32>::min());
    ASSERT_EQ(UpperInclusive(5), 5);
    ASSERT_DEATH(constructFrom<UpperInclusive>(6), ".*");

    using UpperExclusive = Fw::IntUpperBoundExclusive<I32, 5>;
    ASSERT_EQ(UpperExclusive(4), 4);
    ASSERT_DEATH(constructFrom<UpperExclusive>(5), ".*");
}

TEST(IntRangeTest, AssignmentOutOfRange) {
    using Inclusive = Fw::IntRangeInclusive<U32, 3, 5>;
    Inclusive range;
    range = 4U;
    ASSERT_EQ(range, 4U);
    ASSERT_DEATH(range = 2U, ".*");
    ASSERT_DEATH(range = 6U, ".*");
}

#endif
