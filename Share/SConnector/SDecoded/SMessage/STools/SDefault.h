/*
 * File:   Default.h
 * Author: Luis Monteiro
 *
 * Created on 6 de August de 2018, 22:46
 */
#ifndef SMSGTOOLDEFAULT_H
#define SMSGTOOLDEFAULT_H
/**
 * std
 */
#include <stddef.h>
#include <vector>
#include <math.h>
/**
 * space
 */
#include "SContainer.h"
/**
 * Begin namespace Decoded
 */
namespace Decoded {
/**
 * Begin namespace Message
 */
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
    static inline Container& Split(Frame& buf, Container& chunks) {
        // process chunk size -----------------------------
        auto res = div(
            static_cast<int>(buf.Size() + sizeof (framesize_t)), 
            static_cast<int>(chunks.capacity())
        );
        // normalize chunks size --------------------------
        size_t size = res.rem > 0 ? res.quot + 1 : res.quot;
        
        // resize frame and add buffer size ---------------
        buf.Insert(
            size * chunks.capacity()
        ).Number<framesize_t>(buf.Size());

        // container fill up ------------------------------
        OFrame out = move(buf);
        while(!chunks.Full()) {
            chunks.emplace_back(move(out.Read(size)));
        }
        // save buffer ------------------------------------
        buf = move(out);

        // return a split container -----------------------
        return chunks;
    }
    /**
     * ------------------------------------------------------------------------
     * Join buffer
     * ------------------------------------------------------------------------
     */
    static inline Frame& Join(const Container& chunks, Frame& buf) {
        // fill up tmp frame ------------------------------
        IFrame tmp = move(buf);
        for(auto& c: chunks) {
            tmp.Reserve(c.Size()).Write(c);
        }
        // move tmp to buffer -----------------------------
        buf = move(tmp.Shrink());
        
        // resize buffer (read size from end ) ------------ 
        buf.Shrink(buf.Number<framesize_t>());

        // return a joined buffer -------------------------
        return buf;
    }
};
/**
 * End namespace Message
 */
}
/**
 * End namespace Decoded
 */
}
#endif /* SMSGTOOLDEFAULT_H */

