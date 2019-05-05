/**
 * ------------------------------------------------------------------------------------------------
 * File:   SIStreamConnector.h
 * Author: Luis Monteiro
 *
 * Created on June 6, 2018, 11:47 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SISTREAMCONNECTOR_H
#define SISTREAMCONNECTOR_H
/**
 *  space
 */
#include "SContainer.h"
#include "SAddress.h"
#include "SBuffer.h"
#include "STask.h"
#include "SText.h"
/**
 * share
 */
#include "SConnector.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Begin namespace Decoded & Stream
 * ------------------------------------------------------------------------------------------------
 */
namespace Decoded {
namespace Stream  {
/**
 */
template<class Adapter>
class SIStreamConnector : public SInputConnector {
public:
    /**
     * ------------------------------------------------------------------------
     * Constructor
     * ------------------------------------------------------------------------
     */
    SIStreamConnector(
        const SText  address,
        const size_t nframes,
        const size_t sframes )
    : SInputConnector(address), 
    __container(nframes), 
    __buffer(sframes), 
    __res() {}
    /**
     * ------------------------------------------------------------------------
     * Get Resource
     * ------------------------------------------------------------------------
     */
    inline Resource& resource() override {
        return __res.base();
    }
protected:
    /**
     * ------------------------------------------------------------------------
     * Read
     * ------------------------------------------------------------------------
     */
    Document _read() override {
        IOFrame buffer;
        /**
         * fill container
         */
        while (!__container.full()) {
            /**
             * fill buffer
             */
            while (!__buffer.full()) {
                __res.fill(__buffer);
            }
            /**
             * reset buffer
             */
            buffer = IOFrame(__buffer.capacity());
            std::swap(__buffer, buffer);
            /**
             * insert on container
             */
            __container.emplace_back(buffer.detach());
        }
        /**
         * reset container
         */
        auto container = Document(__container.capacity());
        std::swap(__container, container);    
        /**
         * log info
         */
        INFO("DATA::IN::n=" << container.size() << "=" << container.at(0));
        /**
         * return filled container
         */
        return container;
    }
    /**
     * ------------------------------------------------------------------------
     * Drain 
     * ------------------------------------------------------------------------
     */
    std::list<Document> _drain() override {
        Buffer tmp;
        /**
         * drain the remaining container data
         */
        if (!__container.empty()) {
            auto container = Document(__container.capacity());
            std::swap(__container, container);
            tmp.drain(std::move(container));
        }
        /**
         * drain the remaining buffer data
         */
        if (!__buffer.empty()) {
            auto buffer = IOFrame(__buffer.capacity());
            std::swap(__buffer, buffer);
            tmp.drain(std::move(buffer.deflate()));
        }
        /**
         * fill container
         */
        std::list<Document> out;
        for (auto& p : _shape(tmp.size(), __container.capacity())) {
            auto container = Document(p.first);
            while (!container.full()) {
                container.emplace_back(tmp.drain(p.second));
            }
            out.emplace_back(std::move(container));
        }
        /**
         * log info
         */
        INFO("DATA(drain)::IN::n=" << out.size());
        /**
         * return filled container
         */
        return out;
    }
    /**
     * ------------------------------------------------------------------------
     * Open
     * ------------------------------------------------------------------------
     */
    inline void _open() override {
        std::default_random_engine eng{std::random_device{}()};
        /**
         * sleep distribution
         */
        std::uniform_int_distribution<> dist{1000, 5000};
        /**
         * main loop
         */
        int i = 0;
        do {
            try {
                __res.wait(__uri);
                break;
            } catch (std::system_error& ex) {
                WARNING(ex.what());
            }
        } while (STask::Sleep(std::chrono::milliseconds{dist(eng) * ++i}));
    }
    /**
     * ------------------------------------------------------------------------
     * Good
     * ------------------------------------------------------------------------
     */
    inline bool _good() override {
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
     **
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
    Adapter __res;
};
}}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Decoded & Stream
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SISTREAMCONNECTOR_H */
