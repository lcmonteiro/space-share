/**
 * ------------------------------------------------------------------------------------------------
 * File:   SOFileConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 11, 2016, 1:25 AM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SOFILECONNECTORCODED_H
#define SOFILECONNECTORCODED_H
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
 * Base - SOFileConnector
 * ------------------------------------------------------------------------------------------------
 */
namespace Base {
/**
 */
template<typename Adapter, typename Super>
class SOFileConnector : public Super {
public:
    /**
     * ------------------------------------------------------------------------
     * Constructor
     * ------------------------------------------------------------------------
     */
    SOFileConnector(
        const SText  address
    ) : Super(address), __res() {}
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
                __res.link(this->__uri);
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
 * Layer - SOFileConnector
 * ------------------------------------------------------------------------------------------------
 */
namespace Layer {
/**
 */
template<typename Super>
class SOFileConnector : public Super {
public:
    /**
     * ------------------------------------------------------------------------
     * Constructor
     * ------------------------------------------------------------------------
     */
    SOFileConnector(
        const SText  address
    ) : Super(address) {}
protected:
    /**
     * ------------------------------------------------------------------------
     * Write
     * ------------------------------------------------------------------------
     */
    void _write(const Document& doc) override {
        /**
         * log info
         */
        INFO("CODE::OUT::"
            << "pos=" << doc.position()  << " " 
            << "n="   << doc.frame_count() << " "
            << "sz="  << doc.frame_size() << " " 
            << "len=" << doc.size());
        /**
         * write context
         */
        this->__res.drain(Frame().number<reference_t>(
            doc.position()));
        this->__res.drain(Frame().number<framecount_t>(
            doc.frame_count()));
        this->__res.drain(Frame().number<framecount_t>(
            doc.size()));
        this->__res.drain(Frame().number<framesize_t>(
            doc.frame_size()));
        /**
         * write frames
         */
        for (auto& f : doc) { this->__res.drain(f); }
    }
};
}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Encoded & Message
 * ------------------------------------------------------------------------------------------------
 */
}}
#endif /* SOFILECONNECTORCODED_H */
