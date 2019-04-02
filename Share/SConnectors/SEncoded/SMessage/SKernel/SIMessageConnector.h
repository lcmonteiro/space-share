/**
 * -------------------------------------------------------------------------------------------------------------------- 
 * File:   SIMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 11, 2016, 1:25 AM
 * --------------------------------------------------------------------------------------------------------------------
 */
#ifndef SIMESSAGECONNECTORCODED_H
#define SIMESSAGECONNECTORCODED_H
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
 * Base - SOMessageConnector
 * --------------------------------------------------------------------------------------------------------------------
 */
namespace Base {
/**
 */
template<typename RESOURCE, typename SUPER>
class SIMessageConnector : public SUPER {
public:
    /**
     * ------------------------------------------------------------------------
     * constructor
     * ------------------------------------------------------------------------
     */
    SIMessageConnector(
        const SText  address, const size_t maxsmsg 
    ) : SUPER(address), __res() {}
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
    RESOURCE __res;
};
}
/**
 * --------------------------------------------------------------------------------------------------------------------
 * Layer - SOMessageConnector
 * --------------------------------------------------------------------------------------------------------------------
 */
namespace Layer {
/**
 */
template<typename SUPER>
class SIMessageConnector : public SUPER {
public:
    /**
     * ------------------------------------------------------------------------
     * constructor
     * ------------------------------------------------------------------------
     */
    SIMessageConnector(
        const SText address, const size_t maxsmsg 
    ) : SUPER(address, maxsmsg), __buffer(maxsmsg) {}
protected:
    /**
     * ------------------------------------------------------------------------
     * read
     * ------------------------------------------------------------------------
     */
    Document _Read() override { 
        // read buffer ------------------------------------
        this->__res.Read(__buffer.Reset().Expand());
        
        // read context -----------------------------------
        auto position = __buffer.Read(
            sizeof (reference_t)).Number<reference_t>();
        auto nframest = __buffer.Read(
            sizeof (numframes_t)).Number<numframes_t>();
        auto nframesp = __buffer.Read(
            sizeof (numframes_t)).Number<numframes_t>();
        auto framelen = __buffer.Read(
            sizeof (framesize_t)).Number<framesize_t>();

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
        while(!doc.Full()) {
            doc.push_back(__buffer.Read(framelen));
        }
        // return document --------------------------------
        return doc;
    }
    /**
     * ------------------------------------------------------------------------
     * variables
     * ------------------------------------------------------------------------
     * buffer
     */
    IOFrame __buffer;
};
}
/**
 * --------------------------------------------------------------------------------------------------------------------
 * End namespace Encoded & Message
 * --------------------------------------------------------------------------------------------------------------------
 */
}}
#endif /* SIMESSAGECONNECTORCODED_H */
