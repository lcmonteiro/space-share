/*
 * File:   h
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
class SIFrame;
class SOFrame;
typedef class SFrame : public std::vector<uint8_t> {
public:
    using Super = std::vector<uint8_t>;
    /**
     * ------------------------------------------------------------------------
     * initialization
     * ------------------------------------------------------------------------
     * constructors
     * ----------------------------------------------------
     */
    SFrame(const size_t capacity, const size_t size=0, const uint8_t value=0)
    : Super() {
        Capacity(capacity).assign(size, value);
    }
    SFrame(const size_t capacity, const_iterator beg, const_iterator end)
    : Super() {
        Capacity(capacity).assign(beg, end);
    }
    SFrame(const_iterator beg, const_iterator end)
    : Super(beg, end) {
    }
    SFrame(std::initializer_list<uint8_t> l) 
    : Super(l) {
    }

    /**
     * ------------------------------------------------------------------------
     * conversions
     * ------------------------------------------------------------------------
     * constructors
     * ----------------------------------------------------
     */
    SFrame()               = default;
    SFrame(SFrame&&)       = default;
    SFrame(SIFrame&&);
    SFrame(SOFrame&&);
    SFrame(const SFrame&)  = default;
    SFrame(const SIFrame&);
    SFrame(const SOFrame&);
    /**
     * ----------------------------------------------------
     * operations
     * ----------------------------------------------------
     */ 
    inline SFrame& operator=(SFrame&&  f) = default;
    inline SFrame& operator=(SIFrame&& f) {
        return __Consume(SFrame(std::move(f)));
    }
    inline SFrame& operator=(SOFrame&& f) {
        return __Consume(SFrame(std::move(f)));
    } 
    inline SFrame& operator=(const SFrame&  f) = default;
    inline SFrame& operator=(const SIFrame& f) {
        return __Consume(SFrame(f));
    }
    inline SFrame& operator=(const SOFrame& f) {
        return __Consume(SFrame(f));
    }
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
    inline SFrame& Shrink(size_t size = 0) {
        if (Size() < size) {
            throw FrameException(SText("Shrink=(", Size(), "<", size, ")"));
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
protected:
    /**
     * ------------------------------------------------------------------------
     * consume
     * ------------------------------------------------------------------------
     */
    inline SFrame& __Consume(SFrame&& f) {
        // consume super ----------------------------------
        Super::operator=(std::move(f));
        // return this frame ------------------------------
        return *this;
    }
} Frame;
/**
 * ------------------------------------------------------------------------------------------------
 * SIFrame
 * ------------------------------------------------------------------------------------------------
 */
typedef class SIFrame : public SFrame {
public:
    /**
     * ------------------------------------------------------------------------
     * initialization 
     * ------------------------------------------------------------------------
     * constructor
     * ----------------------------------------------------
     */
    SIFrame(size_t capacity) 
    : SFrame(capacity), __it(begin()) { Expand(); }
    /**
     * ------------------------------------------------------------------------
     * conversions
     * ------------------------------------------------------------------------
     * constructors
     * ----------------------------------------------------
     */
    SIFrame();
    SIFrame(SFrame&&  f);
    SIFrame(SIFrame&& f);
    SIFrame(SOFrame&& f);
    SIFrame(const SFrame& f);
    SIFrame(const SIFrame& f);
    SIFrame(const SOFrame& f);
    /**
     * ----------------------------------------------------
     * operators
     * ----------------------------------------------------
     */
    template<typename T> 
    SIFrame& operator=(T&& f) {
        return __Consume(SIFrame(std::move(f)));
    } 
    template<typename T> 
    SIFrame& operator=(const T& f) {
        return __Consume(SIFrame(f));
    }
    /**
     * ------------------------------------------------------------------------
     * capacity
     * ------------------------------------------------------------------------
     */
    inline size_t Capacity() const {
        return size();
    }
    /**
     * ------------------------------------------------------------------------
     * position
     * ------------------------------------------------------------------------
     * begin position
     * ----------------------------------------------------
     */
    inline SIFrame& Reset() {
        __it = begin();
        return *this;
    }
    /**
     * ----------------------------------------------------
     * move position forward (n)
     * ----------------------------------------------------
     */
    inline SIFrame& Insert(size_t n) {
        __it = std::next(__it, n);
        return *this;
    }
    /**
     * ----------------------------------------------------
     * seek to position (p)
     * ----------------------------------------------------
     */
    inline SIFrame& Seek(size_t p) {
        __it = std::next(begin(), p);
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
    inline size_t Size() const {
        return distance(SFrame::const_iterator(__it), end());
    }
    /**
     * ------------------------------------------------------------------------
     * shrink frame
     * ------------------------------------------------------------------------
     */
    inline SIFrame& Shrink() {
        resize(std::distance(begin(), __it));
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * expand frame
     * ------------------------------------------------------------------------
     */
    inline SIFrame& Expand() {
        resize(capacity());
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
            auto sz_cur = size();
            // resize vector ------------------------------    
            resize(sz_cur + sz - sz_rem);
            // reset pointer ------------------------------
            __it = begin() + sz_cur;
        }
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * write frame
     * ------------------------------------------------------------------------
     */
    inline SIFrame& Write(const SFrame& frame) {
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
            begin(), std::next(begin(), offset), __it
        );
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * check size
     * ------------------------------------------------------------------------
     */
    inline bool Empty() const {
        return (__it <= begin());
    }
    inline bool Full() const {
        return (__it >= end());
    }
protected:
    /**
     * ------------------------------------------------------------------------
     * consume
     * ------------------------------------------------------------------------
     */
    inline SIFrame& __Consume(SIFrame&& f) {
        // consume super ----------------------------------
        Super::operator=(std::move(f));
        // consume itrator --------------------------------
        __it = std::move(f.__it);
        // return this frame ------------------------------
        return *this;
    }
private:
    friend class SOFrame;
    /**
     * ------------------------------------------------------------------------
     * variable
     * ------------------------------------------------------------------------
     **
     * iterator
     */
    iterator __it;
} IFrame;
/**
 * ------------------------------------------------------------------------------------------------
 * OFrame
 * ------------------------------------------------------------------------------------------------
 */
typedef class SOFrame: public SFrame {
public:
    /**
     * ------------------------------------------------------------------------
     * conversions
     * ------------------------------------------------------------------------
     * constructors
     * ----------------------------------------------------
     */
    SOFrame();
    SOFrame(SFrame&&  f);
    SOFrame(SIFrame&& f);
    SOFrame(SOFrame&& f);
    SOFrame(const SFrame& f);
    SOFrame(const SIFrame& f);
    SOFrame(const SOFrame& f);
    /**
     * ----------------------------------------------------
     * operators
     * ----------------------------------------------------
     */
    template<typename T> 
    SOFrame& operator=(T&& f) {
        return __Consume(SOFrame(std::move(f)));
    }
    template<typename T> 
    SOFrame& operator=(const T& f) {
        return __Consume(SOFrame(f));
    }
     /**
     * ------------------------------------------------------------------------
     * position
     * ------------------------------------------------------------------------
     * begin position
     * ----------------------------------------------------
     */
    inline SOFrame& Reset() {
        __it = begin();
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
        __it = next(begin(), p);
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
    inline size_t Size() const {
        return distance(SFrame::const_iterator(__it), end());
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
        std::rotate(begin(), __it, end()); 
        // reset ------------------------------------------
        Reset();
        // resize -----------------------------------------
        resize(sz);
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
        return (__it >= end());
    }
    inline bool Full() const {
        return (__it <= begin());
    }
protected:
    /**
     * ------------------------------------------------------------------------
     * consume
     * ------------------------------------------------------------------------
     */
    inline SOFrame& __Consume(SOFrame&& f) {
        // consume super ----------------------------------
        Super::operator=(std::move(f));
        // consume itrator --------------------------------
        __it = std::move(f.__it);
        // return this frame ------------------------------
        return *this;
    }
private:
    friend class SIFrame;
    /**
     * ------------------------------------------------------------------------
     * variable
     * ------------------------------------------------------------------------
     * iterator 
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

