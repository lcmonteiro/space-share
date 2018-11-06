#include <gtest/gtest.h>
#include <SCommand.1.h>
#include <sstream>
#include <string>

using namespace std;
TEST(SCommand, Create)
{
    struct F1 {
        static bool Find(string k) {
            static set<string> __filter{"I", "O", "X"};
            return __filter.count(k) > 0;
        }
    };
    SCommand1<F1> c {
        {"1", {}}
    };
    //use case 1
    EXPECT_EQ("1", "23");
    
}