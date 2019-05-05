/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SIOMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on June 6, 2018, 11:47 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SIOMESSAGECONNECTOR_H
#define SIOMESSAGECONNECTOR_H
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
 * Begin namespace Decoded & Message
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
class SIOMessageConnector : public Super {
public:
    /**
     * ------------------------------------------------------------------------
     * Constructor
     * ------------------------------------------------------------------------
     */
    template<typename V>
    SIOMessageConnector(const V& v): Super(v.address), __res() {}
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
                __res.wait(this->__uri);
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
 * End namespace Decoded & Message
 * ------------------------------------------------------------------------------------------------
 */
}}
#endif /* SIOMESSAGECONNECTOR_H */
