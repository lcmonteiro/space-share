/* 
 * File:   SOStreamConnector.h
 * Author: Luis Monteiro
 *
 * Created on June 11, 2018, 1:34 AM
 */
#ifndef SOSTREAMCONNECTOR_H
#define SOSTREAMCONNECTOR_H
/**
 *  Space Kernel
 */
#include "SContainer.h"
#include "SAddress.h"
#include "STask.h"
/**
 * Share Kernel
 */
#include "SConnector.h"
/**
 * Begin namespace Data
 */
namespace Decoded {
/**
 * Begin namespace Data
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
    void _write(const Container& container) override {
        /**-----------------------------------------------------------------------------------------------------
         * info
         *----------------------------------------------------------------------------------------------------**/
        INFO("DATA::OUT::n=" <<container.size() << "=" << container.front());
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
        mt19937_64 eng{random_device{}()};
        /** 
         */
        uniform_int_distribution<> dist{1000, 5000};
        /**---------------------------------------------------------------------------------------------
         * main loop
         *-------------------------------------------------------------------------------------------**/
        int i = 0;
        do {
            try {
                /**------------------------------------------------------------------------------------
                 * wait connection
                 *-----------------------------------------------------------------------------------**/
                __res.Wait(__uri);
                break;
            } catch (system_error& ex) {
                WARNING(ex.what());
            }
            /**----------------------------------------------------------------------------------------
             * random sleep
             *---------------------------------------------------------------------------------------**/
        } while (STask::Sleep(chrono::milliseconds{dist(eng) + (1000 * i++)}));
    }
    /**
     * good
     */
    inline bool _good() override {
        /**--------------------------------------------------------------------------------------------
         * verify resource status
         *-------------------------------------------------------------------------------------------**/
        return __res.good();
    }
    /**
     * close
     */
    inline void _close() override {
        /**-------------------------------------------------------------------------------------------
         * reset resource
         *------------------------------------------------------------------------------------------**/
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
 * End namespace Decoded
 */
}
#endif /* SOSTREAMCONNECTOR_H */

