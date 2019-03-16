/**
 * ------------------------------------------------------------------------------------------------
 * File:   TestCodec.cpp
 * Author: Luis Monteiro
 *
 * Created on February  2, 2019, 10:21 AM
 * ------------------------------------------------------------------------------------------------
 */
#include <gtest/gtest.h>
/**
 * std
 */
#include <sstream>
#include <string>
/**
 * space
 */
#include "SRandom.h"
#include "SText.h"
/**
 * share
 */
#include "SBufferShare.h"
/**
 * -------------------------------------------------------------------------------------------------
 * Codec
 * -------------------------------------------------------------------------------------------------
 */
TEST(SBufferShare, Code)
{
    // settings -----------------------
    auto info = 200; // infromation size
    auto part = 10;  // messages    size
    auto plus = 1;   // redundacy   size 

    // create buffers -----------------
    OBufferShare enc;
    IBufferShare dec;
    
    // input --------------------------
    Frame in = SRandom::Frame(info);
    
    // encode and decode loop ---------
    for (
        // init loop ------------------ 
        int i = 0, n = enc.Set(in, part, plus); 
        
        // validation -----------------
        (i < n) && (dec.Set(enc.Get()) == false);

        // next ----------------------- 
        ++i
    );
    // test ---------------------------
    EXPECT_EQ(in, dec.Get());
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */