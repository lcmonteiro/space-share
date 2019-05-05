/**
 * ------------------------------------------------------------------------------------------------
 * File:   SEncodeFunction.h
 * Author: Luis Monteiro
 *
 * Created on November 11, 2015, 9:49 AM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SENCODE_FUNCTION_H
#define SENCODE_FUNCTION_H
/**
 * std 
 */
#include <exception>
#include <algorithm>
/**
 * share 
 */
#include "SConnector.h"
#include "SFunction.h"
#include "SEncoderCodec.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Encoder Template
 * @MIM = minimun redundancy
 * ------------------------------------------------------------------------------------------------
 */
template <typename Walker, size_t MIN = 10>
class SEncodeFunctionT : public SFunctionSpread<
    SConnector::Key, Decoded::IConnector, Decoded::Document, Encoded::OConnector> {
    /**
     * Super class
     */ 
    using Super = SFunctionSpread<
        SConnector::Key, Decoded::IConnector, Decoded::Document, Encoded::OConnector>;
    /**
     * helpers
     */
    using ORoad     = typename Super::ORoad;
    using Data      = typename Super::Data;
    using Location  = typename ORoad::Location;
    using Encoder   = Codec::SEncoder;
    using pStamp    = Codec::pStamp;
    using Generator = std::minstd_rand0;
    using Random    = std::random_device;
public:
    /**
     * ------------------------------------------------------------------------
     * Encode Constructors
     * @param stamp
     * @param redundancy
     * ------------------------------------------------------------------------
     */
    SEncodeFunctionT(
        pStamp stamp, 
        uint32_t redundancy, 
        uint32_t energy = 1, 
        uint8_t verbose = 0)
    : Super("Encode", energy, verbose), 
    __stamp(stamp), 
    __redundancy(redundancy) { recover(); }

    SEncodeFunctionT(const std::string& id, 
        pStamp stamp, 
        uint32_t redundancy, 
        uint32_t energy = 1, 
        uint8_t verbose = 0)
    : Super(std::string("Encode(") + id + ")", energy, verbose), 
    __stamp(stamp), 
    __redundancy(redundancy) { recover(); }
    /**
     * ------------------------------------------------------------------------
     * Recover 
     * ------------------------------------------------------------------------
     */
    void recover() override {
        /**
         * refresh stream position
         */
        __position.reset();
        /**
         * call base recover
         */ 
        Super::recover();
    }
protected:
    /**
     * --------------------------------------------------------------------------------------------
     * Process Data
     *---------------------------------------------------------------------------------------------
     */
    void _process_data(ORoad& out) override {    
    }
    void _process_data(Data&& data, ORoad& out) override {
        Random rd;
        Generator gen(rd());
        /**
         * create encoder
         */
	    auto en = Encoder(std::move(data), __stamp);
	    /**
         * create context
         */
        auto ctxt = Encoded::Context(__position.next(), en.size(), en.frame_size());
	    /**
         * log debug
         */
	    DEBUG("encode::" << "pos=" << ctxt.position());
	    /**
         * init remain with num of frames
         */
	    auto remain = std::max(
            size_t(ctxt.frame_count()) + __redundancy, MIN);
	    /**
         * process road until no remain load (remain > 0)
         */
        while (remain > 0) {
            /**
             * weights
             */
	        std::vector<size_t> wgt;
            wgt.reserve(out.size());
	        for (auto& o : out) { wgt.emplace_back(o.second->energy()); }
            /**
             * quantities
             */
            std::discrete_distribution<> d(wgt.begin(), wgt.end());
            std::vector<size_t> qty;
            qty.resize(wgt.size());
            for (auto i = 0; i < remain; ++i) { ++qty[d(gen)]; }
	        /**
             * weighted write
             */
            auto o = out.begin();
	        for (auto q = qty.begin(); qty.end() != q; ++q) {
	            try {
                    /**
                     * write and update iterator and data
                     */
                    o->second->write(
                        Encoded::Document(en.frame_count(*q).pop(), ctxt)); 
                    /**
                     * update references
                     */
                    ++o; remain -= *q;
		        } catch (ConnectorExceptionTIMEOUT& ex) {
                    ++o;
	            } catch (ConnectorExceptionDEAD& ex) {
		            out.exception(o);
		        }    
            }
	    }
	}
private:
    /**
     * ------------------------------------------------------------------------
     * Variables
     * ------------------------------------------------------------------------
     **
     * stamp
     */
    pStamp __stamp;
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
 * Message context
 *-------------------------------------------------------------------------------------------------
 */
namespace Message {
/**
 * ----------------------------------------------------------------------------
 * Walker
 * ----------------------------------------------------------------------------
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
 * ----------------------------------------------------------------------------
 * Encoder
 * ----------------------------------------------------------------------------
 */
class SEncodeFunction : public SEncodeFunctionT<SWalker> {
public:
    using SEncodeFunctionT<SWalker>::SEncodeFunctionT;
};
}
/**
 *-------------------------------------------------------------------------------------------------
 * Stream context
 *-------------------------------------------------------------------------------------------------
 */
namespace Stream {
/**
 * ----------------------------------------------------------------------------
 * Walker
 * ----------------------------------------------------------------------------
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
 * ----------------------------------------------------------------------------
 * Encoder
 * ----------------------------------------------------------------------------
 */
class SEncodeFunction : public SEncodeFunctionT<SWalker> {
public:
    using SEncodeFunctionT<SWalker>::SEncodeFunctionT;
};
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SENCODE_FUNCTION_H */

