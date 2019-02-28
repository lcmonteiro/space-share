/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SIOMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 11, 2016, 1:25 AM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SIOMESSAGECONNECTORCODED_H
#define SIOMESSAGECONNECTORCODED_H
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
 * SIOMessageConnector
 * ------------------------------------------------------------------------------------------------
 */
template<class RESOURCE>
class SIOMessageConnector : public SInOutputConnector {
public:
    /**
     * constructor
     */
    SIOMessageConnector(
        const SText  address,   // connection address
        const size_t maxsmsg    // max size message 
    ) : SInOutputConnector(address), __buffer(maxsmsg), __res() {}
    /**
     * destructor
     */
    virtual ~SIOMessageConnector() = default;
    /**
     * inline overrides
     */
    inline Resource& GetResource() override {
        return __res.Base();
    }
protected:
    /**
     * ----------------------------------------------------------------------------------------
     * IO functions
     * ----------------------------------------------------------------------------------------
     * read
     * ------------------------------------------------------------------------
     */
    Document _Read() override { 
        // fill buffer ------------------------------------
        __res.Fill(__buffer.Expand());
        
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
            << "pos=" << doc.GetPosition()  << " " 
            << "n="   << doc.GetNumFrames() << " "
            << "sz="  << doc.GetFrameSize() << " " 
            << "len=" << doc.Size()
        );
        // process document -------------------------------
        auto split = doc.Split();
        for (auto& c : STools::Split(
            split.second.Detach(), __buffer.Expand().Reset().Size() - HEADER_SIZE)
        ) {
            // write context ------------------------------
            __buffer.Write(Frame().Number<reference_t>(split.first.GetPosition()));
            __buffer.Write(Frame().Number<numframes_t>(split.first.GetNumFrames()));
            __buffer.Write(Frame().Number<numframes_t>(c.Size()));
            __buffer.Write(Frame().Number<framesize_t>(split.first.GetFrameSize()));
            
            // write document -----------------------------
            for (auto& f : c) {
                __buffer.Write(f);
            }
            // write message ------------------------------
            __res.Drain(__buffer);

            //reuse buffer --------------------------------
            __buffer.Reset();
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
                __res.Wait(__uri);
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
#endif /* SIOMESSAGECONNECTORCODED_H */
