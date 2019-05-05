/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SIMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on June 6, 2018, 11:47 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SIMESSAGECONNECTOR_H
#define SIMESSAGECONNECTOR_H
/**
 * Space Kernel
 */
#include "SContainer.h"
#include "SAddress.h"
#include "STask.h"
#include "SText.h"
/**
 * Share Kernel
 */
#include "SConnector.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Begin namespace Decoded
 * ------------------------------------------------------------------------------------------------
 */
namespace Decoded {
namespace Message {
/**
 * ------------------------------------------------------------------------------------------------
 * Base - SOMessageConnector
 * ------------------------------------------------------------------------------------------------
 */
namespace Base {
/**
 * @Adapter - resource adapter
 */
template<typename Adapter, typename Super>
class SIMessageConnector : public Super {
public:
    /**
     * ------------------------------------------------------------------------
     * Constructor
     * ------------------------------------------------------------------------
     */
    template<typename V>
    SIMessageConnector(const V& v): Super(v.address), __res() {}
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
     * Open
     * ------------------------------------------------------------------------
     */
    inline void _open() override {
        std::default_random_engine eng{std::random_device{}()};
        /**
         * sleep distribution
         */
        std::uniform_int_distribution<> dist{100, 1000};
        /**
         * main loop
         */
        int i = 0;
        do {
            try {
                __res.bind(this->__uri);
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
    /**
     * ------------------------------------------------------------------------
     * Variables
     * ------------------------------------------------------------------------
     * resource 
     */
    Adapter __res;
};
}
/**
 * ------------------------------------------------------------------------------------------------
 * Layer - SOMessageConnector
 * ------------------------------------------------------------------------------------------------
 */
namespace Layer {
/**
 */
template<typename Tool, typename Super>
class SIMessageConnector : public Super {
public:
    /**
     * ------------------------------------------------------------------------
     * Constructor
     * ------------------------------------------------------------------------
     */
    template<typename V>
    SIMessageConnector(const V& v)
    : Super(v), __container(v.nframes), __buffer(v.maxsmsg) {}
protected:
    /**
     * ------------------------------------------------------------------------
     * Read
     * ------------------------------------------------------------------------
     */
    Document _read() override {
        Document container(__container.capacity());
        /**
         * fill buffer
         */
        this->__res.read(__buffer.inflate());
        /**
         * split buffer
         */
        Tool::Split(__buffer, __container);
        /**
         * reset container
         */
        std::swap(__container, container);    
        /**
         * log info
         */
        INFO("DATA::IN::"
            << "n=" << container.size() 
            << "0=" << container.at(0));
        /**
         * return filled container
         */
        return std::move(container);
    }
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
};
}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Decoded & Message
 * ------------------------------------------------------------------------------------------------
 */
}}
#endif /* SIMESSAGECONNECTOR_H */
