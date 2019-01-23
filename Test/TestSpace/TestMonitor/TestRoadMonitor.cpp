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
 * tests
 */
TEST(SRoadMonitor, Create)
{
    typedef SRoadMonitor<SText, Message::SRemoteResource> RoadMonitor;
    /**
     * create
     */
    // auto monitor = RoadMonitor()
    //     .Insert("1", move(Message::SRemoteResource()));

    
}
