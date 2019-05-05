/**
 * ------------------------------------------------------------------------------------------------
 * File:   SCodecDecoder.h
 * Author: Luis Monteiro
 *
 * Created on November 30, 2015, 5:48 PM
 * ------------------------------------------------------------------------------------------------
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
#include "SEngineCodec.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Codec Decoder
 * ------------------------------------------------------------------------------------------------
 */
namespace Codec {
/**
 */    
class SDecoder: private SEngine {
public:
    /**
     * ------------------------------------------------------------------------
     * Constructors
     * ------------------------------------------------------------------------
     * constructor
     * ----------------------------------------------------
     */
    SDecoder():
    __data(),
    __coef(),
    __field(),
    __stamp(SStamp::Get(SStamp::FULL)), 
    __capacity(0),
    __size(0),
    __rand() {}
    /**
     * ----------------------------------------------------
     * constructor
     * @param capacity
     * @param stamp
     * ----------------------------------------------------
     */
    SDecoder(
        uint32_t capacity, 
        pStamp stamp = SStamp::Get(SStamp::FULL)): 
    __data(),
    __coef(),
    __field(capacity << 1),
    __stamp(stamp), 
    __capacity(capacity),
    __size(0),
    __rand() {
        __coef.reserve(capacity << 1);
        __data.reserve(capacity << 1);
    }
    /**
     * ----------------------------------------------------
     * constructor
     * @param capacity
     * @param init
     * @param stamp
     * ----------------------------------------------------
     */
    SDecoder(
        uint32_t capacity, 
        Container&& init, 
        pStamp stamp = SStamp::Get(SStamp::FULL)
    ) : SDecoder(capacity, stamp) {
        push(std::move(init));
    }
    /**
     * ----------------------------------------------------
     * constructor
     * @param codec
     * @return 
     * ----------------------------------------------------
     */
    SDecoder(SDecoder&& codec) : SDecoder() {
        *this = std::move(codec);
    }
    /**
     * ------------------------------------------------------------------------
     * Operators
     * ------------------------------------------------------------------------
     * move 
     * ----------------------------------------------------
     */
    inline SDecoder& operator=(SDecoder&& de) {
        __capacity = std::move(de.__capacity);
        __size     = std::move(de.__size    );
        __data     = std::move(de.__data    );
        __coef     = std::move(de.__coef    );
        __field    = std::move(de.__field   );
        __stamp    = std::move(de.__stamp   );
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Data
     * ------------------------------------------------------------------------
     * push data
     * ----------------------------------------------------
     */
    SDecoder& push(Frame&& data) {
        /**
         * decode
         */
        __size = Decode(
            Container({std::move(data)}), 
            __capacity, 
            __data, 
            __coef, 
            __field,
            *__stamp
        );
        /**
         * return itself
         */
        return *this;    
    }
    SDecoder& push(Container&& data) {
        /**
         * decode
         */
        __size = Decode(
            std::move(data), 
            __capacity, 
            __data, 
            __coef, 
            __field, 
            *__stamp
        );
        /**
         * return itself
         */
        return *this;
    }
    /**
     * ----------------------------------------------------
     * pop data
     * ----------------------------------------------------
     */
    inline Container pop() {
        /**
         * move data
         */
        Container out = std::move(__data);
        /**
         * update size
         */
        out.resize(__size);
        /**
         * reset
         */
        clear();
        /**
         * return decoded container
         */
        return out;
    }
    /**
     * ----------------------------------------------------
     * clear data
     * ----------------------------------------------------
     */
    inline SDecoder& clear() {
        __size = 0;
        __coef.clear();
        __data.clear();
        __field.clear();
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Iterators 
     * ------------------------------------------------------------------------
     */
    using const_iterator         = Container::const_iterator;
    using const_reverse_iterator = Container::const_reverse_iterator;
    using const_reference        = Container::const_reference;
    /**
     * ----------------------------------------------------
     * forward 
     * ----------------------------------------------------
     */
    const_iterator begin() const {
        return __data.begin();
    }
    const_iterator end() const {
        return __data.begin() + __size;
    }
    /**
     * ----------------------------------------------------
     * Reverse
     * ----------------------------------------------------
     */
    const_reverse_iterator rbegin() const {
        return __data.rend() - __size;
    }
    const_reverse_iterator rend() const {
        return __data.rend();
    }
    /**
     * ------------------------------------------------------------------------
     * References 
     * ------------------------------------------------------------------------
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
     * ------------------------------------------------------------------------
     * Quantity
     * ------------------------------------------------------------------------
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
     * ------------------------------------------------------------------------
     * Variables
     * ------------------------------------------------------------------------
     **
     * cache
     */
    Container __data;
    Container __coef;
    Frame     __field;
    /**
     * context
     */
    pStamp    __stamp;
    uint32_t  __capacity;
    uint32_t  __size;
    /**
     * seed generator
     */
    Random __rand;
};
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
}
#endif /* SCODEC_H */
