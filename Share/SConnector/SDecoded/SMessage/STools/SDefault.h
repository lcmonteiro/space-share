/*
 * File:   Default.h
 * Author: Luis Monteiro
 *
 * Created on 6 de August de 2018, 22:46
 */

#ifndef SMSGTOOLDEFAULT_H
#define MSGTOOLDEFAULT_H

#include <stddef.h>

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
        /**
	 * constructor
	 */
	SDefault() = default;
	/**
	 * destructor
	 */
	virtual ~SDefault() = default;
        /**
         */
        inline size_t Insert() {
                
        }
        /**
         */
        inline size_t Remove() {
                
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

