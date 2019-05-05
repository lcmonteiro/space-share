/**
 * ------------------------------------------------------------------------------------------------
 * File:   SIMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 11, 2016, 1:25 AM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SIMESSAGECONNECTORCODED_H
#define SIMESSAGECONNECTORCODED_H
/**
 * space
 */
#include "SContainer.h"
#include "SAddress.h"
#include "STools.h"
#include "STask.h"
#include "SText.h"
/**
 * share
 */
#include "SConnector.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Begin namespace Encoded & Message
 * ------------------------------------------------------------------------------------------------
 */
namespace Encoded {
namespace Message {
/**
 * ------------------------------------------------------------------------------------------------
 * Base - SOMessageConnector
 * ------------------------------------------------------------------------------------------------
 */
namespace Base {
/**
 */
template<typename Adapter, typename Super>
class SIMessageConnector : public Super {
public:
    /**
     * ------------------------------------------------------------------------
     * Constructor
     * ------------------------------------------------------------------------
     */
    SIMessageConnector(
        const SText  address, const size_t maxsmsg 
    ) : Super(address), __res() {}
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
template<typename Super>
class SIMessageConnector : public Super {
public:
    /**
     * ------------------------------------------------------------------------
     * Constructor
     * ------------------------------------------------------------------------
     */
    SIMessageConnector(
        const SText address, const size_t maxsmsg 
    ) : Super(address, maxsmsg), __buffer(maxsmsg) {}
protected:
    /**
     * ------------------------------------------------------------------------
     * Read
     * ------------------------------------------------------------------------
     */
    Document _read() override { 
        /**
         * read buffer
         */
        this->__res.read(__buffer.clear().inflate());
        /**
         * read context
         */
        auto position = __buffer.read(
            sizeof (reference_t)).number<reference_t>();
        auto nframest = __buffer.read(
            sizeof (framecount_t)).number<framecount_t>();
        auto nframesp = __buffer.read(
            sizeof (framecount_t)).number<framecount_t>();
        auto framelen = __buffer.read(
            sizeof (framesize_t)).number<framesize_t>();
        /**
         * read nframes
         */
        auto doc = Document(Context(position, nframest, framelen));
        doc.reserve(nframesp);
        while(!doc.full()) {
            doc.push_back(__buffer.read(framelen));
        }
        /**
         * log info
         */
        INFO("CODE::IN::" 
            << "pos=" << position << " " 
            << "n="   << nframest << " " 
            << "sz="  << nframesp << " " 
            << "len=" << framelen );
        /**
         * return document
         */
        return doc;
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
 * End namespace Encoded & Message
 * ------------------------------------------------------------------------------------------------
 */
}}
#endif /* SIMESSAGECONNECTORCODED_H */
