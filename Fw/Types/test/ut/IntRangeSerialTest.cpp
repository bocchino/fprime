// ======================================================================
// @file   IntRangeSerialTest.cpp
// @brief  Unit tests for serializing and deserializing integer ranges
//
// The behavior of the IntRange type itself is tested in IntRangeTest.cpp.
// ======================================================================

#include <gtest/gtest.h>
#include <cstring>
#include <limits>

#include <Fw/FPrimeBasicTypes.hpp>
#include <Fw/Types/IntRange.hpp>
#include <Fw/Types/Serializable.hpp>

namespace {

//! A buffer with room for several values of the largest integer type
class TestBuffer : public Fw::LinearBufferBase {
  public:
    TestBuffer() : Fw::LinearBufferBase(m_data, sizeof(m_data)) {}

  private:
    U8 m_data[32];
};

//! The range containing every value of the integer type T
template <typename T>
using FullRange = Fw::IntRangeInclusive<T, std::numeric_limits<T>::min(), std::numeric_limits<T>::max()>;

//! Serialize a range into a buffer and deserialize it back, checking the
//! result. The buffer type B is either a concrete buffer class or the base
//! class Fw::SerialBufferBase, which is how generated code uses a buffer.
//! Serialization works on both because a range converts to its base type, so
//! the call resolves to the overload for that type. Deserialization works on
//! both because of the template for integer ranges in Fw::SerialBufferBase,
//! which Fw::LinearBufferBase brings into scope with a using declaration.
template <typename B, typename T>
void roundTripThrough(B& buffer, T value, Fw::Endianness mode) {
    using Range = FullRange<T>;
    const Range expected(value);
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(expected, mode));
    ASSERT_EQ(sizeof(T), buffer.getSize());
    // Start from a value that differs from the one in the buffer, so that
    // the test can tell whether deserialization stored anything
    const T different = (value == 0) ? static_cast<T>(1) : static_cast<T>(0);
    Range actual(different);
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.deserializeTo(actual, mode));
    ASSERT_EQ(value, static_cast<T>(actual));
    ASSERT_EQ(0U, buffer.getDeserializeSizeLeft());
}

//! Round trip a value of type T through a fresh buffer of each kind
template <typename T>
void checkRoundTrip(T value, Fw::Endianness mode) {
    TestBuffer concrete;
    ASSERT_NO_FATAL_FAILURE(roundTripThrough(concrete, value, mode));
    TestBuffer other;
    Fw::SerialBufferBase& base = other;
    ASSERT_NO_FATAL_FAILURE(roundTripThrough(base, value, mode));
}

//! Check that serializing a range of type T gives the same bytes as
//! serializing a value of type T
template <typename T>
void checkSameBytesAsBaseType(T value, Fw::Endianness mode) {
    const FullRange<T> range(value);
    TestBuffer rangeBuffer;
    TestBuffer valueBuffer;
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, rangeBuffer.serializeFrom(range, mode));
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, valueBuffer.serializeFrom(value, mode));
    ASSERT_EQ(sizeof(T), rangeBuffer.getSize());
    ASSERT_EQ(valueBuffer.getSize(), rangeBuffer.getSize());
    ASSERT_EQ(0, std::memcmp(valueBuffer.getBuffAddr(), rangeBuffer.getBuffAddr(), sizeof(T)));
}

//! Run the checks above for the values of T at and near its limits
template <typename T>
void checkType() {
    const T minValue = std::numeric_limits<T>::min();
    const T maxValue = std::numeric_limits<T>::max();
    const T values[] = {minValue,          static_cast<T>(minValue + 1), static_cast<T>(0),
                        static_cast<T>(1), static_cast<T>(maxValue - 1), maxValue};
    const Fw::Endianness modes[] = {Fw::Endianness::BIG, Fw::Endianness::LITTLE};
    for (const T value : values) {
        for (const Fw::Endianness mode : modes) {
            ASSERT_NO_FATAL_FAILURE(checkRoundTrip(value, mode));
            ASSERT_NO_FATAL_FAILURE(checkSameBytesAsBaseType(value, mode));
        }
    }
}

//! Serialize a value of type T into a fresh buffer, and deserialize it into
//! the range `range`, whose base type is T.
//! @return The status. On return, `range` holds the value after deserialization.
template <typename R, typename T>
Fw::SerializeStatus deserializeRaw(T raw, R& range, Fw::Endianness mode = Fw::Endianness::BIG) {
    TestBuffer buffer;
    const Fw::SerializeStatus serializeStatus = buffer.serializeFrom(raw, mode);
    EXPECT_EQ(Fw::FW_SERIALIZE_OK, serializeStatus);
    return buffer.deserializeTo(range, mode);
}

//! Serialize a value that is out of range, followed by a marker byte, and
//! deserialize the value into a range. The deserialization must report the
//! error and consume the value, so that the next thing in the buffer is the
//! marker, and not the bits of the rejected value.
template <typename T>
void checkOutOfRangeValueIsConsumed(T raw, Fw::Endianness mode) {
    using Range = Fw::IntRangeInclusive<T, 1, 1>;
    ASSERT_FALSE(Range::isValid(raw));
    const U8 marker = 0xA5;
    TestBuffer buffer;
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(raw, mode));
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(marker));
    ASSERT_EQ(sizeof(T) + sizeof(marker), buffer.getDeserializeSizeLeft());

    Range range(1);
    ASSERT_EQ(Fw::FW_DESERIALIZE_FORMAT_ERROR, buffer.deserializeTo(range, mode));
    ASSERT_EQ(static_cast<T>(1), static_cast<T>(range));
    // The rejected value is consumed: only the marker is left
    ASSERT_EQ(sizeof(marker), buffer.getDeserializeSizeLeft());

    U8 actual = 0;
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.deserializeTo(actual));
    ASSERT_EQ(marker, actual);
    ASSERT_EQ(0U, buffer.getDeserializeSizeLeft());
}

//! Run checkOutOfRangeValueIsConsumed for values of T at the limits and zero,
//! in each mode
template <typename T>
void checkOutOfRangeValuesAreConsumed() {
    const T raws[] = {std::numeric_limits<T>::min(), static_cast<T>(0), std::numeric_limits<T>::max()};
    const Fw::Endianness modes[] = {Fw::Endianness::BIG, Fw::Endianness::LITTLE};
    for (const T raw : raws) {
        for (const Fw::Endianness mode : modes) {
            ASSERT_NO_FATAL_FAILURE(checkOutOfRangeValueIsConsumed(raw, mode));
        }
    }
}

}  // namespace

TEST(IntRangeSerialTest, RoundTripAndWireFormat) {
    checkType<U8>();
    checkType<I8>();
    checkType<U16>();
    checkType<I16>();
    checkType<U32>();
    checkType<I32>();
    checkType<U64>();
    checkType<I64>();
}

TEST(IntRangeSerialTest, KnownBytes) {
    // The serialized form of a range is the serialized form of its base type
    using Range16 = FullRange<U16>;
    {
        TestBuffer buffer;
        const U8* bytes = buffer.getBuffAddr();
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(Range16(0xABCD)));
        ASSERT_EQ(2U, buffer.getSize());
        ASSERT_EQ(0xAB, bytes[0]);
        ASSERT_EQ(0xCD, bytes[1]);
    }
    {
        TestBuffer buffer;
        const U8* bytes = buffer.getBuffAddr();
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(Range16(0xABCD), Fw::Endianness::LITTLE));
        ASSERT_EQ(2U, buffer.getSize());
        ASSERT_EQ(0xCD, bytes[0]);
        ASSERT_EQ(0xAB, bytes[1]);
    }
    // A negative value
    using NegativeRange = Fw::IntRangeInclusive<I32, -5, 5>;
    {
        TestBuffer buffer;
        const U8* bytes = buffer.getBuffAddr();
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(NegativeRange(-3)));
        ASSERT_EQ(4U, buffer.getSize());
        ASSERT_EQ(0xFF, bytes[0]);
        ASSERT_EQ(0xFF, bytes[1]);
        ASSERT_EQ(0xFF, bytes[2]);
        ASSERT_EQ(0xFD, bytes[3]);
    }
}

