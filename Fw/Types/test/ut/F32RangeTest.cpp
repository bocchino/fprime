// ======================================================================
// @file   F32RangeTest.cpp
// @brief  Unit tests for the F32 range types
//
// This file tests two things:
// 1. The constexpr bit-cast functions F32_RANGE_ARG and
//    F32_RANGE_ARG_TYPE_TO_F32. At run time, std::memcpy provides the
//    reference result. The constexpr property is tested with static_assert.
// 2. The F32Range class and its aliases and macros.
//
// Not covered here: rejection of empty ranges, e.g., F32RangeInclusive with
// a lower bound greater than the upper bound. That check is a static_assert,
// so a violation is a compile error, which a gtest test cannot observe.
// The tests also do not cover the default value of a range with an exclusive
// bound, and they avoid reading the public bound constants
// lowerBoundValue and upperBoundValue directly.
// ======================================================================

#include <gtest/gtest.h>
#include <cmath>
#include <cstring>
#include <limits>
#include <type_traits>

#include <Fw/Types/F32Range.hpp>
#include "STest/Pick/Pick.hpp"
#include "STest/Random/Random.hpp"

namespace {

constexpr U32 NEGATIVE_ZERO_BITS = 0x80000000U;
constexpr U32 QUIET_NAN_BITS = 0x7FC00000U;

//! Reinterpret the bits of an F32 as a U32 (the reference implementation)
U32 bitsOf(F32 f32) {
    U32 bits = 0;
    std::memcpy(&bits, &f32, sizeof bits);
    return bits;
}

//! Reinterpret the bits of a U32 as an F32 (the reference implementation)
F32 floatOf(U32 bits) {
    F32 f32 = 0.0f;
    std::memcpy(&f32, &bits, sizeof f32);
    return f32;
}

bool isNaN(F32 f32) {
    return f32 != f32;
}

//! Check both conversions for a bit pattern against the reference
//! implementation, allowing for the documented exceptions: NaN and negative
//! zero in F32_RANGE_ARG, and NaN in F32_RANGE_ARG_TYPE_TO_F32.
//! @return Whether the conversions give the expected results
bool conversionsMatchReference(U32 bits) {
    const F32 reference = floatOf(bits);
    const F32 fromBits = Fw::F32_RANGE_ARG_TYPE_TO_F32(bits);
    const U32 toBits = Fw::F32_RANGE_ARG(reference);
    bool result = true;
    if (isNaN(reference)) {
        result = isNaN(fromBits) && (toBits == QUIET_NAN_BITS);
    } else {
        const U32 expectedToBits = (bits == NEGATIVE_ZERO_BITS) ? 0U : bits;
        result = (bitsOf(fromBits) == bits) && (toBits == expectedToBits);
    }
    return result;
}

//! Pick an arbitrary U32 value, with all 32 bits independent.
//! STest::Pick::any() is not suitable: it scales a 31-bit random number up to
//! 32 bits, so its lowest bit is nearly always equal to its highest bit.
//! Instead, pick the two halves separately.
U32 pickBits() {
    const U32 high = STest::Pick::lowerUpper(0, 0xFFFFU);
    const U32 low = STest::Pick::lowerUpper(0, 0xFFFFU);
    return (high << 16) | low;
}

// Constant expression checks. Each function is evaluated at compile time.

constexpr bool argIs(F32 f32, U32 bits) {
    return Fw::F32_RANGE_ARG(f32) == bits;
}

constexpr bool f32Is(U32 bits, F32 f32) {
    return Fw::F32_RANGE_ARG_TYPE_TO_F32(bits) == f32;
}

static_assert(argIs(0.0f, 0x00000000U), "F32_RANGE_ARG(0) must be a constant expression");
static_assert(argIs(1.0f, 0x3F800000U), "F32_RANGE_ARG(1) must be a constant expression");
static_assert(argIs(-1.0f, 0xBF800000U), "F32_RANGE_ARG(-1) must be a constant expression");
static_assert(argIs(1.5f, 0x3FC00000U), "F32_RANGE_ARG(1.5) must be a constant expression");
static_assert(argIs(0.1f, 0x3DCCCCCDU), "F32_RANGE_ARG(0.1) must be a constant expression");
static_assert(argIs(3.14159274f, 0x40490FDBU), "F32_RANGE_ARG(pi) must be a constant expression");
static_assert(argIs(std::numeric_limits<F32>::max(), 0x7F7FFFFFU), "F32_RANGE_ARG(max) must be a constant expression");
static_assert(argIs(std::numeric_limits<F32>::denorm_min(), 0x00000001U),
              "F32_RANGE_ARG(denorm_min) must be a constant expression");
static_assert(argIs(std::numeric_limits<F32>::infinity(), 0x7F800000U),
              "F32_RANGE_ARG(infinity) must be a constant expression");

static_assert(f32Is(0x00000000U, 0.0f), "F32_RANGE_ARG_TYPE_TO_F32(0) must be a constant expression");
static_assert(f32Is(0x3F800000U, 1.0f), "F32_RANGE_ARG_TYPE_TO_F32(1) must be a constant expression");
static_assert(f32Is(0xBF800000U, -1.0f), "F32_RANGE_ARG_TYPE_TO_F32(-1) must be a constant expression");
static_assert(f32Is(0x3FC00000U, 1.5f), "F32_RANGE_ARG_TYPE_TO_F32(1.5) must be a constant expression");
static_assert(f32Is(0x3DCCCCCDU, 0.1f), "F32_RANGE_ARG_TYPE_TO_F32(0.1) must be a constant expression");
static_assert(f32Is(0x40490FDBU, 3.14159274f), "F32_RANGE_ARG_TYPE_TO_F32(pi) must be a constant expression");
static_assert(f32Is(0x7F7FFFFFU, std::numeric_limits<F32>::max()),
              "F32_RANGE_ARG_TYPE_TO_F32(max) must be a constant expression");
static_assert(f32Is(0x00000001U, std::numeric_limits<F32>::denorm_min()),
              "F32_RANGE_ARG_TYPE_TO_F32(denorm_min) must be a constant expression");
static_assert(f32Is(0x7F800000U, std::numeric_limits<F32>::infinity()),
              "F32_RANGE_ARG_TYPE_TO_F32(infinity) must be a constant expression");

// The result is usable as a template argument, which is what the F32 range types need
static_assert(std::integral_constant<U32, Fw::F32_RANGE_ARG(1.5f)>::value == 0x3FC00000U,
              "F32_RANGE_ARG must be usable as a template argument");

constexpr F32 INF = std::numeric_limits<F32>::infinity();
constexpr F32 NAN_VALUE = std::numeric_limits<F32>::quiet_NaN();

//! The next representable F32 value above x
F32 nextAbove(F32 x) {
    return std::nextafter(x, INF);
}

//! The next representable F32 value below x
F32 nextBelow(F32 x) {
    return std::nextafter(x, -INF);
}

//! Construct a range of type R from a value, discarding the result
template <typename R, typename T>
void constructFrom(T value) {
    R range(value);
    (void)range;
}

//! Assign to a range in a constant expression
using AssignRange = FW_F32_RANGE_INCLUSIVE(1.0f, 2.0f);
constexpr F32 assignAndRead() {
    AssignRange range;
    range = 1.5f;
    return range;
}

}  // namespace

TEST(F32RangeTest, KnownValuesToBits) {
    ASSERT_EQ(Fw::F32_RANGE_ARG(0.0f), 0x00000000U);
    ASSERT_EQ(Fw::F32_RANGE_ARG(1.0f), 0x3F800000U);
    ASSERT_EQ(Fw::F32_RANGE_ARG(-1.0f), 0xBF800000U);
    ASSERT_EQ(Fw::F32_RANGE_ARG(2.0f), 0x40000000U);
    ASSERT_EQ(Fw::F32_RANGE_ARG(0.5f), 0x3F000000U);
    ASSERT_EQ(Fw::F32_RANGE_ARG(1.5f), 0x3FC00000U);
    ASSERT_EQ(Fw::F32_RANGE_ARG(0.1f), 0x3DCCCCCDU);
    ASSERT_EQ(Fw::F32_RANGE_ARG(-0.1f), 0xBDCCCCCDU);
    ASSERT_EQ(Fw::F32_RANGE_ARG(3.14159274f), 0x40490FDBU);
    ASSERT_EQ(Fw::F32_RANGE_ARG(std::numeric_limits<F32>::epsilon()), 0x34000000U);
}

TEST(F32RangeTest, KnownValuesFromBits) {
    ASSERT_EQ(Fw::F32_RANGE_ARG_TYPE_TO_F32(0x00000000U), 0.0f);
    ASSERT_EQ(Fw::F32_RANGE_ARG_TYPE_TO_F32(0x3F800000U), 1.0f);
    ASSERT_EQ(Fw::F32_RANGE_ARG_TYPE_TO_F32(0xBF800000U), -1.0f);
    ASSERT_EQ(Fw::F32_RANGE_ARG_TYPE_TO_F32(0x40000000U), 2.0f);
    ASSERT_EQ(Fw::F32_RANGE_ARG_TYPE_TO_F32(0x3F000000U), 0.5f);
    ASSERT_EQ(Fw::F32_RANGE_ARG_TYPE_TO_F32(0x3FC00000U), 1.5f);
    ASSERT_EQ(Fw::F32_RANGE_ARG_TYPE_TO_F32(0x3DCCCCCDU), 0.1f);
    ASSERT_EQ(Fw::F32_RANGE_ARG_TYPE_TO_F32(0x40490FDBU), 3.14159274f);
    ASSERT_EQ(Fw::F32_RANGE_ARG_TYPE_TO_F32(0x34000000U), std::numeric_limits<F32>::epsilon());
}

