/*
 * Container:   SEventResource.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
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
 * constructors
 * ----------------------------------------------------------------------------
 */
SEventResource::SEventResource(int init) : SResource() {
    SetHandler(make_shared<SResourceHandler>(
        ::eventfd(init, 0)
    ));
}
/**
 * ----------------------------------------------------------------------------
 * interfaces
 * ----------------------------------------------------------------------------
 * send
 */
bool SEventResource::Send() {
     return (eventfd_write (GetHandler<SResourceHandler>()->FD(), 1) == 0);
}
/**
 * clear
 */
int SEventResource::Clear() {
     eventfd_t val;
     eventfd_read(GetHandler<SResourceHandler>()->FD(), &val);
     return val;
}
