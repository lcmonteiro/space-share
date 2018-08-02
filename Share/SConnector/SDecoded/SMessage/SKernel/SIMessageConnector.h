/* 
 * Container:   SIMessageConnector.h
 * Author:      Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SIMESSAGECONNECTOR_H
#define SIMESSAGECONNECTOR_H
/**
 * Space
 */
#include "SKernel/SContainer.h"
#include "SKernel/SAddress.h"
#include "SKernel/SConnector.h"
#include "SKernel/STask.h"
/**
 * Begin namespace Decoded
 */
namespace Decoded {
/**
 * Begin namespace Message
 */
namespace Message {
/**
 */
template<class RESOURCE>
class SIMessageConnector : public SInputConnector {
public:
	/**
	 * constructor
	 */
	SIMessageConnector(
		const string address, 
		const string local,
		const size_t nframes,
                const size_t imax = 1500
	);
	/**
	 * destructor
	 */
	virtual ~SIMessageConnector() = default;
	/**
	 * inline overrides
	 */
	inline Resource& GetResource() override {
		return __res;
	}
protected:
	/**
         * -------------------------------------------------------------------------------------------------------------
	 * IO functions
	 * -------------------------------------------------------------------------------------------------------------
         * read
         */
        inline Container _read() override {
                /**-----------------------------------------------------------------------------------------------------
                 * Fill container
                 *----------------------------------------------------------------------------------------------------**/
                __res.Fill(__buffer);
                /**-----------------------------------------------------------------------------------------------------
                 * Fill container
                 *----------------------------------------------------------------------------------------------------**/
                list<Container> out;
                for (auto& p : Shape(__buffer.Length(), __container.capacity())) {
                        auto container = Container(p.first);
                        while (!container.Full()) {
                                container.push_back(move(__buffer.Read(p.second)));
                        }
                        out.push_back(move(container));
                }
                /**-----------------------------------------------------------------------------------------------------
                 * info
                 *----------------------------------------------------------------------------------------------------**/
                INFO("DATA(drain)::IN::n=" << out.size());
                /**-----------------------------------------------------------------------------------------------------
                 * return filled containers
                 *----------------------------------------------------------------------------------------------------**/
                return out;
        }
	/**
         * -------------------------------------------------------------------------------------------------------------
	 * control functions
	 * -------------------------------------------------------------------------------------------------------------
         * open
         */
        inline void _open() override {
                default_random_engine eng{random_device{}()};
                /** 
                 */
                uniform_int_distribution<> dist{1000, 5000};
                /**-----------------------------------------------------------------------------------------------------
                 * main loop
                 *----------------------------------------------------------------------------------------------------**/
                int i = 0;
                do {
                        try {
                                /**-------------------------------------------------------------------------------------
                                 * connect
                                 *------------------------------------------------------------------------------------**/
                                __res.Connect(__uri);
                                break;
                        } catch (system_error& ex) {
                                WARNING(ex.what());
                        }
                        /**---------------------------------------------------------------------------------------------
                         * random sleep
                         *--------------------------------------------------------------------------------------------**/
                } while (STask::Sleep(chrono::milliseconds{dist(eng) + (1000 * i++)}));
        }
	/**
	 * good
	 */
	inline bool _good() override {
                /**-----------------------------------------------------------------------------------------------------
                 * verify resource status
                 *----------------------------------------------------------------------------------------------------**/
		return __res.Good();
	}
        /**
         * close
         */
	inline void _close() override {
                /**-----------------------------------------------------------------------------------------------------
                 * reset resource
                 *----------------------------------------------------------------------------------------------------**/
		__res.Reset();
	}
private:
	/**
	 * local address
	 */
	Address __local;
	/**
	 * container
	 */
	Container __container;
	/**
         * buffer
         */
	Buffer __buffer;
	/**
	 * resource 
	 */
	RESOURCE __res;
};
/**
 * End namespace Message
 */
}
/**
 * End namespace Decoded
 */
}
#endif /* SIMESSAGECONNECTORSOCKET_H */

