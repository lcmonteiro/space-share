/*
 * File:   SContainer.h
 * Author: Luis Monteiro
 *
 * Created on November 23, 2016, 10:21 AM
 */
#ifndef SCONTAINER_H
#define SCONTAINER_H
/**
 * std
 */
#include <map>
#include <vector>
#include <ostream>
#include <sstream>
#include <cstdint>
#include <cstring>
#include <algorithm>
#include <stdexcept>
/**
 */
using namespace std;
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
 * -------------------------------------------------------------------------------------------------
 * Definitions
 * -------------------------------------------------------------------------------------------------
 **/
typedef uint64_t filesize_t;
typedef uint32_t reference_t;
typedef uint16_t numframes_t;
typedef uint32_t framesize_t;
/**
 * ------------------------------------------------------------------------------------------------
 * Exceptions
 * ------------------------------------------------------------------------------------------------
 **/
typedef class SFrameException : public range_error {
public:
    using range_error::range_error;
} FrameException;

typedef class SContainerException : public range_error {
public:
    using range_error::range_error;
} ContainerException;
/**
 * ------------------------------------------------------------------------------------------------
 * Frame
 * -------------------------------------------------------------------------------------------------
 **/
typedef class SFrame : public std::vector<uint8_t> {
public:
    using Super = std::vector<uint8_t>;
    /**
     * using from super
     **/
    using Super::Super;
    /**
     * ----------------------------------------------------
     * constructors
     * ----------------------------------------------------
     */
    SFrame() = default;

    SFrame(Super& f) : Super(f) {
    }
    SFrame(Super&& f) : Super(move(f)) {
    }
    SFrame(const string && s) : Super(s.begin(), s.end()) {
    }
    SFrame(const size_t size, const size_t capacity, uint8_t val) : Super() {
        reserve(capacity); assign(size, val);
    }
    /**
     * ----------------------------------------------------
     * sum values
     * ----------------------------------------------------
     */
    uint32_t Sum(uint32_t max) {
        uint32_t s = 0;
        for (auto it = begin(); it != end() && s < max; ++it) {
            s += *it;
        }
        return s;
    }
    /**
     * ----------------------------------------------------
     * unserialize number
     * ----------------------------------------------------
     */
    template <class T>
    T Number() const {
        // set iterator position
        auto rit = rbegin();
        for (auto i = 0; (i < sizeof (T)) && (rit != rend()); ++i, ++rit);
        // decode number
        T result = 0;
        for (auto it = rit.base(); it != end(); ++it) {
            result <<= 8;
            result |= T(*it);
        }
        return result;
    }
    /**
     * ----------------------------------------------------
     * serialize number
     * ----------------------------------------------------
     */
    template <class T>
    SFrame& Number(T val) {
        // encode number
        size_t i = 0;
        for (auto it = rbegin(); (it != rend()) && (i < sizeof (T)); ++it, ++i) {
            *it = value_type(val);
            val >>= 8;
        }
        return *this;
    }
    /**
     * ----------------------------------------------------
     * get data
     * ----------------------------------------------------
     */
    inline pointer Data() {
        return data();
    }
    /**
     * ----------------------------------------------------
     * get size
     * ----------------------------------------------------
     */
    inline size_t Size() const {
        return size();
    }
    /**
     * ----------------------------------------------------
     * insert size -> resize
     * ----------------------------------------------------
     */
    inline SFrame& Insert(size_t size) {
        resize(size);
        return *this;
    }
    /**
     * ----------------------------------------------------
     * Shrink to size -> resize 
     *  - throw exception when size > Size()
     * ----------------------------------------------------
     */
    inline SFrame& Shrink(size_t size) {
        if (Size() < size) {
            throw FrameException(
                "Shrink=(" + __to_string(Size()) + "<" + __to_string(size) + ")"
            );
        }
        resize(size);
        return *this;
    }
    /**
     * ----------------------------------------------------
     * expand to capacity
     * ----------------------------------------------------
     */
    inline SFrame& Expand() {
        resize(capacity());
        return *this;
    }
} Frame;
/**
 * ------------------------------------------------------------------------------------------------
 * SFrame
 * ------------------------------------------------------------------------------------------------
 */
