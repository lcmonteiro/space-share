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
        Capacity(capacity).assign(size, value);
    }
    template<typename T, typename = if_iterator_t<T>>
    SFrame(const size_t capacity, T beg, T end)
    : Super() {
        Capacity(capacity).assign(beg, end);
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
    SFrame()               = default;
    SFrame(SFrame&&)       = default;
    SFrame(const SFrame&)  = default;
    /**
     * ----------------------------------------------------
     * operation=
     * ----------------------------------------------------
     */ 
    inline SFrame& operator=(SFrame&&)      = default; 
    inline SFrame& operator=(const SFrame&) = default;
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
} Frame;
/**
 * ------------------------------------------------------------------------------------------------
 * SIFrame
 * ------------------------------------------------------------------------------------------------
 */
typedef class SIFrame : protected SFrame {
public:
    /**
     * ------------------------------------------------------------------------
     * initialization 
     * ------------------------------------------------------------------------
     * constructor
     * ----------------------------------------------------
     */
    SIFrame(size_t capacity) 
    : SFrame(capacity), __end(begin()) { Expand(); }
    /**
     * ------------------------------------------------------------------------
     * conversions
     * ------------------------------------------------------------------------
     * constructors
     * ----------------------------------------------------
     */
    SIFrame();
    SIFrame(SFrame&&);
    SIFrame(SIFrame&&);
    SIFrame(const SFrame&);
    SIFrame(const SIFrame&);
    /**
     * ----------------------------------------------------
     * operator =
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
     * Standard functions
     * ------------------------------------------------------------------------
     * default
     * ----------------------------------------------------
     */
    using SFrame::front; 
    using SFrame::begin; 
    /**
     * ---------------------------------------------------
     * operatores
     * ---------------------------------------------------
     */
    inline const_iterator end() const {
        return __end;
    }
    inline iterator end() {
        return __end;
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
        __end = begin();
        return *this;
    }
    /**
     * ----------------------------------------------------
     * move position forward (n)
     * ----------------------------------------------------
     */
    inline SIFrame& Insert(size_t n) {
        __end = std::next(end(), n);
        return *this;
    }
    /**
     * ----------------------------------------------------
     * seek to position (p)
     * ----------------------------------------------------
     */
    inline SIFrame& Seek(size_t p) {
        __end = std::min(std::next(begin(), p), Super::end());
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * get data
     * ------------------------------------------------------------------------
     */
    inline pointer Data() {
        return __end.base();
    }
    /**
     * ------------------------------------------------------------------------
     * get size
     * ------------------------------------------------------------------------
     */
    inline size_t Size() const {
        return std::distance(end(), Super::end());
    }
    /**
     * ------------------------------------------------------------------------
     * shrink frame
     * ------------------------------------------------------------------------
     */
    inline SIFrame& Shrink() {
        resize(std::distance(begin(), end()));
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
     * reserve size (guaranty that exist (n) bytes )
     * ------------------------------------------------------------------------
     */
    inline SIFrame& Reserve(size_t n) {
        auto sz = Size();
        // verify current size ----------------------------
        if (n > sz) {
            // resize vector ------------------------------    
            resize(Super::size() + n - sz);
            // reset pointer ------------------------------
            __end = std::prev(Super::end(),  n);
        }
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * write frame
     * ------------------------------------------------------------------------
     */
    inline SIFrame& Write(const SFrame& f) {
        __end = std::copy(f.begin(), f.end(), end());
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * shift to position by (n) bytes
     * ------------------------------------------------------------------------
     */
    inline SIFrame& Shift(size_t n) {
        // rotate -----------------------------------------
        std::rotate(begin(), std::next(begin(), n), end());
        // reset ------------------------------------------
        __end = std::prev(end(), n);
        // return -----------------------------------------
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * check size
     * ------------------------------------------------------------------------
     */
    inline bool Empty() const {
        return (end() <= Super::begin());
    }
    inline bool Full() const {
        return (end() >= Super::end());
    }
    /**
     * ------------------------------------------------------------------------
     * down types  
     * ------------------------------------------------------------------------
     */
    inline SFrame& Frame() {
        return static_cast<SFrame&>(*this);
    }
    /**
     * ------------------------------------------------------------------------
     * detach  
     * ------------------------------------------------------------------------
     */
    inline SIFrame&& Detach() {
        return std::move(*this);
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
        __end = std::move(f.__end);
        // return this frame ------------------------------
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * variable
     * ------------------------------------------------------------------------
     **
     * iterator
     */
    iterator __end;
} IFrame;
/**
 * ------------------------------------------------------------------------------------------------
 * OFrame
 * ------------------------------------------------------------------------------------------------
 */
typedef class SOFrame: protected SIFrame {
public:
    /**
     * ------------------------------------------------------------------------
     * conversions
     * ------------------------------------------------------------------------
     * constructors
     * ----------------------------------------------------
     */
    SOFrame();
    SOFrame(SFrame&&);
    SOFrame(SIFrame&&);
    SOFrame(SOFrame&&);
    SOFrame(const SFrame&);
    SOFrame(const SIFrame&);
    SOFrame(const SOFrame&);
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
     * Standard functions
     * ------------------------------------------------------------------------
     * default
     * ----------------------------------------------------
     */
    /**
     * ----------------------------------------------------
     * operators
     * ----------------------------------------------------
     */
    inline const_iterator begin() const {
        return __beg;
    }
    inline iterator begin() {
        return __beg;
    }
     /**
     * ------------------------------------------------------------------------
     * position
     * ------------------------------------------------------------------------
     * begin position
     * ----------------------------------------------------
     */
    inline SOFrame& Reset() {
        __beg = Super::begin();
        return *this;
    }
    /**
     * ----------------------------------------------------
     * move position forward (n)
     * ----------------------------------------------------
     */
    inline SOFrame& Remove(size_t n) {
        __beg = std::next(begin(), n);
        return *this;
    }
    /**
     * ----------------------------------------------------
     * fill data into iframe
     * ----------------------------------------------------
     */
    inline SOFrame& Fill(IFrame& in) {
        // check size -----------------
        auto sz = std::min(Size(), in.Size());
        // copy data ------------------
        std::memcpy(in.Data(), Data(), sz);
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
    inline SOFrame& Seek(size_t p) {
        __beg = std::min(std::next(begin(), p), end());
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * get data pointer
     * ------------------------------------------------------------------------
     */
    inline pointer Data() {
        return __beg.base();
    }
    /**
     * ------------------------------------------------------------------------
     * get size
     * ------------------------------------------------------------------------
     */
    inline size_t Size() const {
        return std::distance(begin(), end());
    }
    /**
     * ------------------------------------------------------------------------
     * Shrink
     * ------------------------------------------------------------------------
     */
    inline SOFrame& Shrink() {
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
     * Read frame witn (n) bytes
     * ------------------------------------------------------------------------
     */
    inline SFrame Read(size_t n) {
        // size check -------------------------------------
        if (Size() < n) {
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
     * down types  
     * ------------------------------------------------------------------------
     */
    inline SFrame& Frame() {
        return static_cast<SFrame&>(*this);
    }
    inline SIFrame& IFrame() {
        return static_cast<SIFrame&>(*this);
    }
    /**
     * ------------------------------------------------------------------------
     * detach  
     * ------------------------------------------------------------------------
     */
    inline SOFrame&& Detach() {
        return std::move(*this);
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
        __beg = std::move(f.__beg);
        // return this frame ------------------------------
        return *this;
    }
private:
    /**
     * ------------------------------------------------------------------------
     * variable
     * ------------------------------------------------------------------------
     * iterator 
     */
    iterator __beg;
} OFrame;
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
