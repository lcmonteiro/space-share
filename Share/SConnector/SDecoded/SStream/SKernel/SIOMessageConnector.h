/* 
 * File:   SIOMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on June 6, 2018, 11:47 PM
 */
#ifndef SIOMESSAGECONNECTOR_H
#define SIOMESSAGECONNECTOR_H
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
class SIOMessageConnector : public SInOutputConnector {
public:
	/**
	 * constructor
	 */
	SIOMessageConnector(
		const string address,   // con address
		const size_t nframes,   // num of frames 
		const size_t maxmsgs    // max message size  
	) : SInOutputConnector(address), __container(nframes), __buffer(maxmsgs), __res() {}
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
         * -------------------------------------------------------------------------------------------------------------
	 * IO functions
	 * -------------------------------------------------------------------------------------------------------------
         * read
         */
	Container _read() override {
                /**-----------------------------------------------------------------------------------------------------
                 * Fill buffer
                 *----------------------------------------------------------------------------------------------------**/
                __res.Fill(__buffer.);
                /**-----------------------------------------------------------------------------------------------------
                 * Normalize buffer
                 *----------------------------------------------------------------------------------------------------**/
                auto size = Normalize(__buffer, __container.size());
                /**-----------------------------------------------------------------------------------------------------
                 * Fill container
                 *----------------------------------------------------------------------------------------------------**/
                while (!__container.Full()) {
                        __container.push_back(move(__buffer.Read(size)));
                }
                /**-----------------------------------------------------------------------------------------------------
                 * swap containers
                 *----------------------------------------------------------------------------------------------------**/
                Container container(__container.capacity());
                swap(__container, container);	
                /**-----------------------------------------------------------------------------------------------------
                 * info
                 *----------------------------------------------------------------------------------------------------**/
                INFO("DATA(read)::IN::n=" << container.size() << "=" << container.front());
                /**-----------------------------------------------------------------------------------------------------
                 * return filled container
                 *----------------------------------------------------------------------------------------------------**/
                return container;
        }
	/**
         * write
         */
	void _write(const Container& container) override {
                /**-----------------------------------------------------------------------------------------------------
                 * info
                 *----------------------------------------------------------------------------------------------------**/
                INFO("DATA::OUT::n=" <<container.size() << "=" << container.front());
                /**-----------------------------------------------------------------------------------------------------
                 * write nframes
                 *----------------------------------------------------------------------------------------------------**/
                for (auto& f : container) {
                        __res.Drain(f);
                }
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
                                 * wait connection
                                 *------------------------------------------------------------------------------------**/
                                __res.Wait(__uri);
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
/**
 */
#endif /* SIOMESSAGECONNECTOR_H */

