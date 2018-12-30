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
    SOFileResource f1("/tmp/test1");
    SOFileResource f2("/tmp/test2");
    SOFileResource f(SRandom::FileName(), f1);
    

    //f1 = move(f2);

    //swap(f1, f2);


    //f3 = move(f1);
    //SOFileResource f(move(f1));
    //f2 = move(f1);


    EXPECT_NE(f.Path(), "/tmp/test1");
    EXPECT_EQ(f1.Path(), "/tmp/test1");
    EXPECT_EQ(f2.Path(), "/tmp/test2");
}