/* 
 * File:   SOMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on June 6, 2018, 11:47 PM
 */
#ifndef SOMESSAGECONNECTOR_H
#define SOMESSAGECONNECTOR_H
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
 * Begin namespace Decoded
 */
namespace Decoded {
/**
 * Begin namespace Message
 */
namespace Message {
/**
 */
template<class RESOURCE, class TOOL>
class SOMessageConnector : public SOutputConnector {
public:
    /**
     * constructor
     */
    SOMessageConnector(
        const string address  // con address
    ) : SOutputConnector(address), __buffer(), __res() {}
    /**
     * destructor
     */
    virtual ~SOMessageConnector() = default;
protected:
    /**
     * -------------------------------------------------------------------------------------------------------------
     * O functions
     * -------------------------------------------------------------------------------------------------------------
     * write
     */
    void _Write(const Container& container) override {
        /**-----------------------------------------------------------------------------------------------------
         * info
         *----------------------------------------------------------------------------------------------------**/
        INFO("DATA::OUT::n=" <<container.size() << "=" << container.front());
        /**-----------------------------------------------------------------------------------------------------
         * compress and remove buffer size
         *----------------------------------------------------------------------------------------------------**/
        TOOL::Join(container, __buffer);
        /**-----------------------------------------------------------------------------------------------------
         * write nframes
         *----------------------------------------------------------------------------------------------------**/
        __res.Drain(__buffer);
    }
    /**
     * -------------------------------------------------------------------------------------------------------------
     * control functions
     * -------------------------------------------------------------------------------------------------------------
     * open
     */
    inline void _Open() override {
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
                 * wait connection
                 *------------------------------------------------------------------------------------**/
                __res.Wait(__uri);
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
    inline bool _Good() override {
        /**-----------------------------------------------------------------------------------------------------
         * verify resource status
         *----------------------------------------------------------------------------------------------------**/
        return __res.Good();
    }
    /**
     * close
     */
    inline void _Close() override {
        /**-----------------------------------------------------------------------------------------------------
         * reset resource
         *----------------------------------------------------------------------------------------------------**/
        __res.Reset();
    }
private:
    /**
     * buffer
     */
    Frame __buffer;
    /**
     * resource 
     */
    RESOURCE __res;
};
/**
 * End namespace Message
 */
}
/**
 * End namespace Decoded
 */
}
/**
 */
#endif /* SOMESSAGECONNECTOR_H */

