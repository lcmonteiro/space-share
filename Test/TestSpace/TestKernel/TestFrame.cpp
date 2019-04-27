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
    IOFrame in = SFrame(10, 1).detach();

    // write --------------------------
    in.Expand().Write({1, 2, 3}).Write({9, 8, 7});

    //test case 
    EXPECT_EQ(IOFrame(in).Read(5), Frame({0, 1, 2, 3, 9}));
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
    IOFrame f = SFrame(10, 1).detach();

    // write --------------------------
    f.Expand().Write({1, 2, 3}).Write({9, 8, 7});

    //test 1 --------------------------
    EXPECT_EQ(f.Read(5), SFrame({0, 1, 2, 3, 9}));

    //test 2 --------------------------
    EXPECT_EQ(SFrame({8, 7}), f);
}
/**
 * ------------------------------------------------------------------------------------------------
 * frame sizes
 * ------------------------------------------------------------------------------------------------
 */
TEST(SFrame, Sizes)
{
    // settings ----------------------
    auto const SIZE = 100;

    // use case 1 --------------------
    auto f = SIOFrame(SIZE);

    // test 1
    EXPECT_EQ(f.size(), 0);
    EXPECT_EQ(f.size(), 0);
    EXPECT_EQ(f.osize(), 0);
    EXPECT_EQ(f.isize(), SIZE);

    // insert
    f.Write(SFrame(SIZE>>1, SIZE>>1));

    // test 2
    EXPECT_EQ(f.size(), SIZE>>1);
    EXPECT_EQ(f.size(), SIZE>>1);
    EXPECT_EQ(f.osize(), 0);
    EXPECT_EQ(f.isize(), SIZE>>1);
    
    // remove -------------------------
    f.Read(SIZE>>2);

    // test 3 -------------------------
    EXPECT_EQ(f.size(), SIZE>>2);
    EXPECT_EQ(f.size(), SIZE>>2);
    EXPECT_EQ(f.osize(), SIZE>>2);
    EXPECT_EQ(f.isize(), SIZE>>1);

    // const --------------------------
    auto const cf = f;
    // test 4 -------------------------
    EXPECT_EQ(cf.size(), SIZE>>2);
    EXPECT_EQ(cf.size(), SIZE>>2);
    EXPECT_EQ(cf.osize(), SIZE>>2);
    EXPECT_EQ(cf.isize(), SIZE>>1);

    // const --------------------------
    auto const cmf = move(f);
    // test 5 -------------------------
    EXPECT_EQ(cmf.size(), SIZE>>2);
    EXPECT_EQ(cmf.size(), SIZE>>2);
    EXPECT_EQ(cmf.osize(), SIZE>>2);
    EXPECT_EQ(cmf.isize(), SIZE>>1);

    // test 6 -------------------------
    EXPECT_EQ(f.size(), 0);
    EXPECT_EQ(f.size(), 0);
    EXPECT_EQ(f.osize(), 0);
    EXPECT_EQ(f.isize(), 0);

}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */