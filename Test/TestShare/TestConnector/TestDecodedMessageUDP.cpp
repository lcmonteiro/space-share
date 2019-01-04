#include <gtest/gtest.h>
/**
 * space
 */
#include "SDecoded/SMessage/SUdpConnector.h"
#include "SResourceMonitor.h"
#include "SCompare.h"
#include "SRandom.h"
/**
 */
TEST(DecodedMessageUDP, FILE)
{
    STask::Enable();
    // create iconnector
    auto ic = Decoded::Message::IUdpConnector::Make(
        "127.0.0.1:9999", 20, 1024
    );
    // create oconnector
    auto oc = Decoded::Message::OUdpConnector::Make(
        "127.0.0.1:9999"
    );
    // connect
    ic->Repair();
    oc->Repair();
    // sleep
    STask::Sleep(chrono::milliseconds(10));
    // test
    EXPECT_EQ(ic->Good(), true);
    EXPECT_EQ(oc->Good(), true);
    
    // create data
    Container idata {
        SRandom::Frame(10), SFrame(4).Number(10)
    }; 
    // write 
    oc->Write(idata);
    // wait
    //SResourceMonitor(chrono::milliseconds(100), ic).Wait();
    // receive
    auto odata = ic->Read();
    // test
    EXPECT_EQ(idata, odata);
}
