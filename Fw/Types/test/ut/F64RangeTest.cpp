// ======================================================================
// @file   F64RangeTest.cpp
// @brief  Unit tests for the F64 range types
//
// This file tests three things:
// 1. The constexpr bit-cast functions F64_RANGE_ARG and
//    F64_RANGE_ARG_TYPE_TO_F64. At run time, std::memcpy provides the
//    reference result. The constexpr property is tested with static_assert.
// 2. The constexpr functions f64NextAbove and f64NextBelow. At run time,
//    std::nextafter provides the reference result.
// 3. The F64Range class and its aliases and macros.
//
// Not covered here: rejection of empty ranges, e.g., F64RangeInclusive with
// a lower bound greater than the upper bound. That check is a static_assert,
// so a violation is a compile error, which a gtest test cannot observe.
// ======================================================================

#include <gtest/gtest.h>
#include <cmath>
#include <cstring>
#include <limits>
#include <type_traits>

#include <Fw/Types/F64Range.hpp>
#include "STest/Pick/Pick.hpp"
#include "STest/Random/Random.hpp"

namespace {

constexpr U64 NEGATIVE_ZERO_BITS = 0x8000000000000000ULL;
constexpr U64 QUIET_NAN_BITS = 0x7FF8000000000000ULL;

//! Reinterpret the bits of an F64 as a U64 (the reference implementation)
U64 bitsOf(F64 f64) {
    U64 bits = 0;
    std::memcpy(&bits, &f64, sizeof bits);
    return bits;
}

//! Reinterpret the bits of a U64 as an F64 (the reference implementation)
F64 doubleOf(U64 bits) {
    F64 f64 = 0.0;
    std::memcpy(&f64, &bits, sizeof f64);
    return f64;
}

bool isNaN(F64 f64) {
    return f64 != f64;
}

//! Check both conversions for a bit pattern against the reference
//! implementation, allowing for the documented exceptions: NaN and negative
//! zero in F64_RANGE_ARG, and NaN in F64_RANGE_ARG_TYPE_TO_F64.
//! @return Whether the conversions give the expected results
bool conversionsMatchReference(U64 bits) {
    const F64 reference = doubleOf(bits);
    const F64 fromBits = Fw::F64_RANGE_ARG_TYPE_TO_F64(bits);
    const U64 toBits = Fw::F64_RANGE_ARG(reference);
    bool result = true;
    if (isNaN(reference)) {
        result = isNaN(fromBits) && (toBits == QUIET_NAN_BITS);
    } else {
        const U64 expectedToBits = (bits == NEGATIVE_ZERO_BITS) ? 0U : bits;
        result = (bitsOf(fromBits) == bits) && (toBits == expectedToBits);
    }
    return result;
}

//! Pick an arbitrary U64 value, with all 64 bits independent.
//! STest::Pick::any() is not suitable: it scales a 31-bit random number up to
//! 32 bits, so its lowest bit is nearly always equal to its highest bit.
//! Instead, pick four 16-bit pieces separately.
U64 pickBits() {
    U64 bits = 0;
    for (U32 i = 0; i < 4; i++) {
        bits = (bits << 16) | STest::Pick::lowerUpper(0, 0xFFFFU);
    }
    return bits;
}

// Constant expression checks. Each function is evaluated at compile time.

constexpr bool argIs(F64 f64, U64 bits) {
    return Fw::F64_RANGE_ARG(f64) == bits;
}

constexpr bool f64Is(U64 bits, F64 f64) {
    return Fw::F64_RANGE_ARG_TYPE_TO_F64(bits) == f64;
}

static_assert(argIs(0.0, 0x0000000000000000ULL), "F64_RANGE_ARG(0) must be a constant expression");
static_assert(argIs(1.0, 0x3FF0000000000000ULL), "F64_RANGE_ARG(1) must be a constant expression");
static_assert(argIs(-1.0, 0xBFF0000000000000ULL), "F64_RANGE_ARG(-1) must be a constant expression");
static_assert(argIs(1.5, 0x3FF8000000000000ULL), "F64_RANGE_ARG(1.5) must be a constant expression");
static_assert(argIs(0.1, 0x3FB999999999999AULL), "F64_RANGE_ARG(0.1) must be a constant expression");
static_assert(argIs(3.141592653589793, 0x400921FB54442D18ULL), "F64_RANGE_ARG(pi) must be a constant expression");
static_assert(argIs(std::numeric_limits<F64>::max(), 0x7FEFFFFFFFFFFFFFULL),
              "F64_RANGE_ARG(max) must be a constant expression");
static_assert(argIs(std::numeric_limits<F64>::denorm_min(), 0x0000000000000001ULL),
              "F64_RANGE_ARG(denorm_min) must be a constant expression");
static_assert(argIs(std::numeric_limits<F64>::infinity(), 0x7FF0000000000000ULL),
              "F64_RANGE_ARG(infinity) must be a constant expression");

static_assert(f64Is(0x0000000000000000ULL, 0.0), "F64_RANGE_ARG_TYPE_TO_F64(0) must be a constant expression");
static_assert(f64Is(0x3FF0000000000000ULL, 1.0), "F64_RANGE_ARG_TYPE_TO_F64(1) must be a constant expression");
static_assert(f64Is(0xBFF0000000000000ULL, -1.0), "F64_RANGE_ARG_TYPE_TO_F64(-1) must be a constant expression");
static_assert(f64Is(0x3FF8000000000000ULL, 1.5), "F64_RANGE_ARG_TYPE_TO_F64(1.5) must be a constant expression");
static_assert(f64Is(0x3FB999999999999AULL, 0.1), "F64_RANGE_ARG_TYPE_TO_F64(0.1) must be a constant expression");
static_assert(f64Is(0x400921FB54442D18ULL, 3.141592653589793),
              "F64_RANGE_ARG_TYPE_TO_F64(pi) must be a constant expression");
static_assert(f64Is(0x7FEFFFFFFFFFFFFFULL, std::numeric_limits<F64>::max()),
              "F64_RANGE_ARG_TYPE_TO_F64(max) must be a constant expression");
static_assert(f64Is(0x0000000000000001ULL, std::numeric_limits<F64>::denorm_min()),
              "F64_RANGE_ARG_TYPE_TO_F64(denorm_min) must be a constant expression");
static_assert(f64Is(0x7FF0000000000000ULL, std::numeric_limits<F64>::infinity()),
              "F64_RANGE_ARG_TYPE_TO_F64(infinity) must be a constant expression");

// The result is usable as a template argument, which is what the F64 range types need
static_assert(std::integral_constant<U64, Fw::F64_RANGE_ARG(1.5)>::value == 0x3FF8000000000000ULL,
              "F64_RANGE_ARG must be usable as a template argument");

constexpr F64 INF = std::numeric_limits<F64>::infinity();
constexpr F64 NAN_VALUE = std::numeric_limits<F64>::quiet_NaN();

//! The next representable F64 value above x
F64 nextAbove(F64 x) {
    return std::nextafter(x, INF);
}

//! The next representable F64 value below x
F64 nextBelow(F64 x) {
    return std::nextafter(x, -INF);
}

//! Construct a range of type R from a value, discarding the result
template <typename R, typename T>
void constructFrom(T value) {
    R range(value);
    (void)range;
}

//! Assign to a range in a constant expression
using AssignRange = FW_F64_RANGE_INCLUSIVE(1.0, 2.0);
constexpr F64 assignAndRead() {
    AssignRange range;
    range = 1.5;
    return range;
}

// The spacing of F64 values near 1 is the epsilon of the type
static_assert(Fw::f64NextAbove(1.0) == 1.0 + std::numeric_limits<F64>::epsilon(),
              "f64NextAbove must be a constant expression");
static_assert(Fw::f64NextBelow(1.0) == 1.0 - std::numeric_limits<F64>::epsilon() / 2,
              "f64NextBelow must be a constant expression");
static_assert(Fw::f64NextAbove(0.0) == std::numeric_limits<F64>::denorm_min(),
              "The next value above zero is the smallest subnormal");
static_assert(Fw::f64NextBelow(0.0) == -std::numeric_limits<F64>::denorm_min(),
              "The next value below zero is the negative of the smallest subnormal");

//! Check f64NextAbove and f64NextBelow for one value against std::nextafter.
//! NaN is excluded: the result for NaN is the argument, which is NaN, and
//! NaN does not compare equal to itself.
//! @return Whether the results are as expected
bool nextValuesMatchReference(F64 value) {
    bool result = true;
    if (!isNaN(value)) {
        // The two zeros compare equal, so this does not distinguish them
        result = (Fw::f64NextAbove(value) == std::nextafter(value, INF)) &&
                 (Fw::f64NextBelow(value) == std::nextafter(value, -INF));
    }
    return result;
}

}  // namespace

TEST(F64RangeTest, KnownValuesToBits) {
    ASSERT_EQ(Fw::F64_RANGE_ARG(0.0), 0x0000000000000000ULL);
    ASSERT_EQ(Fw::F64_RANGE_ARG(1.0), 0x3FF0000000000000ULL);
    ASSERT_EQ(Fw::F64_RANGE_ARG(-1.0), 0xBFF0000000000000ULL);
    ASSERT_EQ(Fw::F64_RANGE_ARG(2.0), 0x4000000000000000ULL);
    ASSERT_EQ(Fw::F64_RANGE_ARG(0.5), 0x3FE0000000000000ULL);
    ASSERT_EQ(Fw::F64_RANGE_ARG(1.5), 0x3FF8000000000000ULL);
    ASSERT_EQ(Fw::F64_RANGE_ARG(0.1), 0x3FB999999999999AULL);
    ASSERT_EQ(Fw::F64_RANGE_ARG(-0.1), 0xBFB999999999999AULL);
    ASSERT_EQ(Fw::F64_RANGE_ARG(3.141592653589793), 0x400921FB54442D18ULL);
    ASSERT_EQ(Fw::F64_RANGE_ARG(std::numeric_limits<F64>::epsilon()), 0x3CB0000000000000ULL);
}

TEST(F64RangeTest, KnownValuesFromBits) {
    ASSERT_EQ(Fw::F64_RANGE_ARG_TYPE_TO_F64(0x0000000000000000ULL), 0.0);
    ASSERT_EQ(Fw::F64_RANGE_ARG_TYPE_TO_F64(0x3FF0000000000000ULL), 1.0);
    ASSERT_EQ(Fw::F64_RANGE_ARG_TYPE_TO_F64(0xBFF0000000000000ULL), -1.0);
    ASSERT_EQ(Fw::F64_RANGE_ARG_TYPE_TO_F64(0x4000000000000000ULL), 2.0);
    ASSERT_EQ(Fw::F64_RANGE_ARG_TYPE_TO_F64(0x3FE0000000000000ULL), 0.5);
    ASSERT_EQ(Fw::F64_RANGE_ARG_TYPE_TO_F64(0x3FF8000000000000ULL), 1.5);
    ASSERT_EQ(Fw::F64_RANGE_ARG_TYPE_TO_F64(0x3FB999999999999AULL), 0.1);
    ASSERT_EQ(Fw::F64_RANGE_ARG_TYPE_TO_F64(0x400921FB54442D18ULL), 3.141592653589793);
    ASSERT_EQ(Fw::F64_RANGE_ARG_TYPE_TO_F64(0x3CB0000000000000ULL), std::numeric_limits<F64>::epsilon());
}

TEST(F64RangeTest, Extremes) {
    // Largest and smallest finite values
    ASSERT_EQ(Fw::F64_RANGE_ARG(std::numeric_limits<F64>::max()), 0x7FEFFFFFFFFFFFFFULL);
    ASSERT_EQ(Fw::F64_RANGE_ARG(std::numeric_limits<F64>::lowest()), 0xFFEFFFFFFFFFFFFFULL);
    ASSERT_EQ(Fw::F64_RANGE_ARG_TYPE_TO_F64(0x7FEFFFFFFFFFFFFFULL), std::numeric_limits<F64>::max());
    ASSERT_EQ(Fw::F64_RANGE_ARG_TYPE_TO_F64(0xFFEFFFFFFFFFFFFFULL), std::numeric_limits<F64>::lowest());
    // Smallest normal value, and the subnormal values on either side of it
    ASSERT_EQ(Fw::F64_RANGE_ARG(std::numeric_limits<F64>::min()), 0x0010000000000000ULL);
    ASSERT_EQ(Fw::F64_RANGE_ARG(doubleOf(0x000FFFFFFFFFFFFFULL)), 0x000FFFFFFFFFFFFFULL);
    ASSERT_EQ(Fw::F64_RANGE_ARG(std::numeric_limits<F64>::denorm_min()), 0x0000000000000001ULL);
    ASSERT_EQ(Fw::F64_RANGE_ARG(-std::numeric_limits<F64>::denorm_min()), 0x8000000000000001ULL);
    ASSERT_EQ(Fw::F64_RANGE_ARG_TYPE_TO_F64(0x0010000000000000ULL), std::numeric_limits<F64>::min());
    ASSERT_EQ(bitsOf(Fw::F64_RANGE_ARG_TYPE_TO_F64(0x000FFFFFFFFFFFFFULL)), 0x000FFFFFFFFFFFFFULL);
    ASSERT_EQ(Fw::F64_RANGE_ARG_TYPE_TO_F64(0x0000000000000001ULL), std::numeric_limits<F64>::denorm_min());
    // Infinities
    ASSERT_EQ(Fw::F64_RANGE_ARG(std::numeric_limits<F64>::infinity()), 0x7FF0000000000000ULL);
    ASSERT_EQ(Fw::F64_RANGE_ARG(-std::numeric_limits<F64>::infinity()), 0xFFF0000000000000ULL);
    ASSERT_EQ(Fw::F64_RANGE_ARG_TYPE_TO_F64(0x7FF0000000000000ULL), std::numeric_limits<F64>::infinity());
    ASSERT_EQ(Fw::F64_RANGE_ARG_TYPE_TO_F64(0xFFF0000000000000ULL), -std::numeric_limits<F64>::infinity());
}

TEST(F64RangeTest, NaN) {
    // Every NaN gives the same quiet NaN
    ASSERT_EQ(Fw::F64_RANGE_ARG(std::numeric_limits<F64>::quiet_NaN()), QUIET_NAN_BITS);
    ASSERT_EQ(Fw::F64_RANGE_ARG(std::numeric_limits<F64>::signaling_NaN()), QUIET_NAN_BITS);
    ASSERT_EQ(Fw::F64_RANGE_ARG(doubleOf(0xFFF8000000000000ULL)), QUIET_NAN_BITS);  // Negative NaN
    ASSERT_EQ(Fw::F64_RANGE_ARG(doubleOf(0x7FF0000000000001ULL)), QUIET_NAN_BITS);  // NaN with a payload
    // Every NaN bit pattern gives a NaN
    ASSERT_TRUE(isNaN(Fw::F64_RANGE_ARG_TYPE_TO_F64(0x7FF8000000000000ULL)));
    ASSERT_TRUE(isNaN(Fw::F64_RANGE_ARG_TYPE_TO_F64(0x7FF0000000000001ULL)));
    ASSERT_TRUE(isNaN(Fw::F64_RANGE_ARG_TYPE_TO_F64(0xFFF8000000000000ULL)));
    ASSERT_TRUE(isNaN(Fw::F64_RANGE_ARG_TYPE_TO_F64(0xFFFFFFFFFFFFFFFFULL)));
}

TEST(F64RangeTest, NegativeZero) {
    // F64_RANGE_ARG does not distinguish the two zeros
    ASSERT_EQ(Fw::F64_RANGE_ARG(-0.0), 0x0000000000000000ULL);
    // F64_RANGE_ARG_TYPE_TO_F64 gives the zero that the bits specify
    ASSERT_EQ(bitsOf(Fw::F64_RANGE_ARG_TYPE_TO_F64(0x0000000000000000ULL)), 0x0000000000000000ULL);
    ASSERT_EQ(bitsOf(Fw::F64_RANGE_ARG_TYPE_TO_F64(NEGATIVE_ZERO_BITS)), NEGATIVE_ZERO_BITS);
}

TEST(F64RangeTest, ExponentAndMantissaPatterns) {
    // Every exponent field, with mantissas that exercise every bit position,
    // the carry between adjacent bits, and the largest and smallest values
    // of each binade
    U64 mantissas[3 * 52 + 7];
    U32 count = 0;
    for (U32 bit = 0; bit < 52; bit++) {
        mantissas[count++] = 1ULL << bit;                         // A single bit
        mantissas[count++] = (1ULL << bit) - 1ULL;                // All the bits below it
        mantissas[count++] = 0xFFFFFFFFFFFFFULL ^ (1ULL << bit);  // All the bits but one
    }
    mantissas[count++] = 0x0000000000000ULL;
    mantissas[count++] = 0xFFFFFFFFFFFFFULL;
    mantissas[count++] = 0xAAAAAAAAAAAAAULL;
    mantissas[count++] = 0x5555555555555ULL;
    mantissas[count++] = 0x8000000000000ULL;
    mantissas[count++] = 0x7FFFFFFFFFFFFULL;
    mantissas[count++] = 0x0000000000001ULL;
    ASSERT_EQ(count, 3U * 52U + 7U);
    for (U64 sign = 0; sign < 2; sign++) {
        for (U64 exponentField = 0; exponentField < 2048; exponentField++) {
            for (U32 i = 0; i < count; i++) {
                const U64 bits = (sign << 63) | (exponentField << 52) | mantissas[i];
                ASSERT_TRUE(conversionsMatchReference(bits)) << "bits = 0x" << std::hex << bits;
            }
        }
    }
}

TEST(F64RangeTest, RandomBitPatterns) {
    // Every 64-bit pattern is a valid F64 bit pattern, so any picked value is
    // allowed. The seed is printed when the test starts (see main below). To
    // repeat a failing run, put the seed in a file called "seed".
    for (U32 i = 0; i < 100000; i++) {
        const U64 bits = pickBits();
        ASSERT_TRUE(conversionsMatchReference(bits)) << "bits = 0x" << std::hex << bits;
    }
}

TEST(F64RangeTest, SubnormalsAtStride) {
    // Every subnormal value is a multiple of the smallest one, so test a
    // spread of them. There are 2^52 values, so an odd stride is coprime to
    // the number of values, and the sample includes both odd and even
    // mantissas. The stride gives about 12,000 iterations: each one converts
    // a value in both directions, and the F64 conversions loop up to about
    // 1,075 times, so more iterations make the test slow.
    constexpr U64 SUBNORMAL_COUNT = 0x10000000000000ULL;  // 2^52
    constexpr U64 STRIDE = 8191ULL * 65537ULL * 7ULL * 101ULL;
    static_assert(STRIDE % 2 == 1, "The stride must be odd, so that it is coprime to 2^52");
    for (U64 mantissa = 0; mantissa < SUBNORMAL_COUNT; mantissa += STRIDE) {
        ASSERT_TRUE(conversionsMatchReference(mantissa)) << "bits = 0x" << std::hex << mantissa;
        ASSERT_TRUE(conversionsMatchReference(NEGATIVE_ZERO_BITS | mantissa))
            << "bits = 0x" << std::hex << (NEGATIVE_ZERO_BITS | mantissa);
    }
}

