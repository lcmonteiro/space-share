/**
 * ------------------------------------------------------------------------------------------------
 * File:   SContainer.h
 * Author: Luis Monteiro
 *
 * Created on November 23, 2016, 10:21 AM
 * ------------------------------------------------------------------------------------------------
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
     * ----------------------------------------------------
     * constructors
     * ----------------------------------------------------
     */
    SContainer(size_t capacity) : Super() {
        reserve(capacity);
    }
    /**
     * ----------------------------------------------------
     * reset
     * ----------------------------------------------------
     */
    inline SContainer& Reset() {
        clear(); 
        return *this;
    }
    /**
     * ----------------------------------------------------
     * append list buffer
     * ---------------------------------------------------
     */
    inline SContainer& Append(const SContainer& buffer) {
        insert(end(), buffer.begin(), buffer.end());
        return *this;
    }
    /**
     * ----------------------------------------------------
     *  check size
     * ----------------------------------------------------
     */
    inline size_t Capacity() const {
        return capacity();
    }
    inline size_t Size() const {
        return size();
    }
    inline bool Full() const {
        return (size() == capacity());
    }
    /**
     * ----------------------------------------------------
     * detach  
     * ----------------------------------------------------
     */
    inline SContainer&& Detach() {
        return std::move(*this);
    }
} Container;
/**
 * ------------------------------------------------------------------------------------------------
 * Buffer
 * ------------------------------------------------------------------------------------------------
 **/
// typedef class SBuffer : public std::basic_stringstream<uint8_t> {
// public:
//     using Super = std::basic_stringstream<uint8_t>;
//     /**
//      * constructors
//      */
//     SBuffer(): Super() {
//         exceptions(std::ios::failbit);
//     }
//     SBuffer(const Frame& frame): Super() {
//         exceptions(std::ios::failbit);
//         Write(frame);
//     }
//     /**
//      * get length between read and write positions
//      */
//     inline size_t Length() {
//         return tellp() - tellg();
//     }
//     /**
//      * write frame
//      */
//     inline SBuffer& Write(const Frame& frame) {
//         write(frame.data(), frame.size()); return *this;
//     }
//     inline SBuffer& Write(Frame&& frame) {
//         write(frame.data(), frame.size()); return *this;
//     }
//     /**
//      * write container
//      */
//     inline SBuffer& Write(Container&& container) {
//         for (auto& frame : container) {
//             Write(frame);
//         }
//         return *this;
//     }
//     /**
//      * read frame with specific length
//      */
//     inline Frame Read(size_t len) {
//         if (Length() < len) {
//             throw ContainerException(SText("len=", len));
//         }
//         auto frame = Frame(len).Expand().Detach();
//         read(frame.Data(), frame.Size());
//         return std::move(frame);
//     }
//     /**
//      * read until the end
//      */
//     inline Frame Read() {
//         Frame frame(Length());
//         read(frame.data(), frame.size());
//         return std::move(frame);
//     }
//     /**
//      * read Read until fill frame or end of buffer
//      */
//     inline SBuffer& Fill(IFrame& f) {
//         do { 
//             f.Insert(readsome(f.Data(), f.Size())); 
//         } while (gcount());
//         return *this;
//     }
// } Buffer;
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

