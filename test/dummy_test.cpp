#include <gtest/gtest.h>
// uncomment line below if you plan to use GMock
// #include <gmock/gmock.h>

// TEST(...)
// TEST_F(...)


TEST(FactorialTest, Positive) {
  EXPECT_EQ(1, 1);
}

TEST(FactorialTest, Negative) {
  EXPECT_EQ(1, 2);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}