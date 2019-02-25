/* 
 * File:   SResourceHandler.h
 * Author: Luis Monteiro
 *
 * Created on January  2, 2019, 22:00 PM
 */
#ifndef SRESOURCEHANDLER_H
#define SRESOURCEHANDLER_H
/**
 * linux
 */
#include <unistd.h>
/**
 * std
 */
#include <chrono>
#include <system_error>
/**
 * space
 */
#include "SResource.h"
/**
 */
using namespace std;
/**
 * ------------------------------------------------------------------------------------------------
 * Linux Resource
 * ------------------------------------------------------------------------------------------------
 */
class SResourceHandler : public SResource::SHandler {
public:
    /**
     * ----------------------------------------------------
     * constructors / destructor
     * ----------------------------------------------------
     */
    SResourceHandler(int h) : __fd(h) {
        if (__fd < 0) {
            throw ResourceException(make_error_code(errc(errno)));
        }
    }
    /**
     */
    virtual ~SResourceHandler() {
        if (__fd >= 0) {
            ::close(__fd);
        }   
    }
    /**
     * ----------------------------------------------------
     * interface
     * ----------------------------------------------------
     * file descriptor
     */
    inline int FD() {
        return __fd;
    }
private:
    /**
     * file descriptor
     */
    int __fd;
};

#endif /* SRESOURCEHANDLER_H */