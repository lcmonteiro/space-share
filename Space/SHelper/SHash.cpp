/* 
 * File:   SHash.cpp
 * Author: Luis Monteiro
 * 
 * Created on July 19, 2017, 6:23 PM
 */
#include <cstring>
/** 
 */
#include "SHash.h"
/*---------------------------------------------------------------------------------------------------------------------*
 *  Implementation of Murmur hash for 64-bit.
 *---------------------------------------------------------------------------------------------------------------------*/
static inline uint64_t unaligned_load(const char* p) {
	uint64_t result;
	memcpy(&result, p, sizeof (result));
	return result;
}
static inline uint64_t load_bytes(const char* p, int n) {
	uint64_t res = 0;
	/** 
	 */
	for (--n; n >= 0; --n) {
		res = (res << 8) + static_cast<unsigned char> (p[n]);
	}
	/** 
	 */
	return res;
}
static inline uint64_t shift_mix(uint64_t v) {
	return v ^ (v >> 47);
}
static uint64_t Hash_bytes(const void* ptr, uint64_t len, uint64_t seed) {
	static const uint64_t mul = (((uint64_t) 0xc6a4a793UL) << 32UL) + (uint64_t) 0x5bd1e995UL;
	const char* const buf = static_cast<const char*> (ptr);
	// Remove the bytes not divisible by the sizeof(size_t).  This
	// allows the main loop to process the data as 64-bit integers.
	const int len_aligned = len & ~0x7;
	const char* const end = buf + len_aligned;
	uint64_t hash = seed ^ (len * mul);
	for (const char* p = buf; p != end; p += 8) {
		const uint64_t data = shift_mix(unaligned_load(p) * mul) * mul;
		hash ^= data;
		hash *= mul;
	}
	if ((len & 0x7) != 0) {
		const uint64_t data = load_bytes(end, len & 0x7);
		hash ^= data;
		hash *= mul;
	}
	hash = shift_mix(hash) * mul;
	hash = shift_mix(hash);
	return hash;
}
/*---------------------------------------------------------------------------------------------------------------------*
 * Digest
 *---------------------------------------------------------------------------------------------------------------------*/
uint64_t SHash::Digest(string value, uint64_t seed) {
	return Hash_bytes(value.data(), value.size(), seed); 
}