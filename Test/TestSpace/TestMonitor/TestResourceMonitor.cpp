/**
 * ------------------------------------------------------------------------------------------------
 * File:   TestResourceMonitor.cpp
 * Author: Luis Monteiro
 *
 * Created on January  2, 2019, 10:21 AM
 * ------------------------------------------------------------------------------------------------
 */
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
#include "STask.h"
/**
 * ------------------------------------------------------------------------------------------------
 * test - ResourceMonitor & Events
 * ------------------------------------------------------------------------------------------------
 */
TEST(SResourceMonitor, Events)
{
    STask::Enable();
    // definitions ---------------------------------------
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

    // clr event 1 ---------------------------------------
    event1.Clear();

    // set event 2 ---------------------------------------
    event2.Send();

    // monitor test --------------------------------------
    auto res2 = monitor.Wait(ResourceMonitor::Time(10));
    EXPECT_EQ(res2.size(),  1);
    EXPECT_EQ(res2.front(), 1);
}
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */