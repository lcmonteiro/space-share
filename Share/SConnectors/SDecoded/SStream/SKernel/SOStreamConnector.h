/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SOStreamConnector.h
 * Author: Luis Monteiro
 *
 * Created on June 11, 2018, 1:34 AM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SOSTREAMCONNECTOR_H
#define SOSTREAMCONNECTOR_H
/**
 *  space
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
 * Begin namespace Decoded & Stream
 * ------------------------------------------------------------------------------------------------
 */
namespace Decoded {
namespace Stream  {
/**
 */
template<class Adapter>
class SOStreamConnector : public SOutputConnector {
public:
    /**
     * ------------------------------------------------------------------------
     * Constructor
     * ------------------------------------------------------------------------
     */
    SOStreamConnector(
        const SText address) 
    : SOutputConnector(address), 
    __res() {}
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
        INFO("DATA::OUT::n=" << container.size() << "=" << container.at(0));
        /**
         * write nframes
         */
        for (auto& f : container) {
            __res.drain(f);
        }
    }
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
                __res.link(__uri);
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
private:
    /**
     * ------------------------------------------------------------------------
     * Variables
     * ------------------------------------------------------------------------
     **
     * resource
     */
    Adapter __res;
};
}}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Decoded & Stream
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SOSTREAMCONNECTOR_H */

