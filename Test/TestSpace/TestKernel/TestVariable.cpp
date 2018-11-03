#include <gtest/gtest.h>
#include <SVariable.h>
#include <sstream>
#include <string>

using namespace std;
TEST(SVariable, Create)
{
    using Var = SVariable<string>; 
    Var a {
        {"1", {
            {"2", "2"}, {"3", "4"}
        }}
    };
    //use case 1
    EXPECT_EQ(Var::Type(a["1"]), Var::Type("23"));
    // use case 2
    EXPECT_EQ(a["1"]["2"], Var("2"));
    // use case 3
    stringstream ss;
    ss << a;
    EXPECT_EQ(ss.str(), "[1[2[2]3[4]]]");
    // use case 4
    Var b;
    ss >> b;
    EXPECT_EQ(a, b);
}