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
    oc->Repair();
    
    // sleep --------------------------
    STask::Sleep(milliseconds(10));

    // create data --------------------
    Container idata {
        SRandom::Frame(size), SFrame().Number(size)
    }; 
    
    // test connection ---------------
    EXPECT_EQ(oc->Wait(milliseconds(100)).Good(), true);
    
    // send ---------------------------
    oc->Write(idata);

    // IN ---------------------------------------------------------------------
    
    // create connector ----------------
    auto ic = Decoded::Message::IFileConnector::Make(
        path, size_t(20)
    );

    // connect ------------------------
    ic->Repair();
    
    // sleep --------------------------
    STask::Sleep(milliseconds(10));

    // test connection ----------------
    EXPECT_EQ(ic->Wait(milliseconds(100)).Good(), true);
    
    // receive ------------------------
    auto odata = ic->Read();

    // COMPARE data -----------------------------------------------------------
    EXPECT_EQ(
        SBuffer().Write(idata).Read(size), 
        SBuffer().Write(odata).Read(size));
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */