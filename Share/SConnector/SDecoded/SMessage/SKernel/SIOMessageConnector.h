/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SIOMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on June 6, 2018, 11:47 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SIOMESSAGECONNECTOR_H
#define SIOMESSAGECONNECTOR_H
/**
 * Space Kernel
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
 * Begin namespace Decoded & Message
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
        const SText  address,   // con address
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
    Document _Read() override {
        Document container(__container.capacity());

        // fill buffer ------------------------------------
        __res.Read(__buffer.Expand());
        
        // split buffer -----------------------------------
        TOOL::Split(__buffer, __container);

        // reset container --------------------------------
        std::swap(__container, container);    

        // info -------------------------------------------
        INFO("DATA::IN::n=" << container.size() << "=" << container.at(0));
        
        // return filled container ------------------------
        return container;
    }
    /**
     * ------------------------------------------------------------------------
     * write
     * ------------------------------------------------------------------------
     */
    void _Write(const Document& container) override {
        // log info ---------------------------------------
        INFO("DATA::OUT::n=" <<container.size());
        
        // compress and remove buffer size ----------------
        TOOL::Join(container, __buffer.Shrink());
        
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
     * container
     */
    Document __container;
    /**
     * buffer
     */
    IOFrame __buffer;
    /**
     * resource 
     */
    RESOURCE __res;
};
}}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Decoded & Message
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SIOMESSAGECONNECTOR_H */
