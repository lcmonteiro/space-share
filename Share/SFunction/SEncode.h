/* 
 * File:   SEncode.h
 * Author: Luis Monteiro
 *
 * Created on November 11, 2015, 9:49 AM
 */
#ifndef SENCODE_FUNCTION_H
#define	SENCODE_FUNCTION_H
/**
 * std
 */
#include <exception>
#include <algorithm>
/**
 * share
 */
#include "SKernel/SConnector.h"
#include "SKernel/SFunction.h"
#include "SKernel/SCodec.h"
/**
 */
template <class W>
class SEncodeT : public STransform<SConnector::Key, Decoded::IConnector, Container, Encoded::OConnector> {
	/**
	 * settings
	 */
	const size_t MIN = 10;
	/**
	 * define types
	 */ 
        using Super    = STransform<SConnector::Key, Decoded::IConnector, Container, Encoded::OConnector>;
        using Road     = typename Super::Road;
        using Data     = typename Super::Data;
        using Location = typename Road::Location;
        using Encoder  = CodecEncoder;
        using Walker   = W;
public:
	/**
	 * Encode
	 * @param stamp
	 * @param reduncancy
	 */
	SEncodeT(const Stamp& stamp, const uint32_t reduncancy, const uint32_t energy = 1, const uint8_t verbose = 0)
	: Super("Encode", energy, verbose), __stamp(stamp), __reduncancy(reduncancy) {
		Recover();
	}
	SEncodeT(const string& id, 
		const Stamp& stamp, const uint32_t reduncancy, const uint32_t energy = 1, const uint8_t verbose = 0
	): Super(string("Encode(") + id + ")", energy, verbose), __stamp(stamp), __reduncancy(reduncancy) {
		Recover();
	}
	/**
	 * Recover 
	 */
	void Recover() override {
		/**
		 * refresh stream position 
		 */
                __position.reset();
		/**
		 * call base recover 
		 */
		SFunction::Recover();
	}
protected:
	/*-------------------------------------------------------------------------------------------------------------*
	 * process container
	 *-------------------------------------------------------------------------------------------------------------*/
	void processData(Road& out) override {    
        }
	void processData(Data&& data, Road& out) override {
		/**
		 * create encoder
		 */
		Encoder en(move(data), __stamp);
		/**
		 * create context
		 **/
		Context ctxt (__position.next(), en.size(), en.nframesize());
		/**
		 * log
		 */
		DEBUG("encode::" << "pos=" << ctxt.GetPosition());
		/**
		 * process road until no remain load (remain > 0)
		 */
                size_t remain = max(size_t(ctxt.GetNumFrames()) + __reduncancy, MIN);
                do {
                        /**
                         * sum energy
                         */
                        size_t total = 0;
                        for (auto& o : out) {
                                total += o.second->GetEnergy();
                        }
                        /**
                         * weighted write 
                         */
                        for (auto it = out.begin(); it != out.end();) {
                                /**
                                 * data length based on energy
                                 */
                                size_t len = ceil(float(it->second->GetEnergy()) / float(total));
                                /**
                                 */
                                try {
                                        /**
                                         * write and update iterator and data
                                         */
					it->second->Write(Document(en.length(len).pop(), ctxt)); ++it; remain -= len;
                                        /**
                                         */
				} catch (ConnectorExceptionDEAD& ex) {
                                        out.Repair(it);
				} catch (ConnectorExceptionTIMEOUT& ex){
                                }    
                        } 
                } while (remain > 0);
	}
private:
	/**
	 * settings
	 */
	StampReference __stamp;
	/**
	 */
	size_t __reduncancy;
	/**
	 * runtime
	 */
        Walker __position; 
};

/**
 *----------------------------------------------------------------------------------------------------------------------
 * message context
 *----------------------------------------------------------------------------------------------------------------------
 */
namespace Message {
/**
 * walker
 */
class SWalker {
        typedef minstd_rand0 Generator;
public:
        /**
         * reset position
         */
        inline void reset() {
                __gen = Generator(__rand());
        }
        /**
         * next position
         * @return position 
         */
        inline uint32_t next() {
                return __gen();
        }
private:
        /**
         */
	Generator __gen;
	/**
	 */
	Codec::Random __rand;
};
/**
 * encoder
 */
class SEncode : public SEncodeT<SWalker> {
public:
        using SEncodeT<SWalker>::SEncodeT;
};
}
/**
 *----------------------------------------------------------------------------------------------------------------------
 * stream context
 *----------------------------------------------------------------------------------------------------------------------
 */
namespace Stream {
/**
 * walker
 */
class SWalker {
public:
        /**
         * reset position
         */
        inline void reset() {
                __position = __rand();
        }
        /**
         * next position
         * @return position 
         */
        inline uint32_t next() {
                return __position++;
        }
private:
        /**
	 * runtime
	 */
	uint32_t __position;
	/**
	 */
	Codec::Random __rand;
};
/**
 * encoder
 */
class SEncode : public SEncodeT<SWalker> {
public:
        using SEncodeT<SWalker>::SEncodeT;
};
}
#endif	/* SENCODE_FUNCTION_H */

