#include <gtest/gtest.h>
#include <SProcess.h>

using namespace std;
TEST(SProcess, Create)
{
    class SProcess1 : public SProcess<string, string> {
    public:
        using SProcess<string, string>::SProcess;
    protected:
        int Execute(const Command & c) override {
            return stoi(c.at("I").at(0).at("A"));
        }
    };
    SProcess1 p("uri", 0, {
        {"I", {{
            {"A", "3"}
        }}}
    });
    // use case 1
    EXPECT_EQ(p.Run(), 3);
}