#include <gtest/gtest.h>
/**
 * space
 */
#include <SFileResource.h>
#include <SRandom.h>
/**
 * tests
 */
TEST(SFileResource, Create)
{
    SOFileResource f("/tmp/test");

    EXPECT_EQ(f.Path(), "/tmp/test");
}
/**
 */
TEST(SFileResource, Move)
{
    SRemoteResource rem_c("/tmp/test1");
    
}