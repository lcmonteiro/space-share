/**
 * ------------------------------------------------------------------------------------------------
 * File:   SFrame.h
 * Author: Luis Monteiro
 *
 * Created on February  2, 2019, 10:21 AM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SFRAME_H
#define SFRAME_H
/**
 * std
 */
#include <cstring>
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
class SIOFrame;
typedef class SFrame : public std::vector<uint8_t> {
public:
    /**
     * ------------------------------------------------------------------------
     * helpres
     * ------------------------------------------------------------------------
     * super class
     * ----------------------------------------------------
     */
    using Super = std::vector<uint8_t>;
    /**
     * ----------------------------------------------------
     * enable conditions
     * ----------------------------------------------------
     */
    template <typename ITERATOR>
    using if_iterator_t = std::enable_if_t<
        std::is_base_of<
            std::input_iterator_tag, 
            typename std::iterator_traits<ITERATOR>::iterator_category
        >::value
    >;
    /**
     * ------------------------------------------------------------------------
     * initialization
     * ------------------------------------------------------------------------
     * constructors
     * ----------------------------------------------------
     */
    SFrame(const size_t capacity, const size_t size=0, const uint8_t value=0)
    : Super() {
        reserve(capacity); assign(size, value);
    }
    template<typename T, typename = if_iterator_t<T>>
    SFrame(const size_t capacity, T beg, T end)
    : Super() {
        reserve(capacity); assign(beg, end);
    }
    template<typename T, typename = if_iterator_t<T>>
    SFrame(T beg, T end)
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
    SFrame()                  = default;
    SFrame(SFrame&&)          = default;
    SFrame(const SFrame&)     = default;
    SFrame(SIOFrame&& f)      { *this = std::move(f); }
    SFrame(const SIOFrame& f) { *this = f;            }
    /**
     * ----------------------------------------------------
     * operation=
     * ----------------------------------------------------
     */ 
    SFrame& operator=(SFrame&&)      = default; 
    SFrame& operator=(const SFrame&) = default;
    SFrame& operator=(SIOFrame&&);
    SFrame& operator=(const SIOFrame&);
    /**
     * ----------------------------------------------------
     * operator ==
     * ----------------------------------------------------
     */
    template<typename T>
    bool operator == (const T&f) const {
        return std::equal(begin(), end(), f.begin(), f.end());
    }
    /**
     * ------------------------------------------------------------------------
     * get capacity
     * ------------------------------------------------------------------------
     */
    inline size_t Capacity() const {
        return capacity();
    }
    /**
     * ------------------------------------------------------------------------
     * sum values
     * ------------------------------------------------------------------------
     */
    inline size_t Sum(size_t max) {
        size_t s = 0;
        for (auto it = begin(); it != end() && s < max; ++it) {
            s += *it;
        }
        return s;
    }
    /**
     * ------------------------------------------------------------------------
     * reserve size (guaranty that exist size (sz) )
     * ------------------------------------------------------------------------
     */
    inline SFrame& Reserve(size_t sz) {
        if (sz > Size()) {  
            resize(sz);
        }
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * unserialize number
     * ------------------------------------------------------------------------
     */
    template <class T>
    T Number() const {
        auto rit = rbegin();
        // set iterator position --------------------------
        for (auto i = 0; (i < sizeof(T)) && (rit != rend());) {
            ++i, ++rit;
        } 
        // decode number ----------------------------------
        T result = 0;
        for (auto it = rit.base(); it != end(); ++it) {
            result <<= 8;
            result |= T(*it);
        }
        // return nunber -----------------------------------
        return result;
    }
    /**
     * ------------------------------------------------------------------------
     * serialize number
     * ------------------------------------------------------------------------
     */
    template <class T>
    SFrame& Number(T val) {
        // reserve sizeof (val) --------------------------- 
        Reserve(sizeof (T));
        // encode number ----------------------------------
        size_t i = 0;
        for (auto it = rbegin(); i < sizeof (T); ++it, ++i) {
            *it = value_type(val);
            val >>= 8;
        }
        // return frame -----------------------------------
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
     * detach  
     * ------------------------------------------------------------------------
     */
    inline SFrame&& Detach() {
        return std::move(*this);
    }
    /**
     * ------------------------------------------------------------------------
     * change context
     * ------------------------------------------------------------------------
     */
    // inline SIOFrame IOFrame() {
    //     return Detach();
    // }
} Frame;
/**
 * ------------------------------------------------------------------------------------------------
 * IOFrame
 * ------------------------------------------------------------------------------------------------
 */
typedef class SIOFrame: protected SFrame {
public:
    friend class SFrame; 
    /**
     * ------------------------------------------------------------------------
     * conversions
     * ------------------------------------------------------------------------
     * constructors
     * ----------------------------------------------------
     */
    SIOFrame();
    SIOFrame(SFrame&&);
    SIOFrame(SIOFrame&&);
    SIOFrame(const SFrame&);
    SIOFrame(const SIOFrame&);
    /**
     * ----------------------------------------------------
     * operators
     * ----------------------------------------------------
     */ 
    SIOFrame& operator=(SFrame&& f); 
    SIOFrame& operator=(SIOFrame&& f); 
    SIOFrame& operator=(const SFrame& f);
    SIOFrame& operator=(const SIOFrame& f);
    /**
     * ------------------------------------------------------------------------
     * Standard functions
     * ------------------------------------------------------------------------
     * general
     * ----------------------------------------------------
     */
    inline value_type    front() const { return *begin();       }
    inline value_type    back()  const { return *end();         }
    inline const_pointer data()  const { return begin().base(); }
    inline size_t        size()  const { return OSize();        }
    /**
     * ----------------------------------------------------
     * operators
     * ----------------------------------------------------
     */
    inline const_iterator begin() const {
        return __beg;
    }
    inline const_iterator end() const {
        return __end;
    }
    inline iterator begin() {
        return __beg;
    }
    inline iterator end() {
        return __end;
    }
    /**
     * ------------------------------------------------------------------------
     * get capacity
     * ------------------------------------------------------------------------
     */
    inline size_t Capacity() const {
        return Super::size();
    }
     /**
     * ------------------------------------------------------------------------
     * position
     * ------------------------------------------------------------------------
     * begin position
     * ----------------------------------------------------
     */
    inline SIOFrame& Reset() {
        __beg = Super::begin();
        __end = Super::begin();
        return *this;
    }
    /**
     * ----------------------------------------------------
     * move position forward (n)
     * ----------------------------------------------------
     */
    inline SIOFrame& Insert(size_t n) {
        __end = std::next(end(), n);
        return *this;
    }
    /**
     * ----------------------------------------------------
     * move position forward (n)
     * ----------------------------------------------------
     */
    inline SIOFrame& Remove(size_t n) {
        __beg = std::next(begin(), n);
        return *this;
    }
    /**
     * ----------------------------------------------------
     * fill data into iframe
     * ----------------------------------------------------
     */
    inline SIOFrame& Fill(SIOFrame& in) {
        // check size -----------------
        auto sz = std::min(OSize(), in.ISize());
        // copy data ------------------
        std::memcpy(in.IData(), OData(), sz);
        // update in ------------------
        in.Insert(sz);
        // update out -----------------
        return Remove(sz);
    }   
    /**
     * ----------------------------------------------------
     * seek to position (p)
     * ----------------------------------------------------
     */
    inline SIOFrame& ISeek(size_t p) {
        __end = std::min(std::next(begin(), p), Super::end());
        return *this;
    }
    inline SIOFrame& OSeek(size_t p) {
        __beg = std::min(std::next(Super::begin(), p), end());
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * get data pointer
     * ------------------------------------------------------------------------
     */
    inline pointer IData() {
        return __end.base();
    }
    inline pointer OData() {
        return __beg.base();
    }
    /**
     * ------------------------------------------------------------------------
     * get size
     * ------------------------------------------------------------------------
     */
    inline size_t ISize() const {
        return std::distance(end(), Super::end());
    }
    inline size_t OSize() const {
        return std::distance(begin(), end());
    }
    /**
     * ------------------------------------------------------------------------
     * Shrink
     * ------------------------------------------------------------------------
     */
    inline SIOFrame& IShrink() { 
        // resize -----------------------------------------
        resize(Super::size() - ISize());
        // return -----------------------------------------
        return *this;
    }
    inline SIOFrame& OShrink() {
        // rotate ----------------------------------------- 
        std::rotate(Super::begin(), begin(), Super::end()); 
        // reset end --------------------------------------
        __end = std::next(
            Super::begin(), std::distance(begin(), end()));
        // reset beg --------------------------------------
        __beg = Super::begin();
        // return -----------------------------------------
        return *this;
    }
    inline SIOFrame& Shrink() {
        // rotate ----------------------------------------- 
        std::rotate(Super::begin(), begin(), Super::end()); 
        // resize -----------------------------------------
        resize(std::distance(begin(), end()));
        // reset ------------------------------------------
        __beg = Super::begin();
        __end = Super::end();
        // ------------------------------------------------
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * expand
     * ------------------------------------------------------------------------
     */
    inline SIOFrame& Expand() {
        Super::resize(Super::capacity());
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * reserve size (guaranty that exist (n) bytes )
     * ------------------------------------------------------------------------
     */
    inline SIOFrame& Reserve(size_t n) {
        auto sz = ISize();
        // verify -----------------------------------------
        if (n > sz) {
            // resize -------------------------------------    
            resize(Super::size() + n - sz);
            // reset --------------------------------------
            __end = std::prev(Super::end(),  n);
        }
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * write frame
     * ------------------------------------------------------------------------
     */
    inline SIOFrame& Write(const SFrame& f) {
        // size check -------------------------------------
        if (ISize() < f.Size()) {
            throw FrameException(
                SText("Write=(", Size(), "<", f.Size(), ")")
            );
        }
        // copy -------------------------------------------
        __end = std::copy(f.begin(), f.end(), end());
        // return -----------------------------------------
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Read frame witn (n) bytes
     * ------------------------------------------------------------------------
     */
    inline SFrame Read(size_t n) {
        // size check -------------------------------------
        if (OSize() < n) {
            throw FrameException(
                SText("Read=(", Size(), "<", n, ")")
            );
        }
        //reference ---------------------------------------
        auto beg = begin();
        // frame ------------------------------------------
        return SFrame(beg, Remove(n).begin());
    }
    /**
     * ------------------------------------------------------------------------
     * check size 
     * ------------------------------------------------------------------------
     */
    inline bool Empty() const {
        return (begin() >= end());
    }
    inline bool Full() const {
        return (begin() <= Super::begin());
    }
    /**
     * ------------------------------------------------------------------------
     * detach  
     * ------------------------------------------------------------------------
     */
    inline SIOFrame&& Detach() {
        return std::move(*this);
    }
    /**
     * ------------------------------------------------------------------------
     * change context
     * ------------------------------------------------------------------------
     */
    inline SFrame Frame() {
        return Detach();
    }
private:
    /**
     * ------------------------------------------------------------------------
     * variable
     * ------------------------------------------------------------------------
     * iterator 
     */
    iterator __end;
    iterator __beg;
} IOFrame, IFrame, OFrame;
/**
 * ------------------------------------------------------------------------------------------------
 * Uilities
 * ------------------------------------------------------------------------------------------------
 **/
template <
    typename FRAME, 
    typename = std::enable_if_t<std::is_base_of<SFrame, FRAME>::value>
>
inline std::ostream& operator<<(std::ostream& os, const FRAME& f) {
    os << "[";
    for (auto v : f) {
        os << int(v) << " ";
    }
    return os << "]";
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SFRAME_H */
