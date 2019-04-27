/**
 * --------------------------------------------------------------------------------------------------------------------
 * File:   SIFileConnector.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 * --------------------------------------------------------------------------------------------------------------------
 */
#ifndef SIFILECONNECTOR_H
#define SIFILECONNECTOR_H
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
 * Base - SIFileConnector
 * --------------------------------------------------------------------------------------------------------------------
 */
namespace Base {
/**
 * @Adpter - file resource adapter
 */
template<typename Adapter, typename Super>
class SIFileConnector : public Super {
public:
    /**
     * ------------------------------------------------------------------------
     * constructor
     * ------------------------------------------------------------------------
     */
    template<typename V>
    SIFileConnector(const V& v): Super(v.address), __res() {}
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
     * resource adapter 
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
    template<typename V>
    SIFileConnector(const V& v)
    : Super(v), __container(v.nframes) {}
protected:
    /**
     * --------------------------------------------------------------------------------------------
     * read
     * --------------------------------------------------------------------------------------------
     */
    Document _Read() override {
        // output container ---------------------------------------------------
        auto out = Document(__container.capacity());

        // process chunk size -------------------------------------------------
        auto res = std::div(
            static_cast<int>(this->__res.size() + sizeof (framesize_t)), 
            static_cast<int>(__container.capacity())
        );
        // normalize frame size -----------------------------------------------
        auto size = ((res.rem > 0) ? (res.quot + 1) : (res.quot));
        
        // container fill up --------------------------------------------------
        try {
            while(!out.full()) {
                IOFrame aux (size);
                this->__res.Read(aux);
                out.emplace_back(aux.Expand(size));
            }
        } catch(...) {
            if(out.empty()) {
                throw;
            }
            while(!out.full()) {
                Frame aux (size, size);
                out.emplace_back(aux.detach());
            }
        }
        // insert size --------------------------------------------------------
        out.Number<framesize_t>(this->__res.size());

        // log info -----------------------------------------------------------
        INFO("DATA::IN::"
            << "(n)=" << out.size() << " " << "[0]=" << out.at(0));

        // return filled document --------------------------------------------
        return out.detach();
    }
    /**
     * ------------------------------------------------------------------------
     * variables
     * ------------------------------------------------------------------------
     **
     * container
     */
    Document __container;
};
}
/**
 * --------------------------------------------------------------------------------------------------------------------
 * End namespace Decoded & Message
 * --------------------------------------------------------------------------------------------------------------------
 */
}}
#endif /* SIFILECONNECTORSOCKET_H */

