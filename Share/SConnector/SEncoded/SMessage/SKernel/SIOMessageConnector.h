/* 
 * File:   SIOStreamConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 11, 2016, 1:25 AM
 */
#ifndef SIOSTREAMCONNECTORCODED_H
#define SIOSTREAMCONNECTORCODED_H
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
 * Begin namespace Stream
 */
namespace Stream {
/**
 */
template<class RESOURCE>
class SIOStreamConnector : public SInOutputConnector {
public:
	/**
	 * constructor
	 */
	SIOStreamConnector(const string address);
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
         * -------------------------------------------------------------------------------------------------------------
	 * IO functions
	 * -------------------------------------------------------------------------------------------------------------
         * read
         */
	Document _read() override { 
                /**-----------------------------------------------------------------------------------------------------
                 * read context
                 *------------------------------------------------------------------------------------**/
                OFrame header(move(__buffer));
                auto position = header.Read(sizeof (reference_t)).Number<reference_t>();
                auto nframest = header.Read(sizeof (numframes_t)).Number<numframes_t>();
                auto nframesp = header.Read(sizeof (numframes_t)).Number<numframes_t>();
                auto framelen = header.Read(sizeof (framesize_t)).Number<framesize_t>();
                /**-------------------------------------------------------------------------------------
                 * info
                 *------------------------------------------------------------------------------------**/
                INFO("CODE::IN::"
                        << "pos=" << position << " " 
                        << "n="	  << nframest << " " 
                        << "sz="  << nframesp << " " 
                        << "len=" << framelen
                );
                /**-------------------------------------------------------------------------------------
                 * prepare frame
                 *------------------------------------------------------------------------------------**/
                __buffer = IFrame(framelen);
                /**-------------------------------------------------------------------------------------
                 * prepare document
                 *------------------------------------------------------------------------------------**/
                __container = Document(Container(nframesp), Context(position, nframest, framelen));

                /**-------------------------------------------------------------------------------------
                 * Fill container
                 *------------------------------------------------------------------------------------**/
                for (IFrame frame; !__container.Full(); __container.push_back(move(frame))) {
                        /**-----------------------------------------------------------------------------
                         * Fill buffer
                         *----------------------------------------------------------------------------**/
                        while (!__buffer.Full()) {
                                __res.Fill(__buffer);
                        }
                        /**-----------------------------------------------------------------------------
                         * swap buffers
                         *----------------------------------------------------------------------------**/
                        frame = IFrame(__buffer.size());
                        swap(__buffer, frame);
                }
                        
                return __container;
        }
	/**
         * drain 
         */
	list<Document> _drain() override {
                /**-----------------------------------------------------------------------------------------------------
                 * info
                 *----------------------------------------------------------------------------------------------------**/
                INFO("CODE(drain)::IN::n=" << __container.size());
                /**-----------------------------------------------------------------------------------------------------
                 * next state
                 *----------------------------------------------------------------------------------------------------**/
                __state = 0;
                /**-----------------------------------------------------------------------------------------------------
                 * drain container
                 *----------------------------------------------------------------------------------------------------**/
                if(__container.empty()){
                        return {};
                }
                return {move(__container)};
        }
	/**
         * write
         */
	void _write(const Document& container) override {
                static Frame SEQ({1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233});
                /**-----------------------------------------------------------------------------------------------------
                 * write sequence
                 *----------------------------------------------------------------------------------------------------**/
                __res.Drain(SEQ);
                /**-----------------------------------------------------------------------------------------------------
                 * write context
                 *----------------------------------------------------------------------------------------------------**/
                __res.Drain(Frame(sizeof (reference_t)).Number<reference_t>(container.GetPosition()));
                __res.Drain(Frame(sizeof (numframes_t)).Number<numframes_t>(container.GetNumFrames()));
                __res.Drain(Frame(sizeof (numframes_t)).Number<numframes_t>(container.size()));
                __res.Drain(Frame(sizeof (framesize_t)).Number<framesize_t>(container.GetFrameSize()));
                /**-----------------------------------------------------------------------------------------------------
                 * info
                 *----------------------------------------------------------------------------------------------------**/
                INFO("CODE::OUT::"
                        << "pos=" << container.GetPosition() << " " << "n=" << container.GetNumFrames() << " "
                        << "sz=" << container.GetFrameSize() << " " << "len=" << container.size()
                );
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
	inline bool _good() override{
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
/**
 * End namespace Stream
 */
}
/**
 * End namespace Encoded
 */
}
#endif /* SIOSTREAMCONNECTORCODED_H */

