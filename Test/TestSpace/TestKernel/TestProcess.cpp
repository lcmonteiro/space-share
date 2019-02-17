/**
 * ------------------------------------------------------------------------------------------------
 * File:   TestProcess.cpp
 * Author: Luis Monteiro
 *
 * Created on January  2, 2019, 10:21 AM
 * ------------------------------------------------------------------------------------------------
 */
#include <gtest/gtest.h>
/**
 * space
 */
#include "SProcess.h"
#include "SCommand.h"
#include "SVariable.h"
/**
 * ------------------------------------------------------------------------------------------------
 * testes
 * ------------------------------------------------------------------------------------------------
 */
using namespace std;
TEST(SProcess, Create)
{
    class SProcess1 : public SProcess<SCommand<string, string>, SVariable<string>> {
    public:
        using SProcess<SCommand<string, string>, SVariable<string>>::SProcess;
    protected:
        int Execute() override {
            for(auto& cmd : __Commands()) {
                return stoi(cmd["I"][0]["A"]);
            }
            return 0;
        }
    };
    SProcess1 p({
        {"I", {{
            {"A", "3"}
        }}}
    });
    // use case 1
    EXPECT_EQ(p.Run(), 3);
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */