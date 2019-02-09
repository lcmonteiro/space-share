#include <gtest/gtest.h>
/**
 * space
 */
#include "SFrame.h"
#include "SRandom.h"
/**
 * ------------------------------------------------------------------------------------------------
 * frame to number
 * ------------------------------------------------------------------------------------------------
 */
TEST(SFrame, Conversion)
{
    // use case 1 --------------------
    IFrame in = SFrame(10, 1).Detach();

    // write --------------------------
    in.Expand().Write({1, 2, 3}).Write({9, 8, 7});

    //test case 
    EXPECT_EQ(OFrame(Frame(in)).Read(5), Frame({0, 1, 2, 3, 9}));
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
 * end
 * ------------------------------------------------------------------------------------------------
 */