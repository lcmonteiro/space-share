/*
 * File:   SOIrcConnector.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 */
#include "SOIrcConnector.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Begin namespace Encoded & Message
 * ------------------------------------------------------------------------------------------------
 */
namespace Encoded {
namespace Message {
/**
 * ----------------------------------------------------------------------------
 * Constructor
 * ----------------------------------------------------------------------------
 * user@host:port/channel
 */
SOIrcConnector::SOIrcConnector(const string address): SOutputConnector(address){
}
/**
 * ----------------------------------------------------------------------------
 * Write
 * ----------------------------------------------------------------------------
 */
void SOIrcConnector::_Write(const Document& container) {
    IFrame in = Frame(
        sizeof (reference_t) + 
        sizeof (numframes_t) + 
        sizeof (framesize_t) + container.GetFrameSize()
    );
    // write context --------------------------------------
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
    // write nframes --------------------------------------
    for (auto& f : container) {
        __res.Write(
            in.Seek(
                sizeof (reference_t) + sizeof (numframes_t) + sizeof (framesize_t)
            ).Write(f).Frame()
        );
    }
}
/**
 * ----------------------------------------------------------------------------
 * Open
 * ----------------------------------------------------------------------------
 */
void SOIrcConnector::_Open() {
    std::mt19937_64 eng{std::random_device{}()};
    /**
     */
    std::uniform_int_distribution<> dist{5000, 20000};
    /**
     */
    int i = 0;
    do {
        try {
            SIRCResource res;
            // connect to server --------------------------
            res.Connect(__uri.Host(), __uri.Port());
            INFO("CONNECTED");
            STask::Sleep(chrono::seconds{1});
            // join to channel ---------------------------
            res.Join(__uri.User(), __uri.Channel());
            INFO("JOINED");
            STask::Sleep(chrono::seconds{1});
            // swap resources ----------------------------
            std::swap(__res, res);
            // active ------------------------------------
            break;
        } catch (IRCExceptionBANNED& ex) {
            ERROR(ex.what());
            // reset connection --------------------------
            __res = SIRCResource();
            break;
        } catch (ResourceExceptionTIMEOUT& ex) {
            WARNING(ex.what());
        } catch (ResourceExceptionABORT& ex) {
            WARNING(ex.what());
        } catch (std::system_error& ex) {
            WARNING(ex.what());
        }
        // random sleep --------------------------------------
    } while (STask::Sleep(std::chrono::milliseconds{dist(eng) + (1000 * i++)}));
}
}}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Encoded & Message
 * ------------------------------------------------------------------------------------------------
 */


