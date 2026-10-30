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

//! An assert hook that counts failed assertions instead of aborting.
//! The hook is registered for the lifetime of the object.
class AssertCounter final : public Fw::AssertHook {
  public:
    AssertCounter() { this->registerHook(); }

    ~AssertCounter() override { this->deregisterHook(); }

    void reportAssert(FILE_NAME_ARG file,
                      FwSizeType lineNo,
                      FwSizeType numArgs,
                      FwAssertArgType arg1,
                      FwAssertArgType arg2,
                      FwAssertArgType arg3,
                      FwAssertArgType arg4,
                      FwAssertArgType arg5,
                      FwAssertArgType arg6) override {
        this->m_arg1 = arg1;
    }

    void doAssert() override { this->m_count++; }

    //! Get the number of failed assertions
    U32 getCount() const { return this->m_count; }

    //! Get the first argument of the most recent failed assertion
    FwAssertArgType getArg1() const { return this->m_arg1; }

  private:
    U32 m_count = 0;
    FwAssertArgType m_arg1 = 0;
};

//! Count the assertions triggered by constructing a range R from a value.
//! The type T must be the base type of R, so that no conversion occurs.
template <typename R, typename T>
U32 constructAsserts(T value) {
    AssertCounter counter;
    R range(value);
    (void)range;
    return counter.getCount();
}

//! Count the assertions triggered by assigning a value to a range R.
//! The type T must be the base type of R, so that no conversion occurs.
template <typename R, typename T>
U32 assignAsserts(T value) {
    R range;
    AssertCounter counter;
    range = value;
    return counter.getCount();
}

