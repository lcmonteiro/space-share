#include <gtest/gtest.h>
#include <SCommand.h>
#include <sstream>
#include <string>

using namespace std;
TEST(SCommand, Create)
{
    COMMAND(c, "I", "O", "X") {
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
    EXPECT_EQ(c["I"].front().at("A"), "a");
    EXPECT_EQ(c["O"].front().at("B"), "b");
    EXPECT_EQ(c["X"].front().at("C"), "c");
    // use case 2 -> negative
    EXPECT_THROW(c["D"], out_of_range);
}