TEST(F32RangeTest, Extremes) {
    // Largest and smallest finite values
    ASSERT_EQ(Fw::F32_RANGE_ARG(std::numeric_limits<F32>::max()), 0x7F7FFFFFU);
    ASSERT_EQ(Fw::F32_RANGE_ARG(std::numeric_limits<F32>::lowest()), 0xFF7FFFFFU);
    ASSERT_EQ(Fw::F32_RANGE_ARG_TYPE_TO_F32(0x7F7FFFFFU), std::numeric_limits<F32>::max());
    ASSERT_EQ(Fw::F32_RANGE_ARG_TYPE_TO_F32(0xFF7FFFFFU), std::numeric_limits<F32>::lowest());
    // Smallest normal value, and the subnormal values on either side of it
    ASSERT_EQ(Fw::F32_RANGE_ARG(std::numeric_limits<F32>::min()), 0x00800000U);
    ASSERT_EQ(Fw::F32_RANGE_ARG(floatOf(0x007FFFFFU)), 0x007FFFFFU);
    ASSERT_EQ(Fw::F32_RANGE_ARG(std::numeric_limits<F32>::denorm_min()), 0x00000001U);
    ASSERT_EQ(Fw::F32_RANGE_ARG(-std::numeric_limits<F32>::denorm_min()), 0x80000001U);
    ASSERT_EQ(Fw::F32_RANGE_ARG_TYPE_TO_F32(0x00800000U), std::numeric_limits<F32>::min());
    ASSERT_EQ(bitsOf(Fw::F32_RANGE_ARG_TYPE_TO_F32(0x007FFFFFU)), 0x007FFFFFU);
    ASSERT_EQ(Fw::F32_RANGE_ARG_TYPE_TO_F32(0x00000001U), std::numeric_limits<F32>::denorm_min());
    // Infinities
    ASSERT_EQ(Fw::F32_RANGE_ARG(std::numeric_limits<F32>::infinity()), 0x7F800000U);
    ASSERT_EQ(Fw::F32_RANGE_ARG(-std::numeric_limits<F32>::infinity()), 0xFF800000U);
    ASSERT_EQ(Fw::F32_RANGE_ARG_TYPE_TO_F32(0x7F800000U), std::numeric_limits<F32>::infinity());
    ASSERT_EQ(Fw::F32_RANGE_ARG_TYPE_TO_F32(0xFF800000U), -std::numeric_limits<F32>::infinity());
}

TEST(F32RangeTest, NaN) {
    // Every NaN gives the same quiet NaN
    ASSERT_EQ(Fw::F32_RANGE_ARG(std::numeric_limits<F32>::quiet_NaN()), QUIET_NAN_BITS);
    ASSERT_EQ(Fw::F32_RANGE_ARG(std::numeric_limits<F32>::signaling_NaN()), QUIET_NAN_BITS);
    ASSERT_EQ(Fw::F32_RANGE_ARG(floatOf(0xFFC00000U)), QUIET_NAN_BITS);  // Negative NaN
    ASSERT_EQ(Fw::F32_RANGE_ARG(floatOf(0x7F800001U)), QUIET_NAN_BITS);  // NaN with a payload
    // Every NaN bit pattern gives a NaN
    ASSERT_TRUE(isNaN(Fw::F32_RANGE_ARG_TYPE_TO_F32(0x7FC00000U)));
    ASSERT_TRUE(isNaN(Fw::F32_RANGE_ARG_TYPE_TO_F32(0x7F800001U)));
    ASSERT_TRUE(isNaN(Fw::F32_RANGE_ARG_TYPE_TO_F32(0xFFC00000U)));
    ASSERT_TRUE(isNaN(Fw::F32_RANGE_ARG_TYPE_TO_F32(0xFFFFFFFFU)));
}

TEST(F32RangeTest, NegativeZero) {
    // F32_RANGE_ARG does not distinguish the two zeros
    ASSERT_EQ(Fw::F32_RANGE_ARG(-0.0f), 0x00000000U);
    // F32_RANGE_ARG_TYPE_TO_F32 gives the zero that the bits specify
    ASSERT_EQ(bitsOf(Fw::F32_RANGE_ARG_TYPE_TO_F32(0x00000000U)), 0x00000000U);
    ASSERT_EQ(bitsOf(Fw::F32_RANGE_ARG_TYPE_TO_F32(NEGATIVE_ZERO_BITS)), NEGATIVE_ZERO_BITS);
}

