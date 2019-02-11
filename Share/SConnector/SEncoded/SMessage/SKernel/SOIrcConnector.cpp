/*
 * Container:   SOIrcConnector.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 */
#include <ext/stdio_filebuf.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
/**
 * C++ std
 */
#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>
#include <chrono>
#include <random>
/**
 * Space Kernel
 */
#include "SBase64.h" 
#include "STask.h"
/**
 * Local
 */
#include "SOIrcConnector.h"
/**
 * Begin namespace Encoded
 */
namespace Encoded {
/**
 * Begin namespace Message
 */
namespace Message {
/**
 * user@host:port/channel
 */
SOIrcConnector::SOIrcConnector(const string address): SOutputConnector(address){
}

void SOIrcConnector::_Open() {
    default_random_engine eng{random_device{}()};
    /**
     */
    uniform_int_distribution<> dist{5000, 20000};
    /**
     */
    int i = 0;
    do {
        try {
            SIRCResource res;
            /**------------------------------------------------------------------------------------*
             * connect to server
             *-------------------------------------------------------------------------------------*/
            res.Connect(__uri.Host(), __uri.Port());
            INFO("CONNECT");
            STask::Sleep(chrono::seconds{1});
            /**------------------------------------------------------------------------------------*
             * join to channel
             *-------------------------------------------------------------------------------------*/
            res.Join(__uri.User(), __uri.Channel());
            INFO("JOIN");
            STask::Sleep(chrono::seconds{1});
            /*-------------------------------------------------------------------------------------*
             * active 
             *-------------------------------------------------------------------------------------*/
            swap(__res, res);
            /*-------------------------------------------------------------------------------------*
             * keep resource
             *-------------------------------------------------------------------------------------*/
            __res.Keep();
        } catch (IRCExceptionBANNED& ex) {
            ERROR(ex.what());
            break;
        } catch (ResourceExceptionTIMEOUT& ex) {
            WARNING(ex.what());
        } catch (ResourceExceptionABORT& ex) {
            WARNING(ex.what());
        } catch (std::system_error& ex) {
            WARNING(ex.what());
        }
        /**
         * reset connection
         */
        __res = SIRCResource();
        /**
         * sleep
         */
    } while (STask::Sleep(chrono::milliseconds{dist(eng) + (1000 * i++)}));
    /**
     * reset connection
     */
    __res = SIRCResource();
}

void SOIrcConnector::_Write(const Document& container) {
    IFrame in = Frame(
        sizeof (reference_t) + 
        sizeof (numframes_t) + 
        sizeof (framesize_t) + container.GetFrameSize()
    );
    /**----------------------------------------------------------------------------------------
     * write context
     *----------------------------------------------------------------------------------------*/
    in.Write(Frame().Number<reference_t>(container.GetPosition()));
    in.Write(Frame().Number<numframes_t>(container.GetNumFrames()));
    in.Write(Frame().Number<framesize_t>(container.GetFrameSize()));
    // log ------------------------------------------------
    INFO("CODE::OUT::"
    << "pos=" << container.GetPosition()  << " " 
        << "n="   << container.GetNumFrames() << " "
    << "sz="  << container.GetFrameSize() << " " 
        << "len=" << container.size()
    );
    /**----------------------------------------------------------------------------------------
     * write nframes
     *----------------------------------------------------------------------------------------*/
    for (auto& f : container) {
        __res.Send(
            in.Seek(sizeof (reference_t) + sizeof (numframes_t) + sizeof (framesize_t)).Write(f)
        ).Flush();
    }
}
/**
 * End namespace Message
 */
}
/**
 * End namespace Encoded
 */
}
