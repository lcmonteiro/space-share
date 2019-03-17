/**
 * ------------------------------------------------------------------------------------------------
 * File:   SDecode.h
 * Author: Luis Monteiro
 *
 * Created on November 11, 2015, 9:49 AM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SDECODE_FUNCTION_H
#define SDECODE_FUNCTION_H
/**
 * C++
 */
#include <vector>
#include <cmath>
#include <sstream>
/**
 * Share Kernel
 */
#include "SConnector.h"
#include "SCache.h"
/**
 *-------------------------------------------------------------------------------------------------
 * message context
 *-------------------------------------------------------------------------------------------------
 */
namespace Message {
/**
 * decode
 */
class SDecode : public SFunctionSpread<
	SConnector::Key, Encoded::IConnector, Encoded::Document, Decoded::OConnector> {
    /**
     * super class
     */ 
    using Super = SFunctionSpread<
        SConnector::Key, Encoded::IConnector, Encoded::Document, Decoded::OConnector
    >;
    /**
     * helpers
     */
    using ORoad    = typename Super::ORoad;
    using Data     = typename Super::Data;
    using Cache    = Message::SCache;
public:
    /**
	 * ------------------------------------------------------------------------
     * SDecode 
     * @param stamp
     * @param nContainers
	 * ------------------------------------------------------------------------
     */
    SDecode(
		const Stamp& stamp, const uint32_t nContainers, const uint32_t energy = 3, const uint8_t verbose = 0
	): Super("Decode", energy, verbose), __cache(stamp, nContainers) {
    }
    SDecode(
		const string& id, 
    	const Stamp& stamp, const uint32_t nContainers, const uint32_t energy = 3, const uint8_t verbose = 0
    ): Super(string("Decode(") + id + ")", energy, verbose), __cache(stamp, nContainers) {
    }
    /**
	 * ------------------------------------------------------------------------
     * Drain
	 * ------------------------------------------------------------------------
     */
    void Drain(ORoad& out) {
	    /**
	     * move cache
	     */
	    __cache.Move();
	    /**
	     * process
	     */
	    processData(out);
    }
    /**
	 * ------------------------------------------------------------------------
     * Recover
	 * ------------------------------------------------------------------------
     */
    void Recover() override {
	    /**
	     * clear cache
	     */
	    __cache.Clear();
	    /** 
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
	    for (auto& doc: __cache.Pop()) {
	        for (auto it = out.begin(), end = out.end(); it != end;) {
	            try {
	                it->second->Write(doc); ++it;
	            } catch (ConnectorExceptionDEAD& ex) {
	                out.Exception(it);
	            } catch (ConnectorExceptionTIMEOUT& ex) {
	            }
	        }
        }
    }
	void processData(Data&& data, ORoad& out) override {
	    DEBUG("receive={" 
	        << " p=" << data.GetPosition() 
	        << " n=" << data.GetNumFrames() 
	        << " s=" << data.size() 
	        << " }"
	    );
	    /**
	     * insert coded data
	     */
	    if(__cache.Push(std::move(data))){
	        processData(out);
	    }
    }
private:
	/**
     * ------------------------------------------------------------------------
     * variables
     *-------------------------------------------------------------------------
	 **
     * cache
     */
    Cache __cache;
};
}
/**
 *-------------------------------------------------------------------------------------------------
 * stream context
 *-------------------------------------------------------------------------------------------------
 */
namespace Stream {
/**
 * Decode
 */
class SDecode : public SFunctionSpread<
	SConnector::Key, Encoded::IConnector, Encoded::Document, Decoded::OConnector> {
    /**
     * settings
     */
    const size_t AUX_SIZE = 5;
    /**
     * super class
     */ 
    using Super = SFunctionSpread<
        SConnector::Key, Encoded::IConnector, Encoded::Document, Decoded::OConnector
    >;
	/**
     * define types
     */ 
    using Road  = typename Super::ORoad;
    using Data  = typename Super::Data;
    using Cache = Stream::SCache;
public:
    /**
	 * ------------------------------------------------------------------------
     * SDecode Connector
     * @param nContainers
	 * ------------------------------------------------------------------------
     */
    SDecode(
		const Stamp& stamp, const uint32_t nContainers, const uint32_t energy = 3, const uint8_t verbose = 0
	): Super("Decode", energy, verbose), __cache(stamp, nContainers), __cache_aux(AUX_SIZE) {
    	for(auto&c :__cache_aux){ c = Cache(stamp, nContainers); }
    }
    SDecode(
    	const string& id, 
    	const Stamp& stamp, const uint32_t nContainers, const uint32_t energy = 3, const uint8_t verbose = 0
    ): Super(string("Decode(") + id + ")", energy, verbose), __cache(stamp, nContainers), __cache_aux(AUX_SIZE) {
    	for(auto&c :__cache_aux){ c = Cache(stamp, nContainers); }
    }
    /**
	 * ------------------------------------------------------------------------
     * Drain
	 * ------------------------------------------------------------------------
     */
    void Drain(Road& out) {
	    /**
	     * move main cache
	     */
	    if(__cache_aux.front().Length()) {
	        __cache.Move(); 
	    }
	    /**
	     * move caches
	     */
	    for(auto&c :__cache_aux) {
	        c.Move(); 
	    }
	    /**
	     * sort aux caches
	     */
	    sortCache();
	    /**
	     * try to swap caches 
	     */
	    if (swapCache(__cache, __cache_aux.front())) {
	        /**
	         * reset Connector
	         */
	        out.Reset();
	    } else {
	        /**
	         * process data
	         */
	        processData(out);
	    }
    }
    /**
	 * ------------------------------------------------------------------------
     * Recover
	 * ------------------------------------------------------------------------
     */
    void Recover() override {
	    /**
	     * clear cache
	     */
	    __cache.Clear();
	    /**
	     * clear aux cache
	     */
	    for(auto&c :__cache_aux){
	        c.Clear(); 
	    }
	    /** 
		 * recover function
	     */
	    SFunction::Recover();
    }
protected:
    /**
	 * ------------------------------------------------------------------------
     * process Data
     * ------------------------------------------------------------------------
	 */
    void processData(Road& out) override {
	    for (auto& data: __cache.Pop()) {
	        for(auto it = out.begin(); it != out.end();){
		        try {
		            it->second->Write(data); ++it;
		        } catch (ConnectorExceptionDEAD& ex) {
		            out.Exception(it);
		        } catch (ConnectorExceptionTIMEOUT& ex) {}
	        }
	        /**
	         * reset cache aux
	         */
	        for(auto&c :__cache_aux){ c.Clear(); }
	    }
    }
    inline void processData(Data&& data, Road& out) {
	    /**
	     * insert on cache
	     */
	    DEBUG("receive::" 
			<< "pos=" << data.GetPosition()  << " " 
			<< "n="   << data.GetNumFrames() << " "
			<<"s=" << data.size()
		);
	    if (!__cache.Push(move(data))) {
	        /**
	         * add to aux caches
	         */
	        for (auto& c : __cache_aux) {
		        DEBUG("receive(aux)::" << "aux=" << c.Density() << " cur=" << __cache.Density());
		        if (c.Push(move(data))) {
		            /**
		             * try to swap caches 
		             */
		            if (swapCache(__cache.Shrink(c.Density()), c)) {
		     	       out.Reset();
		            }
		            return;
		        }
	        }
	        /**
	         * sort aux caches
	         */
	        sortCache();
	        /**
	         * reset last aux cache
	         */
	        __cache_aux.back().Clear();
	        __cache_aux.back().Push(move(data));
	        return;
	    }
	    /**
	     * remove cache
	     */
	    processData(out);
    }
    /**
	 * ------------------------------------------------------------------------
     * cache tools 
	 * ------------------------------------------------------------------------
	 **
	 * sort cache
     */
    inline void sortCache(){
	    sort(__cache_aux.begin(), __cache_aux.end(), [](Cache& a, Cache& b) {
	        return a.Stronger(b);   
	    });
    }
    /**
     * try to swap caches
     */
    inline bool swapCache(Cache& main, Cache& aux) {
	    if (aux.Stronger(main)) {
	        /**
	         * log 
	         */
	        WARNING("broken::"
	 	       	<< " aux=" << aux.Density() << " cur=" << main.Density()
	    	   	<< " aux=" << aux.Length()  << " cur=" << main.Length()
	        	<< " aux=" << aux.Weight()  << " cur=" << main.Weight()
	        );
	        /**
	         *  swap caches 
	         */
	        swap(main, aux);
	        /**
	         *  shrink 
	         */
	        aux.Shrink();
	        return true;
	    }
	    return false;
    }
private:
	/**
	 * ------------------------------------------------------------------------
	 * variables
	 * ------------------------------------------------------------------------
	 **
     * main container
     */
    Cache __cache;
    /**
     * aux containers
     */
    vector<Cache> __cache_aux;
};
}
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */
#endif    /* SDECODE_H */

