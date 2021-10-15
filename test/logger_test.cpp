#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {

// Expect two strings not to be equal.
EXPECT_STRNE("hello", "world");
// Expect equality.
EXPECT_EQ(7 * 6, 42);
// Expect inequality
EXPECT_NE(-1, 0xFFFFFFF0);
EXPECT_NE(7, 0xFFFFFFF0);
}

