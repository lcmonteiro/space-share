#include <gtest/gtest.h>
#include <MSpliter.h>
#include <sstream>
#include <string>

using namespace std;
TEST(SModule, Create)
{
    typedef Module::MSpliter<Decoded::IOConnector, Decoded::IConnector, Decoded::OConnector> Module;
    //use case 1 -> positive
    EXPECT_EQ("a", "a");
    //EXPECT_EQ(c.at("I").at(0).at("A"), "a");
}
