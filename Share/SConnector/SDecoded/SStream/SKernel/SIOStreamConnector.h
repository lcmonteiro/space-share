/* 
 * File:   SIOStreamConnector.h
 * Author: Luis Monteiro
 *
 * Created on June 6, 2018, 11:47 PM
 */
#ifndef SIOSTREAMCONNECTOR_H
#define SIOSTREAMCONNECTOR_H
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
class SIOStreamConnector : public SInOutputConnector {
public:
    /**
     * constructor
     */
    SIOStreamConnector(
        const SText  address,   // con address
        const size_t nframes,   // num of frames
        const size_t sframes    // size of frame
    ) : SInOutputConnector(address), __container(nframes), __buffer(sframes), __res() {}
    /**
     * destructor
     */
    virtual ~SIOStreamConnector() = default;
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
        IFrame buffer;
        // fill container ---------------------------------
        for (;!__container.Full(); __container.push_back(move(buffer))) {
            
            // fill buffer --------------------------------
            while (!__buffer.Full()) {
                __res.Fill(__buffer);
            }
            // reset buffers ------------------------------
            buffer = IFrame(__buffer.Capacity());
            swap(__buffer, buffer);
        }
        // reset container --------------------------------
        Container container(__container.capacity());
        swap(__container, container);    

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
    std::list<Container> _Drain() override {
        Buffer tmp;

        // check if container is full ---------------------
        if (!__container.empty()) {
            auto container = Container(__container.capacity());
            swap(__container, container);
            tmp.Write(move(container));
        }
        // check if frame is full -------------------------
        if (!__buffer.Empty()) {
            auto buffer = IFrame(__buffer.Capacity());
            swap(__buffer, buffer);
            tmp.Write(move(buffer.Shrink()));
        }
        // fill container ---------------------------------
        std::list<Container> out;
        for (auto& p : Shape(tmp.Length(), __container.capacity())) {
            auto container = Container(p.first);
            while (!container.Full()) {
                container.push_back(move(tmp.Read(p.second)));
            }
            out.push_back(move(container));
        }

        // info -------------------------------------------
        INFO("DATA(drain)::IN::n=" << out.size());

        // return filled container ------------------------
        return out;
    }
    /**
     * ------------------------------------------------------------------------
     * write 
     * ------------------------------------------------------------------------
     */
    void _Write(const Container& container) override {

        // log info ---------------------------------------
        INFO("DATA::OUT::n=" <<container.size() << "=" << container.front());

        // write nframes ----------------------------------
        for (auto& f : container) {
            __res.Drain(f);
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
        std::uniform_int_distribution<> dist{1000, 5000};
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
    Container __container;
    /**
     * buffer
     */
    IFrame __buffer;
    /**
     * resource 
     */
    RESOURCE __res;
};
}
}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Decoded & Stream
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SIOSTREAMCONNECTOR_H */
