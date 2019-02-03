/*
 * File:   SFrame.h
 * Author: Luis Monteiro
 *
 * Created on February  2, 2019, 10:21 AM
 */
#ifndef SFRAME_H
#define SFRAME_H
/**
 * std
 */
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
/**
 * space
 */
#include "SText.h"
/**
 * -------------------------------------------------------------------------------------------------
 * Helpers
 * -------------------------------------------------------------------------------------------------
 **/
#if __GNUC__ < 5
#include <sstream>
template <typename T>
std::string __to_string(T val) {
    std::stringstream stream;
    stream << val;
    return stream.str();
}
template <class ForwardIt>
ForwardIt __rotate(ForwardIt first, ForwardIt n_first, ForwardIt last) {
    rotate(first, n_first, last);
    return first + (last - n_first);
}
#else
template <typename T>
std::string __to_string(T val) {
    return to_string(val);
}
template <class ForwardIt>
ForwardIt __rotate(ForwardIt first, ForwardIt n_first, ForwardIt last) {
    return rotate(first, n_first, last);
}
#endif
/**
 * ------------------------------------------------------------------------------------------------
 * Exceptions
 * ------------------------------------------------------------------------------------------------
 **/
typedef class SFrameException : public std::range_error {
public:
    using std::range_error::range_error;
} FrameException;
/**
 * ------------------------------------------------------------------------------------------------
 * Frame
 * -------------------------------------------------------------------------------------------------
 **/
typedef class SFrame : public std::vector<uint8_t> {
public:
    using Super = std::vector<uint8_t>;
    /**
     * ------------------------------------------------------------------------
     * using from super
     * ------------------------------------------------------------------------
     **/
    using Super::Super;
    /**
     * ------------------------------------------------------------------------
     * constructors
     * ------------------------------------------------------------------------
     * initialization
     */
    SFrame(const size_t  size, const size_t  capacity, const uint8_t value = 0)
    : Super() {
        reserve(capacity); 
        assign(size, value);
    }
    /**
     * string 
     */
    SFrame(const std::string& s) : Super(s.begin(), s.end()) {
    }
    /**
     * ------------------------------------------------------------------------
     * sum values
     * ------------------------------------------------------------------------
     */
    uint32_t Sum(uint32_t max) {
        uint32_t s = 0;
        for (auto it = begin(); it != end() && s < max; ++it) {
            s += *it;
        }
        return s;
    }
    /**
     * ------------------------------------------------------------------------
     * unserialize number
     * ------------------------------------------------------------------------
     */
    template <class T>
    T Number() const {
        // set iterator position --------------------------
        auto rit = rbegin();
        for (auto i = 0; (i < sizeof (T)) && (rit != rend()); ++i, ++rit);
        // decode number ----------------------------------
        T result = 0;
        for (auto it = rit.base(); it != end(); ++it) {
            result <<= 8;
            result |= T(*it);
        }
        return result;
    }
    /**
     * ------------------------------------------------------------------------
     * serialize number
     * ------------------------------------------------------------------------
     */
    template <class T>
    SFrame& Number(T val) {
        // encode number ----------------------------------
        size_t i = 0;
        for (auto it = rbegin(); (it != rend()) && (i < sizeof (T)); ++it, ++i) {
            *it = value_type(val);
            val >>= 8;
        }
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * get data
     * ------------------------------------------------------------------------
     */
    inline pointer Data() {
        return data();
    }
    /**
     * ------------------------------------------------------------------------
     * get size
     * ------------------------------------------------------------------------
     */
    inline size_t Size() const {
        return size();
    }
    /**
     * ------------------------------------------------------------------------
     * insert size -> resize
     * ------------------------------------------------------------------------
     */
    inline SFrame& Insert(size_t size) {
        resize(size);
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Remove size -> resize(-size)
     * ------------------------------------------------------------------------
     */
    inline SFrame& Remove(size_t size) {
        if(Size() != size){
            std::rotate(begin(), std::next(begin(), size), end());
            resize(Size() - size);
        } else {
            resize(0);
        } 
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Shrink to size -> resize 
     *  - throw exception when size > Size()
     * ------------------------------------------------------------------------
     */
    inline SFrame& Shrink(size_t size) {
        if (Size() < size) {
            throw FrameException(
                SText("Shrink=(", Size(), "<", size, ")")
            );
        }
        resize(size);
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * expand to capacity
     * ------------------------------------------------------------------------
     */
    inline SFrame& Expand() {
        resize(capacity());
        return *this;
    }
} Frame;
/**
 * ------------------------------------------------------------------------------------------------
 * SIFrame
 * ------------------------------------------------------------------------------------------------
 */
typedef class SIFrame : public Frame {
public:
    /**
     * ------------------------------------------------------------------------
     * defaults
     * ------------------------------------------------------------------------
     */
    SIFrame()                       = default;
    SIFrame(SIFrame&&)              = default;
    SIFrame(const SIFrame&)         = default;
    SIFrame& operator=(SIFrame&& f) = default;
    /**
     * ------------------------------------------------------------------------
     * constructors
     * ------------------------------------------------------------------------
     */
    SIFrame(size_t capacity) 
    : Frame(capacity), __cur(begin()) {
    }
    SIFrame(Frame&& f) 
    : Frame(std::move(f)), __cur(begin()) {
    }
    SIFrame(const Frame& f) 
    : Frame(f), __cur(begin()) {
    }
    /**
     * ------------------------------------------------------------------------
     * shrink frame
     * ------------------------------------------------------------------------
     */
    inline SIFrame& Shrink() {
        resize(distance(begin(), __cur));
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * get data
     * ------------------------------------------------------------------------
     */
    inline pointer Data() {
        return __cur.base();
    }
    /**
     * ------------------------------------------------------------------------
     * get size
     * ------------------------------------------------------------------------
     */
    inline size_t Size() {
        return distance(__cur, end());
    }
    /**
     * ------------------------------------------------------------------------
     * reserve size
     * ------------------------------------------------------------------------
     */
    inline SIFrame& Reserve(size_t sz) {
        auto sz_rem = Size();
        if (sz > sz_rem) {
            auto sz_cur = size();
            // resize vector ------------------------------    
            resize(sz_cur + sz - sz_rem);
            // reset pointer ------------------------------
            __cur = begin() + sz_cur;
        }
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * insert size
     * ------------------------------------------------------------------------
     */
    inline SIFrame& Insert(size_t size) {
        __cur += size;
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * write frame
     * ------------------------------------------------------------------------
     */
    inline SIFrame& Write(const Frame& frame) {
        __cur = copy(frame.begin(), frame.end(), __cur);
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * seek to position given by (pos)
     * ------------------------------------------------------------------------
     */
    inline SIFrame& Seek(size_t pos) {
        __cur = next(begin(), pos);
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * shift to position given by (offset)
     * ------------------------------------------------------------------------
     */
    inline SIFrame& Shift(size_t offset) {
        __cur = __rotate(begin(), next(begin(), offset), __cur);
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * check size
     * ------------------------------------------------------------------------
     */
    inline bool Empty() const {
        return (__cur <= begin());
    }
    inline bool Full() const {
        return (__cur >= end());
    }
private:
    /**
     * ------------------------------------------------------------------------
     * variable
     * ------------------------------------------------------------------------
     */
    iterator __cur;
} IFrame;
/**
 * ------------------------------------------------------------------------------------------------
 * OFrame
 * ------------------------------------------------------------------------------------------------
 */
typedef class SOFrame : public Frame {
public:
    /**
     * ------------------------------------------------------------------------
     * defaults
     * ------------------------------------------------------------------------
     */
    SOFrame()                          = default;
    SOFrame(SOFrame&&)                 = default;
    SOFrame(const SOFrame&)            = default;
    SOFrame& operator=(SOFrame&&)      = default;
    SOFrame& operator=(const SOFrame&) = default;
    /**
     * ------------------------------------------------------------------------
     * constructors
     * ------------------------------------------------------------------------
     */
    SOFrame(SFrame&& f) 
    : Frame(std::move(f)), __cur(begin()) {
    }
    SOFrame(const SFrame& f) 
    : Frame(f), __cur(begin()) {
    }
    /**
     * ------------------------------------------------------------------------
     * get data pointer
     * ------------------------------------------------------------------------
     */
    inline pointer Data() {
        return __cur.base();
    }
    /**
     * ------------------------------------------------------------------------
     * get size
     * ------------------------------------------------------------------------
     */
    inline size_t Size() {
        return distance(__cur, end());
    }
    /**
     * ------------------------------------------------------------------------
     * remove size
     * ------------------------------------------------------------------------
     */
    inline SOFrame& Remove(size_t size) {
        __cur += size;
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Read frame
     */
    inline SFrame Read(size_t size) {
        // size check -------------------------------------
        if (Size() < size) {
            throw FrameException(
                SText("Read=(", Size(), "<", size, ")")
            );
        }
        // move reference ---------------------------------
        auto prev = __cur; __cur += size;
        // copy to new frame ------------------------------
        return SFrame(prev, __cur);
    }
    /**
     * ------------------------------------------------------------------------
     * check size 
     * ------------------------------------------------------------------------
     */
    inline bool Empty() const {
        return (__cur >= end());
    }
    inline bool Full() const {
        return (__cur <= begin());
    }
private:
    /**
     * ------------------------------------------------------------------------
     * variable
     * ------------------------------------------------------------------------
     */
    iterator __cur;
} OFrame;
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SFRAME_H */

