/* 
 * File:   SIOMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on June 6, 2018, 11:47 PM
 */
#ifndef SIOMESSAGECONNECTOR_H
#define SIOMESSAGECONNECTOR_H
/**
 * Space Kernel
 */
#include "SContainer.h"
#include "SAddress.h"
#include "STask.h"
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
class SIOMessageConnector : public SInOutputConnector {
public:
    /**
     * constructor
     */
    SIOMessageConnector(
        const string address,   // con address
        const size_t nframes,   // num of frames 
        const size_t maxsmsg    // max size message  
    ) : SInOutputConnector(address), __container(nframes), __buffer(maxsmsg), __res() {}
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
     * --------------------------------------------------------------------------------------------
     * IO functions
     * --------------------------------------------------------------------------------------------
     * read
     * ------------------------------------------------------------------------
     */
    Container _Read() override {
        Container container(__container.capacity());

        // fill buffer ------------------------------------
        __res.Fill(__buffer.Expand());
        
        // split buffer -----------------------------------
        TOOL::Split(__buffer, __container);

        // reset container --------------------------------
        swap(__container, container);    

        // info -------------------------------------------
        INFO("DATA(read)::IN::n=" << container.size() << "=" << container.front());
        
        // return filled container ------------------------
        return container;
    }
    /**
     * ------------------------------------------------------------------------
     * write
     * ------------------------------------------------------------------------
     */
    void _Write(const Container& container) override {
        // log info ---------------------------------------
        INFO("DATA::OUT::n=" <<container.size());
        
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
        default_random_engine eng{random_device{}()};
        // sleep distribution -----------------------------
        uniform_int_distribution<> dist{100, 1000};
        // main loop --------------------------------------
        int i = 0;
        do {
            try {
                __res.Wait(__uri);
                break;
            } catch (system_error& ex) {
                WARNING(ex.what());
            }
        } while (STask::Sleep(chrono::milliseconds{dist(eng) * ++i}));
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
     * container
     */
    Container __container;
    /**
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
#endif /* SIOMESSAGECONNECTOR_H */

