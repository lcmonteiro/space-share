/**
 * ------------------------------------------------------------------------------------------------
 * File:   TestRemoteResource.cpp
 * Author: Luis Monteiro
 *
 * Created on January  2, 2019, 10:21 AM
 * ------------------------------------------------------------------------------------------------
 */
#include <gtest/gtest.h>
/**
 * std
 */
#include <future>
/**
 * space
 */
#include "SResourceMonitor.h"
#include "SRemoteResource.h"
#include "SRandom.h"
#include "STask.h"
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
    // definitions ---------------------------------------
    typedef SResourceMonitor<> ResourceMonitor;

    // variables --------------------------------------------------------------
    Message::SRemoteResource rem_c;
    Message::SRemoteResource rem_s;
    
    // settings ---------------------------------------------------------------
    auto size   = 100;
    auto addr   = "localhost";
    auto port   = 9999;

    // prepare ----------------------------------------------------------------
    auto const in  = SRandom::Frame(size);
    auto       out = IOFrame(size);
    
    // wait -------------------------------------------------------------------
    auto future = async(std::launch::async, [&] {
        STask::Enable(); 
        rem_s.wait(addr, port, std::chrono::seconds(1));
        return true;
    });
    STask::Sleep(std::chrono::milliseconds(10));

    // link & send ------------------------------------------------------------ 
    rem_c.link(addr, port).write(in);

    // test connection --------------------------------------------------------
    EXPECT_EQ(future.get(), true);
    
    // wait -------------------------------------------------------------------
    ResourceMonitor(&rem_s).wait(std::chrono::milliseconds(100));

    // read -------------------------------------------------------------------
    EXPECT_EQ(rem_s.fill(out).good(), true);

    // test data --------------------------------------------------------------
    EXPECT_EQ(in, out);

    // test reverse send & reset frame ----------------------------------------
    out = IOFrame(size);  

    // send -------------------------------------------------------------------
    EXPECT_EQ(rem_s.write(in).good(), true);

    // wait -------------------------------------------------------------------
    ResourceMonitor(&rem_c).wait(std::chrono::milliseconds(100));

    // receive ----------------------------------------------------------------
    EXPECT_EQ(rem_c.fill(out).good(), true);
    
    // test data --------------------------------------------------------------
    EXPECT_EQ(in, out);
}
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */