#include <gtest/gtest.h>
#include <SCommand.h>
#include <sstream>
#include <string>

using namespace std;
TEST(SCommand, Create)
{
    SCommand<string, string> c {
        {"I", {{
            {"A", "a"}
        }}},
        {"O", {{
            {"B", "b"}
        }}},
        {"X", {{
            {"C", "c"}
        }}},
    };
    //use case 1 -> positive
    EXPECT_EQ(c.at("I").at(0).at("A"), "a");
    EXPECT_EQ(c.at("O").at(0).at("B"), "b");
    EXPECT_EQ(c.at("X").at(0).at("C"), "c");
    // use case 2 -> negative
    EXPECT_THROW(c.at("D"), out_of_range);
}

TEST(SCommand, Constant)
{
    const SCommand<string, string> c {
        {"I", {{
            {"A", "a"}
        }}}
    };
    //use case 1 -> positive
    EXPECT_EQ(c.at("I").at(0).at("A"), "a");
}

TEST(SCommand, Group)
{
    const SCommand<string, string> c {
        {"I", {{
            {"A", "1"}
        }}}
    };
    //use case 1 -> positive
    EXPECT_EQ(c.at("I").at(0).AT("A", 1), 1);
}