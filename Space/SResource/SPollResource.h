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
 * space
 */
#include "SResource.h"
#include "SBimap.h"
/**
 */
template<typename ADAPT>
class SPollResource : public SResource {
public:
    /**
     * --------------------------------------------------------------------------------------------
     * constructors
     * --------------------------------------------------------------------------------------------
     */
    SPollResource();
    /**
     * operator
     */
    SPollResource& operator=(SPollResource &&) = default;
    /**
     * ----------------------------------------------------------------------------------------
     * interfaces
     * ----------------------------------------------------------------------------------------
     **
     * insert resource
     */
    void Insert(ADAPT::Type r);
    /**
     * delete resource
     */
    void Delete(ADAPT::Type r);
    /**
     * read events
     */
    list<ADAPT::Type> Wait(const chrono::milliseconds& timeout, size_t max = 10);
protected:
    using Handler  = SResource::pHandler<>;
    /**
     * ----------------------------------------------------------------------------------------
     * native interfaces
     * ----------------------------------------------------------------------------------------
     **
     * insert
     */
    void __Insert(Handler r);
    /**
     * delete
     */
    void __Delete(Handler r);
    /**
     * wait
     */
    void __Wait(const chrono::milliseconds& timeout, size_t max = 10);
private:
    /**
     * ------------------------------------------------------------------------
     * variables
     * ------------------------------------------------------------------------
     **
     * timeout
     */
    Time __timeout;
    /**
     * map between object and resource handler
     */
    Bimap __map;
};
/**
 */
#endif /* SLINUXPOLL_H */

