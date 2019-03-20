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
 */
TEST(DecodedMessageFile, Link)
{
    // STask::Enable();
    // // settings -----------------------
    // auto size = size_t(100);

    // // create connectors --------------
    // auto ic = Decoded::Message::IUdpConnector::Make(
    //     "127.0.0.1:9999", size_t(20), size
    // );
    // auto oc = Decoded::Message::OUdpConnector::Make(
    //     "127.0.0.1:9999"
    // );

    // // connect ------------------------
    // ic->Repair();
    // oc->Repair();
    
    // // sleep --------------------------
    // STask::Sleep(chrono::milliseconds(10));

    // // create data --------------------
    // Container idata {
    //     SRandom::Frame(size), SFrame().Number(size)
    // }; 
    
    // // test oconnection ---------------
    // EXPECT_EQ(oc->Wait(chrono::milliseconds(100)).Good(), true);
    
    // // send ---------------------------
    // oc->Write(idata);
    
    // // test iconnection ---------------
    // EXPECT_EQ(ic->Wait(chrono::milliseconds(100)).Good(), true);
    
    // // receive ------------------------
    // auto odata = ic->Read();

    // // test data ----------------------
    // EXPECT_EQ(
    //     SBuffer().Write(idata).Read(size), 
    //     SBuffer().Write(odata).Read(size)
    // );
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */