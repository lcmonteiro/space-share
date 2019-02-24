/* 
 * File:   SOMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on June 6, 2018, 11:47 PM
 */
#ifndef SOMESSAGECONNECTOR_H
#define SOMESSAGECONNECTOR_H
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
 */
template<class RESOURCE, class TOOL>
class SOMessageConnector : public SOutputConnector {
public:
    /**
     * constructor
     */
    SOMessageConnector(
        const SText address  // connection address
    ) : SOutputConnector(address), __buffer(), __res() {}
    /**
     * destructor
     */
    virtual ~SOMessageConnector() = default;
protected:
    /**
     * ----------------------------------------------------------------------------------------
     * O functions
     * ----------------------------------------------------------------------------------------
     * write
     * ------------------------------------------------------------------------
     */
    void _Write(const Document& container) override {
        // log info ---------------------------------------
        INFO("DATA::OUT::n=" << container.size());
        
        // compress and remove buffer size ----------------
        TOOL::Join(container, __buffer);
        
        // write buffer -----------------------------------
        __res.Drain(__buffer);
    }
    /**
     * --------------------------------------------------------------------------------------------
     * control functions
     * --------------------------------------------------------------------------------------------
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
                __res.Link(__uri);
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
private:
    /**
     * --------------------------------------------------------------------------------------------
     * variables
     * --------------------------------------------------------------------------------------------
     **
     * buffer
     */
    Frame __buffer;
    /**
     * resource 
     */
    RESOURCE __res;
};
}
}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Decoded & Message
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SOMESSAGECONNECTOR_H */

