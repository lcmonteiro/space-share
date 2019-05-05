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
#include "SItertool.h"
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
     * helpers
     * ------------------------------------------------------------------------
     * Super class
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
     * constructors - initialization
     * ------------------------------------------------------------------------
     */
    SFrame(const size_t capacity, const size_t size, const uint8_t value)
    : Super() { Super::reserve(capacity); assign(size, value); }

    SFrame(const size_t capacity, const size_t size)
    : Super() { Super::reserve(capacity); resize(size);        }
    
    SFrame(const size_t capacity)
    : Super() { Super::reserve(capacity);                      }
    
    template<typename T, typename = if_iterator_t<T>>
    SFrame(const size_t capacity, T beg, T end)
    : Super() { Super::reserve(capacity); assign(beg, end);    }
    
    template<typename T, typename = if_iterator_t<T>>
    SFrame(T beg, T end)
    : Super(beg, end) {                                        }

    SFrame(std::initializer_list<uint8_t> l) 
    : Super(l) {                                               }
    /**
     * ------------------------------------------------------------------------
     * constructors
     * ------------------------------------------------------------------------
     */
    SFrame()                  = default;
    SFrame(SFrame&&)          = default;
    SFrame(const SFrame&)     = default;
    SFrame(SIOFrame&& f);
    SFrame(const SIOFrame& f);
    /**
     * ------------------------------------------------------------------------
     * Operatores
     * ------------------------------------------------------------------------
     * operation =
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
     * Sum all elements until max reach 
     * ------------------------------------------------------------------------
     */
    inline size_t sum(size_t max) {
        size_t s = 0;
        for (auto it = begin(); it != end() && s < max; ++it) {
            s += *it;
        }
        return s;
    }
    /**
     * ------------------------------------------------------------------------
     * Insert frame -> append
     * ------------------------------------------------------------------------
     */
    inline SFrame& insert(const SFrame& f) {
        Super::insert(end(), f.begin(), f.end());
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Insert size -> resize
     * ------------------------------------------------------------------------
     */
    inline SFrame& insert(size_t sz) {
        Super::resize(sz); 
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Remove size -> resize(-size)
     * ------------------------------------------------------------------------
     */
    inline SFrame& remove(size_t sz) {
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
    inline SFrame& shrink(size_t sz = 0) {
        if (size() < sz) {
            throw FrameException(
                SText("Shrink=(", size(), "<", sz, ")"));
        }
        resize(sz);
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Inflate
     * ------------------------------------------------------------------------
     */
    inline SFrame& inflate() {
        resize(capacity());
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Shift to position given by (offset)
     * ------------------------------------------------------------------------
     */
    inline SFrame& shift(size_t offset) {
        std::rotate(
            begin(), next(begin(), offset), end());
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
     * get number
     * ------------------------------------------------------------------------
     */
    template <class Type>
    Type number() const {
        /**
         *  decode number
         */
        return Itertool::GetNumber<Type>(rbegin(), rend());
    }
    /**
     * ------------------------------------------------------------------------
     * set number
     * ------------------------------------------------------------------------
     */
    template <class Type>
    SFrame& number(Type val) {
        /**
         * reserve space
         */
        if (sizeof(Type) > size()) resize(sizeof(Type));
        /**
         * encode number
         */
        Itertool::SetNumber(rbegin(), rend(), val);
        /**
         * return itself
         */
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * detach  
     * ------------------------------------------------------------------------
     */
    inline SFrame&& detach() {
        return std::move(*this);
    }
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
     * constructors
     * ------------------------------------------------------------------------
     */
    SIOFrame(size_t sz = 0);
    SIOFrame(SFrame&&);
    SIOFrame(SIOFrame&&);
    SIOFrame(const SFrame&);
    SIOFrame(const SIOFrame&);
    /**
     * -------------------------------------------------------------------------
     * operator =
     * -------------------------------------------------------------------------
     */ 
    SIOFrame& operator=(SFrame&& f); 
    SIOFrame& operator=(SIOFrame&& f) = default; 
    SIOFrame& operator=(const SFrame& f);
    SIOFrame& operator=(const SIOFrame& f);
    /**
     * -------------------------------------------------------------------------
     * operators != & ==
     * -------------------------------------------------------------------------
     */
    inline bool operator == (const SIOFrame& f) const {
        return std::equal(begin(), end(), f.begin(), f.end());
    }
    inline bool operator != (const SIOFrame& f) const {
        return !std::equal(begin(), end(), f.begin(), f.end());
    }
    /**
     * ------------------------------------------------------------------------
     * references
     * ------------------------------------------------------------------------
     */
    inline value_type    front() const { return *begin(); }
    inline value_type    back()  const { return *end();   }
    /**
     * ------------------------------------------------------------------------
     * iterators
     * ------------------------------------------------------------------------
     */
    inline const_iterator begin()  const { return __beg; }
    inline const_iterator end()    const { return __end; }
    inline iterator       begin()        { return __beg; }
    inline iterator       end()          { return __end; }
    
     /**
     * ------------------------------------------------------------------------
     * position
     * ------------------------------------------------------------------------
     * begin position
     * ----------------------------------------------------
     */
    inline SIOFrame& clear() {
        __beg = Super::begin();
        __end = Super::begin();
        return *this;
    }
    /**
     * ----------------------------------------------------
     * Move end position forward (n)
     * ----------------------------------------------------
     */
    inline SIOFrame& insert(size_t n) {
        __end = std::next(end(), n);
        return *this;
    }
    /**
     * ----------------------------------------------------
     * Move begin position forward (n)
     * ----------------------------------------------------
     */
    inline SIOFrame& remove(size_t n) {
        __beg = std::next(begin(), n);
        return *this;
    }
    /**
     * ----------------------------------------------------
     * Fill data into iframe
     * ----------------------------------------------------
     */
    inline SIOFrame& fill(SIOFrame& in) {
        /**
         *  check size
         */
        auto sz = std::min(size(), in.isize());
        /**
         *  copy data
         */
        std::memcpy(in.idata(), data(), sz);
        /**
         *  update in
         */
        in.insert(sz);
        /**
         *  update out
         */
        return remove(sz);
    }   
    /**
     * ------------------------------------------------------------------------
     * Seek position (p)
     * ------------------------------------------------------------------------
     */
    inline SIOFrame& iseek(size_t p) {
        __end = std::min(std::next(begin(), p), Super::end());
        return *this;
    }
    inline SIOFrame& oseek(size_t p) {
         __beg = std::min(std::next(Super::begin(), p), end());
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Data pointers
     * ------------------------------------------------------------------------
     */
    inline const_pointer odata() const { return Super::data();  }
    inline pointer       idata()       { return end().base();   }
    inline const_pointer data()  const { return begin().base(); }
    inline pointer       data()        { return begin().base(); }
    /**
     * ------------------------------------------------------------------------
     * Capacity
     * ------------------------------------------------------------------------
     */
    inline size_t capacity() const {
        return Super::size();
    }
    /**
     * ------------------------------------------------------------------------
     * Sizes
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
     * Deflate
     * ------------------------------------------------------------------------
     */
    inline SIOFrame& deflate() {
        /**
         * rotate
         */ 
        std::rotate(Super::begin(), begin(), Super::end()); 
        /**
         * resize
         */
        resize(std::distance(begin(), end()));
        /**
         * reset
         */
        __beg = Super::begin();
        __end = Super::end();
        /**
         * return itself
         */ 
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Inflate
     * ------------------------------------------------------------------------
     */
    inline SIOFrame& inflate() {
        /**
         * resize
         */
        Super::resize(Super::capacity());
        /**
         * return itself
         */
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Shrink
     * ------------------------------------------------------------------------
     */
    inline SIOFrame& shrink(size_t sz) {
        /**
         * check
         */  
        if (size() < sz) {
            throw FrameException(
                SText("Shrink=(", size(), "<", sz, ")"));
        }
        /**
         * shrink
         */
        return iseek(sz);
    }
    /**
     * ------------------------------------------------------------------------
     * Expand
     * ------------------------------------------------------------------------
     */
    inline SIOFrame& expand(size_t sz) {
        /**
         * compute delta
         */
        auto delta = (sz - size());
        /**
         * check delta
         */  
        if (0 > delta) {
            throw FrameException(
                SText("Expand=(", delta, ")"));
        }
        /**
         * expand delta
         */
        return reserve(delta).insert(delta);
    }
    /**
     * ------------------------------------------------------------------------
     * reserve size (guaranty that exist (n) bytes )
     * ------------------------------------------------------------------------
     */
    inline SIOFrame& reserve(size_t n) {
        auto isz = isize();
        /**
         * verify
         */ 
        if (n > isz) {
            auto osz = osize();
            /**
             * resize
             */    
            resize(Super::size() + n - isz);
            /**
             * reset
             */ 
            __beg = std::next(Super::begin(), osz);
            __end = std::prev(Super::end(), n);
        }
        /**
         *  return itself
         */
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Unserialize number
     * ------------------------------------------------------------------------
     */
    template <class Type>
    Type number() const {
        /**
         *  decode number
         */
        return Itertool::GetNumber<Type>(
            std::make_reverse_iterator(end()), 
            std::make_reverse_iterator(begin()));
    }
    /**
     * ------------------------------------------------------------------------
     * Serialize number
     * ------------------------------------------------------------------------
     */
    template <class T>
    SIOFrame& number(T val) {
        /**
         * encode number
         */
        Itertool::SetNumber(
            std::make_reverse_iterator(end()), 
            std::make_reverse_iterator(begin()), val);
        /**
         * return itself
         */
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Write frame
     * ------------------------------------------------------------------------
     */
    inline SIOFrame& write(const SFrame& f) {
        /**
         * check size
         */
        if (isize() < f.size()) {
            throw FrameException(
                SText("Write=(", size(), "<", f.size(), ")"));
        }
        /**
         * copy data
         */
        __end = std::copy(f.begin(), f.end(), end());
        /**
         * return itself
         */
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Read frame with (n) bytes
     * ------------------------------------------------------------------------
     */
    inline SFrame read(size_t n) {
        /**
         * check size
         */
        if (size() < n) {
            throw FrameException(
                SText("Read=(", size(), "<", n, ")"));
        }
        /** 
         * save reference
         */
        auto beg = begin();
        /**
         * return new frame
         */
        return SFrame(beg, remove(n).begin());
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
     * Variables
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
    typename Frame, 
    typename = std::enable_if_t<std::is_base_of<SFrame, Frame>::value>
>
inline std::ostream& operator<<(std::ostream& os, const Frame& f) {
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
