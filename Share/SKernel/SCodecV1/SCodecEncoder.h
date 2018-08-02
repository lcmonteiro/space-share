/* 
 * File:   SCodecEncoder.h
 * Author: Luis Monteiro
 *
 * Created on November 30, 2017, 5:48 PM
 */
#ifndef SCODECENCODER_H
#define SCODECENCODER_H
/**
 */
#include "SKernel/SContainer.h"
/**
 */
#include "SCodec.h"
/**
 */
namespace v1 {
        /*-------------------------------------------------------------------------------------------------------------*
         * Encoder class
         *-------------------------------------------------------------------------------------------------------------*/
        class SCodecEncoder: private SCodec {
        public:
                /**
                 * default constructor
                 */
                SCodecEncoder() : __capacity(0), __length(0), __stamp(SCodecStamp::Get(SCodecStamp::FULL)) {
                }
                /**
                 * constructor
                 * @param capacity
                 * @param stamp
                 */
                SCodecEncoder(uint32_t capacity, const Stamp& stamp = SCodecStamp::Get(SCodecStamp::FULL)) 
                : __capacity(capacity), __length(capacity), __stamp(stamp) {
                        // checkup
                        if (__stamp.get().size() < UINT8_MAX) {
                                throw nullptr;
                        }
                        // update
                        __data.reserve(__capacity);
                }
                /**
                 * constructor
                 * @param init
                 * @param stamp
                 */
                SCodecEncoder(Container && init, const Stamp& stamp = SCodecStamp::Get(SCodecStamp::FULL))
                : __stamp(stamp), __data(move(init)) {
                        // checkup
                        if (__stamp.get().size() < UINT8_MAX) {
                                throw nullptr;
                        }
                        // update
                        __capacity = __data.size();
                        __length = __data.size();
                }
                /**
                 *  move constructor
                 */
                SCodecEncoder(SCodecEncoder&& codec)
                : __capacity(0), __length(0), __stamp(SCodecStamp::Get(SCodecStamp::FULL)) {
                        SCodecEncoder::operator=(move(codec));
                }
                /**
                 * destructor
                 */
                virtual ~SCodecEncoder(){
                }
                /**
                 * move 
                 */
                inline SCodecEncoder& operator=(SCodecEncoder&& en) {
                        __capacity = move(en.__capacity);
                        __length = move(en.__length);
                        __stamp = move(en.__stamp);
                        __data = move(en.__data);
                        return *this;
                }
                /**
                 * push data
                 */
                inline SCodecEncoder& push(Frame&& data) {
                        //
                        __data.push_back(move(data));
                        //
                        return *this;
                }
                inline SCodecEncoder& push(Container&& data) {
                        //
                        for (auto& d : data) {
                                __data.push_back(move(d));
                        }
                        //
                        return *this;
                }
                /**
                 * pop data
                 */
                inline Container pop(uint32_t highDensity = 0) {
                        Container out;
                        //
                        SCodec::Encode(out, __length, __data, __rand, highDensity, __stamp.get());
                        //
                        return out;
                }
                /**
                 * clear data
                 */
                inline SCodecEncoder& clear(){
                        //
                        __data.clear();
                        //
                        return *this;
                }
                /**
                 * iterators 
                 */
                typedef Container::const_iterator const_iterator;
                //
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
                inline uint32_t nframesize() {
                        return __data.at(0).size() + SCodec::HeaderSize();
                }
                /**
                 * set properties
                 */
                inline SCodecEncoder& length(uint32_t len) {
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
                 * data
                 */
                StampReference __stamp;
                Container __data;
                /**
                 * seed generator
                 */
                Random __rand;
        };
}
#endif /* SCODECENCODER_H */
