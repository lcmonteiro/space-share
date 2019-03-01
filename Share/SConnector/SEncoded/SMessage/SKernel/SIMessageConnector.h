/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SIMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 11, 2016, 1:25 AM
 * ------------------------------------------------------------------------------------------------
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
 * ------------------------------------------------------------------------------------------------
 * Begin namespace Encoded & Message
 * ------------------------------------------------------------------------------------------------
 */
namespace Encoded {
namespace Message {
/**
 * ------------------------------------------------------------------------------------------------
 * SIMessageConnector
 * ------------------------------------------------------------------------------------------------
 */
template<class RESOURCE>
class SIMessageConnector : public SInputConnector {
public:
    /**
     * constructor
     */
    SIMessageConnector(
        const SText  address,    // connection address
        const size_t maxsmsg     // max size message 
    ) : SInputConnector(address), __buffer(maxsmsg), __res() {}
    /**
     * destructor
     */
    virtual ~SIMessageConnector() = default;
    /**
     * inline overrides
     */
    inline Resource& GetResource() override {
        return __res.Base();
    }
protected:
    /**
     * --------------------------------------------------------------------------------------------
     * IO functions
     * --------------------------------------------------------------------------------------------
     * read
     * ------------------------------------------------------------------------
     */
    Document _Read() override { 
        // read buffer ------------------------------------
        __res.Read(__buffer.Expand());
        
        // read context -----------------------------------
        OFrame frame(__buffer.Detach());
        auto position = frame.Read(sizeof (reference_t)).Number<reference_t>();
        auto nframest = frame.Read(sizeof (numframes_t)).Number<numframes_t>();
        auto nframesp = frame.Read(sizeof (numframes_t)).Number<numframes_t>();
        auto framelen = frame.Read(sizeof (framesize_t)).Number<framesize_t>();

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
            doc.push_back(frame.Read(framelen));
        }
        // resuse buffer ----------------------------------
        __buffer = frame.Detach();
        
        // return document --------------------------------
        return doc;
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
                __res.Bind(__uri);
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
    IFrame __buffer;
    /**
     * resource 
     */
    RESOURCE __res;
};
}}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Encoded & Message
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SIMESSAGECONNECTORCODED_H */
