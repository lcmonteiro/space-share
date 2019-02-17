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
    SAddress a("lm@host.pt/test");
    //use case 1 -> positive
    EXPECT_EQ(a.Host(), "host.pt");
    EXPECT_EQ(a.User(), "lm");
    EXPECT_EQ(a.Port(), 0);
    EXPECT_EQ(a.Path(), "test");    
    // use case 2 -> negative
}

TEST(SAddress, Sum1)
{
    SAddress a("lm@host.pt/test");
    SAddress b("cc@local.com/sample");
    //use case 1 -> positive
    auto s = a + b;
    EXPECT_EQ(s.Host(), "host.pt.local.com");
    EXPECT_EQ(s.User(), "lm_cc");
    EXPECT_EQ(s.Port(), 0);
    EXPECT_EQ(s.Path(), "test/sample");    
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
