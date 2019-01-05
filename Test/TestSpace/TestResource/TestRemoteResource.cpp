#include <gtest/gtest.h>
/**
 * std
 */
#include <future>
/**
 * space
 */
#include <SRemoteResource.h>
#include <SRandom.h>
/**
 * tests
 */
TEST(SRemoteResource, Link)
{
    Message::SRemoteResource rem_c;
    Message::SRemoteResource rem_s;

    rem_c.Link("127.0.0.1", 9999);

    auto future = async(std::launch::async, [&rem_s]{
        rem_s.Wait("127.0.0.1", 9999, chrono::seconds(1));
        return true;
    });
    


    
    EXPECT_EQ(future.get(), true);
}