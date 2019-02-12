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
    // STask::Enable();
    // /**
    //  * files
    //  */
    // auto input  = SRandom::FileName();
    // auto output = SRandom::FileName();
    // /**
    //  * create test data
    //  */
    // SRandom::File(input, 1000);
    // /**
    //  * configure machine
    //  */
    // auto conf = SMachine::Config().Add(
    //     SModuleCommand().AddModule({
    //         {"uri",  "encoder"}, {"type", "encode"}, {"verbose", "4"}
    //     }).AddFunction({
    //         {"type", "message"}, { "verbose", "4"}
    //     }).AddInput({
    //         { "uri", input}, { "type", "message.file"}, { "verbose", "4"}
    //     }).AddOutput({
    //         { "uri",  SRandom::FileName()}, { "type", "message.file"}
    //     }).AddOutput({
    //         { "uri",  SRandom::FileName()}, { "type", "message.file"}
    //     }).AddOutput({
    //         { "uri",  SRandom::FileName()}, { "type", "message.file"}
    //     })
    // );
    // /***
    //  * encoder machine
    //  */
    // SMachine("system.share", conf).Join();
    // /**
    //  * decoder machine
    //  */
    // SMachine("system.share", 
    //     conf.Swap(
    //         "I", "O"
    //     ).Update(
    //         "M", "type", "decoder"
    //     ).Update(
    //         "M", "uri", output
    //     )
    // ).Join();
    // /**
    //  * check data
    //  */
    // EXPECT_TRUE(SCompare::Files(SIFileResource(input), SIFileResource(output)));
}
