#include <gtest/gtest.h>
#include <MYpsilon.h>
#include <sstream>
#include <string>

using namespace std;
TEST(SModule, Create)
{
    typedef Module::MYpsilon<Decoded::IOConnector, Decoded::IConnector, Decoded::OConnector> Module;
    //use case 1 -> positive
    EXPECT_EQ("a", "a");
    //EXPECT_EQ(c.at("I").at(0).at("A"), "a");
}
