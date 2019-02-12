/* 
 * File:   SOStreamConnector.h
 * Author: Luis Monteiro
 *
 * Created on June 11, 2018, 1:34 AM
 */
#ifndef SOSTREAMCONNECTOR_H
#define SOSTREAMCONNECTOR_H
/**
 *  Space Kernel
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
 * Begin namespace Decoded & Stream
 * ------------------------------------------------------------------------------------------------
 */
namespace Decoded {
namespace Stream  {
/**
 */
template<class RESOURCE>
class SOStreamConnector : public SOutputConnector {
public:
    /**
     * constructor
     */
    SOStreamConnector(
        const SText address // connection address
    ) : SOutputConnector(address), __res() {}
    /**
     * destructor
     */
    virtual ~SOStreamConnector() = default;
    /**
     */
protected:
    /**
     * ----------------------------------------------------------------------------------------
     * O functions
     * ----------------------------------------------------------------------------------------
     * write
     * ------------------------------------------------------------------------
     */
    void _Write(const Container& container) override {

        // log info ---------------------------------------
        INFO("DATA::OUT::n=" << container.size() << "=" << container.front());

        // write nframes ----------------------------------
        for (auto& f : container) {
            __res.Drain(f);
        }
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
     * resource
     */
    RESOURCE __res;
};
}
}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Decoded & Stream
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SOSTREAMCONNECTOR_H */