typedef class SIFrame : public Frame {
public:
    /**
     * ----------------------------------------------------
     * constructors
     * ----------------------------------------------------
     */
    SIFrame(size_t sz = 0) : Frame(sz), __cur(begin()) {
    }
    SIFrame(Frame&& f) : Frame(move(f)), __cur(begin()) {
    }
    SIFrame(SIFrame&& f) = default;
    /**
     * move operator
     */
    SIFrame& operator=(SIFrame&& f) = default;
    /**
     * ----------------------------------------------------
     * shrink frame
     * ----------------------------------------------------
     */
    inline SIFrame& Shrink() {
        resize(distance(begin(), __cur));
        return *this;
    }
    /**
     * ----------------------------------------------------
     * get data
     * ----------------------------------------------------
     */
    inline pointer Data() {
        return __cur.base();
    }
    /**
     * ----------------------------------------------------
     * get size
     * ----------------------------------------------------
     */
    inline size_t Size() {
        return distance(__cur, end());
    }
    /**
     * ----------------------------------------------------
     * reserve size
     * ----------------------------------------------------
     */
    inline SIFrame& Reserve(size_t sz) {
        auto sz_rem = Size();
        if (sz > sz_rem) {
            auto sz_cur = size();
            // resize vector    
            resize(sz_cur + sz - sz_rem);
            // reset pointer
            __cur = begin() + sz_cur;
        }
        return *this;
    }
    /**
     * ----------------------------------------------------
     * insert size
     * ----------------------------------------------------
     */
    inline SIFrame& Insert(size_t size) {
        __cur += size;
        return *this;
    }
    /**
     * write frame
     */
    inline SIFrame& Write(const Frame& frame) {
        __cur = copy(frame.begin(), frame.end(), __cur);
        return *this;
    }
    /**
     * ----------------------------------------------------
     * seek to position given by (pos)
     * ----------------------------------------------------
     */
    inline SIFrame& Seek(size_t pos) {
        __cur = next(begin(), pos);
        return *this;
    }
    /**
     * ----------------------------------------------------
     * shift to position given by (offset)
     * ----------------------------------------------------
     */
    inline SIFrame& Shift(size_t offset){
        __cur = __rotate(begin(), next(begin(), offset), __cur);
        return *this;
    }
    /**
     * ----------------------------------------------------
     * check size
     * ----------------------------------------------------
     */
    inline bool Empty() const {
        return (__cur <= begin());
    }
    inline bool Full() const {
        return (__cur >= end());
    }
private:
    /**
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
     * constructors
     */
    SOFrame(size_t sz) : Frame(sz), __cur(begin()) {
    }
    SOFrame(Frame& f) : Frame(f), __cur(begin()) {
    }
    SOFrame(Frame&& f) : SOFrame(f) {
    }
    SOFrame(SOFrame&& f) = default;
    /**
     * move operator
     */
    inline SOFrame& operator=(SOFrame&& f) = default;
    /**
     * get data pointer
     */
    inline pointer Data() {
        return __cur.base();
    }
    /**
     * get size
     */
    inline size_t Size() {
        return distance(__cur, end());
    }
    /**
     * remove size
     */
    inline SOFrame& Remove(size_t size) {
        __cur += size;
        return *this;
    }
    /**
     * move oframe to iframe
     */
    inline SOFrame& Move(IFrame& frame) {
        auto sz = min(Size(), frame.Size());
        memcpy(frame.Data(), Data(), sz);
        frame.Insert(sz);
        return Remove(sz);
    }
    /**
     * Read frame
     */
    inline Frame Read(size_t size) {
        if (Size() < size) {
            throw ContainerException(
                "Read=(" + __to_string(Size()) + "<" + __to_string(size) + ")"
            );
        }
        // move reference
        auto prev = __cur; __cur += size;
        // copy to new frame
        return Frame(prev, __cur);
    }
    /**
     * check empty
     */
    inline bool Empty() const {
        return (__cur >= end());
    }
    /**
     * check full
     */
    inline bool Full() const {
        return (__cur <= begin());
    }
private:
    /**
     */
    iterator __cur;
} OFrame;
/**
 * ------------------------------------------------------------------------------------------------
 * IBreakFrame
 * ------------------------------------------------------------------------------------------------
 */
