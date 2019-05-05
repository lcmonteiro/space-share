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
#include "SDecoded/SMessage/SFileConnector.h"
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
 * ----------------------------------------------------------------------------
 * File - Base
 * ----------------------------------------------------------------------------
 */
TEST(DecodedMessageFile, Base)
{
    STask::Enable();
    // settings ----------------------- 
    auto size = size_t(100);
    auto path = SRandom::FileName();

    // OUT --------------------------------------------------------------------
    
    // create connector ---------------
    auto oc = Decoded::Message::OFileConnector::Make(
        path
    );

    // connect ------------------------
    oc->build();
    
    // sleep --------------------------
    STask::Sleep(milliseconds(10));

    // create data --------------------
    Container idata {
        SRandom::Frame(size), SFrame().number(size)
    }; 
    
    // test connection ---------------
    EXPECT_EQ(oc->wait(milliseconds(100)).good(), true);
    
    // send ---------------------------
    oc->write(idata);

    // IN ---------------------------------------------------------------------
    
    // create connector ----------------
    auto ic = Decoded::Message::IFileConnector::Make(
        path, size_t(20)
    );

    // connect ------------------------
    ic->build();
    
    // sleep --------------------------
    STask::Sleep(milliseconds(10));

    // test connection ----------------
    EXPECT_EQ(ic->wait(milliseconds(100)).good(), true);
    
    // receive ------------------------
    auto odata = ic->read();

    // COMPARE data -----------------------------------------------------------
    EXPECT_EQ(
        SBuffer().drain(idata).drain(size), 
        SBuffer().drain(odata).drain(size));
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */