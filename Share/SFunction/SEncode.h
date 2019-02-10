/**
 * ------------------------------------------------------------------------------------------------
 * File:   SEncode.h
 * Author: Luis Monteiro
 *
 * Created on November 11, 2015, 9:49 AM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SENCODE_FUNCTION_H
#define SENCODE_FUNCTION_H
/**
 * C++ 
 */
#include <exception>
#include <algorithm>
/**
 * Share Kernel
 */
#include "SConnector.h"
#include "SFunction.h"
#include "SCodec.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Encoder Template
 * @MIM = minimun redundancy
 * ------------------------------------------------------------------------------------------------
 */
template <class WALKER, size_t MIN = 10>
class SEncodeT : public SFunctionSpread<
    SConnector::Key, Decoded::IConnector, Decoded::Document, Encoded::OConnector> {
    /**
     * super class
     */ 
    using Super = SFunctionSpread<
        SConnector::Key, Decoded::IConnector, Decoded::Document, Encoded::OConnector
    >;
    /**
     * helpers
     */
    using ORoad    = typename Super::ORoad;
    using Data     = typename Super::Data;
    using Location = typename ORoad::Location;
    using Encoder  = CodecEncoder;
    using Walker   = WALKER;
public:
    /**
     * ------------------------------------------------------------------------
     * Encode
     * @param stamp
     * @param redundancy
     * ------------------------------------------------------------------------
     */
    SEncodeT(
        const Stamp& stamp, const uint32_t redundancy, const uint32_t energy = 1, const uint8_t verbose = 0
    ): Super("Encode", energy, verbose), __stamp(stamp), __redundancy(redundancy) {
        Recover();
    }
    SEncodeT(const string& id, 
        const Stamp& stamp, const uint32_t redundancy, const uint32_t energy = 1, const uint8_t verbose = 0
    ): Super(string("Encode(") + id + ")", energy, verbose), __stamp(stamp), __redundancy(redundancy) {
        Recover();
    }
    /**
     * ------------------------------------------------------------------------
     * Recover 
     * ------------------------------------------------------------------------
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
    /**
     * ------------------------------------------------------------------------
     * process Data
     *-------------------------------------------------------------------------
     */
    void processData(ORoad& out) override {    
    }
    void processData(Data&& data, ORoad& out) override {
	    /**
	     * create encoder
	     */
	    Encoder en(std::move(data), __stamp);
	    /**
	     * create context
	     **/
	    Encoded::Context ctxt (__position.next(), en.size(), en.nframesize());
	    /**
	     * log
	     */
	    DEBUG("encode::" << "pos=" << ctxt.GetPosition());
	    /**
	     * process road until no remain load (remain > 0)
	     */
	    size_t remain = std::max(size_t(ctxt.GetNumFrames()) + __redundancy, MIN);
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
	            size_t len = std::ceil(float(it->second->GetEnergy()) / float(total));
	            try {
                    /**
                     * write and update iterator and data
                     */
                    it->second->Write(Encoded::Document(en.length(len).pop(), ctxt)); 
                    /**
                     * update references
                     */
                    ++it; remain -= len;
		        } catch (ConnectorExceptionDEAD& ex) {
		            out.Exception(it);
		        } catch (ConnectorExceptionTIMEOUT& ex){
	            }    
            } 
	    } while (remain > 0);
	}
private:
    /**
     * ------------------------------------------------------------------------
     * variables
     * ------------------------------------------------------------------------
     **
     * stamp
     */
    StampReference __stamp;
    /**
     * redundancy
     */
    size_t __redundancy;
    /**
     * position flow 
     */
    Walker __position; 
};
/**
 *-------------------------------------------------------------------------------------------------
 * message context
 *-------------------------------------------------------------------------------------------------
 */
namespace Message {
/**
 * ----------------------------------------------------------------------------
 * walker
 * ----------------------------------------------------------------------------
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
 * ----------------------------------------------------------------------------
 * encoder
 * ----------------------------------------------------------------------------
 */
class SEncode : public SEncodeT<SWalker> {
public:
    using SEncodeT<SWalker>::SEncodeT;
};
}
/**
 *-------------------------------------------------------------------------------------------------
 * stream context
 *-------------------------------------------------------------------------------------------------
 */
namespace Stream {
/**
 * ----------------------------------------------------------------------------
 * walker
 * ----------------------------------------------------------------------------
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
 * ----------------------------------------------------------------------------
 * encoder
 * ----------------------------------------------------------------------------
 */
class SEncode : public SEncodeT<SWalker> {
public:
    using SEncodeT<SWalker>::SEncodeT;
};
}
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */
#endif    /* SENCODE_FUNCTION_H */

