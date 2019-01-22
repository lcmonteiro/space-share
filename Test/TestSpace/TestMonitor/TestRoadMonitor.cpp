#include <gtest/gtest.h>
/**
 * std
 */
#include <memory>
/**
 * space
 */
#include "SRemoteResource.h"
#include "SRoadMonitor.h"
#include "SRandom.h"
#include "SText.h"
/**
 * tests
 */
TEST(SRoadMonitor, Create)
{
    typedef SRoadMonitor<SText, std::shared_ptr<Message::SRemoteResource>> RoadMonitor;
    /**
     */
    RoadMonitor monitor;

    monitor.Insert("1", std::make_shared<Message::SRemoteResource>(
    ));

    
}
