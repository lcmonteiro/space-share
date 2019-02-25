/* 
 * File:   SEventResource.h
 * Author:      Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SEVENTRESOURCE_H
#define SEVENTRESOURCE_H
/**
 * space
 */
#include "SResource.h"
/**
 * ------------------------------------------------------------------------------------------------
 * event resource
 * ------------------------------------------------------------------------------------------------
 */
class SEventResource : public SResource {
public:
    /**
     * ----------------------------------------------------
     * constructors
     * ----------------------------------------------------
     * default
     */
    SEventResource(SEventResource&& ) = default;
    SEventResource()                  = default;
    /**
     * main
     * @param init
     */
    SEventResource(int init);
    /**
     * ----------------------------------------------------
     * operators
     * ----------------------------------------------------
     * move 
     */
    SEventResource& operator=(SEventResource&& t) = default;
    /**
     * ----------------------------------------------------
     * interfaces
     * ----------------------------------------------------
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
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SEVENTRESOURCE_H */

