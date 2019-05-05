/**
 * ------------------------------------------------------------------------------------------------
 * File:   SIOIrcConnector.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 * ------------------------------------------------------------------------------------------------
 */
#include "SIOIrcConnector.h"
/**
 * namespaces
 */
using namespace std;
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
SIOIrcConnector::SIOIrcConnector(const SText& address)
: SInOutputConnector(address) {}
/**
 * ----------------------------------------------------------------------------
 * Read
 * ----------------------------------------------------------------------------
 */
Document SIOIrcConnector::_read() {
    Frame tmp;
    /**
     * receive
     */
    __res.read(tmp);
    /**
     * parse
     */
    IOFrame out = std::move(tmp);
    auto position = out.read(
        sizeof (reference_t)).number<reference_t>();
    auto nframest = out.read(
        sizeof (framecount_t)).number<framecount_t>();
    auto framelen = out.read(
        sizeof (framesize_t)).number<framesize_t>();
    /**
     * log info
     */
    INFO("CODE::IN::" 
        << "pos=" << position << " " 
        << "n="   << nframest << " " 
        << "len=" << framelen );
    /**
     * read nframes
     */
    auto container = Document(Context(position, nframest, framelen));
    container.reserve(1);
    container.emplace_back(out.read(framelen));
    /**
     * return container
     */
    return container;
}
/**
 * ----------------------------------------------------------------------------
 * Write
 * ----------------------------------------------------------------------------
 */
void SIOIrcConnector::_write(const Document& container) {
    IOFrame io = Frame(
        sizeof (reference_t) + 
        sizeof (framecount_t) + 
        sizeof (framesize_t) + container.frame_size());
    /**
     * write context
     */ 
    io.write(Frame().number<reference_t>(container.position()));
    io.write(Frame().number<framecount_t>(container.frame_count()));
    io.write(Frame().number<framesize_t>(container.frame_size()));
    /**
     * log info
     */
    INFO("CODE::OUT::"
        << "pos=" << container.position()  << " " 
        << "n="   << container.frame_count() << " "
        << "sz="  << container.frame_size() << " " 
        << "len=" << container.size());
    /**
     * write nframes
     */
    for (auto& f : container) {
        __res.write(io.iseek(
            sizeof (reference_t) + 
            sizeof (framecount_t) + 
            sizeof (framesize_t)).write(f));
    }
}
/**
 * ----------------------------------------------------------------------------
 * Open
 * ----------------------------------------------------------------------------
 */
void SIOIrcConnector::_open() {
    std::mt19937_64 eng{std::random_device{}()};
    /**
     * sleep distribution
     */ 
   std::uniform_int_distribution<> dist{5000, 20000};
    /**
     * process
     */
    int i = 0;
    do {
        try {
            SIRCResource res;
            /**
             * connect to server
             */
            res.connect(__uri.host(), __uri.port());
            INFO("CONNECTED");
            STask::Sleep(chrono::seconds{1});
            /**
             * join to channel
             */
            res.join(__uri.user(), __uri.channel());
            INFO("JOINED");
            STask::Sleep(chrono::seconds{1});
            /**
             * swap resources
             */
            std::swap(__res, res);
            break;
        } catch (IRCExceptionBANNED& ex) {
            ERROR(ex.what());
            /**
             * reset connection
             */
            __res = SIRCResource();
            break;
        } catch (ResourceExceptionTIMEOUT& ex) {
            WARNING(ex.what());
        } catch (ResourceExceptionABORT& ex) {
            WARNING(ex.what());
        } catch (std::system_error& ex) {
            WARNING(ex.what());
        }
    } while (STask::Sleep(std::chrono::milliseconds{dist(eng) + (1000 * i++)}));
}
}}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Encoded & Message
 * ------------------------------------------------------------------------------------------------
 */