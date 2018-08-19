/* 
 * File:   SIStreamConnector.h
 * Author: Luis Monteiro
 *
 * Created on June 10, 2018, 1:25 AM
 */

#ifndef SISTREAMCONNECTORCODED_H
#define SISTREAMCONNECTORCODED_H
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
class SIStreamConnector : public SInputConnector {
public:
	/**
	 * constructor
	 */
	SIStreamConnector(const string address);
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
         * -------------------------------------------------------------------------------------------------------------
	 * IO functions
	 * -------------------------------------------------------------------------------------------------------------
         * read
         */
	Document _read() override { 
                static Frame SEQ({1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233});
                /**
                 * states 
                 */
                switch(__state){
                        case 0: {
                                /**-------------------------------------------------------------------------------------
                                 * prepare start seq
                                 *------------------------------------------------------------------------------------**/
                                __buffer = IFrame(SEQ.size());
                                /**-------------------------------------------------------------------------------------
                                 * next state
                                 *------------------------------------------------------------------------------------**/
                                __state = 1;
                        }
                        case 1: {
                                /**-------------------------------------------------------------------------------------
                                 * fill sequency
                                 *------------------------------------------------------------------------------------**/
                                while (!__buffer.Full()) { __res.Fill(__buffer); }
                                /**-------------------------------------------------------------------------------------
                                 * check sequency
                                 *------------------------------------------------------------------------------------**/
                                while(__buffer != SEQ){
                                        /**-----------------------------------------------------------------------------
                                         * shift sequency
                                         *----------------------------------------------------------------------------**/
                                        __buffer.Shift(1);
                                        /**-----------------------------------------------------------------------------
                                         * fill sequency
                                         *----------------------------------------------------------------------------**/
                                        while (!__buffer.Full()) { __res.Fill(__buffer); }
                                }
                                /**-------------------------------------------------------------------------------------
                                 * next state
                                 *------------------------------------------------------------------------------------**/
                                __state = 2;
                        }
                        case 2: {
                                /**-------------------------------------------------------------------------------------
                                 * prepare header
                                 *------------------------------------------------------------------------------------**/
                                __buffer = IFrame(
                                        sizeof (reference_t) + // reference number
                                        sizeof (numframes_t) + // number of frames total
                                        sizeof (numframes_t) + // number of frames partial
                                        sizeof (framesize_t)   // size   of frames
                                );
                                /**-------------------------------------------------------------------------------------
                                 * next state
                                 *------------------------------------------------------------------------------------**/
                                __state = 3;
                        }
                        case 3: {
                                /**-------------------------------------------------------------------------------------
                                 * Fill header
                                 *------------------------------------------------------------------------------------**/
                                while (!__buffer.Full()) {
                                        __res.Fill(__buffer);
                                }
                                /**-------------------------------------------------------------------------------------
                                 * next state
                                 *------------------------------------------------------------------------------------**/
                                __state = 4;
                        }
                        case 4:	{
                                /**-------------------------------------------------------------------------------------
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
                                 * next state
                                 *------------------------------------------------------------------------------------**/
                                __state = 5;
                        }
                        case 5: {
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
                        }
                        default : {
                                /**-------------------------------------------------------------------------------------
                                 * next state
                                 *------------------------------------------------------------------------------------**/
                                __state = 0;
                        }
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
#endif /* SISTREAMCONNECTORCODED_H */
