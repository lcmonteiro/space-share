/* 
 * File:   SCache.h
 * Author: Luis Monteiro
 *
 * Created on October 6, 2016, 9:49 AM
 */
#ifndef SCACHE_H
#define SCACHE_H
/**
 * std
 */
#include <cmath>
/**
 * space
 */
#include "SKernel/SChain.h"
/**
 * share
 */
#include "SKernel/SConnector.h"
#include "SKernel/SCodec.h"
/**
 *----------------------------------------------------------------------------------------------------------------------
 * message context
 *----------------------------------------------------------------------------------------------------------------------
 */
namespace Message {
/**
 * message cache
 */
class SCache {
        /**
         * types
         */
        typedef enum {Open, Done, Close} State;
        /**
	 */
        using Decoder = CodecDecoder;
        using Chain   = SChain<Context, Decoder>;
        using Storage = map<State, Chain>;
public:
        /**
         * constructor
         * @param stamp
         * @param capacity - number max of containers
         */
        SCache(const Stamp& stamp = CodecStamp::Get(CodecStamp::NONE), size_t capacity = 10)
        : __stamp(stamp), __storage() {
                __storage[Open] = Chain(capacity);
                __storage[Done] = Chain(capacity);
                __storage[Close] = Chain(capacity);
        }
	/**
	 * move constructor 
	 */
	SCache(SCache&& cache): 
		__stamp(move(cache.__stamp)), 
		__storage(move(cache.__storage)){
	}
	/**
	 * move operator 
	 */
	inline SCache& operator=(SCache&& cache) {
		__stamp = move(cache.__stamp);
		__storage = move(cache.__storage);
		return *this;
	}
	/*-------------------------------------------------------------------------------------------------------------*
	 * Add container
	 *-------------------------------------------------------------------------------------------------------------*/
	inline bool Push(Document&& container) {
                if(__storage[Close].Exist(container)) {
                        return false;
                }
                if(__storage[Done].Exist(container)) {
                        return false;
                }
                try {
                        if(__storage[Open].Find(container).push(move(container)).full()) {
                                __storage[Done].Insert(container, move(__storage[Open].Find(container)));
                        }
                } catch(runtime_error& e) {
                        Decoder c(container.GetNumFrames(), move(container), __stamp);
                        if (c.full()) {
                                __storage[Open].Insert(container, move(c));
                        } else {
                                __storage[Done].Insert(container, move(c));
                        }
                }
                return true;
	}
	/*-------------------------------------------------------------------------------------------------------------*
	 * Remove container
	 *-------------------------------------------------------------------------------------------------------------*/
	inline list<Document> Pop() {
                auto& done  = __storage[Done];
                auto& close = __storage[Close];
                /**
                 * get all decoded messages
                 */
                list<Document> docs;
                for(auto it = done.begin(); it != done.end(); it = done.erase(it)) {
                        auto p = *it;
                        /**
                         * create document 
                         */
                        docs.emplace_back(Document(move(p->second.pop()), p->first));
                        /**
                         * move context to close
                         */
                        close.Insert(p->first, move(p->second.clear()));
                }
	} 
        /*-------------------------------------------------------------------------------------------------------------*
         * clear 
         *-------------------------------------------------------------------------------------------------------------*/
        inline void Clear() {
                __storage.clear();
        }
        /*-------------------------------------------------------------------------------------------------------------*
         * move 
         *-------------------------------------------------------------------------------------------------------------*/
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
	/**-------------------------------------------------------------------------------------------------------------
	 * settings
	 **-------------------------------------------------------------------------------------------------------------
         * codec stamp 
         */
	StampReference __stamp;
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
 *----------------------------------------------------------------------------------------------------------------------
 * stream context
 *----------------------------------------------------------------------------------------------------------------------
 */
namespace Stream {
/**
 * stream cache
 */
class SCache {
	/**
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
		 *  SContextConnector operators
		 */
		inline SReference& operator=(const SContext& s) {
			__pos = s.GetPosition();
			return *this;
		}
		inline operator SContext() const {
			return SContext(__pos, 0, 0);
		}
		/**
		 * SContextConnector compare
		 */
		inline bool gt(const SContext& s) const {
			return (__pos - s.GetPosition()) < (UINT32_MAX >> 1);
		}
		inline bool lt(const SContext& s) const {
			return (__pos - s.GetPosition()) > (UINT32_MAX >> 1);
		}
		inline bool eq(const SContext& s) const {
			return (__pos == s.GetPosition());
		}
		inline bool neq(const SContext& s) const {
			return (__pos != s.GetPosition());
		}

	private:
		uint32_t __pos;
	} Reference;
	/**
	 */
	typedef map<Context, CodecDecoder> Storage;
public:
	/**
	 * constructor
	 * @param n - number of Containers
	 */
	SCache(const Stamp& stamp = CodecStamp::Get(CodecStamp::NONE), uint32_t n = 0) 
	: __stamp(stamp), __n(n), __min(), __back(), __front(), __max() {
	}
	/**
	 * move constructor 
	 */
	SCache(SCache&& cache): 
		__stamp(move(cache.__stamp)), 
		__n(move(cache.__n)), 
		__min(move(cache.__min)), 
		__back(move(cache.__back)), 
		__front(move(cache.__front)), 
		__max(move(cache.__max)),
		__storage(move(cache.__storage)){
	}
	/**
	 * move operator 
	 */
	inline SCache& operator=(SCache&& cache) {
		__stamp = move(cache.__stamp);
		__n = move(cache.__n);
		__min = move(cache.__min);
		__max = move(cache.__max);
		__back = move(cache.__back);
		__front = move(cache.__front);
		__storage = move(cache.__storage);
		return *this;
	}
	/*-------------------------------------------------------------------------------------------------------------*
	 * Add container
	 *-------------------------------------------------------------------------------------------------------------*/
	inline bool Push(Document&& container) {
		/**
		 * check context
		 */
		if (__min.gt(container)) {
			if (__min.neq(__max)) {
				return false;
			}
			__min = Reference(container.GetPosition() - __n);
			__max = Reference(container.GetPosition() + __n);
			__back = __front = container;
		}
		if (__max.lt(container)) {
			if (__min.neq(__max)) {
				return false;
			}
			__min = Reference(container.GetPosition() - __n);
			__max = Reference(container.GetPosition() + __n);
			__back = __front = container;
		}
		/**
		 * update storage
		 */
		auto it = __storage.find(container);
		if (it != __storage.end()) {
                        /**
                         * update an existed container
                         */
			it->second.push(move(container));
		} else {
                        /**
                         * inset a new container 
                         */
			__storage[container] = CodecDecoder(container.GetNumFrames(), move(container), __stamp);
                        /**
                         * update movement
                         */
                        if (__front.lt(container)) {
                                /**
                                 * update front
                                 */
                                __front = container;
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
	/*-------------------------------------------------------------------------------------------------------------*
	 * Remove container
	 *-------------------------------------------------------------------------------------------------------------*/
        inline list<Document> Pop() {
                /**
                 * get all decoded messages
                 */
                list<Document> docs;
                for(auto it = __storage.find(__back); 
                        it != __storage.end() && it->second.full(); 
                        it = __storage.find(__back)
                ){
                        /**
                         * insert 
                         */
                        docs.emplace_back(Document(move(it->second.pop()), it->first));
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
	/*-------------------------------------------------------------------------------------------------------------*
	 * Shrink
	 *-------------------------------------------------------------------------------------------------------------*/
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
	/*-------------------------------------------------------------------------------------------------------------*
	 * move
	 *-------------------------------------------------------------------------------------------------------------*/
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
	/*-------------------------------------------------------------------------------------------------------------*
	 * clear
	 *-------------------------------------------------------------------------------------------------------------*/
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
	/*-------------------------------------------------------------------------------------------------------------*
	 * get length
	 *-------------------------------------------------------------------------------------------------------------*/
	inline size_t Length() {
		return __storage.size();
	}
	/*-------------------------------------------------------------------------------------------------------------*
	 * get Count
	 *-------------------------------------------------------------------------------------------------------------*/
	inline size_t Count() {
		size_t size = 0;
		for (auto& c : __storage) {
			if (c.second.full()) {
				++size;
			}
		}
		return size;
	}
	/*-------------------------------------------------------------------------------------------------------------*
	 * get Weight
	 *-------------------------------------------------------------------------------------------------------------*/
	inline size_t Weight() {
		size_t size = 0;
		for (auto& c : __storage) {
			size += c.second.size();
		}
		return size;
	}
	/*-------------------------------------------------------------------------------------------------------------*
	 * get Density
	 *-------------------------------------------------------------------------------------------------------------*/
	inline size_t Density() {
		size_t density = 0;
		/**
		 * forward
		 */
		auto n = __back;
		for (auto it=__storage.find(n); (it!=__storage.end()) && (it->second.full()); it=__storage.find(n)) {
			++density, n.next();
		}
		/**
		 * backward
		 */
		auto p = __back; p.prev();
		for (auto it=__storage.find(p); (it!=__storage.end()) && (it->second.full()); it=__storage.find(p)) {
			++density, p.prev();
		}
		return density;
	}
	/*-------------------------------------------------------------------------------------------------------------*
	 * compare
	 *-------------------------------------------------------------------------------------------------------------*/
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
	 * settings
	 */
	StampReference __stamp;
	/**
	 */
	uint32_t __n;
	/**
	 */
	Reference __min;
	Reference __back;
	Reference __front;
	Reference __max;
	/**
	 */
	Storage __storage;
};
}

#endif /* SCACHE_H */

