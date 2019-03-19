/**
 * ------------------------------------------------------------------------------------------------
 * File:   SCache.h
 * Author: Luis Monteiro
 *
 * Created on October 6, 2016, 9:49 AM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SCACHE_H
#define SCACHE_H
/**
 * std
 */
#include <cmath>
/**
 * Space Kernel
 */
#include "SChain.h"
/**
 * Share Kernel
 */
#include "SConnector.h"
#include "SCodec.h"
/**
 * ------------------------------------------------------------------------------------------------
 * message cache
 * ------------------------------------------------------------------------------------------------
 */
namespace Message {
class SCache {
    /**
     * ------------------------------------------------------------------------
     * Helpers
     * ------------------------------------------------------------------------
     * types
     */
    typedef enum {Open, Done, Close} State;
    /**
     */
    using Context = Encoded::SContext;
    using Decoder = CodecDecoder;
    using Chain   = SChain<Encoded::Context, Decoder>;
    using Storage = map<State, Chain>;
public:
    /**
     * ------------------------------------------------------------------------
     * defaults
     * ------------------------------------------------------------------------
     * constructor
     */
    SCache(SCache&&) = default;
    /**
     * operator
     */
    SCache& operator=(SCache&&) = default;
    /**
     * ------------------------------------------------------------------------
     * constructors
     * ------------------------------------------------------------------------
     * main
     * @param stamp
     * @param capacity - number max of containers
     */
    SCache(SharedStamp stamp = CodecStamp::Get(CodecStamp::NONE), size_t capacity = 10)
    : __stamp(stamp), __storage() {
        __storage[Open] = Chain(capacity);
        __storage[Done] = Chain(capacity);
        __storage[Close] = Chain(capacity);
    }
    /**
     * ------------------------------------------------------------------------
     * Add Encoded Document
     * ------------------------------------------------------------------------
     */
    inline bool Push(Encoded::Document&& doc) {
        if(__storage[Close].Exist(doc)) {
            return false;
        }
        if(__storage[Done].Exist(doc)) {
            return false;
        }
        try {
            if(__storage[Open].Find(doc).push(std::move(doc)).full()) {
                __storage[Done].Insert(
                    doc, std::move(__storage[Open].Find(doc))
                );
            }
        } catch(std::out_of_range&) {
            Decoder c(doc.NumFrames(), std::move(doc), __stamp);
            if (c.full()) {
                __storage[Open].Insert(doc, std::move(c));
            } else {
                __storage[Done].Insert(doc, std::move(c));
            }
        }
        return true;
    }
    /**
     * ------------------------------------------------------------------------
     * Remove Decoded Document
     * ------------------------------------------------------------------------
     */
    inline std::list<Decoded::Document> Pop() {
	    auto& done  = __storage[Done];
	    auto& close = __storage[Close];
	    /**
	     * get all decoded messages
	     */
	    std::list<Decoded::Document> docs;
	    for(auto it = done.begin(); it != done.end(); it = done.erase(it)) {
	        auto p = *it;
	        /**
	         * create document 
	         */
	        docs.emplace_back(std::move(p->second.pop()));
	        /**
	         * move context to close
	         */
	        close.Insert(p->first, std::move(p->second.clear()));
	    }
        return docs;
    } 
    /**
     * ------------------------------------------------------------------------
     * Clear 
     * ------------------------------------------------------------------------
     */
    inline void Clear() {
        __storage.clear();
    }
    /* ------------------------------------------------------------------------
     * Move 
     * ------------------------------------------------------------------------
     */
    inline void Move() {
        /**
         * create a random context
         */
        Context ctxt(__rand(), 0);
        /**
         * insert a random context on done and close states
         */
        __storage[Done].Insert(Context(), Decoder());
        __storage[Close].Insert(Context(), Decoder());
    }
protected:
    /**
     * ------------------------------------------------------------------------
     * settings
     * ------------------------------------------------------------------------
     * codec stamp 
     */
    SharedStamp __stamp;
    /**
     * storage of documents
     */
    Storage __storage;
    /**
     */
    Codec::Random __rand;
};
}
/**
 * ------------------------------------------------------------------------------------------------
 * Stream Cache
 * ------------------------------------------------------------------------------------------------
 */
namespace Stream {
class SCache {
    using Context = Encoded::SContext;
    /**
     * ------------------------------------------------------------------------
     * Reference
     * ------------------------------------------------------------------------
     */
    typedef class SReference {
        public:
        SReference(uint32_t pos = 0) : __pos(pos) {
        }
        /**
         * SReference operators
         */
        inline SReference& operator=(const SReference& ref) {
            __pos = ref.__pos;
            return *this;
        }
        inline SReference operator-(uint32_t n) {
            return (__pos - n);
        }
        /**
         * SReference compare
         */
        inline bool gt(const SReference& ref) const {
            return (__pos - ref.__pos) < (UINT32_MAX >> 1);
        }
        inline bool lt(const SReference& ref) const {
            return (__pos - ref.__pos) > (UINT32_MAX >> 1);
        }
        inline void next() {
            ++__pos;
        }
        inline void prev() {
            --__pos;
        }
        /**
         *  Context operators
         */
        inline SReference& operator=(const Context& s) {
            __pos = s.Position();
            return *this;
        }
        inline operator Context() const {
            return Context(__pos, 0, 0);
        }
        /**
         * Context compare
         */
        inline bool gt(const Context& s) const {
            return (__pos - s.Position()) < (UINT32_MAX >> 1);
        }
        inline bool lt(const Context& s) const {
            return (__pos - s.Position()) > (UINT32_MAX >> 1);
        }
        inline bool eq(const Context& s) const {
            return (__pos == s.Position());
        }
        inline bool neq(const Context& s) const {
            return (__pos != s.Position());
        }
        private:
        uint32_t __pos;
    } Reference;
    /**
     */
    typedef map<Context, CodecDecoder> Storage;
public:
    /**
     * ------------------------------------------------------------------------
     * defaults
     * ------------------------------------------------------------------------
     * constructor
     */
    SCache(SCache&&) = default;
    /**
     * operator
     */
    SCache& operator=(SCache&&) = default;
    /**
     * ------------------------------------------------------------------------
     * constructors
     * ------------------------------------------------------------------------
     * main
     * @param n - number of Containers
     */
    SCache(SharedStamp stamp = CodecStamp::Get(CodecStamp::NONE), uint32_t n = 0) 
    : __stamp(stamp), __n(n), __min(), __back(), __front(), __max() {
    }
    /**
     * ------------------------------------------------------------------------
     * Add Encoded document
     * ------------------------------------------------------------------------
     */
    inline bool Push(Encoded::Document&& doc) {
	    /**
	     * check context
	     */
	    if (__min.gt(doc)) {
	        if (__min.neq(__max)) {
	        	return false;
	        }
	        __min = Reference(doc.Position() - __n);
	        __max = Reference(doc.Position() + __n);
	        __back = __front = doc;
	    }
	    if (__max.lt(doc)) {
	        if (__min.neq(__max)) {
	        	return false;
	        }
	        __min = Reference(doc.Position() - __n);
	        __max = Reference(doc.Position() + __n);
	        __back = __front = doc;
	    }
	    /**
	     * update storage
	     */
	    auto it = __storage.find(doc);
	    if (it != __storage.end()) {
            /**
             * update an existed container
             */
	        it->second.push(std::move(doc));
	    } else {
	        /**
	         * inset a new container 
	         */
	        __storage[doc] = CodecDecoder(doc.NumFrames(), std::move(doc), __stamp);
	        /**
	         * update movement
	         */
	        if (__front.lt(doc)) {
		        /**
		         * update front
		         */
		        __front = doc;
		        /**
		         * move window 
		         */
		        for (auto min = __front - __n; __min.lt(min); __min.next(), __max.next()) {
		            __storage.erase(__min);
		        }
		        /**
		         * update back
		         */
		        if (__back.lt(__min)) {
		            __back = __min;
		        }
	    	}
	    }
    	return true;
    }
    /**
     * ------------------------------------------------------------------------
     * Remove Decoded Document
     * ------------------------------------------------------------------------
     */
    inline std::list<Decoded::Document> Pop() {
        /**
         * get all decoded messages
         */
        std::list<Decoded::Document> docs;
        for(auto it = __storage.find(__back); 
            it != __storage.end() && it->second.full(); 
            it = __storage.find(__back)
        ){
            /**
             * insert 
             */
            docs.emplace_back(std::move(it->second.pop()));
            /**
             * clear decoder
             */
            it->second.clear();
            /**
             * move back reference
             */
            __back.next();
        }
        return docs;
    }
    /**
     * ------------------------------------------------------------------------
     * Shrink
     * ------------------------------------------------------------------------
     */
    inline SCache& Shrink() {
        for (; __min.lt(__back); __min.next()) {
            __storage.erase(__min);
        }
        return *this;
    }
    inline SCache& Shrink(size_t n) {
        for (size_t i = 0; i< n && __min.lt(__back); ++i, __min.next()) {
            __storage.erase(__min);
        }
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Move
     * ------------------------------------------------------------------------
     */
    inline SCache& Move(size_t n = 1) {
        /**
         * shift
         */
        for (size_t i = 0;  i < n ; ++i, __min.next(), __max.next()) {
            __storage.erase(__min);
        }
        /**
         * check
         */
        if (__back.lt(__min)) { 
            __back = __min;
        }
        if (__front.lt(__min)) {
            __front = __min;
        }
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Clear
     * ------------------------------------------------------------------------
     */
    inline void Clear() {
	    /**
	     * erase all storage 
	     */
	    __storage.clear();
	    /**
	     * set reference to begin 
	     */
	    __front = Reference(0);
	    __back = Reference(0);
	    __min = Reference(0);
	    __max = Reference(0);
    }
    /**
     * ------------------------------------------------------------------------
     * Length 
     * ------------------------------------------------------------------------
     */
    inline size_t Length() {
	    return __storage.size();
    }
    /**
     * ------------------------------------------------------------------------
     * Count - number of full contaires
     * ------------------------------------------------------------------------
     */
    inline size_t Count() {
	    size_t size = 0;
	    for (auto& c : __storage) {
	        if (c.second.full()) {
	            ++size;
	        }
	    }
	    return size;
    }
    /**
     * ------------------------------------------------------------------------
     * Weight
     * ------------------------------------------------------------------------
     */
    inline size_t Weight() {
	    size_t size = 0;
	    for (auto& c : __storage) {
	        size += c.second.size();
	    }
	    return size;
    }
    /**
     * ------------------------------------------------------------------------
     * Density
     * ------------------------------------------------------------------------
     */
    inline size_t Density() {
	    size_t density = 0;
	    /**
	     * forward
	     */
	    auto n = __back;
	    for (auto it=__storage.find(n); 
            (it!=__storage.end()) && (it->second.full()); it=__storage.find(n)) {
	        ++density, n.next();
	    }
	    /**
	     * backward
	     */
	    auto p = __back; p.prev();
	    for (auto it=__storage.find(p); 
            (it!=__storage.end()) && (it->second.full()); it=__storage.find(p)) {
	        ++density, p.prev();
	    }
	    return density;
    }
    /**
     * ------------------------------------------------------------------------
     * Compare
     * ------------------------------------------------------------------------
     */
    inline bool Stronger(SCache& cache) {
	    if(cache.Density() < Density()){
	        return true;
	    }
	    if(cache.Length() < Length()){
	        return true;
	    }
	    return cache.Weight() < Weight(); 
    }
protected:
    /**
     * ------------------------------------------------------------------------
     * Settings
     * ------------------------------------------------------------------------
     * stamp
     */
    SharedStamp __stamp;
    /**
     * tolerance
     */
    uint32_t __n;
    /**
     * references
     */
    Reference __min;
    Reference __back;
    Reference __front;
    Reference __max;
    /**
     * storage
     */
    Storage __storage;
};
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SCACHE_H */

