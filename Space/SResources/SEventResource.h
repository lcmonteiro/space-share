/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SEventResource.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SEVENTRESOURCE_H
#define SEVENTRESOURCE_H
/**
 * space
 */
#include "SResource.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Event Resource
 * ------------------------------------------------------------------------------------------------
 */
class SEventResource : public SResource {
public:
    /**
     * ----------------------------------------------------
     * Constructors
     * ----------------------------------------------------
     * default
     */
    SEventResource(SEventResource&&) = default;
    SEventResource()                 = default;
    /**
     * main
     * @param init
     */
    SEventResource(int init);
    /**
     * ----------------------------------------------------
     * Operators
     * ----------------------------------------------------
     * move 
     */
    SEventResource& operator=(SEventResource&& t) = default;
    /**
     * ----------------------------------------------------
     * Interfaces
     * ----------------------------------------------------
     **
     * send event
     */
    bool send();
    /**
     * clear event
     */
    int clear();
};
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SEVENTRESOURCE_H */

