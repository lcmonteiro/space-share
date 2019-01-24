#include <gtest/gtest.h>
/**
 * std
 */
#include <memory>
/**
 * space
 */
#include "SContainerMonitor.h"
#include "SRemoteResource.h"
#include "SRandom.h"
#include "SText.h"
/**
 * ------------------------------------------------------------------------------------------------
 * test - SRoadMonitor & Event resource
 * ------------------------------------------------------------------------------------------------
 */
TEST(SRoadMonitor, Create)
{
    typedef SRoadMonitor<
        SText, 
        SEventResource,
        SResourceMonitor<SMonitor::SDirect, SDynamicMonitor>
    > RoadMonitor;

    // create monitor ------------------------------------- 
    auto monitor = RoadMonitor()
        .Insert("1", SEventResource(0))
        .Insert("2", SEventResource(0))
    .Build();

    // set event 1 ---------------------------------------
    monitor.Find("1").Send();

    // monitor test --------------------------------------
    auto res1 = monitor.Wait();
    EXPECT_EQ(res1.size(),                1);
    EXPECT_EQ(res1.front().get().Clear(), 1);

    // set event 1 ---------------------------------------
    monitor.Find("2").Send();

    // monitor test --------------------------------------
    auto res2 = monitor.Wait();
    EXPECT_EQ(res2.size(),                1);
    EXPECT_EQ(res2.front().get().Clear(), 1);
}
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */