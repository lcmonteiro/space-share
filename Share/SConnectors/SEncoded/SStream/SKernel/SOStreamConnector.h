/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SOStreamConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 6, 2016, 10:21 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SOSTREAMSTREAMCODED_H
#define SOSTREAMSTREAMCODED_H
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
template<class RESOURCE>
class SOStreamConnector : public SOutputConnector {
public:
    /**
     * ------------------------------------------------------------------------
     * Constructor
     * ------------------------------------------------------------------------
     */
    SOStreamConnector(const string address);
protected:
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
#endif /* SOSTREAMSTREAMCODED_H */

