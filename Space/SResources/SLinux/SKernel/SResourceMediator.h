/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SResourceMediator.h
 * Author: Luis Monteiro
 *
 * Created on January  2, 2019, 22:00 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SRESOURCEMEDIATOR_H
#define SRESOURCEMEDIATOR_H
/**
 * linux
 */
#include <unistd.h>
#include <sys/stat.h>
/**
 * space
 */
#include "SResource.h"
#include "SFrame.h"
#include "SText.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Linux Resource Mediator
 * ------------------------------------------------------------------------------------------------
 */
class SResourceMediator {
public:
    /**
     * ------------------------------------------------------------------------
     * path 
     * ------------------------------------------------------------------------
     */
    static SText Path (int fd) {
        std::vector<char> out;
        //read real path
        int len = 0;
        do {
            out.resize(out.size() + 0x100);
            if((len = ::readlink(
                SText("/proc/self/fd/", fd
            ).data(), out.data(), out.size())) < 0) {
                throw ResourceException(std::make_error_code(std::errc(errno)));	
            }
        } while(out.size()==len);
        // return path as string
	    return SText(out.data());
    }
    /**
     * ------------------------------------------------------------------------
     * write 
     * ------------------------------------------------------------------------
     */
    static size_t Write(int fd, Frame::const_pointer p, Frame::size_type s) {
        auto n = ::write(fd, p, s);
        if (n <= 0) {
            if (n < 0) {
                throw OResourceExceptionABORT(strerror(errno));
            }
            throw OResourceExceptionABORT();
        }
        return n;
    }
    /**
     * ------------------------------------------------------------------------
     * read 
     * ------------------------------------------------------------------------
     */
    static size_t Read(int fd, Frame::pointer p, Frame::size_type s) {
        auto n = ::read(fd, p, s);
        if (n <= 0) {
            if (n < 0) {
                throw IResourceExceptionABORT(strerror(errno));
            }
            throw IResourceExceptionABORT();
        }
        return n;
    }
    /**
     * ------------------------------------------------------------------------
     * Size 
     * ------------------------------------------------------------------------
     */
    static size_t Length(int fd) {
        struct stat st;
        if (::fstat(fd, &st) < 0) {
            throw ResourceException(std::make_error_code(std::errc(errno)));
        }
        return st.st_size;
    }
    /**
     * ------------------------------------------------------------------------
     * check - is file 
     * ------------------------------------------------------------------------
     */
    static bool IsFile(int fd) {
        struct stat st;
        if (::fstat(fd, &st) < 0) {
            throw ResourceException(std::make_error_code(std::errc(errno)));
        }
        return (st.st_mode & S_IFMT) == S_IFREG;
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SRESOURCEMEDIATOR_H */