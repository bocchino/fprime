// ----------------------------------------------------------------------
// TestMain.cpp
// ----------------------------------------------------------------------

#include "gtest/gtest.h"

#include "Fw/Dp/test/util/DpContainerHeader.hpp"
#include "STest/Random/Random.hpp"
#include "Fw/Dp/DpContainer.hpp"

using namespace Fw;

TEST(TODO, OK) {
    U8 data[100];
    Fw::Buffer buffer(data, sizeof data);
    DpContainer container(0, buffer);
    auto status = container.serializeHeader();
    ASSERT_EQ(status, Fw::FW_SERIALIZE_OK);
    TestUtil::DpContainerHeader header;
    header.deserialize(buffer);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    STest::Random::seed();
    return RUN_ALL_TESTS();
}
