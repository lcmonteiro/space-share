/**
 * ------------------------------------------------------------------------------------------------
 * File:   Default.h
 * Author: Luis Monteiro
 *
 * Created on 6 de August de 2018, 22:46
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SMSGTOOLDEFAULT_H
#define SMSGTOOLDEFAULT_H
/**
 * std
 */
#include <vector>
#include <cmath>
/**
 * space
 */
#include "SContainer.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Begin namespace Decoded & Message
 * ------------------------------------------------------------------------------------------------
 */
namespace Decoded {
namespace Message {
/**
 */
class SDefault {
public:
    /**
     * ------------------------------------------------------------------------
     * Split buffer
     * ------------------------------------------------------------------------
     */
    static inline Container& Split(IOFrame& buf, Document& chunks) {
        /**
         * compute chunk size
         */
        auto res = div(
            static_cast<int>(buf.size() + sizeof (framesize_t)), 
            static_cast<int>(chunks.capacity())
        );
        /**
         * normalize chunks size
         */
        auto size = size_t(res.rem > 0 ? res.quot + 1 : res.quot);
        /** 
         * resize frame and add buffer size
         */
        buf.expand(
            size * chunks.capacity()
        ).number<framesize_t>(buf.size());
        /**
         * container fill up
         */
        while(!chunks.full()) {
            chunks.emplace_back(buf.read(size));
        }
        /**
         * return a split container
         */
        return chunks;
    }
    /**
     * ------------------------------------------------------------------------
     * Join buffer
     * ------------------------------------------------------------------------
     */
    static inline IOFrame& Join(const Document& chunks, IOFrame& buf) {
        /**
         * reset buffer
         */
        buf.clear();
        /**
         * fill up buffer
         */
        for(auto& c: chunks) {
            buf.reserve(c.size()).write(c);
        }
        /**
         *  resize buffer (read size from end)
         */ 
        buf.shrink(buf.number<framesize_t>());
        /**
         *  return a joined buffer
         */
        return buf;
    }
};
}}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Decoded & Message
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SMSGTOOLDEFAULT_H */

