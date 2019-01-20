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
/**
 * share
 */
#include <MSpliter.h>
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
    auto port   = 9999;

    // build a spliter -------------------------------------------------------- 
    Spliter s ({
        {SModuleCommand::MODULE,   {{
        }}},
        {SModuleCommand::FUNCTION, {{
            {Module::Properties::TYPE, "message"}
        }}},
        {SModuleCommand::INOUT,    {{
            {Module::Properties::URI, "127.0.0.1:9999"}
        }}},
        {SModuleCommand::INPUT,    {{
            {Module::Properties::URI, "127.0.0.1:8888"}
        }}},
        {SModuleCommand::OUTPUT,   {{
            {Module::Properties::URI, "127.0.0.1:8888"}
        }}}
    });
    s.Detach();
    // build a test frames ---------------------------------------------------- 
    auto in  = SRandom::Frame(size);
    auto out = Frame(size);
    // interface resource -----------------------------------------------------
    Message::SRemoteResource interface;
    interface.Link("127.0.0.1", 8888);

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
