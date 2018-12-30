/* 
 * File:   SIMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 11, 2016, 1:25 AM
 */
#ifndef SIMESSAGECONNECTORCODED_H
#define SIMESSAGEONNECTORCODED_H
/**
 * Space
 */
#include "SKernel/SContainer.h"
#include "SKernel/SAddress.h"
#include "SKernel/SConnector.h"
#include "SKernel/STask.h"
/**
 * Begin namespace Encoded
 */
namespace Encoded {
/**
 * Begin namespace Message
 */
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
        const string address,   // connection address
        const size_t maxsmsg    // max size message 
    ) : SInOutputConnector(address), __buffer(maxsmsg), __res() {}
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
       // fill buffer ------------------------------------
        __res.Fill(__buffer.Expand());
        // read context -----------------------------------
        OFrame frame(move(__buffer));
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
        Document container(Context(position, nframest, framelen));
        container.reserve(nframesp);
        while(!container.Full()){
            container.push_back(frame.Read(framelen));
        }
        // resuse buffer ----------------------------------
        __buffer = move(frame);
        // return container -------------------------------
        return container;
    }
    /**
     * --------------------------------------------------------------------------------------------
     * control functions
     * --------------------------------------------------------------------------------------------
     * open
     * ------------------------------------------------------------------------
     */
    inline void _Open() override {
        default_random_engine eng{random_device{}()};
        // sleep distribution ----------------------------- 
        uniform_int_distribution<> dist{1000, 5000};
        // main loop --------------------------------------
        int i = 0;
        do {
            try {
                __res.Connect(__uri);
                break;
            } catch (system_error& ex) {
                WARNING(ex.what());
            }
        } while (STask::Sleep(chrono::milliseconds{dist(eng) + (1000 * i++)}));
     }
    /**
     * ------------------------------------------------------------------------
     * good
     * ------------------------------------------------------------------------
     */
    inline bool _Good() override{
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
     * buffer
     */
    IFrame __buffer;
    /**
     * resource 
	 * resource 
     * resource 
     */
    RESOURCE __res;
};
/**
 * End namespace Message
 */
}
/**
 * End namespace Encoded
 */
}
#endif /* SIMESSAGECONNECTORCODED_H */
