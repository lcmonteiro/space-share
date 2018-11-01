#include <gtest/gtest.h>

TEST(example, test)
{
    ASSERT_NEAR(3.0, 3.0, 1.0e-11);
}
TEST(example, test2)
{
    ASSERT_NEAR(4.0, 3.0, 1.0e-11);
}