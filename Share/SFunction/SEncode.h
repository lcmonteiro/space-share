/**
 * --------------------------------------------------------------------------------------------------------------------
 * File:   SEncode.h
 * Author: Luis Monteiro
 *
 * Created on November 11, 2015, 9:49 AM
 * --------------------------------------------------------------------------------------------------------------------
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
 * --------------------------------------------------------------------------------------------------------------------
 * Encoder Template
 * @MIM = minimun redundancy
 * --------------------------------------------------------------------------------------------------------------------
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
    using ORoad     = typename Super::ORoad;
    using Data      = typename Super::Data;
    using Location  = typename ORoad::Location;
    using Encoder   = CodecEncoder;
    using Walker    = WALKER;
    using Generator = std::minstd_rand0;
    using Random    = std::random_device;
public:
    /**
     * --------------------------------------------------------------------------------------------
     * Encode
     * @param stamp
     * @param redundancy
     * --------------------------------------------------------------------------------------------
     */
    SEncodeT(
        SharedStamp stamp, uint32_t redundancy, uint32_t energy = 1, uint8_t verbose = 0
    ): Super("Encode", energy, verbose), __stamp(stamp), __redundancy(redundancy) {
        Recover();
    }
    SEncodeT(const string& id, 
        SharedStamp stamp, uint32_t redundancy, uint32_t energy = 1, uint8_t verbose = 0
    ): Super(string("Encode(") + id + ")", energy, verbose), __stamp(stamp), __redundancy(redundancy) {
        Recover();
    }
    /**
     * --------------------------------------------------------------------------------------------
     * Recover 
     * --------------------------------------------------------------------------------------------
     */
    void Recover() override {
        // refresh stream position ------------------------
        __position.reset();

        // call base recover ------------------------------ 
        SFunction::Recover();
    }
protected:
    /**
     * --------------------------------------------------------------------------------------------
     * process Data
     *---------------------------------------------------------------------------------------------
     */
    void processData(ORoad& out) override {    
    }
    void processData(Data&& data, ORoad& out) override {
        Random rd;
        Generator gen(rd());
	     
        // create encoder ----------------------------------------------------
	    Encoder en(std::move(data), __stamp);

	    // create context ----------------------------------------------------
	    Encoded::Context ctxt (__position.next(), en.size(), en.FrameSize());

	    // log ----------------------------------------------------------------
	    DEBUG("encode::" << "pos=" << ctxt.Position());

	    // init remain with num of frames -------------------------------------
	    size_t remain = std::max(
            size_t(ctxt.NumFrames()) + __redundancy, MIN);

	    // process road until no remain load (remain > 0) ---------------------
        while (remain > 0) {

            // weights --------------------------------------------------------
	        std::vector<size_t> wgt;
            wgt.reserve(out.size());
	        for (auto& o : out) { wgt.emplace_back(o.second->GetEnergy()); }

            // quantities -----------------------------------------------------
            std::discrete_distribution<> d(wgt.begin(), wgt.end());
            std::vector<size_t> qty;
            qty.resize(wgt.size());
            for (auto i = 0; i < remain; ++i) { ++qty[d(gen)]; }

	        // weighted write -------------------------------------------------
            auto o = out.begin();
	        for (auto q = qty.begin(); qty.end() != q; ++q) {
	            try {
                    // write and update iterator and data ---------------------
                    o->second->Write(
                        Encoded::Document(en.NumFrames(*q).pop(), ctxt)); 
                    // update references --------------------------------------
                    ++o; remain -= *q;
		        } catch (ConnectorExceptionTIMEOUT& ex) {
                    ++o;
	            } catch (ConnectorExceptionDEAD& ex) {
		            out.Exception(o);
		        }    
            }
	    }
	}
private:
    /**
     * ------------------------------------------------------------------------
     * variables
     * ------------------------------------------------------------------------
     **
     * stamp
     */
    SharedStamp __stamp;
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
 *---------------------------------------------------------------------------------------------------------------------
 * Message context
 *---------------------------------------------------------------------------------------------------------------------
 */
namespace Message {
/**
 * ------------------------------------------------------------------------------------------------
 * Walker
 * ------------------------------------------------------------------------------------------------
 */
class SWalker {
    using Generator = std::minstd_rand0;
    using Random    = std::random_device;
public:
    /**
     * ----------------------------------------------------
     * reset position
     * ----------------------------------------------------
     */
    inline void reset() {
        __gen = Generator(__rand());
    }
    /**
     * ----------------------------------------------------
     * next position
     * @return position 
     * ----------------------------------------------------
     */
    inline uint32_t next() {
        return __gen();
    }
private:
    /**
     * ----------------------------------------------------
     * variables
     * ----------------------------------------------------
     * genetor
     */
    Generator __gen;
    /**
     * random
     */
    Random __rand;
};
/**
 * ------------------------------------------------------------------------------------------------
 * Encoder
 * ------------------------------------------------------------------------------------------------
 */
class SEncode : public SEncodeT<SWalker> {
public:
    using SEncodeT<SWalker>::SEncodeT;
};
}
/**
 *---------------------------------------------------------------------------------------------------------------------
 * Stream context
 *---------------------------------------------------------------------------------------------------------------------
 */
namespace Stream {
/**
 * ------------------------------------------------------------------------------------------------
 * Walker
 * ------------------------------------------------------------------------------------------------
 */
class SWalker {
    using Random = std::random_device;
public:
    /**
     * ----------------------------------------------------
     * reset position
     * ----------------------------------------------------
     */
    inline void reset() {
        __position = __rand();
    }
    /**
     * ----------------------------------------------------
     * next position
     * @return position 
     * ----------------------------------------------------
     */
    inline uint32_t next() {
        return __position++;
    }
private:
    /**
     * ----------------------------------------------------
     * variables
     * ----------------------------------------------------
     */
    uint32_t __position;
    /**
     * random
     */
    Random __rand;
};
/**
 * ------------------------------------------------------------------------------------------------
 * Encoder
 * ------------------------------------------------------------------------------------------------
 */
class SEncode : public SEncodeT<SWalker> {
public:
    using SEncodeT<SWalker>::SEncodeT;
};
}
/**
 * --------------------------------------------------------------------------------------------------------------------
 * End
 * --------------------------------------------------------------------------------------------------------------------
 */
#endif    /* SENCODE_FUNCTION_H */

