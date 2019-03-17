/**
 * --------------------------------------------------------------------------------------------------------------------
 * File:   SCodecDecoder.h
 * Author: Luis Monteiro
 *
 * Created on November 30, 2015, 5:48 PM
 * --------------------------------------------------------------------------------------------------------------------
 */
#ifndef SCODECDECODER_H
#define SCODECDECODER_H
/**
 * Space Kernel
 */
#include "SContainer.h"
/**
 * Share Kernel
 */
#include "SCodec.h"
/**
 */
namespace v1 {
    /**
     * ----------------------------------------------------------------------------------------------------------------
     * CodecDecoder 
     * ----------------------------------------------------------------------------------------------------------------
     */
    class SCodecDecoder: private SCodec {
    public:
        /**
         * ----------------------------------------------------------------------------------------
         * Constructors & Desctructor
         * ----------------------------------------------------------------------------------------
         * constructor
         */
        SCodecDecoder():
        __capacity(0),
        __size(0),
        __data(),
        __coef(),
        __field(),
        __stamp(SCodecStamp::Get(SCodecStamp::FULL)) {}
        /**
         * constructor
         * @param capacity
         * @param stamp
         */
        SCodecDecoder(uint32_t capacity, const Stamp& stamp = SCodecStamp::Get(SCodecStamp::FULL)): 
        __capacity(capacity),
        __size(0),
        __data(),
        __coef(),
        __field(),
        __stamp(stamp) {
            __coef.reserve(capacity << 1);
            __data.reserve(capacity << 1);
            __field.reserve(capacity << 1);
        }
        /**
         * constructor
         * @param capacity
         * @param init
         * @param stamp
         */
        SCodecDecoder(
            uint32_t capacity, Container&& init, const Stamp& stamp = SCodecStamp::Get(SCodecStamp::FULL)
        ) : SCodecDecoder(capacity, stamp) {
            push(std::move(init));
        }
        /**
         * constructor
         * @param codec
         * @return 
         */
        SCodecDecoder(SCodecDecoder&& codec) : SCodecDecoder() {
            SCodecDecoder::operator=(std::move(codec));
        }
        /**
         * destructor 
         */
        virtual ~SCodecDecoder() {
        }
        /**
         * ----------------------------------------------------------------------------------------
         *  Operators
         * ----------------------------------------------------------------------------------------
         **
         * move 
         */
        inline SCodecDecoder& operator=(SCodecDecoder&& de) {
            __capacity = std::move(de.__capacity);
            __size     = std::move(de.__size    );
            __data     = std::move(de.__data    );
            __coef     = std::move(de.__coef    );
            __field    = std::move(de.__field   );
            __stamp    = std::move(de.__stamp   );
            return *this;
        }
        /**
         * ----------------------------------------------------------------------------------------
         * Data
         * ----------------------------------------------------------------------------------------
         **
         * push data
         */
        SCodecDecoder& push(Frame&& data) {
            // decode
            __size = SCodec::Decode(
                Container({std::move(data)}), __capacity, __data, __coef, __field, __stamp.get()
            );
            return *this;    
        }
        SCodecDecoder& push(Container&& data) {
            // decode
            __size = SCodec::Decode(std::move(data), __capacity, __data, __coef, __field, __stamp.get());
            return *this;
        }
        /**
         * pop data
         */
        inline Container pop() {
            Container out;
            // move data to out container
            out = std::move(__data);
            out.resize(__size);
            // reset
            clear();
            // return 
            return out;
        }
        /**
         * clear data
         */
        inline SCodecDecoder& clear() {
            __size = 0;
            __coef.clear();
            __coef.reserve(__capacity << 1);
            __data.clear();
            __data.reserve(__capacity << 1);
            __field.clear();
            __field.reserve(__capacity << 1);
            return *this;
        }
        /**
         * ----------------------------------------------------------------------------------------
         * iterators 
         * ----------------------------------------------------------------------------------------
         */
        typedef Container::const_iterator const_iterator;
        /**
         */
        const_iterator begin() const {
            return __data.begin();
        }
        const_iterator end() const {
            return __data.begin() + __size;
        }
        typedef Container::const_reverse_iterator const_reverse_iterator;
        /**
         * reverse
         */
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
        /**
         */
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
         * ----------------------------------------------------------------------------------------
         * Quantity
         * ----------------------------------------------------------------------------------------
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
         * ----------------------------------------------------------------------------------------
         * variables
         * ----------------------------------------------------------------------------------------
         **
         * cache
         */
        Container __data;
        Container __coef;
        Frame __field;
        /**
         * context
         */
        StampReference __stamp;
        uint32_t __capacity;
        uint32_t __size;
        /**
         * seed generator
         */
        Random __rand;
    };
    /**
     * ----------------------------------------------------------------------------------------------------------------
     * End
     * ----------------------------------------------------------------------------------------------------------------
     */
}
#endif /* SCODEC_H */
