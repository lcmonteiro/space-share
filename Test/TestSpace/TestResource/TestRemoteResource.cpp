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
    auto in     = SRandom::Frame(size);
    auto out    = IFrame(size);
    
    // wait -------------------------------------------------------------------
    auto future = async(std::launch::async, [&] {
        STask::Enable(); 
        rem_s.Wait(addr, port, std::chrono::seconds(1));
        return true;
    });
    STask::Sleep(std::chrono::milliseconds(10));

    // link & send ------------------------------------------------------------ 
    rem_c.Link(addr, port).Drain(in);

    // test connection --------------------------------------------------------
    EXPECT_EQ(future.get(), true);
    
    // wait -------------------------------------------------------------------
    ResourceMonitor(&rem_s).Wait(std::chrono::milliseconds(100));

    // read -------------------------------------------------------------------
    EXPECT_EQ(rem_s.Fill(out).Good(), true);

    // test data --------------------------------------------------------------
    EXPECT_EQ(in, out);

    // test reverse send & reset frame ----------------------------------------
    out = IFrame(size);  
    
    // send -------------------------------------------------------------------
    EXPECT_EQ(rem_s.Drain(in).Good(), true);
    
    // wait -------------------------------------------------------------------
    ResourceMonitor(&rem_c).Wait(std::chrono::milliseconds(100));

    // receive ----------------------------------------------------------------
    EXPECT_EQ(rem_c.Fill(out).Good(), true);
    
    // test data --------------------------------------------------------------
    EXPECT_EQ(in, out);
}
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */