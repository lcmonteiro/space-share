/**
 * -------------------------------------------------------------------------------------------------------------------- 
 * File:   SOFileConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 11, 2016, 1:25 AM
 * --------------------------------------------------------------------------------------------------------------------
 */
#ifndef SOFILECONNECTORCODED_H
#define SOFILECONNECTORCODED_H
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
 * Base - SOFileConnector
 * --------------------------------------------------------------------------------------------------------------------
 */
namespace Base {
/**
 */
template<typename Adapter, typename Super>
class SOFileConnector : public Super {
public:
    /**
     * ------------------------------------------------------------------------
     * constructor
     * ------------------------------------------------------------------------
     */
    SOFileConnector(
        const SText  address
    ) : Super(address), __res() {}
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
                __res.Link(this->__uri);
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
 * Layer - SOFileConnector
 * --------------------------------------------------------------------------------------------------------------------
 */
namespace Layer {
/**
 */
template<typename Super>
class SOFileConnector : public Super {
public:
    /**
     * ------------------------------------------------------------------------
     * constructor
     * ------------------------------------------------------------------------
     */
    SOFileConnector(
        const SText  address
    ) : Super(address) {}
protected:
    /**
     * ------------------------------------------------------------------------
     * write
     * ------------------------------------------------------------------------
     */
    void _Write(const Document& doc) override {

        // log info ---------------------------------------
        INFO("CODE::OUT::"
            << "pos=" << doc.Position()  << " " 
            << "n="   << doc.NumFrames() << " "
            << "sz="  << doc.Framesize() << " " 
            << "len=" << doc.size()
        );

        // write context ------------------------------
        this->__res.Drain(Frame().Number<reference_t>(
            doc.Position()));
        this->__res.Drain(Frame().Number<numframes_t>(
            doc.NumFrames()));
        this->__res.Drain(Frame().Number<numframes_t>(
            doc.size()));
        this->__res.Drain(Frame().Number<framesize_t>(
            doc.Framesize()));

        // write frames -----------------------------
        for (auto& f : doc) { this->__res.Drain(f); }
    }
};
}
/**
 * --------------------------------------------------------------------------------------------------------------------
 * End namespace Encoded & Message
 * --------------------------------------------------------------------------------------------------------------------
 */
}}
#endif /* SOFILECONNECTORCODED_H */
