/* 
 * Container:   SLocalResource.h
 * Author:      Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SLOCALRESOURCE_H
#define SLOCALRESOURCE_H
/**
 */
#include "SResourceMonitor.h"
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * linux platform 
 * ---------------------------------------------------------------------------------------------------------------------
 */
#ifdef __linux__
/**
 */
#include "SLinuxSocket.h"
/**
 * message
 */
namespace Message {
    class SLocalResource : public SLinuxSocket {
    public:
        using SLinuxSocket::SLinuxSocket;
        /**
         * connect
         */
        inline void Connect(const string& host) {
            SLinuxSocket::Connect(host, SLinuxSocket::DGRAM);
        }
        /**
         * bind
         */
        inline void Bind(const string& host) {
            SLinuxSocket::Bind(host, SLinuxSocket::DGRAM);
        }
        /**
         * wait
         */
        inline SLocalResource& Wait(chrono::milliseconds timeout) {
            if(!SLinuxResourceMonitor::Wait(*this, timeout).valid()) {
                throw IResourceExceptionABORT();
            }
            return *this;
        }
    };
}
/**
 * stream
 */
namespace Stream {

}
/**
 */
#endif
/**
 */
#endif /* SLOCALRESOURCE_H */

