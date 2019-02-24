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
#include "SLocalResource.h"
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

    // settings ---------------------------------------------------------------
    auto size   = 100;
    auto addr_i = SRandom::String(8);
    auto addr_o = SRandom::String(8);
    auto addr_1 = SRandom::String(8);
    auto addr_2 = SRandom::String(8);
    auto addr_3 = SRandom::String(8);
    auto addr   = SRandom::String(8);
    auto port1  = 9999;
    auto port2  = 8888;

    // build a encode -------------------------------------------------------- 
    Encode en ({
        {Encode::Command::MODULE,   {{
            {Module::TIMEOUT, "200"},
            {Module::IO::VERBOSE, "0"}
        }}},
        {Encode::Command::FUNCTION, {{
            {Module::Function::TYPE, Module::Function::Type::MESSAGE},
            {Module::IO::VERBOSE, "0"}
        }}},
        {Encode::Command::INPUT,   {{
            {Module::IO::TYPE, Module::IO::Type::MESSAGE_LOCAL},
            {Module::IO::URI, addr_i},
            {Module::IO::VERBOSE, "0"}
        }}},
        {Encode::Command::OUTPUT,    {{
            {Module::IO::MINIMUM, "1"}
        }, {
            {Module::IO::TYPE, Module::IO::Type::MESSAGE_LOCAL},
            {Module::IO::URI, addr_1},
            {Module::IO::VERBOSE, "0"}
        }, {
            {Module::IO::TYPE, Module::IO::Type::MESSAGE_LOCAL},
            {Module::IO::URI, addr_2},
            {Module::IO::VERBOSE, "0"} 
        }, {
            {Module::IO::TYPE, Module::IO::Type::MESSAGE_LOCAL},
            {Module::IO::URI, addr_3},
            {Module::IO::VERBOSE, "0"}
        }}}
    });
    // build a decode --------------------------------------------------------- 
    Decode de ({
        {Encode::Command::MODULE,   {{
            {Module::TIMEOUT, "200"},
            {Module::IO::VERBOSE, "0"}
        }}},
        {Encode::Command::FUNCTION, {{
            {Module::Function::TYPE, Module::Function::Type::MESSAGE},
            {Module::IO::VERBOSE, "0"}
        }}},
        {Encode::Command::INPUT,    {{
            {Module::IO::MINIMUM, "1"}
        }, {
            {Module::IO::TYPE, Module::IO::Type::MESSAGE_LOCAL},
            {Module::IO::URI, addr_1},
            {Module::IO::VERBOSE, "0"}
        }, {
            {Module::IO::TYPE, Module::IO::Type::MESSAGE_LOCAL},
            {Module::IO::URI, addr_2},
            {Module::IO::VERBOSE, "0"} 
        }, {
            {Module::IO::TYPE, Module::IO::Type::MESSAGE_LOCAL},
            {Module::IO::URI, addr_3},
            {Module::IO::VERBOSE, "0"}
        }}},
        {Encode::Command::OUTPUT,   {{
            {Module::IO::TYPE, Module::IO::Type::MESSAGE_LOCAL},
            {Module::IO::URI, addr_o},
            {Module::IO::VERBOSE, "0"}
        }}},
    });
    // start ------------------------------------------------------------------
    en.Detach();
    de.Detach();
    
    // wait -------------------------------------------------------------------
    EXPECT_EQ(en.WaitState(Encode::Time(3000), Encode::PLAY), true);
    EXPECT_EQ(de.WaitState(Decode::Time(3000), Decode::PLAY), true);

    // build a test frame ----------------------------------------------------- 
    auto frame_i  = SRandom::Frame(size);

    // interface resource -----------------------------------------------------
    auto interface_i = Message::SLocalResource()
        .Link(addr_i)
    .Detach();
    
    // send ------------------------------------------------------------------- 
    EXPECT_EQ(interface_i.Drain(frame_i).Good(), true);


    
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
