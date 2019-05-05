/**
 * ------------------------------------------------------------------------------------------------
 * File:   SOMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on June 6, 2018, 11:47 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SOMESSAGECONNECTOR_H
#define SOMESSAGECONNECTOR_H
/**
 * space
 */
#include "SContainer.h"
#include "SAddress.h"
#include "STask.h"
#include "SText.h"
/**
 * share
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
 * @Adapter - file resource adapter
 */
template<typename Adapter, typename Super>
class SOMessageConnector : public Super {
public:
    /**
     * ------------------------------------------------------------------------
     * Constructor
     * ------------------------------------------------------------------------
     */
    template<typename V>
    SOMessageConnector(const V& v): Super(v.address), __res() {}
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
                __res.link(this->__uri);
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
template<class Tool, typename Super>
class SOMessageConnector : public Super {
public:
    /**
     * ------------------------------------------------------------------------
     * Constructor
     * ------------------------------------------------------------------------
     */
    template<typename V>
    SOMessageConnector(const V& v): Super(v), __buffer() {}
protected:
    /**
     * ------------------------------------------------------------------------
     * Write
     * ------------------------------------------------------------------------
     */
    void _write(const Document& container) override {
        /**
         *  log info
         */
        INFO("DATA::OUT::n=" << container.size());
        /**
         * compress and write buffer
         */
        this->__res.drain(Tool::Join(container, __buffer));
    }   
    /**
     * ------------------------------------------------------------------------
     * Variables
     * ------------------------------------------------------------------------
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
#endif /* SOMESSAGECONNECTOR_H */