template<size_t OFFSET = 0>
class SIBreakFrame : public Frame {
public:
    /**
     * constructors
     */
    SIBreakFrame() : Frame(),
    __beg(begin()), 
    __cur(begin()), 
    __end(end()), 
    __lim(end()){
    }
    /**
     */
    SIBreakFrame(size_t size) : Frame(size),
    __beg(next(begin(), sizeof (uint16_t))),
    __cur(begin()),
    __end(prev(end(), sizeof (uint16_t))),
    __lim(prev(end(), sizeof (uint16_t) - OFFSET)){
        *__cur++ = 0;
        *__cur++ = 0;
    }
    /**
     */
    SIBreakFrame(SIBreakFrame&& f) = default;
    /**
     * move operator
     */
    SIBreakFrame& operator=(SIBreakFrame&& f) = default;
    /**
     * insert size
     */
    inline void Insert(uint16_t size) {
        // write size
        *--__cur = uint8_t(size >> 8);
        *--__cur = uint8_t(size);
        // update position
        __cur += (sizeof (uint16_t) + size);
        // clear next slot
        *__cur++ = 0;
        *__cur++ = 0;
    }
    /**
     * get data pointer
     */
    inline pointer Data() {
        return __cur.base();
    }
    /**
     * get size
     */
    inline size_t Size() {
        return distance(__cur, __end);
    }
    /**
     * check empty
     */
    inline bool Empty() const {
        return (__cur <= __beg);
    }
    /**
     * check full
     */
    inline bool Full() const {
        return (__cur >= __lim);
    }
private:
    iterator __beg;
    iterator __cur;
    iterator __end;
    iterator __lim;
};
/**
 * ------------------------------------------------------------------------------------------------
 * OBreakFrame
 * ------------------------------------------------------------------------------------------------
 */
template<size_t OFFSET = 0>
class SOBreakFrame : public Frame {
public:
    /**
     * constructors
     */
    SOBreakFrame(Frame& f) : Frame(f),
    __cur(begin()), __size(0), __lim(prev(end(), sizeof (uint16_t) - OFFSET)) {
        __size = ReadSize__(__cur);
    }

    SOBreakFrame(Frame&& f) : SOBreakFrame(f) {
    }
    /**
     * move operator
     */
    SOBreakFrame& operator=(SOBreakFrame&& f) = default;
    /**
     */
    inline void Remove() {
        // update position
        __cur += __size;
        // read size
        __size = ReadSize__(__cur);
    }
    /**
     */
    inline pointer Data() {
        return __cur.base();
    }
    /**
     */
    inline size_t Size() const {
        return __size;
    }
    /**
     */
    inline bool Empty() const {
        return (__size == 0);
    }
    inline bool Full() const {
        return (__cur >= __lim);
    }
private:
    iterator __cur;
    size_t   __size;
    iterator __lim;
    /**
     * read size
     */
    inline size_t ReadSize__(iterator& cur){
        return uint16_t(*cur++) | (uint16_t(*cur++) << 8);
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * Container
 * ------------------------------------------------------------------------------------------------
 **/
typedef class SContainer : public std::vector<Frame> {
public:
    using Super = std::vector<Frame>;
    /**
     * using from supper 
     **/
    using Super::Super;
    using Super::operator=;
    /**
     * constructors
     */
    SContainer(size_t capacity = 0) : Super() {
        reserve(capacity);
    }
    /**
     * append list buffer
     */
    inline SContainer& Append(const SContainer& buffer){
        insert(end(), buffer.begin(), buffer.end());
        return *this;
    }
    /**
     */
    inline bool Full() {
        return (size() == capacity());
    }
} Container;
/**
 * ------------------------------------------------------------------------------------------------
 * Buffer
 * ------------------------------------------------------------------------------------------------
 **/
typedef class SBuffer : public std::basic_stringstream<uint8_t> {
public:
    using Super = std::basic_stringstream<uint8_t>;
    /**
     * constructors
     */
    SBuffer():Super(){
        exceptions(std::ios::failbit);
    }
    SBuffer(const Frame& frame):Super() {
        exceptions(std::ios::failbit);
        Write(frame);
    }
    /**
     * get length between read and write positions
     */
    inline size_t Length() {
        return tellp() - tellg();
    }
    /**
     * write frame
     */
    inline SBuffer& Write(const Frame& frame){
        write(frame.data(), frame.size()); return *this;
    }
    inline SBuffer& Write(Frame&& frame){
        write(frame.data(), frame.size()); return *this;
    }
    /**
     * write container
     */
    inline SBuffer& Write(Container&& container) {
        for (auto& frame : container) {
            Write(frame);
        }
        return *this;
    }
    /**
     * read frame with specific length
     */
    inline Frame Read(size_t len) {
        if (Length() < len) {
            throw ContainerException("len=" + to_string(len));
        }
        Frame frame(len);
        read(frame.data(), frame.size());
        return std::move(frame);
    }
    /**
     * read until the end
     */
    inline Frame Read() {
        Frame frame(Length());
        read(frame.data(), frame.size());
        return std::move(frame);
    }
    /**
     * read Read until fill frame or end of buffer
     */
    inline SBuffer& Fill(IFrame& f) {
        do { 
            f.Insert(readsome(f.Data(), f.Size())); 
        } while (gcount());
        return *this;
    }
} Buffer;
/**
 * ------------------------------------------------------------------------------------------------
 * Context
 * ------------------------------------------------------------------------------------------------
 **/
typedef class SContext {
public:
    /**
     * constructor
     */
    SContext()
    : __init(0), __position(0), __num_frames(0), __frame_size(0){
    }
    SContext(size_t position, size_t num_frames, size_t frame_size)
    : __init(3), __position(position), __num_frames(num_frames), __frame_size(frame_size) {
    }
    SContext(size_t position, size_t num_frames)
    : __init(2), __position(position), __num_frames(num_frames), __frame_size(0) {
    }
    /**
     * default constructors
     */
    SContext(SContext&& c) = default;

    SContext(const SContext& c) = default;
    /**
     * destructor
     */
    virtual ~SContext() = default;
    /**
     * move data
     */
    SContext& operator=(SContext&& context) = default;
    /**
     * copy operator
     */
    SContext& operator=(const SContext& context) = default;
    /**
     */
    inline reference_t GetPosition() const {
        return __position;
    }
    inline numframes_t GetNumFrames() const {
        return __num_frames;
    }
    inline framesize_t GetFrameSize() const {
        return __frame_size;
    }
    /**
     * operator
     */
    inline bool operator<(const SContext& context) const {
        return __position < context.__position;
    }
protected:
    size_t       __init;
    reference_t  __position;
    numframes_t  __num_frames;
    framesize_t  __frame_size;
} Context;
/**
 * ------------------------------------------------------------------------------------------------
 * Document
 * ------------------------------------------------------------------------------------------------
 **/
typedef class SDocument : public Container, public Context {
public:
    /**
     * default constructors
     */
    SDocument() = default;

    SDocument(SDocument&& d) = default;

    SDocument(const SDocument& d) = default;
    /**
     * context constructor
     */
    SDocument(SContext&& ctx) : Container(), Context(move(ctx)) {
    }
    SDocument(const SContext& ctx) : Container(), Context(ctx) {
    }
    /**
     * container constructor
     */
    SDocument(SContainer&& ctn) : Container(move(ctn)), Context() {
    }
    SDocument(const SContainer& ctn) : Container(ctn), Context() {
    }
    /**
     * container&context constructor
     */
    SDocument(SContainer&& ctn, SContext&& ctx) : Container(move(ctn)), Context(move(ctx)) {
    }
    SDocument(const SContainer& ctn, const SContext& ctx) : Container(ctn), Context(ctx) {
    }
    /**
     * destructor
     */
    virtual ~SDocument() = default;
    /**
     * move operator
     */
    SDocument& operator=(SDocument&& doc) = default;
    /**
     * copy operator
     */
    SDocument& operator=(const SDocument& doc) = default;
    /**
     * remove n elements
     */
    inline SDocument Remove(int n){
        SDocument d(Context(*this));
        d.reserve(n);
        while(n--) {
            d.push_back(std::move(back()));
            pop_back();
        }
        return d;
    }
    /**
     * insert elements
     */
    inline SDocument& Insert(SDocument doc){
        std::move(std::begin(doc), std::end(doc), std::back_inserter(*this));
        return *this;
    }
} Document;
/**
 * Input Document
 */
typedef class SIDocument : public SDocument {
public:
    using SDocument::SDocument;
    /**
     * default constructors
     */
    SIDocument() : __capacity(0) {
    }
    SIDocument(SIDocument&& d) = default;

    SIDocument(const SIDocument& d) = default;
    /**
     * destructor
     */
    virtual ~SIDocument() = default;
    /**
     * move operator
     */
    SIDocument& operator=(SIDocument&& doc) = default;
    /**
     * copy operator
     */
    SIDocument& operator=(const SIDocument& doc) = default;
    /**
     * push data
     */
    SIDocument& Push(Frame&& data);
    /**
     * check container
     */
    inline bool Full() {
        return (__init > 3) && (size() >= __capacity);
    }
protected:
    /**
     * capacity
     */
    numframes_t __capacity;
} IDocument;
/**
 * ------------------------------------------------------------------------------------------------
 * Utilities
 * ------------------------------------------------------------------------------------------------
 **/
inline std::ostream& operator<<(std::ostream& os, const Frame& b) {
    os << "[";
    for (auto v : b) {
        os << int(v) << " ";
    }
    return os << "]" << std::endl;
}

inline std::ostream& operator<<(std::ostream& os, const Container& l) {
    os << "[" << std::endl;
    for (auto v : l) {
        os << " " << v;
    }
    return os << "]" << std::endl;
}
/**
 */
#endif /* SSCONTAINER_H */

