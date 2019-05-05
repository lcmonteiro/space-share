/**
 * ------------------------------------------------------------------------------------------------
 * File:   SOMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 11, 2016, 1:25 AM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SOMESSAGECONNECTORCODED_H
#define SOMESSAGECONNECTORCODED_H
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
template<typename RESOURCE, typename SUPER>
class SOMessageConnector : public SUPER {
public:
    /**
     * ------------------------------------------------------------------------
     * Constructor
     * ------------------------------------------------------------------------
     */
    SOMessageConnector(
        const SText  address, const size_t maxsmsg 
    ) : SUPER(address), __res() {}
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
    RESOURCE __res;
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
class SOMessageConnector : public Super {
public:
    /**
     * ------------------------------------------------------------------------
     * Constructor
     * ------------------------------------------------------------------------
     */
    SOMessageConnector(
        const SText address, const size_t maxsmsg 
    ) : Super(address, maxsmsg), __buffer(maxsmsg) {}
protected:
    /**
     * ------------------------------------------------------------------------
     * Write
     * ------------------------------------------------------------------------
     */
    void _write(const Document& doc) override {
        const size_t HEADER_SIZE = 
            sizeof (reference_t)      + 
            sizeof (framecount_t) * 2  + 
            sizeof (framesize_t)
        ;
        /**
         * log info
         */
        INFO("CODE::OUT::"
            << "pos=" << doc.position()  << " " 
            << "n="   << doc.frame_count() << " "
            << "sz="  << doc.frame_size() << " " 
            << "len=" << doc.size());
        /**
         * process document
         */
        auto split = doc.split();
        for (auto& c : STools::Split(split.second.detach(), 
            __buffer.clear().inflate().isize() - HEADER_SIZE)) {
            /**
             * write context
             */
            __buffer.write(Frame().number<reference_t>(
                split.first.position()));
            __buffer.write(Frame().number<framecount_t>(
                split.first.frame_count()));
            __buffer.write(Frame().number<framecount_t>(
                c.size()));
            __buffer.write(Frame().number<framesize_t>(
                split.first.frame_size()));
            /**
             * write document
             */
            for (auto& f : c) { __buffer.write(f); }
            /**
             * write message
             */
            this->__res.drain(__buffer);
            /**
             * reuse buffer
             */
            __buffer.clear();
        }
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
#endif /* SOMESSAGECONNECTORCODED_H */
