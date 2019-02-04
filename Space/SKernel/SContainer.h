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
#include <vector>
#include <ostream>
#include <cstdint>
#include <cstring>
#include <algorithm>
#include <stdexcept>
/**
 * space
 */
#include "SFrame.h"
#include "SText.h"
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
typedef class SContainerException : public std::range_error {
public:
    using std::range_error::range_error;
} ContainerException;
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
    SBuffer(): Super() {
        exceptions(std::ios::failbit);
    }
    SBuffer(const Frame& frame): Super() {
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
    inline SBuffer& Write(const Frame& frame) {
        write(frame.data(), frame.size()); return *this;
    }
    inline SBuffer& Write(Frame&& frame) {
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
            throw ContainerException(SText("len=", len));
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
    SDocument(SContext&& ctx) 
    : Container(), Context(std::move(ctx)) {
    }
    SDocument(const SContext& ctx) 
    : Container(), Context(ctx) {
    }
    /**
     * container constructor
     */
    SDocument(SContainer&& ctn) 
    : Container(std::move(ctn)), Context() {
    }
    SDocument(const SContainer& ctn) 
    : Container(ctn), Context() {
    }
    /**
     * container&context constructor
     */
    SDocument(SContainer&& ctn, SContext&& ctx) 
    : Container(std::move(ctn)), Context(std::move(ctx)) {
    }
    SDocument(const SContainer& ctn, const SContext& ctx) 
    : Container(ctn), Context(ctx) {
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
 * utilities
 * ------------------------------------------------------------------------------------------------
 **/
inline std::ostream& operator<<(std::ostream& os, const Container& l) {
    os << "[" << std::endl;
    for (auto v : l) {
        os << " " << v;
    }
    return os << "]";
}
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 **/
#endif /* SSCONTAINER_H */

