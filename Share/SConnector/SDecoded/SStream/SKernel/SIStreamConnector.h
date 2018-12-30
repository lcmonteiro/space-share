/* 
 * File:   SIStreamConnector.h
 * Author: Luis Monteiro
 *
 * Created on June 6, 2018, 11:47 PM
 */
#ifndef SISTREAMCONNECTOR_H
#define SISTREAMCONNECTOR_H
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
class SIStreamConnector : public SInputConnector {
public:
    /**
     * constructor
     */
    SIStreamConnector(
        const string address,  
        const size_t nframes, 
        const size_t sframes
    );
    /**
     * destructor
     */
    virtual ~SIStreamConnector() = default;
    /**
     * inline overrides
     */
    inline Resource& GetResource() override {
        return __res.Base();
    }
protected:
    /**
     * ----------------------------------------------------------------------------------------
     * IO functions
     * ----------------------------------------------------------------------------------------
     * read
     */
    Container _Read() override {
        IFrame buffer;
        /**-----------------------------------------------------------------------------------------------------
         * fill container
         *----------------------------------------------------------------------------------------------------**/
        for (; !__container.Full(); __container.push_back(move(buffer))) {
            /**---------------------------------------------------------------------------------------------
             * Fill buffer
             *--------------------------------------------------------------------------------------------**/
            while (!__buffer.Full()) {
                __res.Fill(__buffer);
            }
            /*----------------------------------------------------------------------------------------------
             * swap buffers
             *--------------------------------------------------------------------------------------------**/
            buffer = IFrame(__buffer.size());
            swap(__buffer, buffer);
        }
        /*------------------------------------------------------------------------------------------------------
         * swap containers
         *----------------------------------------------------------------------------------------------------**/
        Container container(__container.capacity());
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
     * drain 
     */
    list<Container> _Drain() override {
        Buffer tmp;
        /**-----------------------------------------------------------------------------------------------------
         * check if container is full 
         *----------------------------------------------------------------------------------------------------**/
        if (!__container.empty()) {
            auto container = Container(__container.capacity());
            swap(__container, container);
            tmp.Write(move(container));
        }
        /**-----------------------------------------------------------------------------------------------------
         * check if frame is full 
         *----------------------------------------------------------------------------------------------------**/
        if (!__buffer.Empty()) {
            auto buffer = IFrame(__buffer.size());
            swap(__buffer, buffer);
            tmp.Write(move(buffer.Shrink()));
        }
        /**-----------------------------------------------------------------------------------------------------
         * fill container
         *----------------------------------------------------------------------------------------------------**/
        list<Container> out;
        for (auto& p : Shape(tmp.Length(), __container.capacity())) {
            auto container = Container(p.first);
            while (!container.Full()) {
                container.push_back(move(tmp.Read(p.second)));
            }
            out.push_back(move(container));
        }
        /**-----------------------------------------------------------------------------------------------------
         * info
         *----------------------------------------------------------------------------------------------------**/
        INFO("DATA(drain)::IN::n=" << out.size());
        /**-----------------------------------------------------------------------------------------------------
         * return filled containers
         *----------------------------------------------------------------------------------------------------**/
        return out;
    }
    /**
     * ----------------------------------------------------------------------------------------
     * control functions
     * ----------------------------------------------------------------------------------------
     * open
     */
    inline void _Open() override {
        mt19937_64 eng{random_device{}()};
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
    IFrame __buffer;
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
#endif /* SISTREAMCONNECTOR_H */

