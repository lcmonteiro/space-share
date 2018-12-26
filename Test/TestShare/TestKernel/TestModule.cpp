#include <gtest/gtest.h>
#include <MSpliter.h>
#include <MSpread.h>
#include <sstream>
#include <string>

TEST(SModule, CreateSpliter)
{
    typedef Module::MSpliter<Decoded::IOConnector, Decoded::IConnector, Decoded::OConnector> Spliter;
    // build 
    Spliter s ({
        {"", {{
            {"uri", "test"}
        }}},
        {"F", {{
            {"uri", "test"}
        }}},
        {"I", {{
            {"uri", "test"}
        }}},
        {"O", {{
            {"uri", "test"}
        }}},
        {"X", {{
            {"uri", "test"}
        }}}
    });
    //use case 1 -> positive
    //EXPECT_EQ(s.Run(), 0);
    //EXPECT_EQ(c.at("I").at(0).at("A"), "a");
}

TEST(SModule, CreateSpread)
{
    typedef Module::MSpread<Decoded::IConnector, Container, Encoded::OConnector> Spread;
    // build 
    Spread s ({
        {"", {{
            {"uri", "test"}
        }}},
        {"F", {{
            {"uri", "test"}
        }}},
        {"I", {{
            {"uri", "test"}
        }}},
        {"O", {{
            {"uri", "test"}
        }}}
    });
    //use case 1 -> positive
    //EXPECT_EQ(s.Run(), 0);
    //EXPECT_EQ(c.at("I").at(0).at("A"), "a");
}
