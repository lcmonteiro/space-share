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
#include "MSpliter.h"
//#include <MSpread.h>
/**
 * -------------------------------------------------------------------------------------------------
 * echo Spliter
 * -------------------------------------------------------------------------------------------------
 */
TEST(SModule, EchoSpliter)
{
    typedef Module::MSpliter<Decoded::IOConnector, Decoded::IConnector, Decoded::OConnector> Spliter;
    // settings ---------------------------------------------------------------
    auto size   = 100;
    auto addr   = "localhost";
    auto port1  = 9999;
    auto port2  = 8888;

    // build a spliter -------------------------------------------------------- 
    Spliter s ({
        {Spliter::Command::MODULE,   {{
        }}},
        {Spliter::Command::FUNCTION, {{
            {Module::Function::TYPE, Module::Function::Type::MESSAGE}
        }}},
        {Spliter::Command::INOUT,    {{
            {Module::IO::TYPE, Module::IO::Type::MESSAGE_REMOTE},
            {Module::IO::URI, SText(addr, ":", port1)}
        }}},
        {Spliter::Command::INPUT,    {{
            {Module::IO::TYPE, Module::IO::Type::MESSAGE_REMOTE},
            {Module::IO::URI, SText(addr, ":", port2)}
        }}},
        {Spliter::Command::OUTPUT,   {{
            {Module::IO::TYPE, Module::IO::Type::MESSAGE_REMOTE},
            {Module::IO::URI, SText(addr, ":", port2)}
        }}}
    });
    s.Detach();
    // build a test frames ---------------------------------------------------- 
    auto in  = SRandom::Frame(size);
    auto out = Frame(size);
    // interface resource -----------------------------------------------------
    Message::SRemoteResource interface;
    interface.Link(addr, port1);

    // send ------------------------------------------------------------------- 
    EXPECT_EQ(interface.Drain(in).Good(), true);

    // receive ----------------------------------------------------------------
    EXPECT_EQ(interface.Fill(out).Good(), true);

    // test data --------------------------------------------------------------
    EXPECT_EQ(in, out);
}

// TEST(SModule, CreateSpread)
// {
//     typedef Module::MSpread<Decoded::IConnector, Container, Encoded::OConnector> Spread;
//     // build 
//     Spread s ({
//         {"", {{
//             {"uri", "test"}
//         }}},
//         {"F", {{
//             {"uri", "test"}
//         }}},
//         {"I", {{
//             {"uri", "test"}
//         }}},
//         {"O", {{
//             {"uri", "test"}
//         }}}
//     });
//     //use case 1 -> positive
//     //EXPECT_EQ(s.Run(), 0);
//     //EXPECT_EQ(c.at("I").at(0).at("A"), "a");
// }
