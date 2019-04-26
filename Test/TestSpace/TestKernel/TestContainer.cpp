/**
 * ------------------------------------------------------------------------------------------------
 * File:   TestAdress.cpp
 * Author: Luis Monteiro
 *
 * Created on December  31, 2018, 10:21 AM
 * ------------------------------------------------------------------------------------------------
 */
#include <gtest/gtest.h>
/**
 * space
 */
#include "SContainer.h"
#include "SItertool.h"
#include "SRandom.h"
/**
 * ------------------------------------------------------------------------------------------------
 * frame Convertion
 * ------------------------------------------------------------------------------------------------
 */
TEST(SContainer, Serialize)
{
    // setings --------------------------------------------
    auto size   = 10;
    auto length = 1;

    // create container -----------------------------------
    auto c = SContainer(size);

    // fill container -------------------------------------
    while(!c.full()) {
        c.emplace_back(SFrame(
            length, length, SRandom::Number<int>()));
    }
    // serialize container --------------------------------
    auto s = Itertool::BuildStretch(c);

    // create frame ---------------------------------------
    auto f = SFrame(s.size());

    // copy container to frame ----------------------------
    std::copy(s.begin(), s.end(), std::back_inserter(f));

    // test size ------------------------------------------
    EXPECT_EQ(s.size(),size * length);

    // test forward ---------------------------------------
    EXPECT_EQ(
        SFrame(s.begin(), s.end()), 
        SFrame(s.begin(), s.end()));
    // test backward ---------------------------------------
    EXPECT_EQ(
        SFrame(s.rbegin(), s.rend()), 
        SFrame(s.rbegin(), s.rend()));
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * -----------------------------------------------------------------------------------------------
 */
