/**
 * -------------------------------------------------------------------------------------------------------------------- 
 * File:   SOMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 11, 2016, 1:25 AM
 * --------------------------------------------------------------------------------------------------------------------
 */
#ifndef SOMESSAGECONNECTORCODED_H
#define SOMESSAGECONNECTORCODED_H
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
class SOMessageConnector : public SUPER {
public:
    /**
     * ------------------------------------------------------------------------
     * constructor
     * ------------------------------------------------------------------------
     */
    SOMessageConnector(
        const SText  address, const size_t maxsmsg 
    ) : SUPER(address), __res() {}
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
class SOMessageConnector : public SUPER {
public:
    /**
     * ------------------------------------------------------------------------
     * constructor
     * ------------------------------------------------------------------------
     */
    SOMessageConnector(
        const SText  address, const size_t maxsmsg 
    ) : SUPER(address, maxsmsg), __buffer(maxsmsg) {}
protected:
    /**
     * ------------------------------------------------------------------------
     * write
     * ------------------------------------------------------------------------
     */
    void _Write(const Document& doc) override {
        const size_t HEADER_SIZE = 
            sizeof (reference_t)      + 
            sizeof (numframes_t) * 2  + 
            sizeof (framesize_t)
        ;
        // log info ---------------------------------------
        INFO("CODE::OUT::"
            << "pos=" << doc.Position()  << " " 
            << "n="   << doc.NumFrames() << " "
            << "sz="  << doc.FrameSize() << " " 
            << "len=" << doc.Size()
        );
        // process document -------------------------------
        auto split = doc.Split();
        for (auto& c : STools::Split(split.second.Detach(), 
            __buffer.Reset().Expand().ISize() - HEADER_SIZE)) {

            // write context ------------------------------
            __buffer.Write(Frame().Number<reference_t>(
                split.first.Position()));
            __buffer.Write(Frame().Number<numframes_t>(
                split.first.NumFrames()));
            __buffer.Write(Frame().Number<numframes_t>(
                c.Size()));
            __buffer.Write(Frame().Number<framesize_t>(
                split.first.FrameSize()));
            
            // write document -----------------------------
            for (auto& f : c) { __buffer.Write(f); }
            
            // write message ------------------------------
            this->__res.Drain(__buffer);

            //reuse buffer --------------------------------
            __buffer.Reset();
        }
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
#endif /* SOMESSAGECONNECTORCODED_H */
