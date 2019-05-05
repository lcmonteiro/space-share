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
        drain(frame);
    }
    /**
     * ------------------------------------------------------------------------
     * Length between read and write positions
     * ------------------------------------------------------------------------
     */
    inline size_t size() {
        return tellp() - tellg();
    }
    /**
     * ------------------------------------------------------------------------
     * write frame
     * ------------------------------------------------------------------------
     */
    template <
        typename Frame, 
        typename = std::enable_if_t<std::is_base_of<SFrame, Frame>::value>
    >
    SBuffer& drain(const Frame& f) {
        Super::write(f.data(), f.size()); return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * drain container 
     * ------------------------------------------------------------------------
     */
    SBuffer& drain(const Container& c) {
        for (auto& f : c) { drain(f); } return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * drain specific length to a frame
     * ------------------------------------------------------------------------
     */
    inline Frame drain(size_t len) {
        if (size() < len) 
            throw ContainerException(SText("len=", len));
        auto frame = Frame(len, len);
        Super::read(frame.data(), frame.size());
        return std::move(frame);
    }
    /**
     * ------------------------------------------------------------------------
     * Read until the end
     * ------------------------------------------------------------------------
     */
    inline Frame drain_all() {
        auto frame = Frame(size()).inflate().detach();
        Super::read(frame.data(), frame.size());
        return std::move(frame);
    }
    /**
     * ------------------------------------------------------------------------
     * Read until fill frame or end of buffer
     * ------------------------------------------------------------------------
     */
    inline SBuffer& fill(IOFrame& f) {
        do { 
            f.insert(readsome(f.idata(), f.isize())); 
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
    for (auto& v : b.str()) {
        os << int(v) << " ";
    }
    return os << "]";
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SBUFFER_H */