/*
 * File:   Default.h
 * Author: Luis Monteiro
 *
 * Created on 6 de August de 2018, 22:46
 */

#ifndef SMSGTOOLDEFAULT_H
#define MSGTOOLDEFAULT_H

#include <stddef.h>
#include <vector>
#include <math.h>

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
	 * constructor
	 */
	SDefault() = default;
	/**
	 * destructor
	 */
	virtual ~SDefault() = default;
        /**
         * Split buffer
         */
        static inline Container& Split(Frame& buf, Container& chunks) {
                // process chunks size
                auto res = div((int)(buf.Size() + sizeof (framesize_t)), (int)chunks.size());
                // normalize chunks size
                size_t size = res.rem > 0 ? res.quot + 1 : res.quot;
                // resize frame and add size
                buf.Insert(size * chunks.size()).Number<framesize_t>(buf.Size());
                // container fill up
                OFrame out(move(buf));
                while(!chunks.Full()) {
                        chunks.emplace_back(move(out.Read(size)));
                }
                buf = move(out);
                // return a processed container
                return chunks;
        }
        /**
         * Join buffer
         */
        static inline Frame& Join(const Container& chunks, Frame& buf) {
                // fill up buffer
                IFrame in(move(buf));
                for(auto& c: chunks) {
                        in.Reserve(c.size()).Write(c);
                }
                buf = move(in);
                // read buffer size
                buf.Insert(buf.Number<framesize_t>());
                // return a processed buffer
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

