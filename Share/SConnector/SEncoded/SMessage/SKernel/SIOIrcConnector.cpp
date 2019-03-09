/*
 * File:   SIOIrcConnector.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 */
#include "SIOIrcConnector.h"
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
 */
SIOIrcConnector::SIOIrcConnector(const std::string& address)
: SInOutputConnector(address){
}
/**
 * ----------------------------------------------------------------------------
 * Read
 * ----------------------------------------------------------------------------
 */
Document SIOIrcConnector::_Read() {
    Frame tmp;
    // receive --------------------------------------------
    __res.Read(tmp);
    // parse ----------------------------------------------
    OFrame out    = std::move(tmp);
    auto position = out.Read(sizeof (reference_t)).Number<reference_t>();
    auto nframest = out.Read(sizeof (numframes_t)).Number<numframes_t>();
    auto framelen = out.Read(sizeof (framesize_t)).Number<framesize_t>();
    // log ------------------------------------------------
    INFO("CODE::IN::" 
        << "pos=" << position << " " 
        << "n="   << nframest << " " 
        << "len=" << framelen
    );
    // read nframes ---------------------------------------
    Document container(Context(position, nframest, framelen));
    container.reserve(1);
    container.push_back(out.Read(framelen));
    // return container -----------------------------------
    return container;
}
/**
 * ----------------------------------------------------------------------------
 * Write
 * ----------------------------------------------------------------------------
 */
void SIOIrcConnector::_Write(const Document& container) {
    IOFrame io = Frame(
        sizeof (reference_t) + 
        sizeof (numframes_t) + 
        sizeof (framesize_t) + container.GetFrameSize()
    );
    // write context --------------------------------------
    io.Write(Frame().Number<reference_t>(container.GetPosition()));
    io.Write(Frame().Number<numframes_t>(container.GetNumFrames()));
    io.Write(Frame().Number<framesize_t>(container.GetFrameSize()));
    
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
            io.ISeek(
                sizeof (reference_t) + sizeof (numframes_t) + sizeof (framesize_t)
            ).Write(f)
        );
    }
}
/**
 * ----------------------------------------------------------------------------
 * Open
 * ----------------------------------------------------------------------------
 */
void SIOIrcConnector::_Open() {
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


