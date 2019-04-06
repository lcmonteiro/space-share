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

    // encoder machine --------------------------------------------------------
    auto conf = SMachine::Config();
    conf.add({
        {SModule::Command::MODULE,   {{
            {Module::URI, "encoder"},
            {Module::TYPE, Module::Type::ENCODE},
            {Module::TIMEOUT, "1000"},
            {Module::VERBOSE, "4"}
        }}},
        {SModule::Command::FUNCTION, {{
            {Module::Function::TYPE, Module::Function::Type::MESSAGE},
            {Module::IO::VERBOSE, "4"}
        }}},
        {SModule::Command::INPUT,   {{
            {Module::IO::TYPE, Module::IO::Type::MESSAGE_FILE},
            {Module::IO::URI, in},
            {Module::IO::VERBOSE, "4"}
        }}},
        {SModule::Command::OUTPUT,    {{
            {Module::IO::MINIMUM, "3"},
            {Module::IO::NOMINAL, "3"}
        }, {
            {Module::IO::TYPE, Module::IO::Type::MESSAGE_FILE},
            {Module::IO::URI, SRandom::FileName()},
            {Module::IO::VERBOSE, "4"}
        }, {
            {Module::IO::TYPE, Module::IO::Type::MESSAGE_FILE},
            {Module::IO::URI, SRandom::FileName()},
            {Module::IO::VERBOSE, "4"} 
        }, {
            {Module::IO::TYPE, Module::IO::Type::MESSAGE_FILE},
            {Module::IO::URI, SRandom::FileName()},
            {Module::IO::VERBOSE, "4"}
        }}}
    });
    SMachine("system.share", conf).wait();

    // decoder machine --------------------------------------------------------
    conf.swap(
        SModule::Command::INPUT, 
        SModule::Command::OUTPUT
    ).update(
        SModule::Command::MODULE, 
        Module::TYPE,
        Module::Type::DECODE
    ).update(
        SModule::Command::OUTPUT,
        Module::IO::URI,
        out
    );
    SMachine("system.share", conf).wait();
    
    // check data -------------------------------------------------------------
    EXPECT_TRUE(SCompare::Files(SIFileResource(in), SIFileResource(out)));
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */