/* 
 * File:   SOStreamConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 6, 2016, 10:21 PM
 */
#ifndef SOSTREAMSTREAMCODED_H
#define SOSTREAMSTREAMCODED_H
/**
 * Space Kernel
 */
#include "SContainer.h"
#include "SAddress.h"
#include "STask.h"
/**
 * Share Kernel
 */
#include "SConnector.h"
/**
 * Begin namespace Encoded
 */
namespace Encoded {
/**
 * Begin namespace Stream
 */
namespace Stream {
/**
 */
template<class RESOURCE>
class SOStreamConnector : public SOutputConnector {
public:
    /**
     * constructor
     */
    SOStreamConnector(const string address);
    /**
     * destructor
     */
    virtual ~SOStreamConnector() = default;    
    /**
     */
protected:
    /**
     * -------------------------------------------------------------------------------------------------------------
     * IO functions
     * -------------------------------------------------------------------------------------------------------------
     * write
     */
    void _write(const Document& container) override {
        static Frame SEQ({1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233});
        /**-----------------------------------------------------------------------------------------------------
         * write sequence
         *----------------------------------------------------------------------------------------------------**/
        __res.Drain(SEQ);
        /**-----------------------------------------------------------------------------------------------------
         * write context
         *----------------------------------------------------------------------------------------------------**/
        __res.Drain(Frame(sizeof (reference_t)).Number<reference_t>(container.GetPosition()));
        __res.Drain(Frame(sizeof (numframes_t)).Number<numframes_t>(container.GetNumFrames()));
        __res.Drain(Frame(sizeof (numframes_t)).Number<numframes_t>(container.size()));
        __res.Drain(Frame(sizeof (framesize_t)).Number<framesize_t>(container.GetFrameSize()));
        /**-----------------------------------------------------------------------------------------------------
         * info
         *----------------------------------------------------------------------------------------------------**/
        INFO("CODE::OUT::"
            << "pos=" << container.GetPosition() << " " << "n=" << container.GetNumFrames() << " "
            << "sz=" << container.GetFrameSize() << " " << "len=" << container.size()
        );
        /**-----------------------------------------------------------------------------------------------------
         * write nframes
         *----------------------------------------------------------------------------------------------------**/
        for (auto& f : container) {
            __res.Drain(f);
        }
    }
    /**
     * -------------------------------------------------------------------------------------------------------------
     * control functions
     * -------------------------------------------------------------------------------------------------------------
     * open
     */
    inline void _open() override {
        default_random_engine eng{random_device{}()};
        /** 
         */
        uniform_int_distribution<> dist{1000, 5000};
        /**-----------------------------------------------------------------------------------------------------
         * main loop
         *----------------------------------------------------------------------------------------------------**/
        int i = 0;
        do {
            try {
                /**-------------------------------------------------------------------------------------
                 * connect
                 *------------------------------------------------------------------------------------**/
                __res.Connect(__uri);
                break;
            } catch (system_error& ex) {
                WARNING(ex.what());
            }
            /**---------------------------------------------------------------------------------------------
             * random sleep
             *--------------------------------------------------------------------------------------------**/
        } while (STask::Sleep(chrono::milliseconds{dist(eng) + (1000 * i++)}));
     }
    /**
     * good
     */
    inline bool _good() override{
        /**-----------------------------------------------------------------------------------------------------
         * verify resource status
         *----------------------------------------------------------------------------------------------------**/
        return __res.Good();
    }
    /**
     * close
     */
    inline void _close() override {
        /**-----------------------------------------------------------------------------------------------------
         * reset resource
         *----------------------------------------------------------------------------------------------------**/
        __res.Reset();
    }
private:
    /**
     * resource 
     */
    RESOURCE __res;
};
/**
 * End namespace Stream
 */
}
/**
 * End namespace Encoded
 */
}
#endif /* SOSTREAMSTREAMCODED_H */

