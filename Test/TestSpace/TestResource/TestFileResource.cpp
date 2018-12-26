#include <gtest/gtest.h>
/**
 */
#include <SFileResource.h>
/**
 */
TEST(SFileResource, Create)
{
    SOFileResource f("/tmp/test");

    EXPECT_EQ(f.path(), "/tmp/test");
}