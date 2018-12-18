#include <gtest/gtest.h>
#include <SMachine.h>

using namespace std;
TEST(SMachine, UDP)
{
    STask::Enable();
    /**
     * configure machine
     */
    SMachine m("system.share", {{
        {"M", {{
            {"uri",  "encoder"}, {"type", "encode"}, {"verbose", "4"}
        }}},
        {"F", {{
            {"type", "message"}, { "verbose", "4"}
        }}},
        {"I", {{
            { "uri", "127.0.0.1:1357"}, { "type", "message.udp"}, { "verbose", "4"}
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
    }});
    /**
     * start machine
     */
    

    /**
     * stop machine
     */
    //m = SMachine();


  
}
