/* 
 * File:   SIOMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 11, 2016, 1:25 AM
 */
#ifndef SIOMESSAGECONNECTORCODED_H
#define SIOMESSAGECONNECTORCODED_H
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
 */
template<class RESOURCE>
class SIOMessageConnector : public SInOutputConnector {
public:
	/**
	 * constructor
	 */
	SIOMessageConnector(
                const string address,   // connection address
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
         * -------------------------------------------------------------------------------------------------------------
	 * IO functions
	 * -------------------------------------------------------------------------------------------------------------
         * read
         */
	Document _read() override { 
                /**-----------------------------------------------------------------------------------------------------
                 * Fill buffer
                 *----------------------------------------------------------------------------------------------------**/
                __res.Fill(__buffer.Expand());
                /**-----------------------------------------------------------------------------------------------------
                 * read context
                 *----------------------------------------------------------------------------------------------------**/
                OFrame frame(move(__buffer));
                auto position = frame.Read(sizeof (reference_t)).Number<reference_t>();
                auto nframest = frame.Read(sizeof (numframes_t)).Number<numframes_t>();
                auto nframesp = frame.Read(sizeof (numframes_t)).Number<numframes_t>();
                auto framelen = frame.Read(sizeof (framesize_t)).Number<framesize_t>();
                /**-----------------------------------------------------------------------------------------------------
                 * log
                 *----------------------------------------------------------------------------------------------------**/
                INFO("CODE::IN::" 
                        << "pos=" << position << " " 
                        << "n="   << nframest << " " 
                        << "sz="  << nframesp << " " 
                        << "len=" << framelen
                );
                /**-----------------------------------------------------------------------------------------------------
                 * read nframes
                 *----------------------------------------------------------------------------------------------------**/
                Document container(Context(position, nframest, framelen));
                container.reserve(nframesp);
                while(!container.Full()){
                        container.push_back(frame.Read(framelen));
                }
                /**-----------------------------------------------------------------------------------------------------
                 * reuse buffer
                 *----------------------------------------------------------------------------------------------------**/
                __buffer = move(frame);
                /**-----------------------------------------------------------------------------------------------------
                 * return container
                 *----------------------------------------------------------------------------------------------------**/
                return container;
        }
	/**
         * write
         */
	void _write(const Document& container) override {
                const size_t HEADER_SIZE = sizeof (reference_t) + sizeof (numframes_t) * 2  + sizeof (framesize_t);
                /**-----------------------------------------------------------------------------------------------------
                 * log info
                 *----------------------------------------------------------------------------------------------------**/
                INFO("CODE::OUT::"
                        << "pos=" << container.GetPosition()  << " " 
                        << "n="   << container.GetNumFrames() << " "
                        << "sz="  << container.GetFrameSize() << " " 
                        << "len=" << container.size()
                );
                /**-----------------------------------------------------------------------------------------------------
                 * process container
                 *----------------------------------------------------------------------------------------------------**/
                __buffer.Expand();
                for (auto& c : STools::Split(move(container), __buffer.Size() - HEADER_SIZE)) {
                        IFrame msg(move(__buffer));
                        /**---------------------------------------------------------------------------------------------
                         * write context
                         *--------------------------------------------------------------------------------------------**/
                        msg.Write(Frame(sizeof (reference_t)).Number<reference_t>(container.GetPosition()));
                        msg.Write(Frame(sizeof (numframes_t)).Number<numframes_t>(container.GetNumFrames()));
                        msg.Write(Frame(sizeof (numframes_t)).Number<numframes_t>(c.size()));
                        msg.Write(Frame(sizeof (framesize_t)).Number<framesize_t>(container.GetFrameSize()));
                        /**---------------------------------------------------------------------------------------------
                         * write container
                         *--------------------------------------------------------------------------------------------**/
                        for (auto& f : container) {        
                                msg.Write(f);
                        }
                        /**---------------------------------------------------------------------------------------------
                         * write message
                         *--------------------------------------------------------------------------------------------**/
                        __res.Drain(msg);
                        /**---------------------------------------------------------------------------------------------
                         * reuse buffer
                         *--------------------------------------------------------------------------------------------**/
                        (__buffer = move(msg)).Expand();
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
         * buffer
         */
	IFrame __buffer;
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
 * End namespace Encoded
 */
}
#endif /* SIOMESSAGECONNECTORCODED_H */
