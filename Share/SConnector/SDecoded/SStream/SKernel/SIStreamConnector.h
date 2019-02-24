/* 
 * File:   SIStreamConnector.h
 * Author: Luis Monteiro
 *
 * Created on June 6, 2018, 11:47 PM
 */
#ifndef SISTREAMCONNECTOR_H
#define SISTREAMCONNECTOR_H
/**
 *  Space Kernel
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
 * Begin namespace Decoded & Stream
 * ------------------------------------------------------------------------------------------------
 */
namespace Decoded {
namespace Stream  {
/**
 */
template<class RESOURCE>
class SIStreamConnector : public SInputConnector {
public:
    /**
     * constructor
     */
    SIStreamConnector(
        const SText  address,  // con address
        const size_t nframes,  // num of frames
        const size_t sframes   // size of frame
    ) : SInputConnector(address), __container(nframes), __buffer(sframes), __res() {}
    /**
     * destructor
     */
    virtual ~SIStreamConnector() = default;
    /**
     * inline overrides
     */
    inline Resource& GetResource() override {
        return __res.Base();
    }
protected:
    /**
     * --------------------------------------------------------------------------------------------
     * I functions
     * --------------------------------------------------------------------------------------------
     * read
     * ------------------------------------------------------------------------
     */
    Document _Read() override {
        IFrame buffer;
        // fill container ---------------------------------
        while (!__container.Full()) {
            
            // fill buffer --------------------------------
            __res.Fill(__buffer); 

            // reset buffers ------------------------------
            buffer = IFrame(__buffer.Capacity());
            std::swap(__buffer, buffer);

            // save buffer --------------------------------
            __container.emplace_back(std::move(buffer));
        }
        // reset container --------------------------------
        Document container(__container.capacity());
        std::swap(__container, container);    

        // info -------------------------------------------
        INFO("DATA::IN::n=" << container.size() << "=" << container.at(0));

        // return filled container ------------------------
        return container;
    }
    /**
     * ------------------------------------------------------------------------
     * drain 
     * ------------------------------------------------------------------------
     */
    std::list<Document> _Drain() override {
        Buffer tmp;
        // check if container is full ---------------------
        if (!__container.empty()) {
            auto container = Document(__container.capacity());
            std::swap(__container, container);
            tmp.Write(std::move(container));
        }
        // check if frame is full -------------------------
        if (!__buffer.Empty()) {
            auto buffer = IFrame(__buffer.Capacity());
            std::swap(__buffer, buffer);
            tmp.Write(std::move(buffer.Shrink()));
        }
        // fill container ---------------------------------
        std::list<Document> out;
        for (auto& p : Shape(tmp.Length(), __container.capacity())) {
            auto container = Document(p.first);
            while (!container.Full()) {
                container.emplace_back(tmp.Read(p.second));
            }
            out.emplace_back(std::move(container));
        }

        // info -------------------------------------------
        INFO("DATA(drain)::IN::n=" << out.size());
        
        // return filled container ------------------------
        return out;
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
    IFrame __buffer;
    /**
     * resource 
     */
    RESOURCE __res;
};
}}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Decoded & Stream
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SISTREAMCONNECTOR_H */
