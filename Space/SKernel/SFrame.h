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
    SFrame(const size_t capacity, const size_t size, const uint8_t value)
    : Super() { reserve(capacity); assign(size, value); }

    SFrame(const size_t capacity, const size_t size)
    : Super() { reserve(capacity); resize(size);        }
    
    SFrame(const size_t capacity)
    : Super() { reserve(capacity);                      }
    
    template<typename T, typename = if_iterator_t<T>>
    SFrame(const size_t capacity, T beg, T end)
    : Super() { reserve(capacity); assign(beg, end);    }
    
    template<typename T, typename = if_iterator_t<T>>
    SFrame(T beg, T end)
    : Super(beg, end) {                                 }
    
    SFrame(std::initializer_list<uint8_t> l) 
    : Super(l) {                                        }
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
    SFrame(SIOFrame&& f);
    SFrame(const SIOFrame& f);
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
        if (sz > size()) {  
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
        // return number -----------------------------------
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
    inline const_pointer Data() const {
        return data();
    }
    inline pointer Data() {
        return data();
    }
    /**
     * ------------------------------------------------------------------------
     * insert size -> resize
     * ------------------------------------------------------------------------
     */
    inline SFrame& Insert(size_t sz) {
        resize(sz);
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Remove size -> resize(-size)
     * ------------------------------------------------------------------------
     */
    inline SFrame& Remove(size_t sz) {
        if(size() != sz){
            std::rotate(begin(), std::next(begin(), sz), end());
            resize(size() - sz);
        } else {
            resize(0);
        } 
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Shrink to size -> resize 
     *  - throw exception when size > size()
     * ------------------------------------------------------------------------
     */
    inline SFrame& Shrink(size_t sz = 0) {
        if (size() < sz) {
            throw FrameException(
                SText("Shrink=(", size(), "<", sz, ")"));
        }
        resize(sz);
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
    inline bool empty() const {
        return (size() == 0);
    }
    inline bool full() const {
        return (size() == capacity());
    }
    /**
     * ------------------------------------------------------------------------
     * detach  
     * ------------------------------------------------------------------------
     */
    inline SFrame&& detach() {
        return std::move(*this);
    }
    /**
     * ------------------------------------------------------------------------
     * change context
     * ------------------------------------------------------------------------
     */
    SIOFrame IOFrame();
} Frame;
/**
 * ------------------------------------------------------------------------------------------------
 * IOFrame
 * ------------------------------------------------------------------------------------------------
 */
typedef class SIOFrame: protected SFrame {
public:  
    /**
     * ------------------------------------------------------------------------
     * conversions
     * ------------------------------------------------------------------------
     * constructors
     * ----------------------------------------------------
     */
    SIOFrame(size_t sz = 0);
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
    SIOFrame& operator=(SIOFrame&& f) = default; 
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
    /**
     * ----------------------------------------------------
     * iterators
     * ----------------------------------------------------
     */
    inline const_iterator begin()  const { return __beg; }
    inline const_iterator end()    const { return __end; }
    inline iterator       begin()        { return __beg; }
    inline iterator       end()          { return __end; }
    /**
     * ----------------------------------------------------
     * operators
     * ----------------------------------------------------
     */
    inline bool operator == (const SIOFrame& f) const {
        return std::equal(begin(), end(), f.begin(), f.end());
    }
    inline bool operator != (const SIOFrame& f) const {
        return !std::equal(begin(), end(), f.begin(), f.end());
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
        auto sz = std::min(size(), in.isize());
        // copy data ------------------
        std::memcpy(in.IData(), Data(), sz);
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
    inline const_pointer OData() const {
        return Super::data();
    }
    inline const_pointer Data() const {
        return begin().base();
    }
    inline pointer Data() {
        return begin().base();
    }
    inline pointer IData() {
        return end().base();
    }
    /**
     * ------------------------------------------------------------------------
     * Size
     * ------------------------------------------------------------------------
     */
    inline size_t osize() const {
        return std::distance(Super::begin(), begin());
    }
    inline size_t size() const {
        return std::distance(begin(), end());
    }
    inline size_t isize() const {
        return std::distance(end(), Super::end());
    }
    /**
     * ------------------------------------------------------------------------
     * Shrink
     * ------------------------------------------------------------------------
     */
    inline SIOFrame& Shrink() {
        // rotate ----------------------------------------- 
        std::rotate(Super::begin(), begin(), Super::end()); 
        // resize -----------------------------------------
        resize(std::distance(begin(), end()));
        // reset ------------------------------------------
        __beg = Super::begin();
        __end = Super::end();
        // return -----------------------------------------
        return *this;
    }
    inline SIOFrame& Shrink(size_t sz) {
        // check ------------------------------------------  
        if (size() < sz) {
            throw FrameException(
                SText("Shrink=(", size(), "<", sz, ")"));
        }
        // shrink -----------------------------------------
        return ISeek(sz);
    }
    /**
     * ------------------------------------------------------------------------
     * expand
     * ------------------------------------------------------------------------
     */
    inline SIOFrame& Expand() {
        // resize -----------------------------------------
        Super::resize(Super::capacity());
        // return -----------------------------------------
        return *this;
    }
    inline SIOFrame& Expand(size_t sz) {
        // delta ------------------------------------------
        auto delta = (sz - size());
        // check ------------------------------------------  
        if (0 > delta) {
            throw FrameException(
                SText("Expand=(", delta, ")"));
        }
        // expand -----------------------------------------
        return Reserve(delta).Insert(delta);
    }
    /**
     * ------------------------------------------------------------------------
     * reserve size (guaranty that exist (n) bytes )
     * ------------------------------------------------------------------------
     */
    inline SIOFrame& Reserve(size_t n) {
        auto isz = isize();
        // verify ----------------------------------------- 
        if (n > isz) {
            auto osz = osize();
            // resize -------------------------------------    
            resize(Super::size() + n - isz);
            // reset -------------------------------------- 
            __beg = std::next(Super::begin(), osz);
            __end = std::prev(Super::end(), n);
        }
        // return -----------------------------------------
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * unserialize number
     * ------------------------------------------------------------------------
     */
    template <class T>
    T Number() const {
        // referencies ------------------------------------
        auto rit  = std::make_reverse_iterator(end());
        auto rend = std::make_reverse_iterator(begin());
        // set iterator position --------------------------
        for (auto i = 0; (i < sizeof(T)) && (rit != rend);) {
            ++i, ++rit;
        } 
        // decode number ----------------------------------
        T result = 0;
        for (auto it = rit.base(); it != end(); ++it) {
            result <<= 8;
            result |= T(*it);
        }
        // return number ----------------------------------
        return result;
    }
    /**
     * ------------------------------------------------------------------------
     * serialize number
     * ------------------------------------------------------------------------
     */
    template <class T>
    SIOFrame& Number(T val) {
        // referencies ------------------------------------
        auto rit = std::make_reverse_iterator(end());
        auto rend = std::make_reverse_iterator(begin());
        // encode number ----------------------------------
        size_t i = 0;
        for (auto i = 0; (i < sizeof(T)) && (rit != rend); ++rit, ++i) {
            *rit = value_type(val);
            val >>= 8;
        }
        // return frame -----------------------------------
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * write frame
     * ------------------------------------------------------------------------
     */
    inline SIOFrame& Write(const SFrame& f) {
        // size check -------------------------------------
        if (isize() < f.size()) {
            throw FrameException(
                SText("Write=(", size(), "<", f.size(), ")"));
        }
        // copy -------------------------------------------
        __end = std::copy(f.begin(), f.end(), end());
        // return -----------------------------------------
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Read frame with (n) bytes
     * ------------------------------------------------------------------------
     */
    inline SFrame Read(size_t n) {
        // size check -------------------------------------
        if (size() < n) {
            throw FrameException(
                SText("Read=(", size(), "<", n, ")"));
        }
        // reference --------------------------------------
        auto beg = begin();
        // return new frame -------------------------------
        return SFrame(beg, Remove(n).begin());
    }
    /**
     * ------------------------------------------------------------------------
     * check size 
     * ------------------------------------------------------------------------
     */
    inline bool empty() const {
        return (begin() >= end());
    }
    inline bool full() const {
        return (end() >= Super::end());
    }
    /**
     * ------------------------------------------------------------------------
     * detach  
     * ------------------------------------------------------------------------
     */
    inline SIOFrame&& detach() {
        return std::move(*this);
    }
private:
    friend class SFrame;
    /**
     * ------------------------------------------------------------------------
     * variable
     * ------------------------------------------------------------------------
     * iterator 
     */
    iterator __beg;
    iterator __end;
} IOFrame;
/**
 * ------------------------------------------------------------------------------------------------
 * Utilies
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
