/* 
 * Container:   SPollResource.h
 * Author:      Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SPOLLRESOURCE_H
#define SPOLLRESOURCE_H
/*---------------------------------------------------------------------------------------------------------------------*
 * linux platform 
 *---------------------------------------------------------------------------------------------------------------------*/
#ifdef __linux__
/**
 */
#include "SLinux/SLinuxSocket.h"
/**
 * base
 */
class SPollResource : public SLinuxSocket {
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
        inline SPollResource& Wait(chrono::milliseconds timeout) {
                SLinuxResource::Wait(timeout); 
                return *this;
        }
};
/**
 */
#endif
/**
 */
#endif /* SPOLLRESOURCE_H */

