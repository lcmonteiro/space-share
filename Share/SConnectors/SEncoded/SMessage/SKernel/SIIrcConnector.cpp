/*
 * File:   SIIrcConnector.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 */
#include "SIIrcConnector.h"
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
SIIrcConnector::SIIrcConnector(const std::string& address)
: SInputConnector(address){
}
/**
 * ----------------------------------------------------------------------------
 * Read
 * ----------------------------------------------------------------------------
 */
Document SIIrcConnector::_Read() {
    Frame tmp;
    // receive --------------------------------------------
    __res.Read(tmp);
    // parse ----------------------------------------------
    IOFrame out    = std::move(tmp);
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
 * Open
 * ----------------------------------------------------------------------------
 */
void SIIrcConnector::_Open() {
       mt19937_64 eng{random_device{}()};
       // sleep distribution ---------------------------------------- 
       uniform_int_distribution<> dist{5000, 20000};
       // process ---------------------------------------------------
       int i = 0;
       do {
           try {
               SIRCResource res;
               // connect to server -------------------------
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
       } while (STask::Sleep(chrono::milliseconds{dist(eng) + (1000 * i++)}));
}
}}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Encoded & Message
 * ------------------------------------------------------------------------------------------------
 */
