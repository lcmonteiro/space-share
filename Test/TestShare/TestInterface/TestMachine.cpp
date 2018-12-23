#include <gtest/gtest.h>
/**
 * space
 */
#include <SMachine.h>
#include <SRandom.h>
#include <SCompare.h>
/**
 */
TEST(SMachine, FILE)
{
    STask::Enable();
    /**
     * create test data
     */
    auto data = SRandom::File("/tmp/data", 1000);
    /**
     * configure machine
     */

    auto conf = SMachine::Config().Add(
        SModuleCommand().AddModule({
            {"uri",  "encoder"}, {"type", "encode"}, {"verbose", "4"}
        }).AddFunction({
            {"type", "message"}, { "verbose", "4"}
        }).AddInput({
            { "uri", "/tmp/data"}, { "type", "message.file"}, { "verbose", "4"}
        }).AddOutput({
            { "uri",  "/tmp/out.1"}, { "type", "message.file"}
        }).AddOutput({
            { "uri",  "/tmp/out.2"}, { "type", "message.file"}
        }).AddOutput({
            { "uri",  "/tmp/out.3"}, { "type", "message.file"}
        })
    );
    /***
     * encoder machine
     */
    SMachine("system.share", conf).Join();
    /**
     * decoder machine
     */
    SMachine("system.share", conf.Swap("I", "O")).Join();
    /**
     * check data
     */
    EXPECT_TRUE(SCompare::Files(data, data));
}