TEST(F32RangeTest, ExponentAndMantissaPatterns) {
    // Every exponent field, with mantissas that exercise every bit position,
    // the carry between adjacent bits, and the largest and smallest values
    // of each binade
    U32 mantissas[3 * 23 + 7];
    U32 count = 0;
    for (U32 bit = 0; bit < 23; bit++) {
        mantissas[count++] = 1U << bit;                // A single bit
        mantissas[count++] = (1U << bit) - 1U;         // All the bits below it
        mantissas[count++] = 0x7FFFFFU ^ (1U << bit);  // All the bits but one
    }
    mantissas[count++] = 0x000000U;
    mantissas[count++] = 0x7FFFFFU;
    mantissas[count++] = 0x2AAAAAU;
    mantissas[count++] = 0x555555U;
    mantissas[count++] = 0x400000U;
    mantissas[count++] = 0x3FFFFFU;
    mantissas[count++] = 0x000001U;
    ASSERT_EQ(count, 3U * 23U + 7U);
    for (U32 sign = 0; sign < 2; sign++) {
        for (U32 exponentField = 0; exponentField < 256; exponentField++) {
            for (U32 i = 0; i < count; i++) {
                const U32 bits = (sign << 31) | (exponentField << 23) | mantissas[i];
                ASSERT_TRUE(conversionsMatchReference(bits)) << "bits = 0x" << std::hex << bits;
            }
        }
    }
}

TEST(F32RangeTest, RandomBitPatterns) {
    // Every 32-bit pattern is a valid F32 bit pattern, so any picked value is
    // allowed. The seed is printed when the test starts (see main below). To
    // repeat a failing run, put the seed in a file called "seed".
    for (U32 i = 0; i < 100000; i++) {
        const U32 bits = pickBits();
        ASSERT_TRUE(conversionsMatchReference(bits)) << "bits = 0x" << std::hex << bits;
    }
}

TEST(F32RangeTest, AllSubnormalsAtStride) {
    // Every subnormal value is a multiple of the smallest one, so test a
    // spread of them, with a stride that is coprime to the number of values
    for (U32 mantissa = 0; mantissa < 0x800000U; mantissa += 37) {
        ASSERT_TRUE(conversionsMatchReference(mantissa)) << "bits = 0x" << std::hex << mantissa;
        ASSERT_TRUE(conversionsMatchReference(NEGATIVE_ZERO_BITS | mantissa))
            << "bits = 0x" << std::hex << (NEGATIVE_ZERO_BITS | mantissa);
    }
}

TEST(F32RangeTest, RoundTrip) {
    // Converting a value to bits and back gives the same value
    const F32 values[] = {1.0f,     -1.0f,    0.1f,     -0.1f,     10e-6f,  1.0e-30f, 1.0e30f,
                          123.456f, 65536.0f, 1.0e-40f, -1.0e-40f, 3.0e38f, -3.0e38f};
    for (const F32 value : values) {
        const F32 result = Fw::F32_RANGE_ARG_TYPE_TO_F32(Fw::F32_RANGE_ARG(value));
        ASSERT_EQ(bitsOf(result), bitsOf(value)) << "value = " << value;
    }
}

// ----------------------------------------------------------------------
// F32Range: construction and default values
// ----------------------------------------------------------------------

TEST(F32RangeTest, Construction) {
    using Range = FW_F32_RANGE_INCLUSIVE(1.0f, 2.0f);
    Range rangeDefault;
    ASSERT_EQ(static_cast<F32>(rangeDefault), 1.0f);
    Range range(1.5f);
    ASSERT_EQ(static_cast<F32>(range), 1.5f);
    range = 2.0f;
    ASSERT_EQ(static_cast<F32>(range), 2.0f);
    // The conversion to F32 is implicit
    const F32 value = range;
    ASSERT_EQ(value, 2.0f);
}

TEST(F32RangeTest, DefaultValueWithLowerBound) {
    // The lower bound, if it is inclusive
    using Inclusive = FW_F32_RANGE_INCLUSIVE(1.0f, 2.0f);
    ASSERT_EQ(static_cast<F32>(Inclusive()), 1.0f);
    using InclusiveExclusive = FW_F32_RANGE_INCLUSIVE_EXCLUSIVE(1.0f, 2.0f);
    ASSERT_EQ(static_cast<F32>(InclusiveExclusive()), 1.0f);
    using NegativeLowerBound = FW_F32_LOWER_BOUND_INCLUSIVE(-3.5f);
    ASSERT_EQ(static_cast<F32>(NegativeLowerBound()), -3.5f);
    using ZeroLowerBound = FW_F32_LOWER_BOUND_INCLUSIVE(0.0f);
    ASSERT_EQ(static_cast<F32>(ZeroLowerBound()), 0.0f);
    using InfiniteLowerBound = FW_F32_RANGE_INCLUSIVE(-INF, INF);
    ASSERT_EQ(static_cast<F32>(InfiniteLowerBound()), -INF);
}

