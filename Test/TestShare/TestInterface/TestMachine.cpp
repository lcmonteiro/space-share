#include <gtest/gtest.h>
/**
 * space
 */
#include <SMachine.h>
#include <SRandom.h>
#include <SCompare.h>
/**
 */
using namespace std;
TEST(SMachine, FILE)
{
    STask::Enable();
    /**
     * create file
     */
    auto data = SRandom::File("/tmp/data", 1000);
    /**
     * configure machine
     */
    auto conf = SMachine::Config{{
        {"M", {{
            {"uri",  "encoder"}, {"type", "encode"}, {"verbose", "4"}
        }}},
        {"F", {{
            {"type", "message"}, { "verbose", "4"}
        }}},
        {"I", {{
            { "uri", "/tmp/data"}, { "type", "message.file"}, { "verbose", "4"}
        }}},
        {"O",{
            {
                { "uri",  "/tmp/out.1"}, { "type", "message.file"}
            },
            {
                { "uri",  "/tmp/out.2"}, { "type", "message.file"}
            },
            {
                { "uri",  "/tmp/out.3"}, { "type", "message.file"}
            }
        }}
    }};
    /***
     * encoder machine
     */
    SMachine encoder("system.share", conf);
    encoder.Process(chrono::seconds(1));
    /**
     * decoder machine
     */
    SMachine decoder("system.share", conf);
    decoder.Process(chrono::seconds(1));
    /**
     * check
     */
    EXPECT_TRUE(SCompare::Files(data,data));
}
