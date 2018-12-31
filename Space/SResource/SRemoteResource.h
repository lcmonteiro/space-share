/* 
 * Container:   SRemoteResource.h
 * Author:      Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SREMOTERESOURCE_H
#define SREMOTERESOURCE_H
/**
 */
#include "SResourceMonitor.h"
/**
 * ------------------------------------------------------------------------------------------------
 * linux platform 
 * ------------------------------------------------------------------------------------------------
 */
#ifdef __linux__
/**
 */
#include "SLinuxSocket.h"
/**
 * message
 */
namespace Message {
    class SRemoteResource : public SLinuxSocket {
    public:
        using SLinuxSocket::SLinuxSocket;
        /**
         * connect
         */
        inline void Connect(const string& host, uint16_t host_port) {
            SLinuxSocket::Connect(host, host_port, SLinuxSocket::DGRAM);
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
        inline SRemoteResource& Wait(chrono::milliseconds timeout) {
            if(!SLinuxResourceMonitor::Wait(*this, timeout).Valid()) {
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

