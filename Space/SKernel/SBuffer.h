/**
 * ------------------------------------------------------------------------------------------------
 * File:   SBuffer.h
 * Author: Luis Monteiro
 *
 * Created on February  2, 2019, 10:21 AM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SBUFFER_H
#define SBUFFER_H
/**
 * space
 */
#include "SContainer.h"
#include "SFrame.h"
/**
 * ------------------------------------------------------------------------------------------------
 * SBuffer
 * ------------------------------------------------------------------------------------------------
 */
typedef class SBuffer : public std::basic_stringstream<uint8_t> {
public:
    using Super = std::basic_stringstream<uint8_t>;
    /**
     * ------------------------------------------------------------------------
     * constructors
     * ------------------------------------------------------------------------
     */
    SBuffer(): Super() {
        exceptions(std::ios::failbit);
    }
    SBuffer(const Frame& frame): Super() {
        exceptions(std::ios::failbit);
        Write(frame);
    }
    /**
     * ------------------------------------------------------------------------
     * get length between read and write positions
     * ------------------------------------------------------------------------
     */
    inline size_t Length() {
        return tellp() - tellg();
    }
    /**
     * ------------------------------------------------------------------------
     * write frame
     * ------------------------------------------------------------------------
     */
    inline SBuffer& Write(const Frame& frame) {
        write(frame.data(), frame.size()); return *this;
    }
    inline SBuffer& Write(Frame&& frame) {
        write(frame.data(), frame.size()); return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * write container
     * ------------------------------------------------------------------------
     */
    inline SBuffer& Write(Container&& container) {
        for (auto& frame : container) {
            Write(frame);
        }
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * read frame with specific length
     * ------------------------------------------------------------------------
     */
    inline Frame Read(size_t len) {
        if (Length() < len) {
            throw ContainerException(SText("len=", len));
        }
        auto frame = Frame(len).Expand().Detach();
        read(frame.Data(), frame.Size());
        return std::move(frame);
    }
    /**
     * ------------------------------------------------------------------------
     * read until the end
     * ------------------------------------------------------------------------
     */
    inline Frame Read() {
        Frame frame(Length());
        read(frame.data(), frame.size());
        return std::move(frame);
    }
    /**
     * ------------------------------------------------------------------------
     * read Read until fill frame or end of buffer
     * ------------------------------------------------------------------------
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
 * Utilities
 * ------------------------------------------------------------------------------------------------
 **/
inline std::ostream& operator<<(std::ostream& os, const Buffer& b) {
    os << "[";
    // for (auto v : b) {
    //     os << int(v) << " ";
    // }
    return os << "]";
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SBUFFER_H */