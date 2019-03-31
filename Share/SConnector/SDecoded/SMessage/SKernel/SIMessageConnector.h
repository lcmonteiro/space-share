/**
 * -------------------------------------------------------------------------------------------------------------------- 
 * File:   SIMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on June 6, 2018, 11:47 PM
 * --------------------------------------------------------------------------------------------------------------------
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
 * --------------------------------------------------------------------------------------------------------------------
 * Begin namespace Decoded
 * --------------------------------------------------------------------------------------------------------------------
 */
namespace Decoded {
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
    template<typename V>
    SIMessageConnector(const V& v): SUPER(v.address), __res() {}
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
template<typename TOOL, typename SUPER>
class SIMessageConnector : public SUPER {
public:
    /**
     * ------------------------------------------------------------------------
     * constructor
     * ------------------------------------------------------------------------
     */
    template<typename V>
    SIMessageConnector(const V& v)
    : SUPER(v), __container(v.nframes), __buffer(v.maxsmsg) {}
protected:
    /**
     * ------------------------------------------------------------------------
     * read
     * ------------------------------------------------------------------------
     */
    Document _Read() override {
        Document container(__container.capacity());

        // fill buffer ------------------------------------
        this->__res.Read(__buffer.Expand());
        
        // split buffer -----------------------------------
        TOOL::Split(__buffer, __container);

        // reset container --------------------------------
        std::swap(__container, container);    

        // info -------------------------------------------
        INFO("DATA::IN::"
            << "n=" << container.size() 
            << "0=" << container.at(0));
        
        // return filled container ------------------------
        return std::move(container);
    }
    /**
     * ------------------------------------------------------------------------
     * variables
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
 * --------------------------------------------------------------------------------------------------------------------
 * End namespace Decoded & Message
 * --------------------------------------------------------------------------------------------------------------------
 */
}}
#endif /* SIMESSAGECONNECTOR_H */
