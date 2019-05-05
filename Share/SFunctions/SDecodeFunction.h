/**
 * ------------------------------------------------------------------------------------------------
 * File:   SDecodeFunction.h
 * Author: Luis Monteiro
 *
 * Created on November 11, 2015, 9:49 AM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SDECODE_FUNCTION_H
#define SDECODE_FUNCTION_H
/**
 * std
 */
#include <vector>
#include <cmath>
#include <sstream>
/**
 * share
 */
#include "SConnector.h"
#include "SCache.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Message context
 * ------------------------------------------------------------------------------------------------
 */
namespace Message {
/**
 * decode
 */
class SDecodeFunction : public SFunctionSpread<
	SConnector::Key, Encoded::IConnector, Encoded::Document, Decoded::OConnector> {
    /**
     * Super class
     */ 
    using Super = SFunctionSpread<
        SConnector::Key, Encoded::IConnector, Encoded::Document, Decoded::OConnector>;
    /**
     * helpers
     */
    using ORoad  = typename Super::ORoad;
    using Data   = typename Super::Data;
    using Cache  = Message::SCache;
    using pStamp = Codec::pStamp;
public:
    /**
	 * ------------------------------------------------------------------------
     * Constructor  
     * @param stamp
     * @param nContainers
	 * ------------------------------------------------------------------------
     */
    SDecodeFunction(
		pStamp stamp,
		uint32_t nContainers, 
		uint32_t energy = 3, 
		uint8_t verbose = 0)
	: Super("Decode", energy, verbose), 
	__cache(stamp, nContainers) {}
    
	SDecodeFunction(
		const std::string& id, 
    	pStamp stamp, 
		uint32_t nContainers, 
		uint32_t energy = 3, 
		uint8_t verbose = 0)
	: Super(std::string("Decode(") + id + ")", energy, verbose), 
	__cache(stamp, nContainers) {}
    /**
	 * ------------------------------------------------------------------------
     * Drain
	 * ------------------------------------------------------------------------
     */
    void drain(ORoad& out) {
	    /**
		 * move cache
		 */
	    __cache.move();
		/**
		 * process
		 */
	    _process_data(out);
    }
    /**
	 * ------------------------------------------------------------------------
     * Recover
	 * ------------------------------------------------------------------------
     */
    void recover() override {
	    /**
		 * clear cache
		 */
	    __cache.clear();
		/**
		 * base recover
		 */
	    Super::recover();
    }
protected:
    /**
     * ------------------------------------------------------------------------
     * Process Data
     *-------------------------------------------------------------------------
     */
	void _process_data(ORoad& out) override {
	    for (auto& doc: __cache.pop()) {
	        for (auto it = out.begin(), end = out.end(); it != end;) {
	            try {
	                it->second->write(doc); ++it;
	            } catch (ConnectorExceptionDEAD& ex) {
	                out.exception(it);
	            } catch (ConnectorExceptionTIMEOUT& ex) {
	            }
	        }
        }
    }
	void _process_data(Data&& data, ORoad& out) override {
	    /**
		 * log debug
		 */
		DEBUG("receive={" 
	        << " p=" << data.position() 
	        << " n=" << data.frame_count() 
	        << " s=" << data.size() 
	        << " }");
	    /**
	     * insert coded data
	     */
	    if(__cache.push(std::move(data))){
	        _process_data(out);
	    }
    }
private:
	/**
     * ------------------------------------------------------------------------
     * Variables
     *-------------------------------------------------------------------------
	 **
     * cache
     */
    Cache __cache;
};
}
/**
 * ------------------------------------------------------------------------------------------------
 * Stream Context
 * ------------------------------------------------------------------------------------------------
 */
namespace Stream {
/**
 * Decode
 */
class SDecodeFunction : public SFunctionSpread<
	SConnector::Key, Encoded::IConnector, Encoded::Document, Decoded::OConnector> {
    /**
     * settings
     */
    const size_t AUX_SIZE = 5;
    /**
     * Super class
     */ 
    using Super = SFunctionSpread<
        SConnector::Key, Encoded::IConnector, Encoded::Document, Decoded::OConnector>;
	/**
     * define types
     */ 
    using Road   = typename Super::ORoad;
    using Data   = typename Super::Data;
    using Cache  = Stream::SCache;
	using pStamp = Codec::pStamp;
public:
    /**
	 * ------------------------------------------------------------------------
     * SDecodeFunction Connector
     * @param nContainers
	 * ------------------------------------------------------------------------
     */
    SDecodeFunction(
		pStamp stamp, 
		uint32_t nContainers, 
		uint32_t energy = 3, 
		uint8_t verbose = 0)
	: Super("Decode", energy, verbose), 
	__cache(stamp, nContainers), 
	__cache_aux(AUX_SIZE) {
		for(auto&c :__cache_aux){ c = Cache(stamp, nContainers); }
	}

    SDecodeFunction(
    	const std::string& id, 
    	pStamp stamp,
		uint32_t nContainers, 
		uint32_t energy = 3, 
		uint8_t verbose = 0)
	: Super(std::string("Decode(") + id + ")", energy, verbose), 
	__cache(stamp, nContainers), 
	__cache_aux(AUX_SIZE) {
    	for(auto&c :__cache_aux){ c = Cache(stamp, nContainers); }
    }
    /**
	 * ------------------------------------------------------------------------
     * Drain
	 * ------------------------------------------------------------------------
     */
    void drain(Road& out) {
	    /**
	     * move main cache
	     */
	    if(__cache_aux.front().length()) {
	        __cache.move(); 
	    }
	    /**
	     * move caches
	     */
	    for(auto&c :__cache_aux) {
	        c.move(); 
	    }
	    /**
	     * sort aux caches
	     */
	    _sort_cache();
	    /**
	     * try to swap caches 
	     */
	    if (_swap_cache(__cache, __cache_aux.front())) {
	        out.reset();
	    } else {
	        _process_data(out);
	    }
    }
    /**
	 * ------------------------------------------------------------------------
     * Recover
	 * ------------------------------------------------------------------------
     */
    void recover() override {
	    /**
	     * clear cache
	     */
	    __cache.clear();
	    /**
	     * clear aux cache
	     */
	    for(auto&c :__cache_aux){
	        c.clear(); 
	    }
	    /** 
		 * recover function
	     */
	    Super::recover();
    }
protected:
    /**
	 * ------------------------------------------------------------------------
     * Process Data
     * ------------------------------------------------------------------------
	 */
    void _process_data(Road& out) override {
	    for (auto& data: __cache.pop()) {
	        for(auto it = out.begin(); it != out.end();){
		        try {
		            it->second->write(data); ++it;
		        } catch (ConnectorExceptionDEAD& ex) {
		            out.exception(it);
		        } catch (ConnectorExceptionTIMEOUT& ex) {}
	        }
	        /**
	         * reset cache aux
	         */
	        for(auto&c :__cache_aux){ c.clear(); }
	    }
    }
    inline void _process_data(Data&& data, Road& out) override {
	    /**
	     * insert on cache
	     */
	    DEBUG("receive::" 
			<< "pos=" << data.position()  << " " 
			<< "n="   << data.frame_count() << " "
			<<"s="    << data.size());
	    if (!__cache.push(move(data))) {
	        /**
	         * add to aux caches
	         */
	        for (auto& c : __cache_aux) {
		        DEBUG("receive(aux)::" 
					<< "aux=" << c.density() << " " 
					<< "cur=" << __cache.density());
		        if (c.push(move(data))) {
		            /**
		             * try to swap caches 
		             */
		            if (_swap_cache(__cache.shrink(c.density()), c)) {
		     	       out.reset();
		            }
		            return;
		        }
	        }
	        /**
	         * sort aux caches
	         */
	        _sort_cache();
	        /**
	         * reset last aux cache
	         */
	        __cache_aux.back().clear();
	        __cache_aux.back().push(move(data));
	        return;
	    }
	    /**
	     * remove cache
	     */
	    _process_data(out);
    }
    /**
	 * ------------------------------------------------------------------------
     * cache tools 
	 * ------------------------------------------------------------------------
	 **
	 * sort cache
     */
    inline void _sort_cache(){
	    std::sort(__cache_aux.begin(), __cache_aux.end(), 
			[](Cache& a, Cache& b) { return a.stronger(b); });
    }
    /**
     * try to swap caches
     */
    inline bool _swap_cache(Cache& main, Cache& aux) {
	    if (aux.stronger(main)) {
	        /**
	         * log 
	         */
	        WARNING("broken::"
	 	       	<< " aux=" << aux.density() << " cur=" << main.density()
	    	   	<< " aux=" << aux.length()  << " cur=" << main.length()
	        	<< " aux=" << aux.weight()  << " cur=" << main.weight());
	        /**
	         *  swap caches 
	         */
	        std::swap(main, aux);
	        /**
	         *  shrink 
	         */
	        aux.shrink();
	        return true;
	    }
	    return false;
    }
private:
	/**
	 * ------------------------------------------------------------------------
	 * Variables
	 * ------------------------------------------------------------------------
	 **
     * main container
     */
    Cache __cache;
    /**
     * aux containers
     */
    std::vector<Cache> __cache_aux;
};
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SDECODE_FUNCTION_H */