TEST(F32RangeTest, DefaultValueWithUpperBoundOnly) {
    // The upper bound, if it is inclusive
    using Positive = FW_F32_UPPER_BOUND_INCLUSIVE(7.25f);
    ASSERT_EQ(static_cast<F32>(Positive()), 7.25f);
    using Negative = FW_F32_UPPER_BOUND_INCLUSIVE(-5.0f);
    ASSERT_EQ(static_cast<F32>(Negative()), -5.0f);
}

TEST(F32RangeTest, DefaultValueWithoutBounds) {
    // Zero, whatever the placeholder values of the bounds are
    using NoBounds = Fw::F32Range<Fw::BoundType::NONE, 0, Fw::BoundType::NONE, 0>;
    ASSERT_EQ(static_cast<F32>(NoBounds()), 0.0f);
    using WithPlaceholders =
        Fw::F32Range<Fw::BoundType::NONE, Fw::F32_RANGE_ARG(5.0f), Fw::BoundType::NONE, Fw::F32_RANGE_ARG(-5.0f)>;
    ASSERT_EQ(static_cast<F32>(WithPlaceholders()), 0.0f);
}

// ----------------------------------------------------------------------
// F32Range: constant expressions
// ----------------------------------------------------------------------

TEST(F32RangeTest, Constexpr) {
    using Range = FW_F32_RANGE_INCLUSIVE(1.0f, 2.0f);
    constexpr Range defaultValue = Range();
    static_assert(static_cast<F32>(defaultValue) == 1.0f, "The default value must be a constant expression");
    constexpr Range value(1.5f);
    static_assert(static_cast<F32>(value) == 1.5f, "Construction must be a constant expression");
    static_assert(assignAndRead() == 1.5f, "Assignment must be usable in a constant expression");
}

// ----------------------------------------------------------------------
// F32Range: isValid
// ----------------------------------------------------------------------

TEST(F32RangeTest, IsValidBounds) {
    // The values on either side of each bound, and the bounds themselves
    const F32 belowLower = nextBelow(1.0f);
    const F32 aboveLower = nextAbove(1.0f);
    const F32 belowUpper = nextBelow(2.0f);
    const F32 aboveUpper = nextAbove(2.0f);

    using Inclusive = FW_F32_RANGE_INCLUSIVE(1.0f, 2.0f);
    ASSERT_FALSE(Inclusive::isValid(belowLower));
    ASSERT_TRUE(Inclusive::isValid(1.0f));
    ASSERT_TRUE(Inclusive::isValid(aboveLower));
    ASSERT_TRUE(Inclusive::isValid(1.5f));
    ASSERT_TRUE(Inclusive::isValid(belowUpper));
    ASSERT_TRUE(Inclusive::isValid(2.0f));
    ASSERT_FALSE(Inclusive::isValid(aboveUpper));

    using Exclusive = FW_F32_RANGE_EXCLUSIVE(1.0f, 2.0f);
    ASSERT_FALSE(Exclusive::isValid(belowLower));
    ASSERT_FALSE(Exclusive::isValid(1.0f));
    ASSERT_TRUE(Exclusive::isValid(aboveLower));
    ASSERT_TRUE(Exclusive::isValid(belowUpper));
    ASSERT_FALSE(Exclusive::isValid(2.0f));
    ASSERT_FALSE(Exclusive::isValid(aboveUpper));

    using InclusiveExclusive = FW_F32_RANGE_INCLUSIVE_EXCLUSIVE(1.0f, 2.0f);
    ASSERT_FALSE(InclusiveExclusive::isValid(belowLower));
    ASSERT_TRUE(InclusiveExclusive::isValid(1.0f));
    ASSERT_TRUE(InclusiveExclusive::isValid(belowUpper));
    ASSERT_FALSE(InclusiveExclusive::isValid(2.0f));

    using ExclusiveInclusive = FW_F32_RANGE_EXCLUSIVE_INCLUSIVE(1.0f, 2.0f);
    ASSERT_FALSE(ExclusiveInclusive::isValid(1.0f));
    ASSERT_TRUE(ExclusiveInclusive::isValid(aboveLower));
    ASSERT_TRUE(ExclusiveInclusive::isValid(2.0f));
    ASSERT_FALSE(ExclusiveInclusive::isValid(aboveUpper));
}

TEST(F32RangeTest, IsValidOneSidedBounds) {
    constexpr F32 lowest = std::numeric_limits<F32>::lowest();
    constexpr F32 highest = std::numeric_limits<F32>::max();

    using LowerInclusive = FW_F32_LOWER_BOUND_INCLUSIVE(-5.0f);
    ASSERT_FALSE(LowerInclusive::isValid(nextBelow(-5.0f)));
    ASSERT_TRUE(LowerInclusive::isValid(-5.0f));
    ASSERT_TRUE(LowerInclusive::isValid(highest));

    using LowerExclusive = FW_F32_LOWER_BOUND_EXCLUSIVE(-5.0f);
    ASSERT_FALSE(LowerExclusive::isValid(-5.0f));
    ASSERT_TRUE(LowerExclusive::isValid(nextAbove(-5.0f)));
    ASSERT_TRUE(LowerExclusive::isValid(highest));

    using UpperInclusive = FW_F32_UPPER_BOUND_INCLUSIVE(5.0f);
    ASSERT_TRUE(UpperInclusive::isValid(lowest));
    ASSERT_TRUE(UpperInclusive::isValid(5.0f));
    ASSERT_FALSE(UpperInclusive::isValid(nextAbove(5.0f)));

    using UpperExclusive = FW_F32_UPPER_BOUND_EXCLUSIVE(5.0f);
    ASSERT_TRUE(UpperExclusive::isValid(lowest));
    ASSERT_TRUE(UpperExclusive::isValid(nextBelow(5.0f)));
    ASSERT_FALSE(UpperExclusive::isValid(5.0f));
}

TEST(F32RangeTest, IsValidSignedZero) {
    // Negative zero compares equal to zero, so it is on the same side of a
    // bound at zero as positive zero is
    constexpr F32 negativeZero = -0.0f;
    const F32 smallest = std::numeric_limits<F32>::denorm_min();

    using Inclusive = FW_F32_RANGE_INCLUSIVE(0.0f, 1.0f);
    ASSERT_TRUE(Inclusive::isValid(negativeZero));
    ASSERT_TRUE(Inclusive::isValid(0.0f));
    ASSERT_FALSE(Inclusive::isValid(-smallest));

    using Exclusive = FW_F32_RANGE_EXCLUSIVE(0.0f, 1.0f);
    ASSERT_FALSE(Exclusive::isValid(negativeZero));
    ASSERT_FALSE(Exclusive::isValid(0.0f));
    ASSERT_TRUE(Exclusive::isValid(smallest));
}

TEST(F32RangeTest, IsValidInfinity) {
    constexpr F32 highest = std::numeric_limits<F32>::max();

    // Finite bounds exclude both infinities, and a bound on one side excludes
    // only the infinity on that side
    using Finite = FW_F32_RANGE_INCLUSIVE(-1.0f, 1.0f);
    ASSERT_FALSE(Finite::isValid(INF));
    ASSERT_FALSE(Finite::isValid(-INF));
    using LowerOnly = FW_F32_LOWER_BOUND_INCLUSIVE(0.0f);
    ASSERT_TRUE(LowerOnly::isValid(INF));
    ASSERT_FALSE(LowerOnly::isValid(-INF));
    using UpperOnly = FW_F32_UPPER_BOUND_INCLUSIVE(0.0f);
    ASSERT_FALSE(UpperOnly::isValid(INF));
    ASSERT_TRUE(UpperOnly::isValid(-INF));

    // Bounds at infinity
    using InclusiveInfinite = FW_F32_RANGE_INCLUSIVE(-INF, INF);
    ASSERT_TRUE(InclusiveInfinite::isValid(-INF));
    ASSERT_TRUE(InclusiveInfinite::isValid(0.0f));
    ASSERT_TRUE(InclusiveInfinite::isValid(INF));
    using ExclusiveUpperInfinite = FW_F32_RANGE_INCLUSIVE_EXCLUSIVE(-INF, INF);
    ASSERT_TRUE(ExclusiveUpperInfinite::isValid(-INF));
    ASSERT_TRUE(ExclusiveUpperInfinite::isValid(highest));
    ASSERT_FALSE(ExclusiveUpperInfinite::isValid(INF));
}

TEST(F32RangeTest, IsValidNaN) {
    // NaN is not valid for a range that has a bound, whatever kind of bound.
    // Each type is named with an alias first, because a macro that expands to
    // a template with more than one argument can't be an argument to ASSERT_FALSE.
    using Inclusive = FW_F32_RANGE_INCLUSIVE(1.0f, 2.0f);
    using Exclusive = FW_F32_RANGE_EXCLUSIVE(1.0f, 2.0f);
    using InclusiveExclusive = FW_F32_RANGE_INCLUSIVE_EXCLUSIVE(1.0f, 2.0f);
    using ExclusiveInclusive = FW_F32_RANGE_EXCLUSIVE_INCLUSIVE(1.0f, 2.0f);
    ASSERT_FALSE(Inclusive::isValid(NAN_VALUE));
    ASSERT_FALSE(Exclusive::isValid(NAN_VALUE));
    ASSERT_FALSE(InclusiveExclusive::isValid(NAN_VALUE));
    ASSERT_FALSE(ExclusiveInclusive::isValid(NAN_VALUE));
    ASSERT_FALSE(FW_F32_LOWER_BOUND_INCLUSIVE(1.0f)::isValid(NAN_VALUE));
    ASSERT_FALSE(FW_F32_LOWER_BOUND_EXCLUSIVE(1.0f)::isValid(NAN_VALUE));
    ASSERT_FALSE(FW_F32_UPPER_BOUND_INCLUSIVE(1.0f)::isValid(NAN_VALUE));
    ASSERT_FALSE(FW_F32_UPPER_BOUND_EXCLUSIVE(1.0f)::isValid(NAN_VALUE));
    // Including a NaN with a different sign or payload
    ASSERT_FALSE(Inclusive::isValid(floatOf(0xFFC00000U)));
    ASSERT_FALSE(Inclusive::isValid(floatOf(0x7F800001U)));
}

// ----------------------------------------------------------------------
// F32Range: the macros and aliases
// ----------------------------------------------------------------------

TEST(F32RangeTest, MacrosAreUsableOutsideNamespaceFw) {
    // These tests are in the global namespace, so each macro must qualify
    // every name it uses. Each macro must also give the same type as the alias.
    static_assert(std::is_same<FW_F32_RANGE_INCLUSIVE(1.0f, 2.0f),
                               Fw::F32RangeInclusive<Fw::F32_RANGE_ARG(1.0f), Fw::F32_RANGE_ARG(2.0f)>>::value,
                  "FW_F32_RANGE_INCLUSIVE must name F32RangeInclusive");
    static_assert(std::is_same<FW_F32_RANGE_EXCLUSIVE(1.0f, 2.0f),
                               Fw::F32RangeExclusive<Fw::F32_RANGE_ARG(1.0f), Fw::F32_RANGE_ARG(2.0f)>>::value,
                  "FW_F32_RANGE_EXCLUSIVE must name F32RangeExclusive");
    static_assert(std::is_same<FW_F32_RANGE_INCLUSIVE_EXCLUSIVE(1.0f, 2.0f),
                               Fw::F32RangeInclusiveExclusive<Fw::F32_RANGE_ARG(1.0f), Fw::F32_RANGE_ARG(2.0f)>>::value,
                  "FW_F32_RANGE_INCLUSIVE_EXCLUSIVE must name F32RangeInclusiveExclusive");
    static_assert(std::is_same<FW_F32_RANGE_EXCLUSIVE_INCLUSIVE(1.0f, 2.0f),
                               Fw::F32RangeExclusiveInclusive<Fw::F32_RANGE_ARG(1.0f), Fw::F32_RANGE_ARG(2.0f)>>::value,
                  "FW_F32_RANGE_EXCLUSIVE_INCLUSIVE must name F32RangeExclusiveInclusive");
    static_assert(
        std::is_same<FW_F32_LOWER_BOUND_INCLUSIVE(1.0f), Fw::F32LowerBoundInclusive<Fw::F32_RANGE_ARG(1.0f)>>::value,
        "FW_F32_LOWER_BOUND_INCLUSIVE must name F32LowerBoundInclusive");
    static_assert(
        std::is_same<FW_F32_LOWER_BOUND_EXCLUSIVE(1.0f), Fw::F32LowerBoundExclusive<Fw::F32_RANGE_ARG(1.0f)>>::value,
        "FW_F32_LOWER_BOUND_EXCLUSIVE must name F32LowerBoundExclusive");
    static_assert(
        std::is_same<FW_F32_UPPER_BOUND_INCLUSIVE(1.0f), Fw::F32UpperBoundInclusive<Fw::F32_RANGE_ARG(1.0f)>>::value,
        "FW_F32_UPPER_BOUND_INCLUSIVE must name F32UpperBoundInclusive");
    static_assert(
        std::is_same<FW_F32_UPPER_BOUND_EXCLUSIVE(1.0f), Fw::F32UpperBoundExclusive<Fw::F32_RANGE_ARG(1.0f)>>::value,
        "FW_F32_UPPER_BOUND_EXCLUSIVE must name F32UpperBoundExclusive");
}

#if FW_ASSERT_LEVEL != FW_NO_ASSERT

// ----------------------------------------------------------------------
// F32Range: assertions
// ----------------------------------------------------------------------

// In the tests below, a value that is out of range must cause an assertion
// failure, and the assertion failure aborts the process. The statement inside
// each ASSERT_DEATH contains only the operation under test. Any other values
// are computed outside the statement, so that they cannot cause the death.

TEST(F32RangeTest, ValueOutOfRange) {
    const F32 belowLower = nextBelow(1.0f);
    const F32 aboveUpper = nextAbove(2.0f);

    using Inclusive = FW_F32_RANGE_INCLUSIVE(1.0f, 2.0f);
    ASSERT_DEATH(constructFrom<Inclusive>(belowLower), ".*");
    ASSERT_EQ(static_cast<F32>(Inclusive(1.0f)), 1.0f);
    ASSERT_EQ(static_cast<F32>(Inclusive(2.0f)), 2.0f);
    ASSERT_DEATH(constructFrom<Inclusive>(aboveUpper), ".*");

    using Exclusive = FW_F32_RANGE_EXCLUSIVE(1.0f, 2.0f);
    ASSERT_DEATH(constructFrom<Exclusive>(1.0f), ".*");
    ASSERT_EQ(static_cast<F32>(Exclusive(1.5f)), 1.5f);
    ASSERT_DEATH(constructFrom<Exclusive>(2.0f), ".*");

    using InclusiveExclusive = FW_F32_RANGE_INCLUSIVE_EXCLUSIVE(1.0f, 2.0f);
    ASSERT_EQ(static_cast<F32>(InclusiveExclusive(1.0f)), 1.0f);
    ASSERT_DEATH(constructFrom<InclusiveExclusive>(2.0f), ".*");

    using ExclusiveInclusive = FW_F32_RANGE_EXCLUSIVE_INCLUSIVE(1.0f, 2.0f);
    ASSERT_DEATH(constructFrom<ExclusiveInclusive>(1.0f), ".*");
    ASSERT_EQ(static_cast<F32>(ExclusiveInclusive(2.0f)), 2.0f);

    using LowerInclusive = FW_F32_LOWER_BOUND_INCLUSIVE(-5.0f);
    ASSERT_DEATH(constructFrom<LowerInclusive>(-6.0f), ".*");
    ASSERT_EQ(static_cast<F32>(LowerInclusive(-5.0f)), -5.0f);

    using LowerExclusive = FW_F32_LOWER_BOUND_EXCLUSIVE(-5.0f);
    ASSERT_DEATH(constructFrom<LowerExclusive>(-5.0f), ".*");
    ASSERT_EQ(static_cast<F32>(LowerExclusive(-4.0f)), -4.0f);

    using UpperInclusive = FW_F32_UPPER_BOUND_INCLUSIVE(5.0f);
    ASSERT_EQ(static_cast<F32>(UpperInclusive(5.0f)), 5.0f);
    ASSERT_DEATH(constructFrom<UpperInclusive>(6.0f), ".*");

    using UpperExclusive = FW_F32_UPPER_BOUND_EXCLUSIVE(5.0f);
    ASSERT_EQ(static_cast<F32>(UpperExclusive(4.0f)), 4.0f);
    ASSERT_DEATH(constructFrom<UpperExclusive>(5.0f), ".*");
}

TEST(F32RangeTest, AssignmentOutOfRange) {
    using Inclusive = FW_F32_RANGE_INCLUSIVE(1.0f, 2.0f);
    Inclusive range;
    range = 1.5f;
    ASSERT_EQ(static_cast<F32>(range), 1.5f);
    ASSERT_DEATH(range = 0.5f, ".*");
    ASSERT_DEATH(range = 2.5f, ".*");
}

TEST(F32RangeTest, NaNAndInfinityOutOfRange) {
    // NaN is not valid for a range that has a bound
    using Inclusive = FW_F32_RANGE_INCLUSIVE(1.0f, 2.0f);
    ASSERT_DEATH(constructFrom<Inclusive>(NAN_VALUE), ".*");
    using LowerOnly = FW_F32_LOWER_BOUND_INCLUSIVE(1.0f);
    ASSERT_DEATH(constructFrom<LowerOnly>(NAN_VALUE), ".*");
    using UpperOnly = FW_F32_UPPER_BOUND_EXCLUSIVE(1.0f);
    ASSERT_DEATH(constructFrom<UpperOnly>(NAN_VALUE), ".*");
    // The value reported by the assertion is computed without converting the
    // value to an integer, which is undefined for NaN and infinity, so these
    // values must fail the assertion and not do anything else
    ASSERT_DEATH(constructFrom<Inclusive>(INF), ".*");
    ASSERT_DEATH(constructFrom<Inclusive>(-INF), ".*");
    ASSERT_DEATH(constructFrom<Inclusive>(std::numeric_limits<F32>::max()), ".*");
    // The same holds for assignment
    Inclusive range;
    ASSERT_DEATH(range = NAN_VALUE, ".*");
    ASSERT_DEATH(range = INF, ".*");
    // An infinity that is within the range is accepted
    using LowerInfinite = FW_F32_LOWER_BOUND_INCLUSIVE(0.0f);
    ASSERT_EQ(static_cast<F32>(LowerInfinite(INF)), INF);
}

#endif

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
