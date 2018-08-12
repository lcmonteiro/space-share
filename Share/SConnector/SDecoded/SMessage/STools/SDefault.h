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
         * Split frame 
         */
        static inline Container& Split(Frame& frame, Container& container) {
                // process chunks size
                size_t size = std::ceil(
                        static_cast<float_t>(frame.Size() + sizeof (framesize_t)) / static_cast<float_t>(container.size())
                );
                // resize frame and add size
                frame.Insert(size * container.size()).Number<framesize_t>(frame.Size());
                // container fill up 
                OFrame out(move(frame));
                while(!container.Full()) {
                        container.emplace_back(move(out.Read(size)));
                }
                frame = move(out);
                // return a processed container
                return container;
        }
        /**
         * Join
         */
        static inline Frame& Join(const Container& container, Frame& frame) {
                
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

