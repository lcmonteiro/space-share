/**
 * ------------------------------------------------------------------------------------------------
 * File:   SIFileConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 11, 2016, 1:25 AM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SIFILECONNECTORCODED_H
#define SIFILECONNECTORCODED_H
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
 * Base - SIFileConnector
 * ------------------------------------------------------------------------------------------------
 */
namespace Base {
/**
 */
template<typename Adapter, typename Super>
class SIFileConnector : public Super {
public:
    /**
     * ------------------------------------------------------------------------
     * Constructor
     * ------------------------------------------------------------------------
     */
    SIFileConnector(
        const SText address
    ): Super(address), __res() {}
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
 * --------------------------------------------------------------------------------------------------------------------
 * Layer - SIFileConnector
 * --------------------------------------------------------------------------------------------------------------------
 */
namespace Layer {
/**
 */
template<typename Super>
class SIFileConnector : public Super {
public:
    /**
     * ------------------------------------------------------------------------
     * Constructor
     * ------------------------------------------------------------------------
     */
    SIFileConnector(
        const SText address
    ) : Super(address) {}
protected:
    /**
     * ------------------------------------------------------------------------
     * Read
     * ------------------------------------------------------------------------
     */
    Document _read() override {
        /**
         * read context
         */
        IOFrame buf_position(sizeof (reference_t)); 
        this->__res.fill(buf_position);
        auto position = buf_position.number<reference_t>();

        IOFrame buf_nframest(sizeof (framecount_t)); 
        this->__res.fill(buf_nframest);
        auto nframest = buf_nframest.number<reference_t>();
        
        IOFrame buf_nframesp(sizeof (framecount_t)); 
        this->__res.fill(buf_nframesp);
        auto nframesp = buf_nframesp.number<reference_t>();
    
        IOFrame buf_framelen(sizeof (reference_t)); 
        this->__res.fill(buf_framelen);
        auto framelen = buf_framelen.number<reference_t>();
        /**
         * read nframes
         */
        auto doc = Document(Context(position, nframest, framelen));
        doc.reserve(nframesp);
        while(!doc.full()) {
            IOFrame buf(framelen);
            this->__res.fill(buf);
            doc.emplace_back(buf.detach());
        }
        /**
         * log info
         */
        INFO("CODE::IN::" 
            << "pos=" << position << " " 
            << "n="   << nframest << " " 
            << "sz="  << nframesp << " " 
            << "len=" << framelen);
        /**
         * return document
         */
        return doc;
    }
};
}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Encoded & Message
 * ------------------------------------------------------------------------------------------------
 */
}}
#endif /* SIFILECONNECTORCODED_H */
