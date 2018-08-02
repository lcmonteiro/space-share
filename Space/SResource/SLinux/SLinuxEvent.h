/* 
 * Container:   SLinuxEvent.h
 * Author:      Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SLINUXEVENT_H
#define SLINUXEVENT_H
/**
 * std
 */
#include <sstream>
/**
 * local
 */
#include "SLinuxResource.h"
/**
 */
class SLinuxEvent : public SLinuxResource {
public:
        /**
         * -------------------------------------------------------------------------------------------------------------
         * constructors
         * -------------------------------------------------------------------------------------------------------------
         */
        SLinuxEvent() = default;
        
        SLinuxEvent(int init);
        /**
         * -------------------------------------------------------------------------------------------------------------
         * interfaces
         * -------------------------------------------------------------------------------------------------------------
         **
         * send event
         */
        bool Send();
        /**
         * clear event
         */
        int Clear();
};
/**
 */
#endif /* SLINUXEVENT_H */

