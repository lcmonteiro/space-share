/**
 * -------------------------------------------------------------------------------------------------------------------- 
 * File:   SIFileConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 11, 2016, 1:25 AM
 * --------------------------------------------------------------------------------------------------------------------
 */
#ifndef SIFILECONNECTORCODED_H
#define SIFILECONNECTORCODED_H
/**
 * Space Kernel
 */
#include "SContainer.h"
#include "SAddress.h"
#include "STools.h"
#include "STask.h"
#include "SText.h"
/**
 * Share Kernel
 */
#include "SConnector.h"
/**
 * --------------------------------------------------------------------------------------------------------------------
 * Begin namespace Encoded & Message
 * --------------------------------------------------------------------------------------------------------------------
 */
namespace Encoded {
namespace Message {
/**
 * --------------------------------------------------------------------------------------------------------------------
 * Base - SIFileConnector
 * --------------------------------------------------------------------------------------------------------------------
 */
namespace Base {
/**
 */
template<typename Adapter, typename Super>
class SIFileConnector : public Super {
public:
    /**
     * ------------------------------------------------------------------------
     * constructor
     * ------------------------------------------------------------------------
     */
    SIFileConnector(
        const SText  address
    ): Super(address), __res() {}
    /**
     * ------------------------------------------------------------------------
     * get resource
     * ------------------------------------------------------------------------
     */
    inline Resource& GetResource() override {
        return __res.Base();
    }
protected:
    /**
     * ------------------------------------------------------------------------
     * open
     * ------------------------------------------------------------------------
     */
    inline void _Open() override {
        std::default_random_engine eng{std::random_device{}()};
        // sleep distribution -----------------------------
        std::uniform_int_distribution<> dist{100, 1000};
        // main loop --------------------------------------
        int i = 0;
        do {
            try {
                __res.Bind(this->__uri);
                break;
            } catch (std::system_error& ex) {
                WARNING(ex.what());
            }
        } while (STask::Sleep(std::chrono::milliseconds{dist(eng) * ++i}));
    }
    /**
     * ------------------------------------------------------------------------
     * good
     * ------------------------------------------------------------------------
     */
    inline bool _Good() override {
        return __res.Good();
    }
    /**
     * ------------------------------------------------------------------------
     * close
     * ------------------------------------------------------------------------
     */
    inline void _Close() override {
        __res.Reset();
    }
    /**
     * ------------------------------------------------------------------------
     * variables
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
     * constructor
     * ------------------------------------------------------------------------
     */
    SIFileConnector(
        const SText address
    ) : Super(address) {}
protected:
    /**
     * ------------------------------------------------------------------------
     * read
     * ------------------------------------------------------------------------
     */
    Document _Read() override {
        // read context -----------------------------------
        IOFrame buf_position(sizeof (reference_t)); 
        this->__res.Fill(buf_position);
        auto position = buf_position.Number<reference_t>();

        IOFrame buf_nframest(sizeof (numframes_t)); 
        this->__res.Fill(buf_nframest);
        auto nframest = buf_nframest.Number<reference_t>();
        
        IOFrame buf_nframesp(sizeof (numframes_t)); 
        this->__res.Fill(buf_nframesp);
        auto nframesp = buf_nframesp.Number<reference_t>();
    
        IOFrame buf_framelen(sizeof (reference_t)); 
        this->__res.Fill(buf_framelen);
        auto framelen = buf_framelen.Number<reference_t>();
        
        // log info ---------------------------------------
        INFO("CODE::IN::" 
            << "pos=" << position << " " 
            << "n="   << nframest << " " 
            << "sz="  << nframesp << " " 
            << "len=" << framelen
        );
        // read nframes -----------------------------------
        Document doc(Context(position, nframest, framelen));
        doc.reserve(nframesp);
        while(!doc.full()) {
            IOFrame buf(framelen);
            this->__res.Fill(buf);
            doc.emplace_back(buf.detach());
        }
        // return document --------------------------------
        return doc;
    }
};
}
/**
 * --------------------------------------------------------------------------------------------------------------------
 * End namespace Encoded & Message
 * --------------------------------------------------------------------------------------------------------------------
 */
}}
#endif /* SIFILECONNECTORCODED_H */
