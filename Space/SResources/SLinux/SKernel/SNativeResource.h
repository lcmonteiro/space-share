/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SNativeResource.h
 * Author: Luis Monteiro
 *
 * Created on January  2, 2019, 22:00 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SNATIVERESOURCE_H
#define SNATIVERESOURCE_H
/**
 * linux
 */
#include <unistd.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <sys/socket.h>
/**
 * space
 */
#include "SResource.h"
#include "SFrame.h"
#include "SText.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Linux Resource
 * ------------------------------------------------------------------------------------------------
 */
class SNativeResource {
public:
    /**
     * ------------------------------------------------------------------------
     * Path 
     * ------------------------------------------------------------------------
     */
    static SText Path(int fd) {
        std::vector<char> out;
        /**
         * read real path
         */
        int len = 0;
        do {
            out.resize(out.size() + 0x100);
            if((len = ::readlink(
                SText("/proc/self/fd/", fd
            ).data(), out.data(), out.size())) < 0) {
                throw ResourceException(std::make_error_code(std::errc(errno)));	
            }
        } while(out.size()==len);
        /**
         * return path as string
         */
	    return SText(out.data());
    }
    /**
     * ------------------------------------------------------------------------
     * Send 
     * ------------------------------------------------------------------------
     */
    static size_t Send(int fd, Frame::const_pointer p, Frame::size_type s) {
        auto n = ::send(fd, p, s, MSG_NOSIGNAL);
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
     * Write 
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
     * Receive 
     * ------------------------------------------------------------------------
     */
    static size_t Receive(int fd, Frame::pointer p, Frame::size_type s) {
        auto n = ::recv(fd, p, s, 0);
        if (n <= 0) {
            if (n < 0) {
                if (errno == EAGAIN) {
                    throw ResourceExceptionTIMEOUT();
                }
                throw IResourceExceptionABORT(strerror(errno));
            }
            throw IResourceExceptionABORT();
        }
        return n;
    }
    /**
     * ------------------------------------------------------------------------
     * Read 
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
    static size_t Size(int fd) {
        struct stat st;
        if (::fstat(fd, &st) < 0) {
            throw ResourceException(
                std::make_error_code(std::errc(errno)));
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
            throw ResourceException(
                std::make_error_code(std::errc(errno)));
        }
        return (st.st_mode & S_IFMT) == S_IFREG;
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SNATIVERESOURCE_H */