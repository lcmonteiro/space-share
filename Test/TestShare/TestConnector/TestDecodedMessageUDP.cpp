/**
 * ------------------------------------------------------------------------------------------------
 * File:   TestMachine.cpp
 * Author: Luis Monteiro
 *
 * Created on February  2, 2019, 10:21 AM
 * ------------------------------------------------------------------------------------------------
 */
#include <gtest/gtest.h>
/**
 * share
 */
#include "SDecoded/SMessage/SUdpConnector.h"
/**
 * space
 */
#include "SCompare.h"
#include "SRandom.h"
#include "SBuffer.h"
/**
 * namespace
 */
using namespace std::chrono;
/**
 * ------------------------------------------------------------------------------------------------
 * UDP - link
 * ------------------------------------------------------------------------------------------------
 */
TEST(DecodedMessageUDP, Link)
{
    
    STask::Enable();
    // settings -----------------------
    auto size = size_t(100);

    // create connectors --------------
    auto ic = Decoded::Message::IUdpConnector::Make(
        "127.0.0.1:9999", size_t(20), size
    );
    auto oc = Decoded::Message::OUdpConnector::Make(
        "127.0.0.1:9999"
    );

    // connect ------------------------
    ic->build();
    oc->build();
    
    // sleep --------------------------
    STask::Sleep(milliseconds(10));

    // create data --------------------
    Container idata {
        SRandom::Frame(size), SFrame().number(size)
    }; 
    
    // test oconnection ---------------
    EXPECT_EQ(oc->wait(milliseconds(100)).good(), true);
    
    // send ---------------------------
    oc->write(idata);
    
    // test iconnection ---------------
    EXPECT_EQ(ic->wait(milliseconds(100)).good(), true);
    
    // receive ------------------------
    auto odata = ic->read();

    // test data ----------------------
    EXPECT_EQ(
        SBuffer().drain(idata).drain(size), 
        SBuffer().drain(odata).drain(size));
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */