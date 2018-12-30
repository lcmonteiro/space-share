/* 
 * File:   SCodec.h
 * Author: Luis Monteiro
 *
 * Created on November 30, 2015, 5:48 PM
 */
#ifndef SCODEC_H
#define SCODEC_H
/**
 */
#include <utility>
#include <vector>
#include <random>
#include <functional>
#include <cstdint>
/**
 */
#include "SKernel/SContainer.h"
/**
 */
#include "SCodecStamp.h"
/**
 */
namespace v2 {
	/**
	 */
	using namespace std;
	/**/
	typedef random_device Random;
	/**/
	typedef reference_wrapper<const Stamp> StampReference;
	/**
	 */
	class SCodec {
	public:
		/**/
		typedef random_device Random;
		/*----------------------------------------------------------------------------------------*
		 * Encoder class
		 *----------------------------------------------------------------------------------------*/
		class Encoder {
		public:
			/**
			 *  default constructor
			 */
			Encoder() :  __capacity(0), __length(0), __stamp(SCodecStamp::Get(SCodecStamp::FULL)) {
			}
			/**
			 *  constructor
			 * @param codeSize
			 * @param density
			 */
			Encoder(
				uint32_t capacity,
				const Stamp& stamp = SCodecStamp::Get(SCodecStamp::FULL)
			) :  __capacity(capacity), __length(capacity), __stamp(stamp) {
				/**
				 * prepare
				 */
				if (__stamp.get().size() < UINT8_MAX) {
					throw nullptr;
				}
				/**
				 */
				__data.reserve(__capacity);
			}
			Encoder(
				Container && init,
				const Stamp& stamp = SCodecStamp::Get(SCodecStamp::FULL)
			) : __stamp(stamp), __data(move(init)) {
				/**
				 * prepare
				 */
				if (__stamp.get().size() < UINT8_MAX) {
					throw nullptr;
				}
				/**
				 */
				__capacity = __data.size();
				__length = __data.size();
			}
			/**
			 *  move constructor
			 */
			Encoder(Encoder&& codec) 
			: __capacity(0), __length(0), __stamp(SCodecStamp::Get(SCodecStamp::FULL)) {
				Encoder::operator=(move(codec));
			}
			/**
			 * destructor
			 */
			virtual ~Encoder() = default;
			/**
			 * move 
			 */
			inline Encoder& operator=(Encoder&& en) {
				__capacity = move(en.__capacity);
				__length = move(en.__length);
				__stamp = move(en.__stamp);
				__data = move(en.__data);
				return *this;
			}
			/**
			 * push data
			 */
			Encoder& push(Frame&& data);
			Encoder& push(Container&& data);
			/**
			 * pop data
			 */
			Container pop(uint32_t highDensity = 0);
			/**
			 * clear data
			 */
			void clear();
			/**
			 * iterators 
			 */
			typedef Container::const_iterator const_iterator;
			const_iterator begin() const {
				return __data.begin();
			}
			const_iterator end() const {
				return __data.end();
			}
			/**
			 * utilities
			 */
			inline bool full() {
				return (__data.size() >= __capacity);
			}
			inline uint32_t size() {
				return __data.size();
			}
			inline uint32_t capacity() {
				return __capacity;
			}
			inline uint32_t length() {
				return __length;
			}
			inline uint32_t nframesize(){
				return __data.at(0).size() + SCodec::HeaderSize();
			}
			/**
			 * set properties
			 */
			inline Encoder& length(uint32_t len) {
				__length = len; 
				return *this;
			}
		private:
			/**
			 * context
			 */
			uint32_t __capacity;
			uint32_t __length;
			/**
			 */
			StampReference __stamp;
			Container __data;
			/**
			 * seed generator
			 */
			Random __rand;
		};

		/*----------------------------------------------------------------------------------------*
		 * Decoder class
		 *----------------------------------------------------------------------------------------*/
		class Decoder {
		public:
			Decoder() : __stamp(SCodecStamp::Get(SCodecStamp::FULL)), __capacity(0), __size(0){
			}
			/**
			 *  constructor
			 * @param codeSize
			 */
			Decoder(
				uint32_t capacity,
				const Stamp& stamp = SCodecStamp::Get(SCodecStamp::FULL)
			) : __stamp(stamp), __capacity(capacity) {
				__coef.reserve(capacity << 1);
				__data.reserve(capacity << 1);
				__field.reserve(capacity << 1);
			}
			Decoder(
				uint32_t capacity,
				Container&& init,
				const Stamp& stamp = SCodecStamp::Get(SCodecStamp::FULL)
			) : Decoder(capacity, stamp){
				push(move(init));
			}
			Decoder(Decoder&& codec): Decoder() {
				Decoder::operator=(move(codec));
			}
			/**
			 * destructor 
			 */
			virtual ~Decoder() = default;
			/**
			 * move 
			 */
			inline Decoder& operator=(Decoder&& de) {
				swap(__capacity, de.__capacity);
				swap(__size, de.__size);
				swap(__data, de.__data);
				swap(__coef, de.__coef);
				swap(__field, de.__field);
				swap(__stamp, de.__stamp);
				return *this;
			}
			/**
			 * push data
			 */
			Decoder& push(Frame&& data);
			Decoder& push(Container&& data);
			/**
			 * pop data
			 */
			Container pop();
			/**
			 * clear data
			 */
			void clear();
			/**
			 * iterators 
			 */
			typedef Container::const_iterator const_iterator;
			const_iterator begin() const {
				return __data.begin();
			}
			const_iterator end() const {
				return __data.begin() + __size;
			}
			typedef Container::const_reverse_iterator const_reverse_iterator;
			const_reverse_iterator rbegin() const {
				return __data.rend() - __size;
			}
			const_reverse_iterator rend() const {
				return __data.rend();
			}
			/**
			 * references 
			 */
			typedef Container::const_reference const_reference;
			const_reference front() const {
				return __data.front();
			}
			const_reference at(size_t n) const {
				return __data.at(n);
			}
			const_reference back() const {
				return __data.at(__size - 1);
			}
			/**
			 * utilities
			 */
			inline bool full() {
				return (__size >= __capacity);
			}
			inline bool empty() {
				return (__size == 0);
			}
			inline uint32_t size() {
				return __size;
			}
			inline uint32_t capacity() {
				return __capacity;
			}
			inline void resize(uint32_t size) {
				__data.resize(size);
				__coef.resize(size);
				__field.resize(size);
				if (__size > size) {
					__size = size;
				}
			}
		private:
			/**
			 * context
			 */
			Container __data;
			Container __coef;
			Frame __field;
			/**
			 */
			StampReference __stamp;
			uint32_t __capacity;
			uint32_t __size;
			/**
			 * seed generator
			 */
			Random __rand;
		};
		/*----------------------------------------------------------------------------------------*
		 * base codec functions
		 *----------------------------------------------------------------------------------------*/
		static uint32_t Encode(
			Container& code, uint32_t size, Container& data, Random& rand, uint32_t highDensity, const Stamp& stamp
		);
		/** 
		 */
		static uint32_t Decode(
			Container&& code, uint32_t capacity, Container& data, Container& coefs, Frame& fields, const Stamp& stamp 
		);
		/**
		 */
		static inline uint32_t HeaderSize() {
			return (sizeof (uint32_t)); // seed
		}
	};
}
#endif /* SCODEC_H */
