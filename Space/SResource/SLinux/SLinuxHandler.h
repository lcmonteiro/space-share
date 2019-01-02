/* 
 * Container:   SLinuxHandler.h
 * Author: Luis Monteiro
 *
 * Created on January  2, 2019, 22:00 PM
 */
#ifndef SLINUXHANDLER_H
#define SLINUXHANDLER_H
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
class SLinuxHandler : public SResource::SHandler {
public:
    /**
     * ---------------------------------------------
     * constructors / destructor
     * ---------------------------------------------
     */
    SLinuxHandler(int h) : __fd(h) {
        if (__fd < 0) {
            throw ResourceException(make_error_code(errc(errno)));
        }
    }
    /**
     */
    virtual ~SLinuxHandler() {
        if (__fd >= 0) {
            ::close(__fd);
        }   
    }
    /**
     * ---------------------------------------------
     * interface
     * ---------------------------------------------
     * get file descriptor
     */
    inline int FD() {
        return __fd;
    }
private:
    /**
     * native handler
     */
    int __fd;
};

#endif /* SLINUXHANDLER_H */