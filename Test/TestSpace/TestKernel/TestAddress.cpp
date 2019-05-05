/**
 * ------------------------------------------------------------------------------------------------
 * File:   TestAddress.cpp
 * Author: Luis Monteiro
 *
 * Created on November  2, 2018, 10:21 AM
 * ------------------------------------------------------------------------------------------------
 */
#include <gtest/gtest.h>
#include <SAddress.h>

using namespace std;
TEST(SAddress, Create)
{
    //use case 1
    SAddress a("lm@host.pt/test");
    EXPECT_EQ(a.host(), "host.pt");
    EXPECT_EQ(a.user(), "lm");
    EXPECT_EQ(a.port(), 0);
    EXPECT_EQ(a.path(), "test");    
    // use case 2
    SAddress b("7aquzu0b");
    EXPECT_EQ(b.file(), "7aquzu0b");
}

TEST(SAddress, Sum1)
{
    SAddress a("lm@host.pt/test");
    SAddress b("cc@local.com/sample");
    //use case 1 -> positive
    auto s = a + b;
    EXPECT_EQ(s.host(), "host.pt.local.com");
    EXPECT_EQ(s.user(), "lm_cc");
    EXPECT_EQ(s.port(), 0);
    EXPECT_EQ(s.path(), "test/sample");    
    // use case 2 -> negative
}

TEST(SAddress, Sum2)
{
    SAddress a("system");
    SAddress b("test");
    //use case 1 -> positive
    auto s = a + b;
    EXPECT_EQ("system.test", s);
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