TEST(IntRangeSerialTest, EndiannessIsUsedInBothDirections) {
    // The mode argument reaches the base type in both directions: bytes
    // written in one mode and read in the other give a different value
    using Range = FullRange<U16>;
    TestBuffer buffer;
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(Range(0x0102), Fw::Endianness::BIG));
    Range actual(0);
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.deserializeTo(actual, Fw::Endianness::LITTLE));
    ASSERT_EQ(0x0201U, static_cast<U16>(actual));
}

TEST(IntRangeSerialTest, InteroperatesWithBaseType) {
    // A range can be read as a value of its base type
    using Range = Fw::IntRangeInclusive<U32, 3, 5>;
    {
        TestBuffer buffer;
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(Range(4)));
        U32 value = 0;
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.deserializeTo(value));
        ASSERT_EQ(4U, value);
    }
    // A value of the base type can be read as a range
    {
        TestBuffer buffer;
        const U32 value = 5;
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(value));
        Range range(3);
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.deserializeTo(range));
        ASSERT_EQ(5U, static_cast<U32>(range));
    }
}

TEST(IntRangeSerialTest, SeveralValuesInOneBuffer) {
    // Each deserialization consumes exactly the bytes of its value
    using Range8 = Fw::IntRangeInclusive<U8, 1, 9>;
    using Range16 = Fw::IntRangeInclusive<I16, -100, 100>;
    using Range32 = Fw::IntRangeInclusive<U32, 0, 1000>;
    TestBuffer buffer;
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(Range8(7)));
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(Range16(-42)));
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(Range32(999)));
    ASSERT_EQ(1U + 2U + 4U, buffer.getSize());

    Range8 value8;
    Range16 value16;
    Range32 value32;
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.deserializeTo(value8));
    ASSERT_EQ(7U, static_cast<U8>(value8));
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.deserializeTo(value16));
    ASSERT_EQ(-42, static_cast<I16>(value16));
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.deserializeTo(value32));
    ASSERT_EQ(999U, static_cast<U32>(value32));
    ASSERT_EQ(0U, buffer.getDeserializeSizeLeft());
}

TEST(IntRangeSerialTest, DeserializeInRange) {
    // Values at and between the bounds are accepted
    using Range = Fw::IntRangeInclusive<U32, 3, 5>;
    for (U32 raw = 3; raw <= 5; raw++) {
        Range range;
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, deserializeRaw(raw, range));
        ASSERT_EQ(raw, static_cast<U32>(range));
    }
}

TEST(IntRangeSerialTest, DeserializeOutOfRange) {
    // A value that is not in the range gives an error and leaves the range unchanged
    using Range = Fw::IntRangeInclusive<U32, 3, 5>;
    const U32 values[] = {0, 2, 6, std::numeric_limits<U32>::max()};
    for (const U32 raw : values) {
        Range range(4);
        ASSERT_EQ(Fw::FW_DESERIALIZE_FORMAT_ERROR, deserializeRaw(raw, range)) << "raw = " << raw;
        ASSERT_EQ(4U, static_cast<U32>(range));
    }
    // The same in the other mode
    Range range(4);
    ASSERT_EQ(Fw::FW_DESERIALIZE_FORMAT_ERROR, deserializeRaw(static_cast<U32>(6), range, Fw::Endianness::LITTLE));
    ASSERT_EQ(4U, static_cast<U32>(range));
}

TEST(IntRangeSerialTest, DeserializeOutOfRangeBounds) {
    // Each kind of bound is checked
    using Exclusive = Fw::IntRangeExclusive<I16, -5, 5>;
    {
        Exclusive range(0);
        ASSERT_EQ(Fw::FW_DESERIALIZE_FORMAT_ERROR, deserializeRaw(static_cast<I16>(-5), range));
        ASSERT_EQ(Fw::FW_DESERIALIZE_FORMAT_ERROR, deserializeRaw(static_cast<I16>(5), range));
        ASSERT_EQ(0, static_cast<I16>(range));
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, deserializeRaw(static_cast<I16>(-4), range));
        ASSERT_EQ(-4, static_cast<I16>(range));
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, deserializeRaw(static_cast<I16>(4), range));
        ASSERT_EQ(4, static_cast<I16>(range));
    }
    using LowerOnly = Fw::IntLowerBoundExclusive<U8, 0>;
    {
        LowerOnly range(7);
        ASSERT_EQ(Fw::FW_DESERIALIZE_FORMAT_ERROR, deserializeRaw(static_cast<U8>(0), range));
        ASSERT_EQ(7U, static_cast<U8>(range));
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, deserializeRaw(static_cast<U8>(1), range));
        ASSERT_EQ(1U, static_cast<U8>(range));
    }
    using UpperOnly = Fw::IntUpperBoundInclusive<I32, 5>;
    {
        UpperOnly range(0);
        ASSERT_EQ(Fw::FW_DESERIALIZE_FORMAT_ERROR, deserializeRaw(static_cast<I32>(6), range));
        ASSERT_EQ(0, static_cast<I32>(range));
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, deserializeRaw(std::numeric_limits<I32>::min(), range));
        ASSERT_EQ(std::numeric_limits<I32>::min(), static_cast<I32>(range));
    }
}

TEST(IntRangeSerialTest, DeserializeOutOfRangeConsumesTheValue) {
    // An out-of-range value has the bits of a valid value of the base type, so
    // it is consumed. Otherwise the next deserialization would read its bits
    // as something else.
    checkOutOfRangeValuesAreConsumed<U8>();
    checkOutOfRangeValuesAreConsumed<I8>();
    checkOutOfRangeValuesAreConsumed<U16>();
    checkOutOfRangeValuesAreConsumed<I16>();
    checkOutOfRangeValuesAreConsumed<U32>();
    checkOutOfRangeValuesAreConsumed<I32>();
    checkOutOfRangeValuesAreConsumed<U64>();
    checkOutOfRangeValuesAreConsumed<I64>();
}

TEST(IntRangeSerialTest, DeserializeContinuesAfterOutOfRangeValue) {
    // Report the out-of-range value, and then deserialize the next value
    using Range8 = Fw::IntRangeInclusive<U8, 1, 9>;
    using Range16 = Fw::IntRangeInclusive<I16, -100, 100>;
    using Range32 = Fw::IntRangeInclusive<U32, 0, 1000>;
    TestBuffer buffer;
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(static_cast<U8>(7)));
    // This value is out of range for the type that will read it
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(static_cast<I16>(500)));
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(static_cast<U32>(999)));

    Range8 value8(1);
    Range16 value16(-1);
    Range32 value32(0);
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.deserializeTo(value8));
    ASSERT_EQ(7U, static_cast<U8>(value8));
    // The second value is reported and left out of the range
    ASSERT_EQ(Fw::FW_DESERIALIZE_FORMAT_ERROR, buffer.deserializeTo(value16));
    ASSERT_EQ(-1, static_cast<I16>(value16));
    // The third value is read from the right place
    ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.deserializeTo(value32));
    ASSERT_EQ(999U, static_cast<U32>(value32));
    ASSERT_EQ(0U, buffer.getDeserializeSizeLeft());
}

TEST(IntRangeSerialTest, DeserializeBufferErrors) {
    // Errors from reading the base type are passed through, and the range is unchanged
    using Range = FullRange<U32>;
    {
        TestBuffer buffer;
        Range range(7);
        ASSERT_EQ(Fw::FW_DESERIALIZE_BUFFER_EMPTY, buffer.deserializeTo(range));
        ASSERT_EQ(7U, static_cast<U32>(range));
    }
    {
        TestBuffer buffer;
        const U16 shortValue = 0x1234;
        ASSERT_EQ(Fw::FW_SERIALIZE_OK, buffer.serializeFrom(shortValue));
        Range range(7);
        ASSERT_EQ(Fw::FW_DESERIALIZE_SIZE_MISMATCH, buffer.deserializeTo(range));
        ASSERT_EQ(7U, static_cast<U32>(range));
    }
}

TEST(IntRangeSerialTest, SerializeNoRoom) {
    U8 small[sizeof(U32) - 1] = {};
    Fw::ExternalSerializeBuffer tight(small, sizeof(small));
    ASSERT_EQ(Fw::FW_SERIALIZE_NO_ROOM_LEFT, tight.serializeFrom(FullRange<U32>(1)));
    ASSERT_EQ(0U, tight.getSize());
}
