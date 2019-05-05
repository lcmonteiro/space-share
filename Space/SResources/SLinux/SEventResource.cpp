/**
 * ------------------------------------------------------------------------------------------------
 * File:   SEventResource.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 * ------------------------------------------------------------------------------------------------
 **
 * base linux
 */
#include <poll.h>
#include <unistd.h>
#include <sys/eventfd.h>
/**
 * space linux
 */
#include "SResourceHandler.h"
/**
 * space
 */
#include "SEventResource.h"
/**
 * ----------------------------------------------------------------------------
 * Constructors
 * ----------------------------------------------------------------------------
 */
SEventResource::SEventResource(int init) : SResource() {
    handler(std::make_shared<SResourceHandler>(::eventfd(init, 0)));
}
/**
 * ----------------------------------------------------------------------------
 * Interfaces
 * ----------------------------------------------------------------------------
 * send
 */
bool SEventResource::send() {
    return (::eventfd_write (handler<SResourceHandler>()->fd(), 1) == 0);
}
/**
 * clear
 */
int SEventResource::clear() {
    eventfd_t val = 0;
    ::eventfd_read(handler<SResourceHandler>()->fd(), &val);
    return val;
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */