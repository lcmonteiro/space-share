/**
 * ------------------------------------------------------------------------------------------------
 * File:   TestRoadMonitor.cpp
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
#include "SEventResource.h"
#include "SRoadMonitor.h"
#include "SRandom.h"
#include "SText.h"
#include "STask.h"
/**
 * ------------------------------------------------------------------------------------------------
 * test - SRoadMonitor & Event resource
 * ------------------------------------------------------------------------------------------------
 */
class SEventConnector: public SEventResource {
public:
    // build
    using Connector = std::shared_ptr<SEventConnector>;
    static Connector Make(int n) {
        return std::make_shared<SEventConnector>(n);
    }
    // interfaces
    using SEventResource::SEventResource;
    bool good() {
        return true;
    }
    bool inactive() {
        return false;
    }
    void build() {
    }
};
TEST(SRoadMonitor, Create)
{
    STask::Enable();
    // create monitor type --------------------------------
    typedef SRoadMonitor<
        SText, 
        SEventConnector::Connector,
        Monitor::Resource::SDirect
    > RoadMonitor;

    // create monitor ------------------------------------- 
    auto monitor = RoadMonitor(
        RoadMonitor::Time(10), 
        RoadMonitor::Road(2, 0)
            .insert("1", SEventConnector::Make(0))
            .insert("2", SEventConnector::Make(0))
        .detach()
    );

    // set event 1 ---------------------------------------
    monitor.update().find("1")->send();

    // monitor test --------------------------------------
    auto res1 = monitor.update().wait();
    EXPECT_EQ(res1.size(),                   1);
    EXPECT_EQ(res1.front()->second->clear(), 1);

    // set event 1 ---------------------------------------
    monitor.update().find("2")->send();

    // monitor test --------------------------------------
    auto res2 = monitor.wait();
    EXPECT_EQ(res2.size(),           1);
    EXPECT_EQ(res2.front()->second->clear(), 1);
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */