#include <gtest/gtest.h>
/**
 * space
 */
#include <SContainer.h>
#include <SRandom.h>
/**
 */
using namespace std;
TEST(SFrame, Number)
{
    auto sample = SRandom::Number<int>();

    // test case 1 --------------------
    SFrame frm1 (10);
    // set sample on a frame
    frm1.Number(sample);
    // test case 1 
    EXPECT_EQ(frm1.Number<int>(), sample);
    
    // test case 2 --------------------
    SFrame frm2 (4);
    // set sample on a frame
    frm2.Number(sample);
    // test case 1 
    EXPECT_EQ(frm2.Number<int>(), sample);
}
