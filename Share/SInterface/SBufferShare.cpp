/* 
 * File:   SBufferShare.cpp
 * Author: Luis Monteiro
 *
 * Created on September 14, 2016, 9:49 AM
 */
#include <map>
#include <set>
#include <algorithm>
#include <iostream>
#include <cassert>
/**
 */
#include "SBufferShare.h"
/*---------------------------------------------------------------------------------------------------------------------*
 * Encode interface
 *---------------------------------------------------------------------------------------------------------------------*/
size_t OBufferShare::Set(const Frame& data, size_t sframes, size_t redundancy) {
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
         * validation
         */
        assert(sframes >= sizeof (uint32_t) + sizeof (uint32_t));
	/**
	 * data frame size
	 */
	int size = sframes - Codec::HeaderSize();
	/**
	 *  split data and add to encoder
	 */
	auto it = data.begin();
	for (__encoder.clear().length(1); distance(it, data.end()) >= size; it += size) {
		__encoder.push(Frame(it, it + size));
	}
	/**
	 *  process last nframes
	 */
	Frame last(size, 0);
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
Frame OBufferShare::Get() {
	return move(__encoder.pop().front());
}
/*---------------------------------------------------------------------------------------------------------------------*
 * Decode interface
 *---------------------------------------------------------------------------------------------------------------------*/
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
bool IBufferShare::Set(Frame frame) {
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
		if (frame.Sum(1) == 0) {
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
		auto n = uint32_t(aux / frame.size()); //nnframes
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

Frame IBufferShare::Get() {
	uint32_t aux = 0;
	/**
	 * serialize data 
	 */
	Frame out;
	for (auto f : __decoder) {
		out.insert(out.end(), f.begin(), f.end());
	}
        __decoder.clear();
	/**
	 * resize out to original size 
	 */
	auto rit = out.rbegin() + sizeof (uint32_t);
	GET_UINT32(aux);
	out.resize(aux);
	/**
	 * return decoded data 
	 */
	return out;
}

