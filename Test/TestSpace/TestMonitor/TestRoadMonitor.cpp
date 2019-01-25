#include <gtest/gtest.h>
/**
 * std
 */
#include <memory>
/**
 * space
 */
#include "SRoadMonitor.h"
#include "SEventResource.h"
#include "SRandom.h"
#include "SText.h"
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
    bool Good() {
        return true;
    }
    bool Inactive() {
        return false;
    }
};
TEST(SRoadMonitor, Create)
{
    // create monitor type --------------------------------
    typedef SRoadMonitor<
        SText, 
        SEventConnector::Connector,
        Monitor::Resource::SDirect
    > RoadMonitor;

    // create monitor ------------------------------------- 
    auto monitor = RoadMonitor(
        RoadMonitor::Time(10), 
        RoadMonitor::Road(2)
            .Insert("1", SEventConnector::Make(0))
            .Insert("2", SEventConnector::Make(0))
        .Build()
    );

    // set event 1 ---------------------------------------
    monitor.Update().Find("1")->Send();

    // monitor test --------------------------------------
    auto res1 = monitor.Wait();
    EXPECT_EQ(res1.size(),           1);
    EXPECT_EQ(res1.front()->second->Clear(), 1);

    // set event 1 ---------------------------------------
    monitor.Update().Find("2")->Send();

    // monitor test --------------------------------------
    auto res2 = monitor.Wait();
    EXPECT_EQ(res2.size(),           1);
    EXPECT_EQ(res2.front()->second->Clear(), 1);
}
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */