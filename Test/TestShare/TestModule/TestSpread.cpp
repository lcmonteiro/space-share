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
#include "SSpreadModule.h"
/**
 * -------------------------------------------------------------------------------------------------
 * Spread Data
 * -------------------------------------------------------------------------------------------------
 */
TEST(Spread, Data)
{
    STask::Enable();
    // define types -----------------------------------------------------------
    using Emitter  = Module::SSpreadModule<
        Decoded::IConnector, Decoded::Document, Decoded::OConnector
    >;
    using Receptor = Module::SSpreadModule<
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

    // build a emitter -------------------------------------------------------- 
    Emitter em ({
        {Emitter::Command::MODULE,   {{
            {Module::IO::URI, "Emitter"},
            {Module::TIMEOUT, "1000"},
            {Module::IO::VERBOSE, "0"}
        }}},
        {Emitter::Command::FUNCTION, {{
            {Module::Function::TYPE, Module::Function::Type::MESSAGE},
            {Module::IO::VERBOSE, "4"}
        }}},
        {Emitter::Command::INPUT,   {{
            {Module::IO::TYPE, Module::IO::Type::MESSAGE_LOCAL},
            {Module::IO::URI, addr_i},
            {Module::IO::VERBOSE, "0"}
        }}},
        {Emitter::Command::OUTPUT,    {{
            {Module::IO::MINIMUM, "3"},
            {Module::IO::NOMINAL, "3"}
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

    // build a recptor -------------------------------------------------------- 
    Receptor re ({
        {Receptor::Command::MODULE,   {{
            {Module::IO::URI, "Receptor"},
            {Module::TIMEOUT, "1000"},
            {Module::IO::VERBOSE, "0"}
        }}},
        {Receptor::Command::FUNCTION, {{
            {Module::Function::TYPE, Module::Function::Type::MESSAGE},
            {Module::IO::VERBOSE, "0"}
        }}},
        {Receptor::Command::INPUT,    {{
            {Module::IO::MINIMUM, "3"},
            {Module::IO::NOMINAL, "3"}
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
        {Receptor::Command::OUTPUT,   {{
            {Module::IO::TYPE, Module::IO::Type::MESSAGE_LOCAL},
            {Module::IO::URI, addr_o},
            {Module::IO::VERBOSE, "0"}
        }}},
    });

    // build a test frame ----------------------------------------------------- 
    auto const frame_i = SRandom::Frame(size);
    auto       frame_1 = IOFrame(size);
    auto       frame_2 = IOFrame(size);
    auto       frame_3 = IOFrame(size);

    // out interface resource --------------------------------------------------
    auto interface_o = Message::SLocalResource()
        .bind(addr_o)
    .detach();
    // decode start ------------------------------------------------------------
    re.start();

    // decode wait -------------------------------------------------------------
    EXPECT_EQ(re.state_wait(Receptor::Time(30000), Receptor::PLAY), true);
    
    // encode start ------------------------------------------------------------
    em.start();
    
    // encode wait -------------------------------------------------------------
    EXPECT_EQ(em.state_wait(Emitter::Time(30000), Emitter::PLAY), true);
    
    // in interface resource ---------------------------------------------------
    auto interface_i = Message::SLocalResource()
        .link(addr_i)
    .detach();

    // send ------------------------------------------------------------------- 
    EXPECT_EQ(interface_i.write(frame_i).good(), true);

    // wait ------------------------------------------------------------------- 
    Monitor(Monitor::Time(3000), &interface_o).wait();

    // receive ----------------------------------------------------------------
    EXPECT_EQ(interface_o.read(frame_1).good(), true);
    EXPECT_EQ(interface_o.read(frame_2).good(), true);
    EXPECT_EQ(interface_o.read(frame_3).good(), true);

    // test data --------------------------------------------------------------
    EXPECT_EQ(frame_i, frame_1);
    EXPECT_EQ(frame_i, frame_2);
    EXPECT_EQ(frame_i, frame_3);
}
/**
 * -------------------------------------------------------------------------------------------------
 *  function
 * -------------------------------------------------------------------------------------------------
 */
TEST(Spread, Code)
{
    STask::Enable();
    // define types -----------------------------------------------------------
    using Encode  = Module::SSpreadModule<
        Decoded::IConnector, Decoded::Document, Encoded::OConnector
    >;
    using Decode  = Module::SSpreadModule<
        Encoded::IConnector, Encoded::Document, Decoded::OConnector
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

    // build a encode -------------------------------------------------------- 
    Encode en ({
        {Encode::Command::MODULE,   {{
            {Module::IO::URI, "Encode"},
            {Module::TIMEOUT, "1000"},
            {Module::IO::VERBOSE, "4"}
        }}},
        {Encode::Command::FUNCTION, {{
            {Module::Function::TYPE, Module::Function::Type::MESSAGE},
            {Module::IO::VERBOSE, "4"}
        }}},
        {Encode::Command::INPUT,   {{
            {Module::IO::TYPE, Module::IO::Type::MESSAGE_LOCAL},
            {Module::IO::URI, addr_i},
            {Module::IO::VERBOSE, "4"}
        }}},
        {Encode::Command::OUTPUT,    {{
            {Module::IO::MINIMUM, "3"},
            {Module::IO::NOMINAL, "3"}
        }, {
            {Module::IO::TYPE, Module::IO::Type::MESSAGE_LOCAL},
            {Module::IO::URI, addr_1},
            {Module::IO::VERBOSE, "4"}
        }, {
            {Module::IO::TYPE, Module::IO::Type::MESSAGE_LOCAL},
            {Module::IO::URI, addr_2},
            {Module::IO::VERBOSE, "4"} 
        }, {
            {Module::IO::TYPE, Module::IO::Type::MESSAGE_LOCAL},
            {Module::IO::URI, addr_3},
            {Module::IO::VERBOSE, "4"}
        }}}
    });

    // build a decode --------------------------------------------------------- 
    Decode de ({
        {Decode::Command::MODULE,   {{
            {Module::IO::URI, "Decode"},
            {Module::TIMEOUT, "1000"},
            {Module::IO::VERBOSE, "4"}
        }}},
        {Decode::Command::FUNCTION, {{
            {Module::Function::TYPE, Module::Function::Type::MESSAGE},
            {Module::IO::VERBOSE, "4"}
        }}},
        {Decode::Command::INPUT,    {{
            {Module::IO::MINIMUM, "3"},
            {Module::IO::NOMINAL, "3"}
        }, {
            {Module::IO::TYPE, Module::IO::Type::MESSAGE_LOCAL},
            {Module::IO::URI, addr_1},
            {Module::IO::VERBOSE, "4"}
        }, {
            {Module::IO::TYPE, Module::IO::Type::MESSAGE_LOCAL},
            {Module::IO::URI, addr_2},
            {Module::IO::VERBOSE, "4"} 
        }, {
            {Module::IO::TYPE, Module::IO::Type::MESSAGE_LOCAL},
            {Module::IO::URI, addr_3},
            {Module::IO::VERBOSE, "4"}
        }}},
        {Decode::Command::OUTPUT,   {{
            {Module::IO::TYPE, Module::IO::Type::MESSAGE_LOCAL},
            {Module::IO::URI, addr_o},
            {Module::IO::VERBOSE, "4"}
        }}},
    });

    // build a test frame ----------------------------------------------------- 
    auto const  frame_i = SRandom::Frame(size);
    auto        frame_o = IOFrame(size);

    // out interface resource --------------------------------------------------
    auto interface_o = Message::SLocalResource()
        .bind(addr_o)
    .detach();
    
    // decode start ------------------------------------------------------------
    de.start();

    // decode wait -------------------------------------------------------------
    EXPECT_EQ(de.state_wait(Decode::Time(3000), Decode::PLAY), true);
    
    // encode start ------------------------------------------------------------
    en.start();
    
    // encode wait -------------------------------------------------------------
    EXPECT_EQ(en.state_wait(Encode::Time(3000), Encode::PLAY), true);
    
    // in interface resource ---------------------------------------------------
    auto interface_i = Message::SLocalResource()
        .link(addr_i)
    .detach();

    // send ------------------------------------------------------------------- 
    EXPECT_EQ(interface_i.drain(frame_i).good(), true);

        // wait ------------------------------------------------------------------- 
    Monitor(Monitor::Time(3000), &interface_o).wait();

    // receive ----------------------------------------------------------------
    EXPECT_EQ(interface_o.read(frame_o).good(), true);

    // test data --------------------------------------------------------------
    EXPECT_EQ(frame_i, frame_o);
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
