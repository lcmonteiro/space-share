/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SIOStreamConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 11, 2016, 1:25 AM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SIOSTREAMCONNECTORCODED_H
#define SIOSTREAMCONNECTORCODED_H
/**
 * space
 */
#include "SContainer.h"
#include "SAddress.h"
#include "STask.h"
/**
 * share
 */
#include "SConnector.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Begin namespace Encoded & Stream
 * ------------------------------------------------------------------------------------------------
 */
namespace Encoded {
namespace Stream  {
/**
 */
template<class RE>
class SIOStreamConnector : public SInOutputConnector {
public:
    /**
     * ------------------------------------------------------------------------
     * Constructor
     * ------------------------------------------------------------------------
     */
    SIOStreamConnector(const string address);
    /**
     * ------------------------------------------------------------------------
     * Get Resource
     * ------------------------------------------------------------------------
     */
    inline Resource& resource() override {
        return __res.Base();
    }
protected:
    /**
     * ------------------------------------------------------------------------
     * Read
     * ------------------------------------------------------------------------
     */
    Document _read() override { 
        static Frame SEQ({1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233});
        /**
         * states 
         */
        switch(__state){
            case 0: {
                /**
                 * prepare start seq
                 */
                __buffer = IOFrame(SEQ.size());
                /**
                 * next state
                 */
                __state = 1;
            }
            case 1: {
                /**
                 * fill sequency
                 */
                while (!__buffer.full()) { 
                    __res.Fill(__buffer); 
                }
                /**
                 * check sequency
                 */
                while(__buffer != SEQ) {
                    /**
                     * shift sequency
                     */
                    __buffer.Shift(1);
                    /**
                     * fill sequency
                     */
                    while (!__buffer.full()) { 
                        __res.Fill(__buffer); 
                    }
                }
                /**
                 * next state
                 */
                __state = 2;
            }
            case 2: {
                /**
                 * prepare header
                 */
                __buffer = IOFrame(
                    sizeof (reference_t) +  // reference number
                    sizeof (framecount_t) + // number of frames total
                    sizeof (framecount_t) + // number of frames partial
                    sizeof (framesize_t)    // size   of frames
                );
                /**
                 * next state
                 */
                __state = 3;
            }
            case 3: {
                /**
                 * Fill header
                 */
                while (!__buffer.full()) {
                    __res.Fill(__buffer);
                }
                /**
                 * next state
                 */
                __state = 4;
            }
            case 4:    {
                /**
                 * read context
                 */
                IOFrame header(move(__buffer));
                auto position = header.read(sizeof (reference_t)).Number<reference_t>();
                auto nframest = header.read(sizeof (framecount_t)).Number<framecount_t>();
                auto nframesp = header.read(sizeof (framecount_t)).Number<framecount_t>();
                auto framelen = header.read(sizeof (framesize_t)).Number<framesize_t>();
                /**
                 * log info
                 */
                INFO("CODE::IN::"
                    << "pos=" << position << " " 
                    << "n="   << nframest << " " 
                    << "sz="  << nframesp << " " 
                    << "len=" << framelen );
                /**
                 * prepare frame
                 */
                __buffer = IOFrame(framelen);
                /**
                 * prepare document
                 */
                __container = Document(
                    Container(nframesp), 
                    Context(position, nframest, framelen));
                /**
                 * next state
                 */
                __state = 5;
            }
            case 5: {
                /**
                 * Fill container
                 */
                for (IOFrame frame; !__container.full(); __container.push_back(move(frame))) {
                    /**
                     * Fill buffer
                     */
                    while (!__buffer.full()) {
                        __res.Fill(__buffer);
                    }
                    /**
                     * swap buffers
                     */
                    frame = IOFrame(__buffer.size());
                    std::swap(__buffer, frame);
                }
            }
            default : {
                /**
                 * next state
                 */
                __state = 0;
            }
        }
        return __container;
    }
    /**
     * ------------------------------------------------------------------------
     * Drain 
     * ------------------------------------------------------------------------
     */
    list<Document> _drain() override {
        /**
         * log info
         */
        INFO("CODE(drain)::IN::n=" << __container.size());
        /**
         * next state
         */
        __state = 0;
        /**
         * drain container
         */
        if(__container.empty()){
            return {};
        }
        return {move(__container)};
    }
    /**
     * ------------------------------------------------------------------------
     * Write
     * ------------------------------------------------------------------------
     */
    void _write(const Document& container) override {
        static Frame SEQ({1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233});
        /**
         * write sequence
         */
        __res.drain(SEQ);
        /**
         * write context
         */
        __res.drain(Frame().Number<reference_t>(container.position()));
        __res.drain(Frame().Number<framecount_t>(container.frame_count()));
        __res.drain(Frame().Number<framecount_t>(container.size()));
        __res.drain(Frame().Number<framesize_t>(container.frame_size()));
        /**
         * log info
         */
        INFO("CODE::OUT::"
            << "pos=" << container.position()    << " " 
            << "n="   << container.frame_count() << " "
            << "sz="  << container.frame_size()  << " " 
            << "len=" << container.size());
        /**
         * write nframes
         */
        for (auto& f : container) {
            __res.drain(f);
        }
    }
    /**
     * ------------------------------------------------------------------------
     * Open
     * ------------------------------------------------------------------------
     */
    inline void _open() override {
        default_random_engine eng{random_device{}()};
        /**
         * sleep distribution
         */
        uniform_int_distribution<> dist{1000, 5000};
        /**
         * main loop
         */
        int i = 0;
        do {
            try {
                __res.Connect(__uri);
                break;
            } catch (system_error& ex) {
                WARNING(ex.what());
            }
        } while (STask::Sleep(chrono::milliseconds{dist(eng) + (1000 * i++)}));
     }
    /**
     * ------------------------------------------------------------------------
     * Good
     * ------------------------------------------------------------------------
     */
    inline bool _good() override{
        return __res.good();
    }
    /**
     * ------------------------------------------------------------------------
     * Close
     * ------------------------------------------------------------------------
     */
    inline void _close() override {
        __res.reset();
    }
private:
    /**
     * ------------------------------------------------------------------------
     * Variables
     * ------------------------------------------------------------------------
     * container
     */
    Document __container;
    /**
     * buffer
     */
    IOFrame __buffer;
    /**
     * resource 
     */
    RESOURCE __res;
};
}}
/**
 * ------------------------------------------------------------------------------------------------
 * Begin namespace Encoded & Stream
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SIOSTREAMCONNECTORCODED_H */

