// ======================================================================
// @file   F32RangeTest.cpp
// @brief  Unit tests for the F32 range types
//
// So far this file tests only the constexpr bit-cast functions F32_RANGE_ARG
// and F32_RANGE_ARG_TYPE_TO_F32. At run time, std::memcpy provides the
// reference result. The constexpr property is tested with static_assert.
// ======================================================================

#include <gtest/gtest.h>
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

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