//! Count the assertions triggered by converting a range of type S to a range of type R
template <typename R, typename S>
U32 convertAsserts(const S& source) {
    AssertCounter counter;
    R range = source;
    (void)range;
    return counter.getCount();
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
    // Conversion from a range with a different base type and different bounds
    constexpr Fw::IntRangeInclusive<U8, 0, 9> narrow(1);
    constexpr Fw::IntRangeInclusive<U32, 0, 20> wide = narrow;
    static_assert(static_cast<U32>(wide) == 1, "Conversion must be a constant expression");
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

TEST(IntRangeTest, IsValidMixedTypes) {
    // The value is compared with the bounds as a mathematical integer, so
    // wraparound and sign conversion cannot make an invalid value look valid
    using U8Range = Fw::IntRangeInclusive<U8, 3, 5>;
    ASSERT_TRUE(U8Range::isValid(static_cast<I8>(4)));
    ASSERT_FALSE(U8Range::isValid(static_cast<U16>(259)));   // 259 mod 256 == 3
    ASSERT_FALSE(U8Range::isValid(static_cast<I32>(-253)));  // -253 mod 256 == 3
    ASSERT_FALSE(U8Range::isValid(std::numeric_limits<I64>::min()));

    using I8Range = Fw::IntRangeInclusive<I8, -5, 5>;
    ASSERT_TRUE(I8Range::isValid(static_cast<U32>(4)));
    ASSERT_FALSE(I8Range::isValid(std::numeric_limits<U32>::max()));
    ASSERT_FALSE(I8Range::isValid(static_cast<I64>(-6)));
    ASSERT_FALSE(I8Range::isValid(std::numeric_limits<U64>::max()));

    using FullU64Range = Fw::IntRangeInclusive<U64, 0, std::numeric_limits<U64>::max()>;
    ASSERT_FALSE(FullU64Range::isValid(static_cast<I64>(-1)));
    ASSERT_TRUE(FullU64Range::isValid(std::numeric_limits<I64>::max()));

    using FullI64Range = Fw::IntRangeInclusive<I64, std::numeric_limits<I64>::min(), std::numeric_limits<I64>::max()>;
    ASSERT_FALSE(FullI64Range::isValid(std::numeric_limits<U64>::max()));
    ASSERT_TRUE(FullI64Range::isValid(static_cast<U64>(std::numeric_limits<I64>::max())));
}

// ----------------------------------------------------------------------
// Conversion between ranges
// ----------------------------------------------------------------------

TEST(IntRangeTest, ConversionInRange) {
    AssertCounter counter;

    // Widening, by copy initialization
    Fw::IntRangeInclusive<U8, 0, 9> narrow(4);
    Fw::IntRangeInclusive<U32, 0, 20> wide = narrow;
    ASSERT_EQ(wide, 4U);

    // Narrowing: the value is in range if it is in the bounds of the target
    using U16Range = Fw::IntRangeInclusive<U16, 0, std::numeric_limits<U16>::max()>;
    using U8Range = Fw::IntRangeInclusive<U8, 3, 5>;
    for (U16 value = 3; value <= 5; value++) {
        U16Range source(value);
        U8Range target = source;
        ASSERT_EQ(target, static_cast<U8>(value));
        U8Range assigned;
        assigned = source;
        ASSERT_EQ(assigned, static_cast<U8>(value));
    }

    // Signed to unsigned
    using I16Range = Fw::IntRangeInclusive<I16, std::numeric_limits<I16>::min(), std::numeric_limits<I16>::max()>;
    using U8NonNegativeRange = Fw::IntRangeInclusive<U8, 0, 5>;
    I16Range signedSource(2);
    U8NonNegativeRange unsignedTarget = signedSource;
    ASSERT_EQ(unsignedTarget, static_cast<U8>(2));

    // Unsigned to signed, and negative values
    using I8Range = Fw::IntRangeInclusive<I8, -5, 5>;
    U16Range unsignedSource(3);
    I8Range signedTarget = unsignedSource;
    ASSERT_EQ(signedTarget, static_cast<I8>(3));
    I16Range negativeSource(-3);
    I8Range negativeTarget = negativeSource;
    ASSERT_EQ(negativeTarget, static_cast<I8>(-3));

    ASSERT_EQ(counter.getCount(), 0U);
}

#if FW_ASSERT_LEVEL != FW_NO_ASSERT

// ----------------------------------------------------------------------
// Assertions
// ----------------------------------------------------------------------

TEST(IntRangeTest, ValueOutOfRange) {
    using Inclusive = Fw::IntRangeInclusive<U32, 3, 5>;
    ASSERT_EQ(constructAsserts<Inclusive>(2U), 1U);
    ASSERT_EQ(constructAsserts<Inclusive>(3U), 0U);
    ASSERT_EQ(constructAsserts<Inclusive>(5U), 0U);
    ASSERT_EQ(constructAsserts<Inclusive>(6U), 1U);

    using Exclusive = Fw::IntRangeExclusive<U32, 3, 5>;
    ASSERT_EQ(constructAsserts<Exclusive>(3U), 1U);
    ASSERT_EQ(constructAsserts<Exclusive>(4U), 0U);
    ASSERT_EQ(constructAsserts<Exclusive>(5U), 1U);

    using InclusiveExclusive = Fw::IntRangeInclusiveExclusive<U32, 3, 5>;
    ASSERT_EQ(constructAsserts<InclusiveExclusive>(3U), 0U);
    ASSERT_EQ(constructAsserts<InclusiveExclusive>(5U), 1U);

    using ExclusiveInclusive = Fw::IntRangeExclusiveInclusive<U32, 3, 5>;
    ASSERT_EQ(constructAsserts<ExclusiveInclusive>(3U), 1U);
    ASSERT_EQ(constructAsserts<ExclusiveInclusive>(5U), 0U);

    using LowerInclusive = Fw::IntLowerBoundInclusive<I32, -5>;
    ASSERT_EQ(constructAsserts<LowerInclusive>(-6), 1U);
    ASSERT_EQ(constructAsserts<LowerInclusive>(-5), 0U);
    ASSERT_EQ(constructAsserts<LowerInclusive>(std::numeric_limits<I32>::max()), 0U);

    using LowerExclusive = Fw::IntLowerBoundExclusive<I32, -5>;
    ASSERT_EQ(constructAsserts<LowerExclusive>(-5), 1U);
    ASSERT_EQ(constructAsserts<LowerExclusive>(-4), 0U);

    using UpperInclusive = Fw::IntUpperBoundInclusive<I32, 5>;
    ASSERT_EQ(constructAsserts<UpperInclusive>(std::numeric_limits<I32>::min()), 0U);
    ASSERT_EQ(constructAsserts<UpperInclusive>(5), 0U);
    ASSERT_EQ(constructAsserts<UpperInclusive>(6), 1U);

    using UpperExclusive = Fw::IntUpperBoundExclusive<I32, 5>;
    ASSERT_EQ(constructAsserts<UpperExclusive>(4), 0U);
    ASSERT_EQ(constructAsserts<UpperExclusive>(5), 1U);
}

TEST(IntRangeTest, AssignmentOutOfRange) {
    using Inclusive = Fw::IntRangeInclusive<U32, 3, 5>;
    ASSERT_EQ(assignAsserts<Inclusive>(4U), 0U);
    ASSERT_EQ(assignAsserts<Inclusive>(2U), 1U);
    ASSERT_EQ(assignAsserts<Inclusive>(6U), 1U);
}

TEST(IntRangeTest, AssertionReportsValue) {
    AssertCounter counter;
    Fw::IntRangeInclusive<U32, 3, 5> range(6);
    ASSERT_EQ(counter.getCount(), 1U);
    ASSERT_EQ(counter.getArg1(), static_cast<FwAssertArgType>(6));
}

TEST(IntRangeTest, ConversionOutOfRange) {
    using U16Range = Fw::IntRangeInclusive<U16, 0, std::numeric_limits<U16>::max()>;
    using I16Range = Fw::IntRangeInclusive<I16, std::numeric_limits<I16>::min(), std::numeric_limits<I16>::max()>;
    using U8Range = Fw::IntRangeInclusive<U8, 3, 5>;
    using U8NonNegativeRange = Fw::IntRangeInclusive<U8, 0, 5>;
    using I8Range = Fw::IntRangeInclusive<I8, -5, 5>;

    // The check uses the width of the source type, so a value that is out of
    // range is not truncated into range
    ASSERT_EQ(convertAsserts<U8Range>(U16Range(256)), 1U);  // 256 mod 256 == 0
    ASSERT_EQ(convertAsserts<U8Range>(U16Range(259)), 1U);  // 259 mod 256 == 3
    ASSERT_EQ(convertAsserts<U8Range>(U16Range(6)), 1U);

    // The check accounts for signedness
    ASSERT_EQ(convertAsserts<U8NonNegativeRange>(I16Range(-253)), 1U);  // -253 mod 256 == 3
    ASSERT_EQ(convertAsserts<U8NonNegativeRange>(I16Range(-1)), 1U);
    ASSERT_EQ(convertAsserts<I8Range>(U16Range(65531)), 1U);  // 65531 as I8 is -5

    // The assertion reports the value in the source type, not the truncated value
    {
        AssertCounter counter;
        U16Range source(256);
        U8Range target = source;
        (void)target;
        ASSERT_EQ(counter.getCount(), 1U);
        ASSERT_EQ(counter.getArg1(), static_cast<FwAssertArgType>(256));
    }

    // Assignment as well as construction
    {
        AssertCounter counter;
        U16Range source(256);
        U8Range target;
        target = source;
        ASSERT_EQ(counter.getCount(), 1U);
    }
}

#endif
