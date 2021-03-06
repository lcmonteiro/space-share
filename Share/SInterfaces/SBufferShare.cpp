/**
 * ------------------------------------------------------------------------------------------------
 * File:   SBufferShare.cpp
 * Author: Luis Monteiro
 *
 * Created on September 14, 2016, 9:49 AM
 * ------------------------------------------------------------------------------------------------
 */
#include <map>
#include <set>
#include <algorithm>
#include <iostream>
#include <cassert>
/**
 */
#include "SBufferShare.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Encode interface
 * ------------------------------------------------------------------------------------------------
 **/
#define SET_UINT32(VAL) do{                         \
        uint32_t aux = (VAL);                       \
        *rit = uint8_t(aux);                        \
        ++rit;                                      \
        aux >>= 8;                                  \
        *rit = uint8_t(aux);                        \
        ++rit;                                      \
        aux >>= 8;                                  \
        *rit = uint8_t(aux);                        \
        ++rit;                                      \
        aux >>= 8;                                  \
        *rit = uint8_t(aux);                        \
        ++rit;                                      \
}while(0)
/**
 * ----------------------------------------------------------------------------
 * Set
 * ----------------------------------------------------------------------------
 */
size_t OBufferShare::set(const Frame& data, size_t sframes, size_t redundancy) {
	/**
	 * validation
	 */
	assert(sframes >= sizeof (uint32_t) + sizeof (uint32_t));
	/**
	 * data frame size
	 */
	int size = sframes - __encoder.HeaderSize();
	/**
	 *  split data and add to encoder
	 */
	auto it = data.begin();
	for (__encoder.clear().frame_count(1); distance(it, data.end()) >= size; it += size) {
		__encoder.push(Frame(it, it + size));
	}
	/**
	 *  process last nframes
	 */
	Frame last(size, size);
	copy(it, data.end(), last.begin());
	/**
	 * check size for extra information
	 */
	if ((size - last.size()) < (sizeof (uint32_t) + sizeof (uint32_t))) {
		/**
		 * add last info frame
		 */
		__encoder.push(move(last));
		/**
		 * reset last frame
		 */
		last.assign(size, 0);
	}
	/**
	 * write extra information on last frame
	 */
	auto rit = last.rbegin();
	/**
	 * add coded size information
	 */
	SET_UINT32(__encoder.size() + 1);
	/**
	 * add data size information 
	 */
	SET_UINT32(data.size());
	/**
	 * add last frame with extra information 
	 */
	__encoder.push(move(last));
	/**
	 *  return encoder size
	 */
	return __encoder.size() + redundancy;
}
/**
 * ----------------------------------------------------------------------------
 * Get
 * ----------------------------------------------------------------------------
 */
Frame OBufferShare::get() {
	return move(__encoder.pop().front());
}
/**
 * ------------------------------------------------------------------------------------------------
 * Decode interface
 * ------------------------------------------------------------------------------------------------
 **/
#define GET_UINT32(VAR) do{                         \
        VAR = uint32_t(*rit);                       \
        ++rit;                                      \
        VAR |= uint32_t(*rit)<<8;                   \
        ++rit;                                      \
        VAR |= uint32_t(*rit)<<16;                  \
        ++rit;                                      \
        VAR |= uint32_t(*rit)<<24;                  \
        ++rit;                                      \
}while(0)
/**
 * ----------------------------------------------------------------------------
 * Set
 * ----------------------------------------------------------------------------
 */
bool IBufferShare::set(Frame frame) {
	uint32_t aux = 0;
    /**
	 * add frame to decoder 
	 */
	__decoder.push(move(frame));
	/**
	 * find ended frame 
	 */
	for (auto size = __decoder.size(); size > 0; --size) {
		auto frame = __decoder.at(size - 1);
		/**
		 * check if all frame is zero 
		 */
		if (frame.sum(1) == 0) {
			continue;
		}
		/**
		 * check number of frame
		 */
		auto rit = frame.rbegin();
		GET_UINT32(aux);
		if (aux != size) {
			return false;
		}
		GET_UINT32(aux);
		auto n = uint32_t(aux / frame.size()); //nframes
		auto o = uint32_t(aux % frame.size()); //offset
		/**
		 * check data size
		 */
		if (n == (size - 1)) {
			for (auto end = frame.rend() - o; rit != end; ++rit) {
				if (*rit) {
					return false;
				}
			}
			__decoder.resize(size);
			return true;
		}
		if (n == (size - 2)) {
			auto nframe = __decoder.at(n);
			for (auto it = nframe.begin() + o, end = nframe.end(); it != end; ++it) {
				if (*it) {
					return false;
				}
			}
			__decoder.resize(size);
			return true;
		}
		break;
	}
	return false;
}
/**
 * ----------------------------------------------------------------------------
 * Get
 * ----------------------------------------------------------------------------
 */
Frame IBufferShare::get() {
	uint32_t aux = 0;
	/**
	 * serialize data 
	 */
	auto out = Frame();
	auto it  = __decoder.begin();
	auto end = __decoder.end();
	if(it != end) {
		out = Frame(it->size() * __decoder.size());
		do {
			out.insert(*it);
		} while(++it != end);
	}
	/**
	 * resize out to original size 
	 */
	auto rit = out.rbegin() + sizeof (uint32_t);
	GET_UINT32(aux);
	out.resize(aux);
	/**
	 * clear and return decoded data 
	 */
	__decoder.clear();
	return out;
}
/**
 * ------------------------------------------------------------------------------------------------
 *  End
 * ------------------------------------------------------------------------------------------------
 */
