/* 
 * Container:   SLinuxPoll.h
 * Author:      Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SLINUXPOLL_H
#define SLINUXPOLL_H
/**
 * std
 */
#include <list>
#include <chrono>
/**
 * local
 */
#include "SLinuxResource.h"
/**
 */
class SLinuxPoll : public SLinuxResource {
public:
        /**
         * -------------------------------------------------------------------------------------------------------------
         * constructors
         * -------------------------------------------------------------------------------------------------------------
         */
        SLinuxPoll();
        /**
         * -------------------------------------------------------------------------------------------------------------
         * interfaces
         * -------------------------------------------------------------------------------------------------------------
         **
         * insert linux resource
         */
        void Insert(SLinuxResource* r);
        /**
         * delete linux resource
         */
        void Delete(SLinuxResource* r);
        /**
         * read events
         */
        list<SLinuxResource*> Poll(const chrono::milliseconds& timeout, size_t max = 10);
};
/**
 */
#endif /* SLINUXPOLL_H */

