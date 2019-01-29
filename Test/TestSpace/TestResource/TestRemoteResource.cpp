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
#include <STask.h>
/**
 * ------------------------------------------------------------------------------------------------
 * link test
 * ------------------------------------------------------------------------------------------------
 */
TEST(SRemoteResource, Create)
{
    auto rem_c = Message::SRemoteResource();
}
/**
 * ------------------------------------------------------------------------------------------------
 * link test
 * ------------------------------------------------------------------------------------------------
 */
TEST(SRemoteResource, Link)
{
    STask::Enable();
    // variables --------------------------------------------------------------
    Message::SRemoteResource rem_c;
    Message::SRemoteResource rem_s;
    // settings ---------------------------------------------------------------
    auto size   = 100;
    auto addr   = "localhost";
    auto port   = 9999;

    // prepare ----------------------------------------------------------------
    auto in     = SRandom::Frame(size);
    auto out    = Frame(size);
    
    // wait -------------------------------------------------------------------
    auto future = async(std::launch::async, [&]{
        rem_s.Wait(addr, port, chrono::seconds(1));
        return true;
    });
    STask::Sleep(chrono::milliseconds(10));

    // link & send ------------------------------------------------------------ 
    rem_c.Link(addr, port).Drain(in);

    // test connection --------------------------------------------------------
    EXPECT_EQ(future.get(), true);
    
    // test read --------------------------------------------------------------
    EXPECT_EQ(rem_s.Fill(out).Good(), true);

    // test data --------------------------------------------------------------
    EXPECT_EQ(in, out);

    // test reverse send & reset frame ----------------------------------------
    out = Frame(size);  
    
    // test -------------------------------------------------------------------
    EXPECT_EQ(rem_s.Drain(in).Good(), true);
    EXPECT_EQ(rem_c.Fill(out).Good(), true);
    EXPECT_EQ(in, out);
}
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */