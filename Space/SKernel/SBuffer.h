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
    SBuffer(SBuffer&& b): Super(std::forward<Super>(b)) {
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
    template <
        typename FRAME, 
        typename = std::enable_if_t<std::is_base_of<SFrame, FRAME>::value>
    >
    SBuffer& Write(const FRAME& f) {
        write(f.data(), f.size()); return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * write container
     * ------------------------------------------------------------------------
     */
    SBuffer& Write(const Container& c) {
        for (auto& f : c) { Write(f); } return *this;
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
        auto frame = Frame(len).Expand().detach();
        read(frame.Data(), frame.size());
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
    inline SBuffer& Fill(IOFrame& f) {
        do { 
            f.Insert(readsome(f.IData(), f.isize())); 
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