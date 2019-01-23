#include <gtest/gtest.h>
/**
 * std
 */
#include <memory>
/**
 * space
 */
#include "SResourceMonitor.h"
#include "SEventResource.h"
#include "SRandom.h"
#include "SText.h"
/**
 * ------------------------------------------------------------------------------------------------
 * tests
 * ------------------------------------------------------------------------------------------------
 */
TEST(SResourceMonitor, Events)
{
    typedef SResourceMonitor<> ResourceMonitor;

    // create events -------------------------------------
    auto event1 = SEventResource(0);
    auto event2 = SEventResource(0);
    // create monitor ------------------------------------ 
    auto monitor = ResourceMonitor(&event1, &event2);

    // set event 1 ---------------------------------------
    event1.Send();

    // monitor test --------------------------------------
    auto res1 = monitor.Wait(ResourceMonitor::Time(10));
    EXPECT_EQ(res1.size(),  1);
    EXPECT_EQ(res1.front(), 0);
    
    // set event 1 ---------------------------------------
    event2.Send();

    // monitor test --------------------------------------
    auto res2 = monitor.Wait(ResourceMonitor::Time(10));
    EXPECT_EQ(res2.size(),  1);
    EXPECT_EQ(res2.front(), 1);
    
}
