/* 
 * File:   SIOStreamConnector.h
 * Author: Luis Monteiro
 *
 * Created on June 6, 2018, 11:47 PM
 */
#ifndef SIOSTREAMCONNECTOR_H
#define SIOSTREAMCONNECTOR_H
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
 * Begin namespace Decoded
 */
namespace Decoded {
/**
 * Begin namespace Stream
 */
namespace Stream {
/**
 */
template<class RESOURCE>
class SIOStreamConnector : public SInOutputConnector {
public:
    /**
     * constructor
     */
    SIOStreamConnector(
        const string address, 
        const size_t nframes, 
        const size_t sframes  
    ) : SInOutputConnector(address), __container(nframes), __buffer(sframes), __res() {}
    /**
     * destructor
     */
    virtual ~SIOStreamConnector() = default;
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
         * Fill container
         *----------------------------------------------------------------------------------------------------**/
        for (; !__container.Full(); __container.push_back(move(buffer))) {
            /**---------------------------------------------------------------------------------------------
             * Fill buffer
             *--------------------------------------------------------------------------------------------**/
            while (!__buffer.Full()) {
                __res.Fill(__buffer);
            }
            /**---------------------------------------------------------------------------------------------
             * swap buffers
             *--------------------------------------------------------------------------------------------**/
            buffer = IFrame(__buffer.size());
            swap(__buffer, buffer);
        }
        /**-----------------------------------------------------------------------------------------------------
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
         * Fill container
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
     * write
     */
    void _Write(const Container& container) override {
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
/**
 */
#endif /* SIOSTREAMCONNECTOR_H */
