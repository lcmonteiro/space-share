/**
 * ------------------------------------------------------------------------------------------------
 * File:   SOFileConnector.h
 * Author: Luis Monteiro
 *
 * Created on June 6, 2018, 11:47 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SOFILECONNECTOR_H
#define SOFILECONNECTOR_H
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
 * Base - SOFileConnector
 * ------------------------------------------------------------------------------------------------
 */
namespace Base {
/**
 * @Adapter - file resource adapter
 */
template<typename Adapter, typename Super>
class SOFileConnector : public Super {
public:
    /**
     * ------------------------------------------------------------------------
     * Constructor
     * ------------------------------------------------------------------------
     */
    template<typename V>
    SOFileConnector(const V& v): Super(v.address), __res() {}
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
 * Layer - SOFileConnector
 * ------------------------------------------------------------------------------------------------
 */
namespace Layer {
/**
 */
template<typename Super>
class SOFileConnector : public Super {
public:
    /**
     * ------------------------------------------------------------------------
     * Constructor
     * ------------------------------------------------------------------------
     */
    template<typename V>
    SOFileConnector(const V& v): Super(v), __buffer() {}
protected:
    /**
     * ------------------------------------------------------------------------
     * Write
     * ------------------------------------------------------------------------
     */
    void _write(const Document& container) override {
        /**
         * log info
         */
        INFO("DATA::OUT::"
            << "(n)=" << container.size() << " " 
            << "[0]=" << container.at(0));
        /**
         * get size
         */ 
        auto size = container.number<framesize_t>();
        /**
         * fill up buffer
         */
        __buffer.clear(); 
        for(auto& c: container) {
            __buffer.reserve(c.size()).write(c);
        }    
        /**
         * resize & write buffer 
         */
        this->__res.drain(__buffer.shrink(size));
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
#endif /* SOFILECONNECTOR_H */
