/**
 * ------------------------------------------------------------------------------------------------
 * File:   TestSpread.cpp
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
#include "MSpread.h"
/**
 * -------------------------------------------------------------------------------------------------
 * Create
 * -------------------------------------------------------------------------------------------------
 */
TEST(Spread, Create)
{
    STask::Enable();
    // define types -----------------------------------------------------------
    using Encode  = Module::MSpread<
        Decoded::IConnector, Decoded::Document, Decoded::OConnector
    >;
    using Decode  = Module::MSpread<
        Decoded::IConnector, Decoded::Document, Decoded::OConnector
    >;
    using Monitor = SResourceMonitor<
    >;

    
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
