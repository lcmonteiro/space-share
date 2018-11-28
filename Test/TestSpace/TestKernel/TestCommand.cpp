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
    EXPECT_EQ(c["I"][0]["A"], "a");
    EXPECT_EQ(c["O"][0]["B"], "b");
    EXPECT_EQ(c["X"][0]["C"], "c");
    // use case 2 -> negative
    EXPECT_THROW(c["D"], out_of_range);
}

TEST(SCommand, Constant)
{
    const SCommand<string, string> c {
        {"I", {{
            {"A", "a"}
        }}}
    };
    //use case 1 -> positive
    EXPECT_EQ(c["I"][0]["A"], "a");
}

TEST(SCommand, Group)
{
    const SCommand<string, string> c {
        {"I", {{
            {"A", "1"}
        }}}
    };
    //use case 1 -> positive
    EXPECT_EQ(c["I"][0].get("A", 1), 1);
}

TEST(SCommand, String)
{
    SCommand<string, string> c ("-I --a 1");
    //use case 1 -> positive
    EXPECT_EQ(c["I"][0].get("a", 1), 1);
}