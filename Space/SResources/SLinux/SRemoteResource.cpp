/**
 * ------------------------------------------------------------------------------------------------
 * File:   SLinuxSocket.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 * ------------------------------------------------------------------------------------------------
 */
//#define __DEBUG__
/**
 * base linux
 */
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
/**
 * std
 */
#ifdef __DEBUG__
#include <iostream>
#endif
#include <cstring>
/**
 * space linux
 */
#include "SResourceHandler.h"
#include "SMonitorHandler.h"
#include "SNativeResource.h"
/**
 * space
 */
#include "SRemoteResource.h"
#include "SFrame.h"
/**
 * definitions
 */
#define INIT_IO_TIMEOUT   10000 // us
/**
 * namespaces 
 */
using namespace std;
/**
 * ------------------------------------------------------------------------------------------------
 * BASE general interfaces
 * ------------------------------------------------------------------------------------------------
 * check
 * ----------------------------------------------------------------------------
 */
bool SRemoteResource::good() {
    int error = 0;
    socklen_t len = sizeof (error);
    /**
     * validation
     */
    try {
        if (::getsockopt(
            handler<SResourceHandler>()->fd(), SOL_SOCKET, SO_ERROR, &error, &len
        ) < 0) {
            return false;
        }
    } catch(...) {
        return false;
    }
    return error == 0;
}
/**
 * ----------------------------------------------------------------------------
 * Set Timeout
 * ----------------------------------------------------------------------------
 */
SRemoteResource& SRemoteResource::timeout_tx(int timeout) {
    struct timeval t = {
        .tv_sec = timeout,
        .tv_usec = 0
    };
    if (::setsockopt(
        handler<SResourceHandler>()->fd(), SOL_SOCKET, SO_SNDTIMEO, (void*) & t, sizeof (t)
    ) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
    return *this;
}
SRemoteResource& SRemoteResource::timeout_rx(int timeout) {
    struct timeval t = {
        .tv_sec = timeout,
        .tv_usec = 0
    };
    if (::setsockopt(
        handler<SResourceHandler>()->fd(), SOL_SOCKET, SO_RCVTIMEO, (void*) & t, sizeof (t)
    ) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
    return *this;
}
/**
 * ----------------------------------------------------------------------------
 * Set Delay
 * ----------------------------------------------------------------------------
 */
SRemoteResource& SRemoteResource::delay(bool flag) {
    int f = flag ? 0 : 1;
    if (::setsockopt(
        handler<SResourceHandler>()->fd(), IPPROTO_TCP, TCP_NODELAY, (void*) & f, sizeof (f)
    ) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
    return *this;
}
/**
 * ------------------------------------------------------------------------------------------------
 * Input
 * ------------------------------------------------------------------------------------------------
 * Fill
 * ----------------------------------------------------------------------------
 */
template<>
SRemoteResource& SRemoteResource::fill(IOFrame& f) {
    while (!f.full()) {
        f.insert(SNativeResource::Receive(
            handler<SResourceHandler>()->fd(), f.idata(), f.isize()));
    }
    return *this;
}
template<>
SRemoteResource& SRemoteResource::fill(Frame& f) {
    for (auto it = f.begin(), end = f.end(); it != end;) {
        it = next(it, SNativeResource::Receive(
            handler<SResourceHandler>()->fd(), it.base(), distance(it, end)));
    }
    return *this;
}
/**
 * ----------------------------------------------------------------------------
 * Read
 * ----------------------------------------------------------------------------
 */
template<>
SRemoteResource& SRemoteResource::read(IOFrame& f) {
    f.insert(SNativeResource::Receive(
        handler<SResourceHandler>()->fd(), f.idata(), f.isize()));
    return *this;
}
template<>
SRemoteResource& SRemoteResource::read(Frame& f) {
    f.insert(SNativeResource::Receive(
        handler<SResourceHandler>()->fd(), f.data(), f.size()));
    return *this;
}
/**
 * ------------------------------------------------------------------------------------------------
 * Output
 * ------------------------------------------------------------------------------------------------
 * Drain
 * ----------------------------------------------------------------------------
 */
template<typename T>
SRemoteResource& SRemoteResource::drain(T& f) {
    while (!f.empty()) {
        f.remove(SNativeResource::Send(
            handler<SResourceHandler>()->fd(), f.data(), f.size()));
    }
    return *this;
}
template<typename T>
SRemoteResource& SRemoteResource::drain(const T& f) {
    for (auto it = f.begin(), end = f.end(); it != end;) {
        it = next(it, SNativeResource::Send(
            handler<SResourceHandler>()->fd(), it.base(), distance(it, end)));
    }
    return *this;
}
template SRemoteResource& SRemoteResource::drain(Frame&);
template SRemoteResource& SRemoteResource::drain(IOFrame&);
template SRemoteResource& SRemoteResource::drain(const Frame&);
template SRemoteResource& SRemoteResource::drain(const IOFrame&);
/**
 * ----------------------------------------------------------------------------
 * Write
 * ----------------------------------------------------------------------------
 */
template<typename T>
SRemoteResource& SRemoteResource::write(T& f) {
    f.remove(SNativeResource::Send(
        handler<SResourceHandler>()->fd(), f.data(), f.size()));
    return *this;
}
template<typename T>
SRemoteResource& SRemoteResource::write(const T& f) {
    SNativeResource::Send(
        handler<SResourceHandler>()->fd(), f.data(), f.size());
    return *this;
}
template SRemoteResource& SRemoteResource::write(Frame&);
template SRemoteResource& SRemoteResource::write(IOFrame&);
template SRemoteResource& SRemoteResource::write(const Frame&);
template SRemoteResource& SRemoteResource::write(const IOFrame&);
/**
 * ------------------------------------------------------------------------------------------------
 * MESSAGE general interfaces
 * ------------------------------------------------------------------------------------------------
 * Bind
 * ----------------------------------------------------------------------------
 */
Message::SRemoteResource& Message::SRemoteResource::bind(
    const string& host, uint16_t port) {
    /**
     * bind parameters
     */
    struct addrinfo hints;
    memset(&hints, 0, sizeof (struct addrinfo));
    hints.ai_family = AF_UNSPEC;            // Allow IPv4 or IPv6
    hints.ai_socktype = SOCK_DGRAM;         // Datagram socket
    hints.ai_flags = AI_PASSIVE;            // For wildcard IP address
    hints.ai_protocol = 0;                  // Any protocol
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    /**
     * get info
     */
    struct addrinfo *result;
    if (::getaddrinfo(host.c_str(), to_string(port).c_str(), &hints, &result) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
    /**
     * connect
     */
    int i = 0;
    for (auto rp = result; rp != NULL; rp = rp->ai_next, ++i) {
        struct sockaddr_storage addr;
        socklen_t len = sizeof(addr);
        /**
         * create a linux handler
         */
        auto h = make_shared<SResourceHandler>(
            ::socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)
        );
        /**
         * set options
         */
        int opt = 1;
        if (::setsockopt(h->fd(), SOL_SOCKET, SO_REUSEADDR, (int*) & opt, sizeof (int)) < 0) {
            continue;
        }
        if (::bind(h->fd(), rp->ai_addr, rp->ai_addrlen) < 0) {
            continue;
        }
        struct timeval t = {.tv_sec = 0, .tv_usec = INIT_IO_TIMEOUT};
        if (::setsockopt(h->fd(), SOL_SOCKET, SO_SNDTIMEO, (void*) &t, sizeof (t)) < 0) {
            continue;
        }
        if (::setsockopt(h->fd(), SOL_SOCKET, SO_RCVTIMEO, (void*) &t, sizeof (t)) < 0) {
            continue;
        }
#ifdef __DEBUG__
        char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
        if (::getnameinfo(
            rp->ai_addr, rp->ai_addrlen,
            hbuf, sizeof (hbuf),
            sbuf, sizeof (sbuf),
            NI_NUMERICHOST | NI_NUMERICSERV
        ) == 0) {
            cout << "binded: " << "host=" << hbuf << ", serv=" << sbuf << endl;
        }
#endif
        /**
         * free results
         **/
        ::freeaddrinfo(result);
        /**
         * save handler
         */
        handler(h);
        return *this;
    }
    /**
     * fail
     **/
    ::freeaddrinfo(result);
    throw ResourceException(make_error_code(errc::no_such_device_or_address));
}
/**
 * ----------------------------------------------------------------------------
 * Wait
 * ----------------------------------------------------------------------------
 */
Message::SRemoteResource& Message::SRemoteResource::wait(
    const string& host, uint16_t port, chrono::seconds timeout) {
    /**
     * bind parameters
     */
    struct addrinfo hints;
    memset(&hints, 0, sizeof (struct addrinfo));
    hints.ai_family = AF_UNSPEC;            // Allow IPv4 or IPv6
    hints.ai_socktype = SOCK_DGRAM;         // Datagram socket
    hints.ai_flags = AI_PASSIVE;            // For wildcard IP address
    hints.ai_protocol = 0;                  // Any protocol
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    /**
     * get info
     */
    struct addrinfo *result;
    if (::getaddrinfo(host.c_str(), to_string(port).c_str(), &hints, &result) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
    /**
     * connect
     */
    int i = 0;
    for (auto rp = result; rp != NULL; rp = rp->ai_next, ++i) {
        struct sockaddr_storage addr;
        socklen_t len = sizeof(addr);
        /**
         * create a linux handler
         */
        auto h = make_shared<SResourceHandler>(
            ::socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)
        );
        /**
         * set options
         */
        int opt = 1;
        if (::setsockopt(h->fd(), SOL_SOCKET, SO_REUSEADDR, (int*) & opt, sizeof (int)) < 0) {
            continue;
        }
        if (::bind(h->fd(), rp->ai_addr, rp->ai_addrlen) < 0) {
            continue;
        }
        struct timeval t = {.tv_sec = 0, .tv_usec = INIT_IO_TIMEOUT};
        if (::setsockopt(h->fd(), SOL_SOCKET, SO_SNDTIMEO, (void*) &t, sizeof (t)) < 0) {
            continue;
        }
        if (::setsockopt(h->fd(), SOL_SOCKET, SO_RCVTIMEO, (void*) &t, sizeof (t)) < 0) {
            continue;
        }
#ifdef __DEBUG__
        char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
        if (::getnameinfo(
            rp->ai_addr, rp->ai_addrlen,
            hbuf, sizeof (hbuf),
            sbuf, sizeof (sbuf),
            NI_NUMERICHOST | NI_NUMERICSERV
        ) == 0) {
            cout << "binded: " << "host=" << hbuf << ", serv=" << sbuf << endl;
        }
#endif
        /**
         * free results
         **/
        ::freeaddrinfo(result);
        /**
         * wait for data 
         */
        SStaticMonitorHandler({h}).wait(timeout);
        /**
         * get address and connect
         */
        if (::recvfrom(h->fd(), nullptr, 0, MSG_PEEK,(struct sockaddr *)&addr, &len) < 0) {
            throw ResourceException(make_error_code(errc(errno)));
        }
#ifdef __DEBUG__
        char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
        if (::getnameinfo(
            (struct sockaddr *)&addr, len,
            hbuf, sizeof (hbuf),
            sbuf, sizeof (sbuf),
            NI_NUMERICHOST | NI_NUMERICSERV) == 0
            ) {
            cout << "connected: " << "host=" << hbuf << ", serv=" << sbuf << endl;
        }
#endif
        if (::connect(h->fd(), (struct sockaddr *)&addr, len) < 0) {
            throw ResourceException(make_error_code(errc(errno)));
        }
        /**
         * save handler
         */
        handler(h);
        return *this;
    }
    /**
     * fail
     **/
    ::freeaddrinfo(result);
    throw ResourceException(make_error_code(errc::no_such_device_or_address));
}
/**
 * ----------------------------------------------------------------------------
 * Link
 * ----------------------------------------------------------------------------
 */
Message::SRemoteResource& Message::SRemoteResource::link(
    const string& host, uint16_t host_port) {
    /**
     * connect parameters
     */
    struct addrinfo hints;
    memset(&hints, 0, sizeof (struct addrinfo));
    hints.ai_family   = AF_UNSPEC;          // Allow IPv4 or IPv6 
    hints.ai_socktype = SOCK_DGRAM;         // Datagram socket
    /**
     * get info
     */
    struct addrinfo *result;
    if (::getaddrinfo(host.c_str(), to_string(host_port).c_str(), &hints, &result) != 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
    /**
     * create connection
     */
    int i = 0;
    for (auto rp = result; rp != NULL; rp = rp->ai_next, ++i) {
        /**
         * create a linux handler
         */
        auto h = make_shared<SResourceHandler>(
            ::socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)
        );
        /**
         * try to connect
         */
        if (::connect(h->fd(), rp->ai_addr, rp->ai_addrlen) < 0) {
            continue;
        }
        /**
         * set options
         */
        struct timeval t = {.tv_sec = 0, .tv_usec = INIT_IO_TIMEOUT};
        if (::setsockopt(h->fd(), SOL_SOCKET, SO_SNDTIMEO, (void*) &t, sizeof (t)) < 0) {
            continue;
        }
        if (::setsockopt(h->fd(), SOL_SOCKET, SO_RCVTIMEO, (void*) &t, sizeof (t)) < 0) {
            continue;
        }
#ifdef __DEBUG__
        char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
        if (::getnameinfo(
            rp->ai_addr, rp->ai_addrlen,
            hbuf, sizeof (hbuf),
            sbuf, sizeof (sbuf),
            NI_NUMERICHOST | NI_NUMERICSERV) == 0
            ) {
            cout << "connected: " << "host=" << hbuf << ", serv=" << sbuf << endl;
        }
#endif
        /**
         * free results
         **/
        ::freeaddrinfo(result);
        /**
         * save handler
         */
        handler(h);
        return *this;
    }
    /**
     * fail
     **/
    ::freeaddrinfo(result);
    throw ResourceException(make_error_code(errc::no_such_device_or_address));
}
/**
 * ------------------------------------------------------------------------------------------------
 * STREAM general interfaces
 * ------------------------------------------------------------------------------------------------
 * Wait
 * ----------------------------------------------------------------------------
 */
Stream::SRemoteResource& Stream::SRemoteResource::wait(
    const string& host, uint16_t port, chrono::seconds timeout) {
    /**
     * bind parameters
     */
    struct addrinfo hints;
    memset(&hints, 0, sizeof (struct addrinfo));
    hints.ai_family = AF_UNSPEC;            // Allow IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;        // stream socket
    hints.ai_flags = AI_PASSIVE;            // For wildcard IP address
    hints.ai_protocol = 0;                  // Any protocol
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    /**
     * get info
     */
    struct addrinfo *result;
    if (::getaddrinfo(host.c_str(), to_string(port).c_str(), &hints, &result) != 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
    /**
     * connect
     */
    int i = 0;
    for (auto rp = result; rp != NULL; rp = rp->ai_next, ++i) {
        struct sockaddr_storage addr;
        socklen_t len = sizeof(addr);
        /**
         * create a server handler
         */
        auto s = make_shared<SResourceHandler>(
            ::socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)
        );
        /**
         * bind and listen
         */
        int opt = 1;
        if (::setsockopt(s->fd(), SOL_SOCKET, SO_REUSEADDR, (int*) & opt, sizeof (int)) < 0) {
            continue;
        }
        if (::bind(s->fd(), rp->ai_addr, rp->ai_addrlen) < 0) {
            continue;
        }
        if (::listen(s->fd(), 1) < -1) {
            continue;
        }
#ifdef __DEBUG__
        char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
        if (::getnameinfo(
            rp->ai_addr, rp->ai_addrlen,
            hbuf, sizeof (hbuf),
            sbuf, sizeof (sbuf),
            NI_NUMERICHOST | NI_NUMERICSERV) == 0
            ) {
            cout << "binded: " << "host=" << hbuf << ", serv=" << sbuf << endl;
        }
#endif
        /**
         * free results
         **/
        ::freeaddrinfo(result);
        /**
         * wait connection
         */
        SStaticMonitorHandler({s}).wait(timeout);        
        /**
         * accept handler
         */
        auto h = make_shared<SResourceHandler>(
            ::accept(s->fd(), (struct sockaddr *)&addr, &len)
        );
        /**
         * set options
         */
        struct timeval t = {.tv_sec = 0, .tv_usec = INIT_IO_TIMEOUT};
        if (::setsockopt(h->fd(), SOL_SOCKET, SO_SNDTIMEO, (void*) &t, sizeof (t)) < 0) {
            throw ResourceException(make_error_code(errc(errno)));
        }
        if (::setsockopt(h->fd(), SOL_SOCKET, SO_RCVTIMEO, (void*) &t, sizeof (t)) < 0) {
            throw ResourceException(make_error_code(errc(errno)));
        }
        /**
         * save handler
         */
        handler(h);
        return *this;
    }
    /**
     * fail
     **/
    ::freeaddrinfo(result);
    throw ResourceException(make_error_code(errc::no_such_device_or_address));
}
/**
 * ----------------------------------------------------------------------------
 * Link
 * ----------------------------------------------------------------------------
 */
Stream::SRemoteResource& Stream::SRemoteResource::link(
    const string& host, uint16_t host_port) {
    /**
     * connect parameters
     */
    struct addrinfo hints;
    memset(&hints, 0, sizeof (struct addrinfo));
    hints.ai_family = AF_UNSPEC;            // Allow IPv4 or IPv6 
    hints.ai_socktype = SOCK_STREAM;        // stream socket
    /**
     * get info
     */
    struct addrinfo *result;
    if (::getaddrinfo(host.c_str(), to_string(host_port).c_str(), &hints, &result) != 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
    /**
     * create connection
     */
    int i = 0;
    for (auto rp = result; rp != NULL; rp = rp->ai_next, ++i) {
        /**
         * create a linux handler
         */
        auto h = make_shared<SResourceHandler>(
            ::socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)
        );
        /**
         * try to connect
         */
        if (::connect(h->fd(), rp->ai_addr, rp->ai_addrlen) < 0) {
            continue;
        }
        /**
         * set options
         */
        struct timeval t = {.tv_sec = 0, .tv_usec = INIT_IO_TIMEOUT};
        if (::setsockopt(h->fd(), SOL_SOCKET, SO_SNDTIMEO, (void*) &t, sizeof (t)) < 0) {
            continue;
        }
        if (::setsockopt(h->fd(), SOL_SOCKET, SO_RCVTIMEO, (void*) &t, sizeof (t)) < 0) {
            continue;
        }
#ifdef __DEBUG__
        char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
        if (::getnameinfo(
            rp->ai_addr, rp->ai_addrlen,
            hbuf, sizeof (hbuf),
            sbuf, sizeof (sbuf),
            NI_NUMERICHOST | NI_NUMERICSERV) == 0
            ) {
            cout << "connected: " << "host=" << hbuf << ", serv=" << sbuf << endl;
        }
#endif
        /**
         * success
         **/
        ::freeaddrinfo(result);
        /**
         * save handler
         */
        handler(h);
        return *this;
    }
    /**
     * fail
     **/
    ::freeaddrinfo(result);
    throw ResourceException(make_error_code(errc::no_such_device_or_address));
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */