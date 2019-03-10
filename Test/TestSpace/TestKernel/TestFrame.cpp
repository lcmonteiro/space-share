/**
 * ------------------------------------------------------------------------------------------------
 * File:   TestFrame.cpp
 * Author: Luis Monteiro
 *
 * Created on February  2, 2019, 10:21 AM
 * ------------------------------------------------------------------------------------------------
 */
#include <gtest/gtest.h>
/**
 * space
 */
#include "SFrame.h"
#include "SRandom.h"
/**
 * ------------------------------------------------------------------------------------------------
 * frame Convertion
 * ------------------------------------------------------------------------------------------------
 */
TEST(SFrame, Conversion)
{
    // use case 1 --------------------
    IFrame in = SFrame(10, 1).Detach();

    // write --------------------------
    in.Expand().Write({1, 2, 3}).Write({9, 8, 7});

    //test case 
    EXPECT_EQ(OFrame(in).Read(5), Frame({0, 1, 2, 3, 9}));
}
/**
 * ------------------------------------------------------------------------------------------------
 * frame to number
 * ------------------------------------------------------------------------------------------------
 */
TEST(SFrame, Number)
{
    auto sample = SRandom::Number<int>();

    // test case 1 --------------------
    Frame frm1 (10, 10);
    // set sample on a frame
    frm1.Number(sample);
    // test case 1 
    EXPECT_EQ(frm1.Number<int>(), sample);
    
    // test case 2 --------------------
    Frame frm2 (4, 4);
    // set sample on a frame
    frm2.Number(sample);
    // test case 1 
    EXPECT_EQ(frm2.Number<int>(), sample);
}
/**
 * ------------------------------------------------------------------------------------------------
 * frame down convertions
 * ------------------------------------------------------------------------------------------------
 */
TEST(SFrame, DownConversion)
{
    // use case 1 --------------------
    IOFrame f = SFrame(10, 1).Detach();

    // write --------------------------
    f.Expand().Write({1, 2, 3}).Write({9, 8, 7});

    //test 1 --------------------------
    EXPECT_EQ(f.Read(5), SFrame({0, 1, 2, 3, 9}));

    //test 2 --------------------------
    EXPECT_EQ(f.Frame(), SFrame({0, 1, 2, 3, 9, 8, 7}));
}
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */