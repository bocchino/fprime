// ======================================================================
// @file   F64RangeSerialTest.cpp
// @brief  Unit tests for serializing and deserializing F64 ranges
//
// The behavior of the F64Range type itself is tested in F64RangeTest.cpp.
//
// Values are compared by their bits, so that the tests distinguish negative
// zero from zero. The NaN values used here are quiet NaNs: copying a signaling
// NaN may quiet it on some platforms, which would change its bits.
// ======================================================================

#include <gtest/gtest.h>
#include <cmath>
#include <cstring>
#include <limits>

#include <Fw/FPrimeBasicTypes.hpp>
#include <Fw/Types/NumericRange.hpp>
#include <Fw/Types/Serializable.hpp>

// F64Range is not available in every configuration (see NumericRange.hpp)
#if FW_HAS_F64_RANGE

namespace {

//! A buffer with room for several F64 values
class TestBuffer : public Fw::LinearBufferBase {
  public:
    TestBuffer() : Fw::LinearBufferBase(m_data, sizeof(m_data)) {}

  private:
    U8 m_data[64];
};

constexpr F64 INF = std::numeric_limits<F64>::infinity();
constexpr F64 NAN_VALUE = std::numeric_limits<F64>::quiet_NaN();

//! Reinterpret the bits of an F64 as a U64
U64 bitsOf(F64 f64) {
    U64 bits = 0;
    std::memcpy(&bits, &f64, sizeof bits);
    return bits;
}

//! Reinterpret the bits of a U64 as an F64
F64 doubleOf(U64 bits) {
    F64 f64 = 0.0;
    std::memcpy(&f64, &bits, sizeof f64);
    return f64;
}

//! The range of every F64 value except NaN
using AllButNaN = FW_F64_RANGE_INCLUSIVE(-INF, INF);

//! The range with no bounds, which contains every F64 value, including NaN
using NoBounds = Fw::F64Range<Fw::BoundType::NONE, 0, Fw::BoundType::NONE, 0>;

//! Serialize a range of type R into a buffer and deserialize it back,
//! checking the result. The buffer type B is either a concrete buffer class
//! or the base class Fw::SerialBufferBase, which is how generated code uses a
//! buffer. Serialization works on both because a range converts to F64.
//! Deserialization works on both because of the template for F64 ranges in
//! Fw::SerialBufferBase, which Fw::LinearBufferBase brings into scope.
template <typename R, typename B>
void roundTripThrough(B& buffer, F64 value, Fw::Endianness mode) {
    const R expected(value);
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(expected, mode));
    ASSERT_EQ(sizeof(F64), buffer.getSize());
    // Start from a value with different bits, so that the test can tell
    // whether deserialization stored anything
    const F64 different = (bitsOf(value) == bitsOf(1.0)) ? 2.0 : 1.0;
    R actual(different);
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.deserializeTo(actual, mode));
    ASSERT_EQ(bitsOf(value), bitsOf(actual));
    ASSERT_EQ(0U, buffer.getDeserializeSizeLeft());
}

//! Round trip a value through a fresh buffer of each kind
template <typename R>
void checkRoundTrip(F64 value, Fw::Endianness mode) {
    TestBuffer concrete;
    ASSERT_NO_FATAL_FAILURE(roundTripThrough<R>(concrete, value, mode));
    TestBuffer other;
    Fw::SerialBufferBase& base = other;
    ASSERT_NO_FATAL_FAILURE(roundTripThrough<R>(base, value, mode));
}

//! Check that serializing a range of type R gives the same bytes as
//! serializing the F64 value
template <typename R>
void checkSameBytesAsF64(F64 value, Fw::Endianness mode) {
    const R range(value);
    TestBuffer rangeBuffer;
    TestBuffer valueBuffer;
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, rangeBuffer.serializeFrom(range, mode));
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, valueBuffer.serializeFrom(value, mode));
    ASSERT_EQ(sizeof(F64), rangeBuffer.getSize());
    ASSERT_EQ(valueBuffer.getSize(), rangeBuffer.getSize());
    ASSERT_EQ(0, std::memcmp(valueBuffer.getBuffAddr(), rangeBuffer.getBuffAddr(), sizeof(F64)));
}

//! Run the checks above for a value, in each mode
template <typename R>
void checkValue(F64 value) {
    const Fw::Endianness modes[] = {Fw::Endianness::BIG, Fw::Endianness::LITTLE};
    for (const Fw::Endianness mode : modes) {
        ASSERT_NO_FATAL_FAILURE(checkRoundTrip<R>(value, mode)) << "bits = 0x" << std::hex << bitsOf(value);
        ASSERT_NO_FATAL_FAILURE(checkSameBytesAsF64<R>(value, mode)) << "bits = 0x" << std::hex << bitsOf(value);
    }
}

//! Serialize an F64 value into a fresh buffer, and deserialize it into the
//! range `range`.
//! @return The status. On return, `range` holds the value after deserialization.
template <typename R>
Fw::SerializeStatus deserializeRaw(F64 raw, R& range, Fw::Endianness mode = Fw::Endianness::BIG) {
    TestBuffer buffer;
    const Fw::SerializeStatus serializeStatus = buffer.serializeFrom(raw, mode);
    EXPECT_EQ(Fw::FW_SERIALIZE_OK, serializeStatus);
    return buffer.deserializeTo(range, mode);
}

//! Check that deserializing a value that is not valid for the range R gives an
//! error and leaves a range of type R unchanged
template <typename R>
void checkRejected(F64 raw, F64 initial, Fw::Endianness mode = Fw::Endianness::BIG) {
    R range(initial);
    ASSERT_EQ(Fw::FW_DESERIALIZE_FORMAT_ERROR, deserializeRaw(raw, range, mode))
        << "bits = 0x" << std::hex << bitsOf(raw);
    ASSERT_EQ(bitsOf(initial), bitsOf(range)) << "bits = 0x" << std::hex << bitsOf(raw);
}

//! Check that deserializing a value that is valid for the range R stores it
template <typename R>
void checkAccepted(F64 raw, F64 initial) {
    R range(initial);
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, deserializeRaw(raw, range)) << "bits = 0x" << std::hex << bitsOf(raw);
    ASSERT_EQ(bitsOf(raw), bitsOf(range)) << "bits = 0x" << std::hex << bitsOf(raw);
}

//! Serialize a value that is out of range, followed by a marker byte, and
//! deserialize the value into a range. The deserialization must report the
//! error and consume the value, so that the next thing in the buffer is the
//! marker, and not the bits of the rejected value.
void checkOutOfRangeValueIsConsumed(F64 raw, Fw::Endianness mode) {
    using Range = FW_F64_RANGE_INCLUSIVE(1.0, 1.0);
    ASSERT_FALSE(Range::isValid(raw));
    const U8 marker = 0xA5;
    TestBuffer buffer;
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(raw, mode));
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(marker));
    ASSERT_EQ(sizeof(F64) + sizeof(marker), buffer.getDeserializeSizeLeft());

    Range range(1.0);
    ASSERT_EQ(Fw::FW_DESERIALIZE_FORMAT_ERROR, buffer.deserializeTo(range, mode));
    ASSERT_EQ(bitsOf(1.0), bitsOf(range));
    // The rejected value is consumed: only the marker is left
    ASSERT_EQ(sizeof(marker), buffer.getDeserializeSizeLeft());

    U8 actual = 0;
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.deserializeTo(actual));
    ASSERT_EQ(marker, actual);
    ASSERT_EQ(0U, buffer.getDeserializeSizeLeft());
}

}  // namespace

// ----------------------------------------------------------------------
// Round trips and the wire format
// ----------------------------------------------------------------------

TEST(F64RangeSerialTest, RoundTripAndWireFormat) {
    // A value of each kind: zeros of both signs, normal values, the largest
    // and smallest finite values, the smallest normal value, subnormal
    // values, and infinities
    const F64 values[] = {0.0,
                          -0.0,
                          1.0,
                          -1.0,
                          0.1,
                          -3.5,
                          1.0e300,
                          std::numeric_limits<F64>::max(),
                          std::numeric_limits<F64>::lowest(),
                          std::numeric_limits<F64>::min(),
                          -std::numeric_limits<F64>::min(),
                          std::numeric_limits<F64>::denorm_min(),
                          -std::numeric_limits<F64>::denorm_min(),
                          doubleOf(0x000FFFFFFFFFFFFFULL),  // The largest subnormal value
                          INF,
                          -INF};
    for (const F64 value : values) {
        ASSERT_NO_FATAL_FAILURE(checkValue<AllButNaN>(value));
        ASSERT_NO_FATAL_FAILURE(checkValue<NoBounds>(value));
    }
}

TEST(F64RangeSerialTest, RoundTripNaN) {
    // A range with no bounds accepts NaN, so NaN round trips. Quiet NaNs with
    // each sign, and with a payload, keep their bits.
    const F64 values[] = {NAN_VALUE, doubleOf(0xFFF8000000000000ULL), doubleOf(0x7FF8000000000001ULL),
                          doubleOf(0x7FFFFFFFFFFFFFFFULL)};
    for (const F64 value : values) {
        ASSERT_NO_FATAL_FAILURE(checkValue<NoBounds>(value));
    }
}

TEST(F64RangeSerialTest, KnownBytes) {
    // The serialized form of a range is the serialized form of F64, which is
    // its IEEE 754 bit pattern as a U64
    using Range = FW_F64_RANGE_INCLUSIVE(-10.0, 10.0);
    {
        TestBuffer buffer;
        const U8* bytes = buffer.getBuffAddr();
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(Range(1.0)));
        ASSERT_EQ(8U, buffer.getSize());
        const U8 expected[] = {0x3F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        ASSERT_EQ(0, std::memcmp(expected, bytes, sizeof(expected)));
    }
    {
        TestBuffer buffer;
        const U8* bytes = buffer.getBuffAddr();
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(Range(1.0), Fw::Endianness::LITTLE));
        ASSERT_EQ(8U, buffer.getSize());
        const U8 expected[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F};
        ASSERT_EQ(0, std::memcmp(expected, bytes, sizeof(expected)));
    }
    // A negative value
    {
        TestBuffer buffer;
        const U8* bytes = buffer.getBuffAddr();
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(Range(-2.5)));
        ASSERT_EQ(8U, buffer.getSize());
        const U8 expected[] = {0xC0, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        ASSERT_EQ(0, std::memcmp(expected, bytes, sizeof(expected)));
    }
}

TEST(F64RangeSerialTest, EndiannessIsUsedInBothDirections) {
    // The mode argument reaches F64 in both directions: bytes written in one
    // mode and read in the other give the value with the bytes swapped
    TestBuffer buffer;
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(AllButNaN(1.0), Fw::Endianness::BIG));
    AllButNaN actual(2.0);
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.deserializeTo(actual, Fw::Endianness::LITTLE));
    ASSERT_EQ(0x000000000000F03FULL, bitsOf(actual));
}

TEST(F64RangeSerialTest, InteroperatesWithF64) {
    using Range = FW_F64_RANGE_INCLUSIVE(1.0, 2.0);
    // A range can be read as an F64
    {
        TestBuffer buffer;
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(Range(1.5)));
        F64 value = 0.0;
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.deserializeTo(value));
        ASSERT_EQ(bitsOf(1.5), bitsOf(value));
    }
    // An F64 can be read as a range
    {
        TestBuffer buffer;
        const F64 value = 2.0;
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(value));
        Range range(1.0);
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.deserializeTo(range));
        ASSERT_EQ(bitsOf(2.0), bitsOf(range));
    }
}

TEST(F64RangeSerialTest, SeveralValuesInOneBuffer) {
    // Each deserialization consumes exactly the bytes of its value, including
    // when F64 ranges are mixed with integer ranges and F32 ranges
    using F64Range = FW_F64_RANGE_INCLUSIVE(-1.0, 1.0);
    using U8Range = Fw::IntRangeInclusive<U8, 1, 9>;
    TestBuffer buffer;
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(F64Range(0.25)));
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(U8Range(7)));
#if FW_HAS_F32_RANGE
    using F32Range = FW_F32_RANGE_INCLUSIVE(-1.0f, 1.0f);
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(F32Range(0.5f)));
#endif
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(F64Range(-0.75)));

    F64Range first;
    U8Range second;
    F64Range fourth;
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.deserializeTo(first));
    ASSERT_EQ(bitsOf(0.25), bitsOf(first));
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.deserializeTo(second));
    ASSERT_EQ(7U, static_cast<U8>(second));
#if FW_HAS_F32_RANGE
    F32Range third;
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.deserializeTo(third));
    ASSERT_EQ(0.5f, static_cast<F32>(third));
#endif
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.deserializeTo(fourth));
    ASSERT_EQ(bitsOf(-0.75), bitsOf(fourth));
    ASSERT_EQ(0U, buffer.getDeserializeSizeLeft());
}

// ----------------------------------------------------------------------
// Validity of deserialized values
// ----------------------------------------------------------------------

TEST(F64RangeSerialTest, DeserializeInRange) {
    // Values at, next to, and between the bounds are accepted
    using Range = FW_F64_RANGE_INCLUSIVE(1.0, 2.0);
    const F64 values[] = {1.0, std::nextafter(1.0, INF), 1.5, std::nextafter(2.0, -INF), 2.0};
    for (const F64 value : values) {
        ASSERT_NO_FATAL_FAILURE(checkAccepted<Range>(value, 1.5));
    }
}

TEST(F64RangeSerialTest, DeserializeOutOfRange) {
    // A value that is not in the range gives an error and leaves the range unchanged
    using Range = FW_F64_RANGE_INCLUSIVE(1.0, 2.0);
    const F64 values[] = {std::nextafter(1.0, -INF),       std::nextafter(2.0, INF),           0.0, -0.0, -1.5, 1.0e300,
                          std::numeric_limits<F64>::max(), std::numeric_limits<F64>::lowest(), INF, -INF};
    for (const F64 value : values) {
        ASSERT_NO_FATAL_FAILURE(checkRejected<Range>(value, 1.5));
    }
    // The same in the other mode
    ASSERT_NO_FATAL_FAILURE(checkRejected<Range>(2.5, 1.5, Fw::Endianness::LITTLE));
}

TEST(F64RangeSerialTest, DeserializeOutOfRangeBounds) {
    // Each kind of bound is checked
    using Exclusive = FW_F64_RANGE_EXCLUSIVE(1.0, 2.0);
    ASSERT_NO_FATAL_FAILURE(checkRejected<Exclusive>(1.0, 1.5));
    ASSERT_NO_FATAL_FAILURE(checkRejected<Exclusive>(2.0, 1.5));
    ASSERT_NO_FATAL_FAILURE(checkAccepted<Exclusive>(std::nextafter(1.0, INF), 1.5));
    ASSERT_NO_FATAL_FAILURE(checkAccepted<Exclusive>(std::nextafter(2.0, -INF), 1.5));

    // An exclusive bound at zero rejects both zeros
    using PositiveOnly = FW_F64_LOWER_BOUND_EXCLUSIVE(0.0);
    ASSERT_NO_FATAL_FAILURE(checkRejected<PositiveOnly>(0.0, 1.0));
    ASSERT_NO_FATAL_FAILURE(checkRejected<PositiveOnly>(-0.0, 1.0));
    ASSERT_NO_FATAL_FAILURE(checkAccepted<PositiveOnly>(std::numeric_limits<F64>::denorm_min(), 1.0));
    ASSERT_NO_FATAL_FAILURE(checkAccepted<PositiveOnly>(INF, 1.0));

    // An upper bound only accepts every value below it, including -infinity
    using UpperOnly = FW_F64_UPPER_BOUND_INCLUSIVE(5.0);
    ASSERT_NO_FATAL_FAILURE(checkAccepted<UpperOnly>(-INF, 0.0));
    ASSERT_NO_FATAL_FAILURE(checkAccepted<UpperOnly>(std::numeric_limits<F64>::lowest(), 0.0));
    ASSERT_NO_FATAL_FAILURE(checkAccepted<UpperOnly>(5.0, 0.0));
    ASSERT_NO_FATAL_FAILURE(checkRejected<UpperOnly>(std::nextafter(5.0, INF), 0.0));
    ASSERT_NO_FATAL_FAILURE(checkRejected<UpperOnly>(INF, 0.0));
}

TEST(F64RangeSerialTest, DeserializeNaN) {
    // NaN is not valid for a range that has a bound, so a NaN in the buffer
    // gives an error, whatever its sign or payload
    using Inclusive = FW_F64_RANGE_INCLUSIVE(1.0, 2.0);
    using Exclusive = FW_F64_RANGE_EXCLUSIVE(1.0, 2.0);
    using LowerOnly = FW_F64_LOWER_BOUND_INCLUSIVE(1.0);
    using UpperOnly = FW_F64_UPPER_BOUND_EXCLUSIVE(1.0);
    const F64 nans[] = {NAN_VALUE, doubleOf(0xFFF8000000000000ULL), doubleOf(0x7FF8000000000001ULL)};
    for (const F64 nan : nans) {
        ASSERT_NO_FATAL_FAILURE(checkRejected<Inclusive>(nan, 1.5));
        ASSERT_NO_FATAL_FAILURE(checkRejected<Exclusive>(nan, 1.5));
        ASSERT_NO_FATAL_FAILURE(checkRejected<LowerOnly>(nan, 1.5));
        ASSERT_NO_FATAL_FAILURE(checkRejected<UpperOnly>(nan, 0.5));
        ASSERT_NO_FATAL_FAILURE(checkRejected<AllButNaN>(nan, 0.0));
        // A range with no bounds accepts it
        ASSERT_NO_FATAL_FAILURE(checkAccepted<NoBounds>(nan, 0.0));
    }
}

TEST(F64RangeSerialTest, DeserializeOutOfRangeConsumesTheValue) {
    // An out-of-range value is a valid F64, so it is consumed. Otherwise the
    // next deserialization would read its bits as something else.
    const F64 values[] = {0.0,
                          -0.0,
                          2.0,
                          std::numeric_limits<F64>::denorm_min(),
                          std::numeric_limits<F64>::max(),
                          std::numeric_limits<F64>::lowest(),
                          INF,
                          -INF,
                          NAN_VALUE};
    const Fw::Endianness modes[] = {Fw::Endianness::BIG, Fw::Endianness::LITTLE};
    for (const F64 value : values) {
        for (const Fw::Endianness mode : modes) {
            ASSERT_NO_FATAL_FAILURE(checkOutOfRangeValueIsConsumed(value, mode))
                << "bits = 0x" << std::hex << bitsOf(value);
        }
    }
}

TEST(F64RangeSerialTest, DeserializeContinuesAfterOutOfRangeValue) {
    // Report the out-of-range value, and then deserialize the next value
    using Range = FW_F64_RANGE_INCLUSIVE(0.0, 10.0);
    TestBuffer buffer;
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(1.5));
    // These values are out of range for the type that will read them
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(NAN_VALUE));
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(-1.0));
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(9.0));

    Range first(5.0);
    Range second(5.0);
    Range third(5.0);
    Range fourth(5.0);
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.deserializeTo(first));
    ASSERT_EQ(bitsOf(1.5), bitsOf(first));
    // The second and third values are reported, and the ranges are unchanged
    ASSERT_EQ(Fw::FW_DESERIALIZE_FORMAT_ERROR, buffer.deserializeTo(second));
    ASSERT_EQ(bitsOf(5.0), bitsOf(second));
    ASSERT_EQ(Fw::FW_DESERIALIZE_FORMAT_ERROR, buffer.deserializeTo(third));
    ASSERT_EQ(bitsOf(5.0), bitsOf(third));
    // The fourth value is read from the right place
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.deserializeTo(fourth));
    ASSERT_EQ(bitsOf(9.0), bitsOf(fourth));
    ASSERT_EQ(0U, buffer.getDeserializeSizeLeft());
}

// ----------------------------------------------------------------------
// Buffer errors
// ----------------------------------------------------------------------

TEST(F64RangeSerialTest, DeserializeBufferErrors) {
    // Errors from reading the F64 are passed through, and the range is unchanged
    {
        TestBuffer buffer;
        AllButNaN range(7.0);
        ASSERT_EQ(Fw::FW_DESERIALIZE_BUFFER_EMPTY, buffer.deserializeTo(range));
        ASSERT_EQ(bitsOf(7.0), bitsOf(range));
    }
    {
        // Fewer bytes than an F64 needs
        TestBuffer buffer;
        const U32 shortValue = 0x12345678;
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(shortValue));
        AllButNaN range(7.0);
        ASSERT_EQ(Fw::FW_DESERIALIZE_SIZE_MISMATCH, buffer.deserializeTo(range));
        ASSERT_EQ(bitsOf(7.0), bitsOf(range));
    }
}

TEST(F64RangeSerialTest, SerializeNoRoom) {
    U8 small[sizeof(F64) - 1] = {};
    Fw::ExternalSerializeBuffer tight(small, sizeof(small));
    ASSERT_EQ(Fw::FW_SERIALIZE_NO_ROOM_LEFT, tight.serializeFrom(AllButNaN(1.0)));
    ASSERT_EQ(0U, tight.getSize());
}

#endif  // FW_HAS_F64_RANGE
