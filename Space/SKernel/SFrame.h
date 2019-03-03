/**
 * ------------------------------------------------------------------------------------------------
 * File:   h
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
    SFrame(SIFrame&&);
    SFrame(SOFrame&&);
    SFrame(SIOFrame&&);
    SFrame(const SFrame&)  = default;
    SFrame(const SIFrame&);
    SFrame(const SOFrame&);
    SFrame(const SIOFrame&);
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
    inline SFrame& operator=(SIOFrame&& f) {
        return __Consume(SFrame(std::move(f)));
    } 
    inline SFrame& operator=(const SFrame&  f) = default;
    inline SFrame& operator=(const SIFrame& f) {
        return __Consume(SFrame(f));
    }
    inline SFrame& operator=(const SOFrame& f) {
        return __Consume(SFrame(f));
    }
    inline SFrame& operator=(const SIOFrame& f) {
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
    SIFrame(SOFrame&&);
    SIFrame(SIOFrame&&);
    SIFrame(const SFrame&);
    SIFrame(const SIFrame&);
    SIFrame(const SOFrame&);
    SIFrame(const SIOFrame&);
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
     * ----------------------------------------------------
     * operators
     * ----------------------------------------------------
     */
    const_iterator end() const {
        return __end;
    }
    iterator end() {
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
        __end = std::next(__end, n);
        return *this;
    }
    /**
     * ----------------------------------------------------
     * seek to position (p)
     * ----------------------------------------------------
     */
    inline SIFrame& Seek(size_t p) {
        __end = std::next(begin(), p);
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
        return std::distance(const_iterator(__end), Super::end());
    }
    /**
     * ------------------------------------------------------------------------
     * shrink frame
     * ------------------------------------------------------------------------
     */
    inline SIFrame& Shrink() {
        resize(std::distance(begin(), __end));
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
            __end = begin() + sz_cur;
        }
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * write frame
     * ------------------------------------------------------------------------
     */
    inline SIFrame& Write(const SFrame& frame) {
        __end = std::copy(frame.begin(), frame.end(), __end);
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * shift to position given by (offset)
     * ------------------------------------------------------------------------
     */
    inline SIFrame& Shift(size_t offset) {
        __end = __rotate(
            begin(), std::next(begin(), offset), __end
        );
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * check size
     * ------------------------------------------------------------------------
     */
    inline bool Empty() const {
        return (__end <= begin());
    }
    inline bool Full() const {
        return (__end >= end());
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
private:
    friend class SOFrame;
    friend class SIOFrame;
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
    SOFrame(SFrame&&);
    SOFrame(SIFrame&&);
    SOFrame(SOFrame&&);
    SOFrame(SIOFrame&&);
    SOFrame(const SFrame&);
    SOFrame(const SIFrame&);
    SOFrame(const SOFrame&);
    SOFrame(const SIOFrame&);
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
     * ----------------------------------------------------
     * operators
     * ----------------------------------------------------
     */
    const_iterator begin() const {
        return __beg;
    }
    iterator begin() {
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
        __beg = begin();
        return *this;
    }
    /**
     * ----------------------------------------------------
     * move position forward (n)
     * ----------------------------------------------------
     */
    inline SOFrame& Remove(size_t n) {
        __beg = next(__beg, n);
        return *this;
    }
    /**
     * ----------------------------------------------------
     * fill data into iframe
     * ----------------------------------------------------
     */
    inline SOFrame& Fill(IFrame& frame) {
        auto sz = std::min(Size(), frame.Size());
        std::memcpy(frame.Data(), Data(), sz);
        frame.Insert(sz);
        return Remove(sz);
    }   
    /**
     * ----------------------------------------------------
     * seek to position (p)
     * ----------------------------------------------------
     */
    inline SOFrame& Seek(size_t p) {
        __beg = next(begin(), p);
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
        return distance(SFrame::const_iterator(__beg), end());
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
        std::rotate(begin(), __beg, end()); 
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
        iterator prev = __beg; __beg = std::next(__beg, size);
        // copy to new frame ------------------------------
        return SFrame(prev, __beg);
    }
    /**
     * ------------------------------------------------------------------------
     * check size 
     * ------------------------------------------------------------------------
     */
    inline bool Empty() const {
        return (__beg >= end());
    }
    inline bool Full() const {
        return (__beg <= begin());
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
    friend class SIFrame;
    friend class SIOFrame;
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
 * SIOFrame
 * ------------------------------------------------------------------------------------------------
 */
typedef class SIOFrame : public SFrame {
public:
    /**
     * ------------------------------------------------------------------------
     * initialization 
     * ------------------------------------------------------------------------
     * constructor
     * ----------------------------------------------------
     */
    SIOFrame(size_t capacity) 
    : SFrame(capacity), __beg(begin()), __end(begin()) { Expand(); }
    /**
     * ------------------------------------------------------------------------
     * conversions
     * ------------------------------------------------------------------------
     * constructors
     * ----------------------------------------------------
     */
    SIOFrame();
    SIOFrame(SFrame&&);
    SIOFrame(SIFrame&&);
    SIOFrame(SOFrame&&);
    SIOFrame(SIOFrame&&);
    SIOFrame(const SFrame&);
    SIOFrame(const SIFrame&);
    SIOFrame(const SOFrame&);
    SIOFrame(const SIOFrame&);
    /**
     * ----------------------------------------------------
     * operators
     * ----------------------------------------------------
     */
    template<typename T> 
    SIOFrame& operator=(T&& f) {
        return __Consume(SIOFrame(std::move(f)));
    } 
    template<typename T> 
    SIOFrame& operator=(const T& f) {
        return __Consume(SIOFrame(f));
    }
    /**
     * ----------------------------------------------------
     * operators
     * ----------------------------------------------------
     */
    const_iterator begin() const {
        return __beg;
    }
    const_iterator end() const {
        return __end;
    }
    iterator begin() {
        return __beg;
    }
    iterator end() {
        return __end;
    }
    /**
     * ------------------------------------------------------------------------
     * capacity
     * ------------------------------------------------------------------------
     */
    inline size_t Capacity() const {
        return Size();
    }
    /**
     * ------------------------------------------------------------------------
     * position
     * ------------------------------------------------------------------------
     * begin position
     * ----------------------------------------------------
     */
    inline SIOFrame& Reset() {
        __end = begin();
        __beg = begin();
        return *this;
    }
    /**
     * ----------------------------------------------------
     * move position (n)
     * ----------------------------------------------------
     */
    inline SIOFrame& Insert(size_t n) {
        __end = std::next(__end, n);
        return *this;
    }
    inline SIOFrame& Remove(size_t n) {
        __beg = std::next(__beg, n);
        return *this;
    }
    /**
     * ----------------------------------------------------
     * seek to position (p)
     * ----------------------------------------------------
     */
    inline SIOFrame& ISeek(size_t p) {
        __end = std::max(std::next(begin(), p), __beg);
        return *this;
    }
    inline SIOFrame& OSeek(size_t p) {
        __beg = std::min(std::next(begin(), p), __end);
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * get data
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
        return std::distance(const_iterator(__end), end());
    }
    inline size_t OSize() const {
        return distance(const_iterator(__beg), const_iterator(__end));
    }
    /**
     * ------------------------------------------------------------------------
     * shift and remove n
     * ------------------------------------------------------------------------
     */
    inline SIOFrame& Shift(size_t n) {
        // rotate -----------------------------------------
        std::rotate(__beg, std::next(__beg, n), __end);
        // reset ------------------------------------------
        __end = std::prev(__end, n);
        // ------------------------------------------------
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Ishrink frame
     * ------------------------------------------------------------------------
     */
    inline SIOFrame& IShrink() { 
        // resize -----------------------------------------
        resize(std::distance(begin(), __end));
        // reset ------------------------------------------
        __end = end();
        // ------------------------------------------------
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * shrink frame
     * ------------------------------------------------------------------------
     */
    inline SIOFrame& Shrink() {
        // rotate ----------------------------------------- 
        std::rotate(begin(), __beg, end()); 
        // resize -----------------------------------------
        resize(std::distance(__beg, __end));
        // reset ------------------------------------------
        __beg = begin();
        __end = end();
        // ------------------------------------------------
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * expand frame
     * ------------------------------------------------------------------------
     */
    inline SIOFrame& Expand() {
        resize(capacity());
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * reserve size (guaranty that exist size (sz) )
     * ------------------------------------------------------------------------
     */
    inline SIOFrame& Reserve(size_t sz) {
        auto sz_i = ISize();
        // verify current size ----------------------------
        if (sz > sz_i) {
            auto sz_o = OSize();
            // resize -------------------------------------    
            resize(size() + sz - sz_i);
            // reset --------------------------------------
            __end = std::prev(end(),  sz);
            __beg = std::prev(__end, sz_o);
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
                SText("Write=(", ISize(), "<", f.Size(), ")")
            );
        }
        // copy -------------------------------------------
        __end = std::copy(f.begin(), f.end(), __end);
        // ------------------------------------------------
        return *this;
    }
    /**
     * ----------------------------------------------------
     * transfer data to frame
     * ----------------------------------------------------
     */
    inline SIOFrame& Fill(SIOFrame& in) {
        // check size -----------------
        auto sz = std::min(Size(), in.ISize());
        // copy data ------------------
        std::memcpy(in.IData(), OData(), sz);
        // update in ------------------
        in.Insert(sz);
        // update out -----------------
        return Remove(sz);
    }
    /**
     * ------------------------------------------------------------------------
     * Read frame
     * ------------------------------------------------------------------------
     */
    inline SFrame Read(size_t size) {
        // size check -------------------------------------
        if (OSize() < size) {
            throw FrameException(
                SText("Read=(", Size(), "<", size, ")")
            );
        }
        //reference ---------------------------------------
        auto ref = __beg;
        // reset ------------------------------------------ 
        __beg = std::next(__beg, size);
        // frame ------------------------------------------
        return SFrame(ref, __beg);
    }
    /**
     * ------------------------------------------------------------------------
     * check size
     * ------------------------------------------------------------------------
     */
    inline bool Empty() const {
        return (__end <= __beg);
    }
    inline bool Full() const {
        return (__end >= end());
    }
    /**
     * ------------------------------------------------------------------------
     * detach  
     * ------------------------------------------------------------------------
     */
    inline SIOFrame&& Detach() {
        return std::move(*this);
    }
protected:
    /**
     * ------------------------------------------------------------------------
     * consume
     * ------------------------------------------------------------------------
     */
    inline SIOFrame& __Consume(SIOFrame&& f) {
        // consume super ----------------------------------
        Super::operator=(std::move(f));
        // consume itrators -------------------------------
        __beg = std::move(f.__beg);
        __end = std::move(f.__end);
        // return this frame ------------------------------
        return *this;
    }
private:
    friend class SIFrame;
    friend class SOFrame;
    /**
     * ------------------------------------------------------------------------
     * variable
     * ------------------------------------------------------------------------
     **
     * iterators
     */
    iterator __end;
    iterator __beg;
} IOFrame;
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

