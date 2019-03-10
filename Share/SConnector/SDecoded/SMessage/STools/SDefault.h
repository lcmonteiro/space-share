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
        // process chunk size -----------------------------
        auto res = div(
            static_cast<int>(buf.size() + sizeof (framesize_t)), 
            static_cast<int>(chunks.capacity())
        );
        // normalize chunks size --------------------------
        size_t size = res.rem > 0 ? res.quot + 1 : res.quot;
        
        // resize frame and add buffer size ---------------
        buf.Expand(
            size * chunks.capacity()
        ).Number<framesize_t>(buf.size());

        // container fill up ------------------------------
        while(!chunks.Full()) {
            chunks.emplace_back(buf.Read(size));
        }
        // return a split container -----------------------
        return chunks;
    }
    /**
     * ------------------------------------------------------------------------
     * Join buffer
     * ------------------------------------------------------------------------
     */
    static inline IOFrame& Join(const Document& chunks, IOFrame& buf) {
        // reset buffer -----------------------------------
        buf.Reset();

        // fill up buffer ---------------------------------
        for(auto& c: chunks) {
            buf.Reserve(c.Size()).Write(c);
        }
        // resize buffer (read size from end) ------------ 
        buf.Shrink(buf.Number<framesize_t>());

        // return a joined buffer -------------------------
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

