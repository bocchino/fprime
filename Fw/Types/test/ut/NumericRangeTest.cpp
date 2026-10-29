#include <gtest/gtest.h>
#include <Fw/Types/NumericRange.hpp>

TEST(NumericRangeTest, Construction) {
    Fw::IntRange<U32, Fw::BoundType::INCLUSIVE, 0, Fw::BoundType::EXCLUSIVE, 10> rangeDefault;
    ASSERT_EQ(rangeDefault, 0U);
    Fw::IntRange<U32, Fw::BoundType::INCLUSIVE, 0, Fw::BoundType::EXCLUSIVE, 10> range(1);
    ASSERT_EQ(range, 1U);
    Fw::IntRangeLower<U32, Fw::BoundType::EXCLUSIVE, 0> rangeLower(2);
    ASSERT_EQ(rangeLower, 2U);
    Fw::IntRangeUpper<U32, Fw::BoundType::EXCLUSIVE, 10> rangeUpper(3);
    ASSERT_EQ(rangeUpper, 3U);
}
