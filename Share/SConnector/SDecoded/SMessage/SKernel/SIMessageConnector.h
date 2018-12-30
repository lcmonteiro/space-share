/* 
 * File:   SIMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on June 6, 2018, 11:47 PM
 */
#ifndef SIMESSAGECONNECTOR_H
#define SIMESSAGECONNECTOR_H
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
class SIMessageConnector : public SInputConnector {
public:
    /**
     * constructor
     */
    SIMessageConnector(
        const string address,   // con address
        const size_t nframes,   // num of frames 
        const size_t maxsmsg    // max size message  
    ) : SInputConnector(address), __container(nframes), __buffer(maxsmsg), __res() {}
    /**
     * destructor
     */
    virtual ~SIMessageConnector() = default;
    /**
     * inline overrides
     */
    inline Resource& GetResource() override {
        return __res.Base();
    }
protected:
    /**
     * ----------------------------------------------------------------------------------------
     * I functions
     * ----------------------------------------------------------------------------------------
     * read
     */
    Container _Read() override {
        Container container(__container.capacity());
        /**-----------------------------------------------------------------------------------------------------
         * Fill buffer
         *----------------------------------------------------------------------------------------------------**/
        __res.Fill(__buffer.Expand());
        /**-----------------------------------------------------------------------------------------------------
         * split buffer 
         *----------------------------------------------------------------------------------------------------**/
        TOOL::Split(__buffer, __container);
        /**-----------------------------------------------------------------------------------------------------
         * swap containers
         *----------------------------------------------------------------------------------------------------**/
        swap(__container, container);    
        /**-----------------------------------------------------------------------------------------------------
         * info
         *----------------------------------------------------------------------------------------------------**/
        INFO("DATA(read)::IN::n=" << container.size() << "=" << container.front());
        /**-----------------------------------------------------------------------------------------------------
         * return filled container
         *----------------------------------------------------------------------------------------------------**/
        return container;
    }
    /**
     * ----------------------------------------------------------------------------------------
     * control functions
     * ----------------------------------------------------------------------------------------
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
     * container
     */
    Container __container;
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
#endif /* SIMESSAGECONNECTOR_H */

