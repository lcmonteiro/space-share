/**
 * ------------------------------------------------------------------------------------------------
 * File:   TestMachine.cpp
 * Author: Luis Monteiro
 *
 * Created on February  2, 2019, 10:21 AM
 * ------------------------------------------------------------------------------------------------
 */
#include <gtest/gtest.h>
/**
 * space
 */
#include <SMachine.h>
#include <SRandom.h>
#include <SCompare.h>
/**
 */
TEST(SMachine, File)
{
    STask::Enable();

    // files ------------------------------------------------------------------
    auto in  = SRandom::FileName();
    auto out = SRandom::FileName();

    // create test data -------------------------------------------------------
    SRandom::File(in, 1000);

    // configure machine ------------------------------------------------------
    auto conf = SMachine::Config().Add(
        SModuleCommand().AddModule({
            {"uri",  "encoder"}, {"type", "encode"}, {"verbose", "4"}
        }).AddFunction({
            {"type", "message"}, { "verbose", "4"}
        }).AddInput({
            { "uri", in}, {"type", "message.file"}, { "verbose", "4"}
        }).AddOutput({
            { "uri",  SRandom::FileName()}, { "type", "message.file"}, {"verbose", "4"}
        }).AddOutput({
            { "uri",  SRandom::FileName()}, { "type", "message.file"}, {"verbose", "4"}
        }).AddOutput({
            { "uri",  SRandom::FileName()}, { "type", "message.file"}, {"verbose", "4"}
        })
    );
    // encoder machine --------------------------------------------------------
    SMachine("system.share", conf).Join();

    // decoder machine --------------------------------------------------------
    SMachine("system.share", 
        conf.Swap("I", "O")
            .Update("M", "type", "decoder")
            .Update("O", "uri", out)
    ).Join();
    
    // check data -------------------------------------------------------------
    EXPECT_TRUE(SCompare::Files(SIFileResource(in), SIFileResource(out)));
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */