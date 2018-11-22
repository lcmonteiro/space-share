#include <gtest/gtest.h>
#include <SProcess.h>

using namespace std;
TEST(SProcess, Create)
{
    class SProcess1 : public SProcess<string, string> {
    public:
        using SProcess<string, string>::SProcess;
    protected:
        int Execute() override {
            return stoi(__cmd["I"][0]["A"]);
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