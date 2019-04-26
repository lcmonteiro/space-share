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
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/un.h>
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
 * linux interface
 * ------------------------------------------------------------------------------------------------
 */
static size_t __Send(int fd, Frame::const_pointer p, Frame::size_type s);
static size_t __Recv(int fd, Frame::pointer       p, Frame::size_type s);
/**
 * ------------------------------------------------------------------------------------------------
 * BASE general interfaces
 * ------------------------------------------------------------------------------------------------
 * check good
 */
bool SRemoteResource::Good() {
    int error = 0;
    socklen_t len = sizeof (error);
    /**
     * validation
     */
    try {
        if (::getsockopt(
            GetHandler<SResourceHandler>()->FD(), SOL_SOCKET, SO_ERROR, &error, &len
        ) < 0) {
            return false;
        }
    } catch(...) {
        return false;
    }
    return error == 0;
}
/**
 * Set Timeout
 */
SRemoteResource& SRemoteResource::SetTxTimeout(int timeout) {
    struct timeval t = {
        .tv_sec = timeout,
        .tv_usec = 0
    };
    if (::setsockopt(
        GetHandler<SResourceHandler>()->FD(), SOL_SOCKET, SO_SNDTIMEO, (void*) & t, sizeof (t)
    ) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
    return *this;
}
SRemoteResource& SRemoteResource::SetRxTimeout(int timeout) {
    struct timeval t = {
        .tv_sec = timeout,
        .tv_usec = 0
    };
    if (::setsockopt(
        GetHandler<SResourceHandler>()->FD(), SOL_SOCKET, SO_RCVTIMEO, (void*) & t, sizeof (t)
    ) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
    return *this;
}
/**
 * SetNoDelay
 */
SRemoteResource& SRemoteResource::SetNoDelay(bool flag) {
    int f = flag ? 1 : 0;
    if (::setsockopt(
        GetHandler<SResourceHandler>()->FD(), IPPROTO_TCP, TCP_NODELAY, (void*) & f, sizeof (f)
    ) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
    return *this;
}
/**
 * ------------------------------------------------------------------------------------------------
 * IO functions
 * ------------------------------------------------------------------------------------------------
 * Input
 * ----------------------------------------------------------------------------
 * fill
 */
template<>
SRemoteResource& SRemoteResource::Fill(IOFrame& f) {
    while (!f.Full()) {
        f.Insert(__Recv(
            GetHandler<SResourceHandler>()->FD(), f.IData(), f.ISize()
        ));
    }
    return *this;
}
template<>
SRemoteResource& SRemoteResource::Fill(Frame& f) {
    for (auto it = f.begin(), end = f.end(); it != end;) {
        it = next(it, __Recv(
            GetHandler<SResourceHandler>()->FD(), it.base(), distance(it, end)
        ));
    }
    return *this;
}
/**
 * read
 */
template<>
SRemoteResource& SRemoteResource::Read(IOFrame& f) {
    f.Insert(__Recv(
        GetHandler<SResourceHandler>()->FD(), f.IData(), f.ISize())
    );
    return *this;
}
template<>
SRemoteResource& SRemoteResource::Read(Frame& f) {
    f.Insert(__Recv(
        GetHandler<SResourceHandler>()->FD(), f.Data(), f.Size())
    );
    return *this;
}
/**
 * ----------------------------------------------------------------------------
 * Output
 * ----------------------------------------------------------------------------
 * drain
 */
template<typename T>
SRemoteResource& SRemoteResource::Drain(T& f) {
    // send loop ----------------------
    while (!f.Empty()) {
        f.Remove(__Send(
            GetHandler<SResourceHandler>()->FD(), f.Data(), f.Size()
        ));
    }
    return *this;
}
template<typename T>
SRemoteResource& SRemoteResource::Drain(const T& f) {
    // send loop ----------------------
    for (auto it = f.begin(), end = f.end(); it != end;) {
        it = next(it, __Send(
            GetHandler<SResourceHandler>()->FD(), it.base(), distance(it, end)
        ));
    }
    return *this;
}
template SRemoteResource& SRemoteResource::Drain(Frame&);
template SRemoteResource& SRemoteResource::Drain(IOFrame&);
template SRemoteResource& SRemoteResource::Drain(const Frame&);
template SRemoteResource& SRemoteResource::Drain(const IOFrame&);
/**
 * write
 */
template<typename T>
SRemoteResource& SRemoteResource::Write(T& f) {
    f.Remove(
        __Send(GetHandler<SResourceHandler>()->FD(), f.Data(), f.Size())
    );
    return *this;
}
template<typename T>
SRemoteResource& SRemoteResource::Write(const T& f) {
    __Send(GetHandler<SResourceHandler>()->FD(), f.Data(), f.Size());
    return *this;
}
template SRemoteResource& SRemoteResource::Write(Frame&);
template SRemoteResource& SRemoteResource::Write(IOFrame&);
template SRemoteResource& SRemoteResource::Write(const Frame&);
template SRemoteResource& SRemoteResource::Write(const IOFrame&);
/**
 * ------------------------------------------------------------------------------------------------
 * MESSAGE general interfaces
 * ------------------------------------------------------------------------------------------------
 * bind
 */
Message::SRemoteResource& Message::SRemoteResource::Bind(
    const string& host, uint16_t port
) {
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
        if (::setsockopt(h->FD(), SOL_SOCKET, SO_REUSEADDR, (int*) & opt, sizeof (int)) < 0) {
            continue;
        }
        if (::bind(h->FD(), rp->ai_addr, rp->ai_addrlen) < 0) {
            continue;
        }
        struct timeval t = {.tv_sec = 0, .tv_usec = INIT_IO_TIMEOUT};
        if (::setsockopt(h->FD(), SOL_SOCKET, SO_SNDTIMEO, (void*) &t, sizeof (t)) < 0) {
            continue;
        }
        if (::setsockopt(h->FD(), SOL_SOCKET, SO_RCVTIMEO, (void*) &t, sizeof (t)) < 0) {
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
        SetHandler(h);
        return *this;
    }
    /**
     * fail
     **/
    ::freeaddrinfo(result);
    throw ResourceException(make_error_code(errc::no_such_device_or_address));
}
/**
 * wait
 */
Message::SRemoteResource& Message::SRemoteResource::Wait(
    const string& host, uint16_t port, chrono::seconds timeout
) {
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
        if (::setsockopt(h->FD(), SOL_SOCKET, SO_REUSEADDR, (int*) & opt, sizeof (int)) < 0) {
            continue;
        }
        if (::bind(h->FD(), rp->ai_addr, rp->ai_addrlen) < 0) {
            continue;
        }
        struct timeval t = {.tv_sec = 0, .tv_usec = INIT_IO_TIMEOUT};
        if (::setsockopt(h->FD(), SOL_SOCKET, SO_SNDTIMEO, (void*) &t, sizeof (t)) < 0) {
            continue;
        }
        if (::setsockopt(h->FD(), SOL_SOCKET, SO_RCVTIMEO, (void*) &t, sizeof (t)) < 0) {
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
        SStaticMonitorHandler({h}).Wait(timeout);
        /**
         * get address and connect
         */
        if (::recvfrom(h->FD(), nullptr, 0, MSG_PEEK,(struct sockaddr *)&addr, &len) < 0) {
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
        if (::connect(h->FD(), (struct sockaddr *)&addr, len) < 0) {
            throw ResourceException(make_error_code(errc(errno)));
        }
        /**
         * save handler
         */
        SetHandler(h);
        return *this;
    }
    /**
     * fail
     **/
    ::freeaddrinfo(result);
    throw ResourceException(make_error_code(errc::no_such_device_or_address));
}
/**
 * link
 */
Message::SRemoteResource& Message::SRemoteResource::Link(const string& host, uint16_t host_port) {
    /**
     * connect parameters
     */
    struct addrinfo hints;
    memset(&hints, 0, sizeof (struct addrinfo));
    hints.ai_family = AF_UNSPEC;            // Allow IPv4 or IPv6 
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
        if (::connect(h->FD(), rp->ai_addr, rp->ai_addrlen) < 0) {
            continue;
        }
        /**
         * set options
         */
        struct timeval t = {.tv_sec = 0, .tv_usec = INIT_IO_TIMEOUT};
        if (::setsockopt(h->FD(), SOL_SOCKET, SO_SNDTIMEO, (void*) &t, sizeof (t)) < 0) {
            continue;
        }
        if (::setsockopt(h->FD(), SOL_SOCKET, SO_RCVTIMEO, (void*) &t, sizeof (t)) < 0) {
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
        SetHandler(h);
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
 * wait
 */
Stream::SRemoteResource& Stream::SRemoteResource::Wait(
    const string& host, uint16_t port, chrono::seconds timeout
) {
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
        if (::setsockopt(s->FD(), SOL_SOCKET, SO_REUSEADDR, (int*) & opt, sizeof (int)) < 0) {
            continue;
        }
        if (::bind(s->FD(), rp->ai_addr, rp->ai_addrlen) < 0) {
            continue;
        }
        if (::listen(s->FD(), 1) < -1) {
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
        SStaticMonitorHandler({s}).Wait(timeout);        
        /**
         * accept handler
         */
        auto h = make_shared<SResourceHandler>(
            ::accept(s->FD(), (struct sockaddr *)&addr, &len)
        );
        /**
         * set options
         */
        struct timeval t = {.tv_sec = 0, .tv_usec = INIT_IO_TIMEOUT};
        if (::setsockopt(h->FD(), SOL_SOCKET, SO_SNDTIMEO, (void*) &t, sizeof (t)) < 0) {
            throw ResourceException(make_error_code(errc(errno)));
        }
        if (::setsockopt(h->FD(), SOL_SOCKET, SO_RCVTIMEO, (void*) &t, sizeof (t)) < 0) {
            throw ResourceException(make_error_code(errc(errno)));
        }
        /**
         * save handler
         */
        SetHandler(h);
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
 * Connect
 * ------------------------------------------------------------------------------------------------
 */
Stream::SRemoteResource& Stream::SRemoteResource::Link(const string& host, uint16_t host_port) {
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
        if (::connect(h->FD(), rp->ai_addr, rp->ai_addrlen) < 0) {
            continue;
        }
        /**
         * set options
         */
        struct timeval t = {.tv_sec = 0, .tv_usec = INIT_IO_TIMEOUT};
        if (::setsockopt(h->FD(), SOL_SOCKET, SO_SNDTIMEO, (void*) &t, sizeof (t)) < 0) {
            continue;
        }
        if (::setsockopt(h->FD(), SOL_SOCKET, SO_RCVTIMEO, (void*) &t, sizeof (t)) < 0) {
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
        SetHandler(h);
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
 * linux functions
 * ------------------------------------------------------------------------------------------------
 */
size_t __Send(int fd, Frame::const_pointer p, Frame::size_type s) {
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
 */
size_t __Recv(int fd, Frame::pointer p, Frame::size_type s) {
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
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */