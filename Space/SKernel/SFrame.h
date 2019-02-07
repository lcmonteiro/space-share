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
#include <ostream>
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
        Capacity(capacity).assign(size, value);
    }
    /**
     * string 
     */
    SFrame(const std::string& s) : Super(s.begin(), s.end()) {
    }
    /**
     * ------------------------------------------------------------------------
     * convertions
     * ------------------------------------------------------------------------
     */
    template<typename T> SFrame& operator=(T&& f);
    template<typename T> SFrame& operator=(T&  f);
    /**
     * ------------------------------------------------------------------------
     * set capacity
     * ------------------------------------------------------------------------
     */
    inline SFrame& Capacity(size_t size) {
        reserve(size);
        return *this;
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
    /**
     * ------------------------------------------------------------------------
     * shift to position given by (offset)
     * ------------------------------------------------------------------------
     */
    inline SFrame& Shift(size_t offset) {
        std::rotate(
            begin(), next(begin(), offset), end()
        );
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * check size 
     * ------------------------------------------------------------------------
     */
    inline SFrame&& Detach() {
        return std::move(*this);
    }
} Frame;
/**
 * ------------------------------------------------------------------------------------------------
 * SIFrame
 * ------------------------------------------------------------------------------------------------
 */
typedef class SIFrame {
public:
    using pointer = Frame::pointer;
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
     * constructor 
     * ------------------------------------------------------------------------
     */
    SIFrame(size_t capacity) : __frame(capacity), __it(__frame.begin()) {}
    /**
     * ------------------------------------------------------------------------
     * Frame - interface
     * ------------------------------------------------------------------------
     * constructors
     * ----------------------------------------------------
     * move
     */
    SIFrame(SFrame&& f)
    : __frame(std::move(f)), __it(__frame.end()) {}
    /**
     * copy
     */
    SIFrame(const SFrame& f)
    : __frame(f), __it(__frame.end()) {}
    /**
     * ----------------------------------------------------
     * convertions
     * ----------------------------------------------------
     */
    template<typename T> SIFrame& operator=(T&& f);
    template<typename T> SIFrame& operator=(const T& f);
    /**
     * ----------------------------------------------------
     *  cast operators
     * ----------------------------------------------------
     */
    operator SFrame&() {
        Shrink();
        return __frame;
    }
    // operator SFrame&&() { 
    //     return move(SFrame(__frame).Insert(std::distance(__frame.begin(), __it))); 
    // }
    /**
     * ------------------------------------------------------------------------
     * capacity
     * ------------------------------------------------------------------------
     */
    inline size_t Capacity() const {
        return __frame.size();
    }
    /**
     * ------------------------------------------------------------------------
     * position
     * ------------------------------------------------------------------------
     * begin position
     * ----------------------------------------------------
     */
    inline SIFrame& Reset() {
        __it = __frame.begin();
        return *this;
    }
    /**
     * ----------------------------------------------------
     * move position forward (n)
     * ----------------------------------------------------
     */
    inline SIFrame& Insert(size_t n) {
        __it = std::next(__frame.begin(), n);
        return *this;
    }
    /**
     * ----------------------------------------------------
     * seek to position (p)
     * ----------------------------------------------------
     */
    inline SIFrame& Seek(size_t p) {
        __it = std::next(__frame.begin(), p);
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * get data
     * ------------------------------------------------------------------------
     */
    inline pointer Data() {
        return __it.base();
    }
    /**
     * ------------------------------------------------------------------------
     * get size
     * ------------------------------------------------------------------------
     */
    inline size_t Size() {
        return std::distance(__it, __frame.end());
    }
    /**
     * ------------------------------------------------------------------------
     * shrink frame
     * ------------------------------------------------------------------------
     */
    inline SIFrame& Shrink() {
        __frame.resize(std::distance(__frame.begin(), __it));
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * expand frame
     * ------------------------------------------------------------------------
     */
    inline SIFrame& Expand() {
        __frame.resize(__frame.capacity());
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * reserve size (guaranty that exist size (sz) )
     * ------------------------------------------------------------------------
     */
    inline SIFrame& Reserve(size_t sz) {
        auto sz_rem = Size();
        // verify current size ----------------------------
        if (sz > sz_rem) {
            auto sz_cur = __frame.size();
            // resize vector ------------------------------    
            __frame.resize(sz_cur + sz - sz_rem);
            // reset pointer ------------------------------
            __it = __frame.begin() + sz_cur;
        }
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * write frame
     * ------------------------------------------------------------------------
     */
    inline SIFrame& Write(const Frame& frame) {
        __it = std::copy(frame.begin(), frame.end(), __it);
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * shift to position given by (offset)
     * ------------------------------------------------------------------------
     */
    inline SIFrame& Shift(size_t offset) {
        __it = __rotate(
            __frame.begin(), next(__frame.begin(), offset), __it
        );
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * check size
     * ------------------------------------------------------------------------
     */
    inline bool Empty() const {
        return (__it <= __frame.begin());
    }
    inline bool Full() const {
        return (__it >= __frame.end());
    }
private:
    /**
     * ------------------------------------------------------------------------
     * variable
     * ------------------------------------------------------------------------
     * frame
     */
    SFrame __frame;
    /**
     * iterator
     */
    SFrame::iterator __it;
} IFrame;
/**
 * ------------------------------------------------------------------------------------------------
 * OFrame
 * ------------------------------------------------------------------------------------------------
 */
typedef class SOFrame {
public:
    using pointer = Frame::pointer;
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
     * Frame - interface
     * ------------------------------------------------------------------------
     * constructors
     * ----------------------------------------------------
     * move
     */
    SOFrame(Frame&& f)
    : __frame(std::move(f)), __it(__frame.begin()) {}
    /**
     * copy
     */
    SOFrame(const Frame& f)
    : __frame(f), __it(__frame.begin()) {}
    /**
     * ----------------------------------------------------
     * convertions
     * ----------------------------------------------------
     */
    template<typename T> SOFrame& operator=(T&& f);
    template<typename T> SOFrame& operator=(const T& f);
    /**
     * ----------------------------------------------------
     * operators =
     * ----------------------------------------------------
     * move
     */
   
    /**
     * ----------------------------------------------------
     *  cast operators 
     * ----------------------------------------------------
     */
    operator Frame&() {
        Shrink();
        return __frame; 
    }
     /**
     * ------------------------------------------------------------------------
     * position
     * ------------------------------------------------------------------------
     * begin position
     * ----------------------------------------------------
     */
    inline SOFrame& Reset() {
        __it = __frame.begin();
        return *this;
    }
    /**
     * ----------------------------------------------------
     * move position forward (n)
     * ----------------------------------------------------
     */
    inline SOFrame& Remove(size_t n) {
        __it = next(__it, n);
        return *this;
    }
    /**
     * ----------------------------------------------------
     * seek to position (p)
     * ----------------------------------------------------
     */
    inline SOFrame& Seek(size_t p) {
        __it = next(__frame.begin(), p);
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * get data pointer
     * ------------------------------------------------------------------------
     */
    inline pointer Data() {
        return __it.base();
    }
    /**
     * ------------------------------------------------------------------------
     * get size
     * ------------------------------------------------------------------------
     */
    inline size_t Size() {
        return distance(__it, __frame.end());
    }
    /**
     * ------------------------------------------------------------------------
     * Shrink
     * ------------------------------------------------------------------------
     */
    inline SOFrame& Shrink() {
        // current size -----------------------------------  
        auto sz = Size();
        // rotate ----------------------------------------- 
        std::rotate(__frame.begin(), __it, __frame.end()); 
        // reset ------------------------------------------
        Reset();
        // resize -----------------------------------------
        __frame.resize(sz);
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Read frame
     * ------------------------------------------------------------------------
     */
    inline SFrame Read(size_t size) {
        // size check -------------------------------------
        if (Size() < size) {
            throw FrameException(
                SText("Read=(", Size(), "<", size, ")")
            );
        }
        // move reference ---------------------------------
        auto prev = __it; __it += size;
        // copy to new frame ------------------------------
        return SFrame(prev, __it);
    }
    /**
     * ------------------------------------------------------------------------
     * check size 
     * ------------------------------------------------------------------------
     */
    inline bool Empty() const {
        return (__it >= __frame.end());
    }
    inline bool Full() const {
        return (__it <= __frame.begin());
    }
private:
    /**
     * ------------------------------------------------------------------------
     * variable
     * ------------------------------------------------------------------------
     * frame
     */
    SFrame __frame;
    /**
     *iterator 
     */
    SFrame::iterator __it;
} OFrame;
/**
 * ------------------------------------------------------------------------------------------------
 * uilities
 * ------------------------------------------------------------------------------------------------
 **/
inline std::ostream& operator<<(std::ostream& os, const Frame& b) {
    os << "[";
    for (auto v : b) {
        os << int(v) << " ";
    }
    return os << "]";
}

/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SFRAME_H */

