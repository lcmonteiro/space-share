#include <gtest/gtest.h>

#include <SMachine.h>
#include <SFileResource.h>

using namespace std;
TEST(SMachine, FILE)
{
    STask::Enable();
    /**
     * create file
     */
    SRandomFileResource<> data("/tmp/data", 1000);
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
    }});
    /**
     * start machine
     */
    m.Process(chrono::seconds(1));
    /**
     * stop machine
     */
    //m = SMachine();


  
}