TEST(F64RangeTest, RoundTrip) {
    // Converting a value to bits and back gives the same value
    const F64 values[] = {1.0,     -1.0,    0.1,      -0.1,      10e-6,   1.0e-300, 1.0e300,
                          123.456, 65536.0, 1.0e-310, -1.0e-310, 1.5e308, -1.5e308};
    for (const F64 value : values) {
        const F64 result = Fw::F64_RANGE_ARG_TYPE_TO_F64(Fw::F64_RANGE_ARG(value));
        ASSERT_EQ(bitsOf(result), bitsOf(value)) << "value = " << value;
    }
}

// ----------------------------------------------------------------------
// F64Range: construction and default values
// ----------------------------------------------------------------------

TEST(F64RangeTest, Construction) {
    using Range = FW_F64_RANGE_INCLUSIVE(1.0, 2.0);
    Range rangeDefault;
    ASSERT_EQ(static_cast<F64>(rangeDefault), 1.0);
    Range range(1.5);
    ASSERT_EQ(static_cast<F64>(range), 1.5);
    range = 2.0;
    ASSERT_EQ(static_cast<F64>(range), 2.0);
    // The conversion to F64 is implicit
    const F64 value = range;
    ASSERT_EQ(value, 2.0);
}

TEST(F64RangeTest, DefaultValueWithLowerBound) {
    // The lower bound, if it is in range
    using Inclusive = FW_F64_RANGE_INCLUSIVE(1.0, 2.0);
    ASSERT_EQ(static_cast<F64>(Inclusive()), 1.0);
    using InclusiveExclusive = FW_F64_RANGE_INCLUSIVE_EXCLUSIVE(1.0, 2.0);
    ASSERT_EQ(static_cast<F64>(InclusiveExclusive()), 1.0);
    using NegativeLowerBound = FW_F64_LOWER_BOUND_INCLUSIVE(-3.5);
    ASSERT_EQ(static_cast<F64>(NegativeLowerBound()), -3.5);
    using ZeroLowerBound = FW_F64_LOWER_BOUND_INCLUSIVE(0.0);
    ASSERT_EQ(static_cast<F64>(ZeroLowerBound()), 0.0);
    using InfiniteLowerBound = FW_F64_RANGE_INCLUSIVE(-INF, INF);
    ASSERT_EQ(static_cast<F64>(InfiniteLowerBound()), -INF);

    // Otherwise the next value above it
    using Exclusive = FW_F64_RANGE_EXCLUSIVE(1.0, 2.0);
    ASSERT_EQ(static_cast<F64>(Exclusive()), nextAbove(1.0));
    using ExclusiveInclusive = FW_F64_RANGE_EXCLUSIVE_INCLUSIVE(1.0, 2.0);
    ASSERT_EQ(static_cast<F64>(ExclusiveInclusive()), nextAbove(1.0));
    using LowerExclusive = FW_F64_LOWER_BOUND_EXCLUSIVE(-3.5);
    ASSERT_EQ(static_cast<F64>(LowerExclusive()), nextAbove(-3.5));
    // A lower bound at zero: the next value is the smallest subnormal
    using ZeroExclusive = FW_F64_LOWER_BOUND_EXCLUSIVE(0.0);
    ASSERT_EQ(static_cast<F64>(ZeroExclusive()), std::numeric_limits<F64>::denorm_min());
    // A lower bound at -infinity: the next value is the lowest finite value
    using InfiniteExclusive = FW_F64_LOWER_BOUND_EXCLUSIVE(-INF);
    ASSERT_EQ(static_cast<F64>(InfiniteExclusive()), std::numeric_limits<F64>::lowest());
}

TEST(F64RangeTest, DefaultValueWithLowerBoundWhereEpsilonFails) {
    // A large bound: adding a fixed epsilon would give back the bound
    using Large = FW_F64_LOWER_BOUND_EXCLUSIVE(1.0e20);
    ASSERT_GT(static_cast<F64>(Large()), 1.0e20);
    ASSERT_EQ(static_cast<F64>(Large()), nextAbove(1.0e20));
    // A narrow range: adding a fixed epsilon would go past the upper bound
    using Narrow = FW_F64_RANGE_EXCLUSIVE_INCLUSIVE(0.0, 5.0e-320);
    ASSERT_EQ(static_cast<F64>(Narrow()), std::numeric_limits<F64>::denorm_min());
    // A range with one valid value, between two adjacent F64 values
    using OneValue = FW_F64_RANGE_EXCLUSIVE(1.0, Fw::f64NextAbove(Fw::f64NextAbove(1.0)));
    ASSERT_EQ(static_cast<F64>(OneValue()), nextAbove(1.0));
}

TEST(F64RangeTest, DefaultValueWithUpperBoundOnly) {
    // The upper bound, if it is in range
    using Positive = FW_F64_UPPER_BOUND_INCLUSIVE(7.25);
    ASSERT_EQ(static_cast<F64>(Positive()), 7.25);
    using Negative = FW_F64_UPPER_BOUND_INCLUSIVE(-5.0);
    ASSERT_EQ(static_cast<F64>(Negative()), -5.0);

    // Otherwise the next value below it
    using Exclusive = FW_F64_UPPER_BOUND_EXCLUSIVE(7.25);
    ASSERT_EQ(static_cast<F64>(Exclusive()), nextBelow(7.25));
    using NegativeExclusive = FW_F64_UPPER_BOUND_EXCLUSIVE(-5.0);
    ASSERT_EQ(static_cast<F64>(NegativeExclusive()), nextBelow(-5.0));
    // An upper bound at zero: the next value is the negative of the smallest subnormal
    using ZeroExclusive = FW_F64_UPPER_BOUND_EXCLUSIVE(0.0);
    ASSERT_EQ(static_cast<F64>(ZeroExclusive()), -std::numeric_limits<F64>::denorm_min());
    // An upper bound at +infinity: the next value is the largest finite value
    using InfiniteExclusive = FW_F64_UPPER_BOUND_EXCLUSIVE(INF);
    ASSERT_EQ(static_cast<F64>(InfiniteExclusive()), std::numeric_limits<F64>::max());
    // A large bound
    using Large = FW_F64_UPPER_BOUND_EXCLUSIVE(-1.0e20);
    ASSERT_LT(static_cast<F64>(Large()), -1.0e20);
    ASSERT_EQ(static_cast<F64>(Large()), nextBelow(-1.0e20));
}

TEST(F64RangeTest, DefaultValueWithoutBounds) {
    // Zero, whatever the placeholder values of the bounds are
    using NoBounds = Fw::F64Range<Fw::BoundType::NONE, 0, Fw::BoundType::NONE, 0>;
    ASSERT_EQ(static_cast<F64>(NoBounds()), 0.0);
    using WithPlaceholders =
        Fw::F64Range<Fw::BoundType::NONE, Fw::F64_RANGE_ARG(5.0), Fw::BoundType::NONE, Fw::F64_RANGE_ARG(-5.0)>;
    ASSERT_EQ(static_cast<F64>(WithPlaceholders()), 0.0);
}

TEST(F64RangeTest, NoBoundsAcceptsAnyValue) {
    // With no bounds, there is nothing for a value to fail, so every value is
    // valid, including NaN and the infinities
    using NoBounds = Fw::F64Range<Fw::BoundType::NONE, 0, Fw::BoundType::NONE, 0>;
    ASSERT_TRUE(NoBounds::isValid(NAN_VALUE));
    ASSERT_TRUE(NoBounds::isValid(INF));
    ASSERT_TRUE(NoBounds::isValid(-INF));
    ASSERT_TRUE(NoBounds::isValid(0.0));
    NoBounds range(NAN_VALUE);
    ASSERT_TRUE(isNaN(range));
    range = INF;
    ASSERT_EQ(static_cast<F64>(range), INF);
}

TEST(F64RangeTest, BoundValues) {
    using Range = FW_F64_RANGE_INCLUSIVE(-1.5, 2.25);
    ASSERT_EQ(Range::getLowerBoundValue(), -1.5);
    ASSERT_EQ(Range::getUpperBoundValue(), 2.25);
    static_assert(Range::getLowerBoundValue() == -1.5, "The lower bound must be a constant expression");
    static_assert(Range::getUpperBoundValue() == 2.25, "The upper bound must be a constant expression");
    // For a range with one bound, the other bound is a placeholder: zero
    using LowerOnly = FW_F64_LOWER_BOUND_EXCLUSIVE(3.0);
    ASSERT_EQ(LowerOnly::getLowerBoundValue(), 3.0);
    ASSERT_EQ(LowerOnly::getUpperBoundValue(), 0.0);
    using UpperOnly = FW_F64_UPPER_BOUND_EXCLUSIVE(4.0);
    ASSERT_EQ(UpperOnly::getUpperBoundValue(), 4.0);
    ASSERT_EQ(UpperOnly::getLowerBoundValue(), 0.0);
}

// ----------------------------------------------------------------------
// f64NextAbove and f64NextBelow
// ----------------------------------------------------------------------

TEST(F64RangeTest, NextValuesKnownValues) {
    ASSERT_EQ(Fw::f64NextAbove(1.0), nextAbove(1.0));
    ASSERT_EQ(Fw::f64NextBelow(1.0), nextBelow(1.0));
    ASSERT_EQ(Fw::f64NextAbove(-1.0), nextAbove(-1.0));
    ASSERT_EQ(Fw::f64NextBelow(-1.0), nextBelow(-1.0));
    // The step crosses a power of two, where the exponent changes
    ASSERT_EQ(Fw::f64NextAbove(nextBelow(2.0)), 2.0);
    ASSERT_EQ(Fw::f64NextBelow(2.0), nextBelow(2.0));
    ASSERT_EQ(Fw::f64NextAbove(-2.0), nextAbove(-2.0));
    // Zero, of either sign
    ASSERT_EQ(Fw::f64NextAbove(0.0), std::numeric_limits<F64>::denorm_min());
    ASSERT_EQ(Fw::f64NextAbove(-0.0), std::numeric_limits<F64>::denorm_min());
    ASSERT_EQ(Fw::f64NextBelow(0.0), -std::numeric_limits<F64>::denorm_min());
    ASSERT_EQ(Fw::f64NextBelow(-0.0), -std::numeric_limits<F64>::denorm_min());
    // Crossing zero
    ASSERT_EQ(Fw::f64NextAbove(-std::numeric_limits<F64>::denorm_min()), 0.0);
    ASSERT_EQ(Fw::f64NextBelow(std::numeric_limits<F64>::denorm_min()), 0.0);
    // The boundary between subnormal and normal values
    ASSERT_EQ(Fw::f64NextAbove(nextBelow(std::numeric_limits<F64>::min())), std::numeric_limits<F64>::min());
}

TEST(F64RangeTest, NextValuesAtLimits) {
    constexpr F64 highest = std::numeric_limits<F64>::max();
    constexpr F64 lowest = std::numeric_limits<F64>::lowest();
    // Out of the finite values and into infinity
    ASSERT_EQ(Fw::f64NextAbove(highest), INF);
    ASSERT_EQ(Fw::f64NextBelow(lowest), -INF);
    // Out of infinity and into the finite values
    ASSERT_EQ(Fw::f64NextAbove(-INF), lowest);
    ASSERT_EQ(Fw::f64NextBelow(INF), highest);
    // There is no next value past infinity
    ASSERT_EQ(Fw::f64NextAbove(INF), INF);
    ASSERT_EQ(Fw::f64NextBelow(-INF), -INF);
}

TEST(F64RangeTest, NextValuesOfNaN) {
    ASSERT_TRUE(isNaN(Fw::f64NextAbove(NAN_VALUE)));
    ASSERT_TRUE(isNaN(Fw::f64NextBelow(NAN_VALUE)));
}

TEST(F64RangeTest, NextValuesExponentAndMantissaPatterns) {
    // Every exponent field, crossed with mantissas that are at and next to the
    // edges of the field and that set each bit, for both signs
    const U64 mantissas[] = {0x0000000000000ULL, 0x0000000000001ULL, 0x0000000000002ULL, 0x8000000000000ULL,
                             0xFFFFFFFFFFFFEULL, 0xFFFFFFFFFFFFFULL, 0x5555555555555ULL, 0xAAAAAAAAAAAAAULL};
    for (U64 sign = 0; sign <= 1; sign++) {
        for (U64 exponentField = 0; exponentField <= 0x7FF; exponentField++) {
            for (const U64 mantissa : mantissas) {
                const U64 bits = (sign << 63) | (exponentField << 52) | mantissa;
                ASSERT_TRUE(nextValuesMatchReference(doubleOf(bits))) << "bits = 0x" << std::hex << bits;
            }
        }
    }
}

TEST(F64RangeTest, NextValuesRandomBitPatterns) {
    // Every 64-bit pattern is a valid F64 bit pattern, so any picked value is
    // allowed. The seed is printed when the test starts (see main below).
    for (U32 i = 0; i < 100000; i++) {
        const U64 bits = pickBits();
        ASSERT_TRUE(nextValuesMatchReference(doubleOf(bits))) << "bits = 0x" << std::hex << bits;
    }
}

TEST(F64RangeTest, NextValuesRoundTrip) {
    // Stepping up and then down gives the original value, except at the ends
    // and at zero, where the step goes across the two zeros
    const F64 values[] = {1.0, -1.0, 0.1, -0.1, 1.0e-300, 1.0e300, 1.0e-310, -1.0e-310, 1.5e308, -1.5e308};
    for (const F64 value : values) {
        ASSERT_EQ(Fw::f64NextBelow(Fw::f64NextAbove(value)), value) << "value = " << value;
        ASSERT_EQ(Fw::f64NextAbove(Fw::f64NextBelow(value)), value) << "value = " << value;
    }
}

// ----------------------------------------------------------------------
// F64Range: constant expressions
// ----------------------------------------------------------------------

TEST(F64RangeTest, Constexpr) {
    using Range = FW_F64_RANGE_INCLUSIVE(1.0, 2.0);
    constexpr Range defaultValue = Range();
    static_assert(static_cast<F64>(defaultValue) == 1.0, "The default value must be a constant expression");
    constexpr Range value(1.5);
    static_assert(static_cast<F64>(value) == 1.5, "Construction must be a constant expression");
    static_assert(assignAndRead() == 1.5, "Assignment must be usable in a constant expression");
}

// ----------------------------------------------------------------------
// F64Range: isValid
// ----------------------------------------------------------------------

TEST(F64RangeTest, IsValidBounds) {
    // The values on either side of each bound, and the bounds themselves
    const F64 belowLower = nextBelow(1.0);
    const F64 aboveLower = nextAbove(1.0);
    const F64 belowUpper = nextBelow(2.0);
    const F64 aboveUpper = nextAbove(2.0);

    using Inclusive = FW_F64_RANGE_INCLUSIVE(1.0, 2.0);
    ASSERT_FALSE(Inclusive::isValid(belowLower));
    ASSERT_TRUE(Inclusive::isValid(1.0));
    ASSERT_TRUE(Inclusive::isValid(aboveLower));
    ASSERT_TRUE(Inclusive::isValid(1.5));
    ASSERT_TRUE(Inclusive::isValid(belowUpper));
    ASSERT_TRUE(Inclusive::isValid(2.0));
    ASSERT_FALSE(Inclusive::isValid(aboveUpper));

    using Exclusive = FW_F64_RANGE_EXCLUSIVE(1.0, 2.0);
    ASSERT_FALSE(Exclusive::isValid(belowLower));
    ASSERT_FALSE(Exclusive::isValid(1.0));
    ASSERT_TRUE(Exclusive::isValid(aboveLower));
    ASSERT_TRUE(Exclusive::isValid(belowUpper));
    ASSERT_FALSE(Exclusive::isValid(2.0));
    ASSERT_FALSE(Exclusive::isValid(aboveUpper));

    using InclusiveExclusive = FW_F64_RANGE_INCLUSIVE_EXCLUSIVE(1.0, 2.0);
    ASSERT_FALSE(InclusiveExclusive::isValid(belowLower));
    ASSERT_TRUE(InclusiveExclusive::isValid(1.0));
    ASSERT_TRUE(InclusiveExclusive::isValid(belowUpper));
    ASSERT_FALSE(InclusiveExclusive::isValid(2.0));

    using ExclusiveInclusive = FW_F64_RANGE_EXCLUSIVE_INCLUSIVE(1.0, 2.0);
    ASSERT_FALSE(ExclusiveInclusive::isValid(1.0));
    ASSERT_TRUE(ExclusiveInclusive::isValid(aboveLower));
    ASSERT_TRUE(ExclusiveInclusive::isValid(2.0));
    ASSERT_FALSE(ExclusiveInclusive::isValid(aboveUpper));
}

TEST(F64RangeTest, IsValidOneSidedBounds) {
    constexpr F64 lowest = std::numeric_limits<F64>::lowest();
    constexpr F64 highest = std::numeric_limits<F64>::max();

    using LowerInclusive = FW_F64_LOWER_BOUND_INCLUSIVE(-5.0);
    ASSERT_FALSE(LowerInclusive::isValid(nextBelow(-5.0)));
    ASSERT_TRUE(LowerInclusive::isValid(-5.0));
    ASSERT_TRUE(LowerInclusive::isValid(highest));

    using LowerExclusive = FW_F64_LOWER_BOUND_EXCLUSIVE(-5.0);
    ASSERT_FALSE(LowerExclusive::isValid(-5.0));
    ASSERT_TRUE(LowerExclusive::isValid(nextAbove(-5.0)));
    ASSERT_TRUE(LowerExclusive::isValid(highest));

    using UpperInclusive = FW_F64_UPPER_BOUND_INCLUSIVE(5.0);
    ASSERT_TRUE(UpperInclusive::isValid(lowest));
    ASSERT_TRUE(UpperInclusive::isValid(5.0));
    ASSERT_FALSE(UpperInclusive::isValid(nextAbove(5.0)));

    using UpperExclusive = FW_F64_UPPER_BOUND_EXCLUSIVE(5.0);
    ASSERT_TRUE(UpperExclusive::isValid(lowest));
    ASSERT_TRUE(UpperExclusive::isValid(nextBelow(5.0)));
    ASSERT_FALSE(UpperExclusive::isValid(5.0));
}

TEST(F64RangeTest, IsValidSignedZero) {
    // Negative zero compares equal to zero, so it is on the same side of a
    // bound at zero as positive zero is
    constexpr F64 negativeZero = -0.0;
    const F64 smallest = std::numeric_limits<F64>::denorm_min();

    using Inclusive = FW_F64_RANGE_INCLUSIVE(0.0, 1.0);
    ASSERT_TRUE(Inclusive::isValid(negativeZero));
    ASSERT_TRUE(Inclusive::isValid(0.0));
    ASSERT_FALSE(Inclusive::isValid(-smallest));

    using Exclusive = FW_F64_RANGE_EXCLUSIVE(0.0, 1.0);
    ASSERT_FALSE(Exclusive::isValid(negativeZero));
    ASSERT_FALSE(Exclusive::isValid(0.0));
    ASSERT_TRUE(Exclusive::isValid(smallest));
}

TEST(F64RangeTest, IsValidInfinity) {
    constexpr F64 highest = std::numeric_limits<F64>::max();

    // Finite bounds exclude both infinities, and a bound on one side excludes
    // only the infinity on that side
    using Finite = FW_F64_RANGE_INCLUSIVE(-1.0, 1.0);
    ASSERT_FALSE(Finite::isValid(INF));
    ASSERT_FALSE(Finite::isValid(-INF));
    using LowerOnly = FW_F64_LOWER_BOUND_INCLUSIVE(0.0);
    ASSERT_TRUE(LowerOnly::isValid(INF));
    ASSERT_FALSE(LowerOnly::isValid(-INF));
    using UpperOnly = FW_F64_UPPER_BOUND_INCLUSIVE(0.0);
    ASSERT_FALSE(UpperOnly::isValid(INF));
    ASSERT_TRUE(UpperOnly::isValid(-INF));

    // Bounds at infinity
    using InclusiveInfinite = FW_F64_RANGE_INCLUSIVE(-INF, INF);
    ASSERT_TRUE(InclusiveInfinite::isValid(-INF));
    ASSERT_TRUE(InclusiveInfinite::isValid(0.0));
    ASSERT_TRUE(InclusiveInfinite::isValid(INF));
    using ExclusiveUpperInfinite = FW_F64_RANGE_INCLUSIVE_EXCLUSIVE(-INF, INF);
    ASSERT_TRUE(ExclusiveUpperInfinite::isValid(-INF));
    ASSERT_TRUE(ExclusiveUpperInfinite::isValid(highest));
    ASSERT_FALSE(ExclusiveUpperInfinite::isValid(INF));
}

TEST(F64RangeTest, IsValidNaN) {
    // NaN is not valid for a range that has a bound, whatever kind of bound.
    // Each type is named with an alias first, because a macro that expands to
    // a template with more than one argument can't be an argument to ASSERT_FALSE.
    using Inclusive = FW_F64_RANGE_INCLUSIVE(1.0, 2.0);
    using Exclusive = FW_F64_RANGE_EXCLUSIVE(1.0, 2.0);
    using InclusiveExclusive = FW_F64_RANGE_INCLUSIVE_EXCLUSIVE(1.0, 2.0);
    using ExclusiveInclusive = FW_F64_RANGE_EXCLUSIVE_INCLUSIVE(1.0, 2.0);
    ASSERT_FALSE(Inclusive::isValid(NAN_VALUE));
    ASSERT_FALSE(Exclusive::isValid(NAN_VALUE));
    ASSERT_FALSE(InclusiveExclusive::isValid(NAN_VALUE));
    ASSERT_FALSE(ExclusiveInclusive::isValid(NAN_VALUE));
    ASSERT_FALSE(FW_F64_LOWER_BOUND_INCLUSIVE(1.0)::isValid(NAN_VALUE));
    ASSERT_FALSE(FW_F64_LOWER_BOUND_EXCLUSIVE(1.0)::isValid(NAN_VALUE));
    ASSERT_FALSE(FW_F64_UPPER_BOUND_INCLUSIVE(1.0)::isValid(NAN_VALUE));
    ASSERT_FALSE(FW_F64_UPPER_BOUND_EXCLUSIVE(1.0)::isValid(NAN_VALUE));
    // Including a NaN with a different sign or payload
    ASSERT_FALSE(Inclusive::isValid(doubleOf(0xFFF8000000000000ULL)));
    ASSERT_FALSE(Inclusive::isValid(doubleOf(0x7FF0000000000001ULL)));
}

// ----------------------------------------------------------------------
// F64Range: the macros and aliases
// ----------------------------------------------------------------------

TEST(F64RangeTest, MacrosAreUsableOutsideNamespaceFw) {
    // These tests are in the global namespace, so each macro must qualify
    // every name it uses. Each macro must also give the same type as the alias.
    static_assert(std::is_same<FW_F64_RANGE_INCLUSIVE(1.0, 2.0),
                               Fw::F64RangeInclusive<Fw::F64_RANGE_ARG(1.0), Fw::F64_RANGE_ARG(2.0)>>::value,
                  "FW_F64_RANGE_INCLUSIVE must name F64RangeInclusive");
    static_assert(std::is_same<FW_F64_RANGE_EXCLUSIVE(1.0, 2.0),
                               Fw::F64RangeExclusive<Fw::F64_RANGE_ARG(1.0), Fw::F64_RANGE_ARG(2.0)>>::value,
                  "FW_F64_RANGE_EXCLUSIVE must name F64RangeExclusive");
    static_assert(std::is_same<FW_F64_RANGE_INCLUSIVE_EXCLUSIVE(1.0, 2.0),
                               Fw::F64RangeInclusiveExclusive<Fw::F64_RANGE_ARG(1.0), Fw::F64_RANGE_ARG(2.0)>>::value,
                  "FW_F64_RANGE_INCLUSIVE_EXCLUSIVE must name F64RangeInclusiveExclusive");
    static_assert(std::is_same<FW_F64_RANGE_EXCLUSIVE_INCLUSIVE(1.0, 2.0),
                               Fw::F64RangeExclusiveInclusive<Fw::F64_RANGE_ARG(1.0), Fw::F64_RANGE_ARG(2.0)>>::value,
                  "FW_F64_RANGE_EXCLUSIVE_INCLUSIVE must name F64RangeExclusiveInclusive");
    static_assert(
        std::is_same<FW_F64_LOWER_BOUND_INCLUSIVE(1.0), Fw::F64LowerBoundInclusive<Fw::F64_RANGE_ARG(1.0)>>::value,
        "FW_F64_LOWER_BOUND_INCLUSIVE must name F64LowerBoundInclusive");
    static_assert(
        std::is_same<FW_F64_LOWER_BOUND_EXCLUSIVE(1.0), Fw::F64LowerBoundExclusive<Fw::F64_RANGE_ARG(1.0)>>::value,
        "FW_F64_LOWER_BOUND_EXCLUSIVE must name F64LowerBoundExclusive");
    static_assert(
        std::is_same<FW_F64_UPPER_BOUND_INCLUSIVE(1.0), Fw::F64UpperBoundInclusive<Fw::F64_RANGE_ARG(1.0)>>::value,
        "FW_F64_UPPER_BOUND_INCLUSIVE must name F64UpperBoundInclusive");
    static_assert(
        std::is_same<FW_F64_UPPER_BOUND_EXCLUSIVE(1.0), Fw::F64UpperBoundExclusive<Fw::F64_RANGE_ARG(1.0)>>::value,
        "FW_F64_UPPER_BOUND_EXCLUSIVE must name F64UpperBoundExclusive");
}

// ----------------------------------------------------------------------
// F64Range: assertions
// ----------------------------------------------------------------------

// In the tests below, a value that is out of range must cause an assertion
// failure, and the assertion failure aborts the process. The statement inside
// each ASSERT_DEATH contains only the operation under test. Any other values
// are computed outside the statement, so that they cannot cause the death.
//
// The pattern "Assert: " is the start of the message that the default assertion
// handler prints to stderr, so a process that dies for another reason does not
// pass. These tests assume that assertions are enabled, as they should be in a
// unit test build. If they are not, the tests fail.

TEST(F64RangeTest, ValueOutOfRange) {
    const F64 belowLower = nextBelow(1.0);
    const F64 aboveUpper = nextAbove(2.0);

    using Inclusive = FW_F64_RANGE_INCLUSIVE(1.0, 2.0);
    ASSERT_DEATH(constructFrom<Inclusive>(belowLower), "Assert: ");
    ASSERT_EQ(static_cast<F64>(Inclusive(1.0)), 1.0);
    ASSERT_EQ(static_cast<F64>(Inclusive(2.0)), 2.0);
    ASSERT_DEATH(constructFrom<Inclusive>(aboveUpper), "Assert: ");

    using Exclusive = FW_F64_RANGE_EXCLUSIVE(1.0, 2.0);
    ASSERT_DEATH(constructFrom<Exclusive>(1.0), "Assert: ");
    ASSERT_EQ(static_cast<F64>(Exclusive(1.5)), 1.5);
    ASSERT_DEATH(constructFrom<Exclusive>(2.0), "Assert: ");

    using InclusiveExclusive = FW_F64_RANGE_INCLUSIVE_EXCLUSIVE(1.0, 2.0);
    ASSERT_EQ(static_cast<F64>(InclusiveExclusive(1.0)), 1.0);
    ASSERT_DEATH(constructFrom<InclusiveExclusive>(2.0), "Assert: ");

    using ExclusiveInclusive = FW_F64_RANGE_EXCLUSIVE_INCLUSIVE(1.0, 2.0);
    ASSERT_DEATH(constructFrom<ExclusiveInclusive>(1.0), "Assert: ");
    ASSERT_EQ(static_cast<F64>(ExclusiveInclusive(2.0)), 2.0);

    using LowerInclusive = FW_F64_LOWER_BOUND_INCLUSIVE(-5.0);
    ASSERT_DEATH(constructFrom<LowerInclusive>(-6.0), "Assert: ");
    ASSERT_EQ(static_cast<F64>(LowerInclusive(-5.0)), -5.0);

    using LowerExclusive = FW_F64_LOWER_BOUND_EXCLUSIVE(-5.0);
    ASSERT_DEATH(constructFrom<LowerExclusive>(-5.0), "Assert: ");
    ASSERT_EQ(static_cast<F64>(LowerExclusive(-4.0)), -4.0);

    using UpperInclusive = FW_F64_UPPER_BOUND_INCLUSIVE(5.0);
    ASSERT_EQ(static_cast<F64>(UpperInclusive(5.0)), 5.0);
    ASSERT_DEATH(constructFrom<UpperInclusive>(6.0), "Assert: ");

    using UpperExclusive = FW_F64_UPPER_BOUND_EXCLUSIVE(5.0);
    ASSERT_EQ(static_cast<F64>(UpperExclusive(4.0)), 4.0);
    ASSERT_DEATH(constructFrom<UpperExclusive>(5.0), "Assert: ");
}

TEST(F64RangeTest, AssignmentOutOfRange) {
    using Inclusive = FW_F64_RANGE_INCLUSIVE(1.0, 2.0);
    Inclusive range;
    range = 1.5;
    ASSERT_EQ(static_cast<F64>(range), 1.5);
    ASSERT_DEATH(range = 0.5, "Assert: ");
    ASSERT_DEATH(range = 2.5, "Assert: ");
}

TEST(F64RangeTest, NaNAndInfinityOutOfRange) {
    // NaN is not valid for a range that has a bound
    using Inclusive = FW_F64_RANGE_INCLUSIVE(1.0, 2.0);
    ASSERT_DEATH(constructFrom<Inclusive>(NAN_VALUE), "Assert: ");
    using LowerOnly = FW_F64_LOWER_BOUND_INCLUSIVE(1.0);
    ASSERT_DEATH(constructFrom<LowerOnly>(NAN_VALUE), "Assert: ");
    using UpperOnly = FW_F64_UPPER_BOUND_EXCLUSIVE(1.0);
    ASSERT_DEATH(constructFrom<UpperOnly>(NAN_VALUE), "Assert: ");
    // The values reported by the assertion are computed without converting the
    // value to an integer, which is undefined for NaN and infinity, so these
    // values must fail the assertion and not do anything else
    ASSERT_DEATH(constructFrom<Inclusive>(INF), "Assert: ");
    ASSERT_DEATH(constructFrom<Inclusive>(-INF), "Assert: ");
    ASSERT_DEATH(constructFrom<Inclusive>(std::numeric_limits<F64>::max()), "Assert: ");
    // The same holds for assignment
    Inclusive range;
    ASSERT_DEATH(range = NAN_VALUE, "Assert: ");
    ASSERT_DEATH(range = INF, "Assert: ");
    // An infinity that is within the range is accepted
    using LowerInfinite = FW_F64_LOWER_BOUND_INCLUSIVE(0.0);
    ASSERT_EQ(static_cast<F64>(LowerInfinite(INF)), INF);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
