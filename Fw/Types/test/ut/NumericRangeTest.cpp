#include <gtest/gtest.h>
#include <Fw/Types/NumericRange.hpp>

TEST(NumericRangeTest, Construction) {
    Fw::IntRangeExclusiveInclusive<U32, 0, 10> rangeDefault;
    ASSERT_EQ(rangeDefault, 1U);
    Fw::IntRangeInclusiveExclusive<U32, 0, 10> range(1);
    ASSERT_EQ(range, 1U);
    Fw::IntLowerBoundExclusive<U32, 0> rangeLower(2);
    ASSERT_EQ(rangeLower, 2U);
    Fw::IntUpperBoundExclusive<U32, 10> rangeUpper(3);
    ASSERT_EQ(rangeUpper, 3U);
}
