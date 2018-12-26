/*
 * Container:   SLinuxSocket.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 */
//#define __DEBUG__
/*
 * linux
 */
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <sys/un.h>
/**
 * linux
 */
#include "SLinuxResourceMonitor.h"
/**
 */
#include "SLinuxSocket.h"
/**
 * definitions
 */
#define IO_TIMEOUT   5
/**
 * 
 */
static map<SLinuxSocket::Type, int> MAP_TYPE {
    { SLinuxSocket::STREAM, SOCK_STREAM },
    { SLinuxSocket::DGRAM,  SOCK_DGRAM  }
};
/**
 */
SLinuxSocket::~SLinuxSocket() {
    if (__fd > 0) {
        shutdown(__fd, SHUT_RDWR);
    }
}
/**
 */
bool SLinuxSocket::Good() {
    int error = 0;
    socklen_t len = sizeof (error);
    /**
     * validation
     */
    if (getsockopt(__fd, SOL_SOCKET, SO_ERROR, &error, &len) < 0) {
        return false;
    }
    return error == 0;
}
/**
 */
void SLinuxSocket::SetTxTimeout(int timeout) {
    struct timeval t = {
        .tv_sec = timeout,
        .tv_usec = 0
    };
    if (setsockopt(__fd, SOL_SOCKET, SO_SNDTIMEO, (void*) & t, sizeof (t)) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
}
void SLinuxSocket::SetRxTimeout(int timeout) {
    struct timeval t = {
        .tv_sec = timeout,
        .tv_usec = 0
    };
    if (setsockopt(__fd, SOL_SOCKET, SO_RCVTIMEO, (void*) & t, sizeof (t)) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
}
/**
 *
 */
void SLinuxSocket::SetNoDelay(bool flag) {
    int f = flag ? 1 : 0;
    if (setsockopt(__fd, IPPROTO_TCP, TCP_NODELAY, (void*) & f, sizeof (f)) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
}
/**
 */
#ifdef __DEBUG__
#include <iostream>
#endif
void SLinuxSocket::Wait(const string& host, uint16_t port, Type type) {
    /**
     * bind parameters
     */
    struct addrinfo hints;
    memset(&hints, 0, sizeof (struct addrinfo));
    hints.ai_family = AF_UNSPEC;            // Allow IPv4 or IPv6
    hints.ai_socktype = MAP_TYPE[type];     // Datagram socket
    hints.ai_flags = AI_PASSIVE;            // For wildcard IP address
    hints.ai_protocol = 0;                  // Any protocol
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;
    /**
     * get info
     */
    struct addrinfo *result;
    if (getaddrinfo(host.c_str(), to_string(port).c_str(), &hints, &result) != 0) {
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
         * create update resource
         */
        SLinuxResource s(socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol));
        /**
         * set options
         */
        int opt = 1;
        if (setsockopt(s.handler(), SOL_SOCKET, SO_REUSEADDR, (int*) & opt, sizeof (int)) < 0) {
            continue;
        }
        if (bind(s.handler(), rp->ai_addr, rp->ai_addrlen) < 0) {
            continue;
        }
#ifdef __DEBUG__
        /**
         */
        char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
        if (getnameinfo(
            rp->ai_addr, rp->ai_addrlen,
            hbuf, sizeof (hbuf),
            sbuf, sizeof (sbuf),
            NI_NUMERICHOST | NI_NUMERICSERV) == 0
            ) {
            cout << "binded: " << "host=" << hbuf << ", serv=" << sbuf << endl;
        }
#endif
        /**
         * listen
         */
        if (listen(s.handler(), 1) < -1) {
            continue;
        }
        /**
         * wait connection
         */
        SLinuxResourceMonitor::Wait(s, chrono::hours{24});
        /**
         * accept connection
         */
        *this = SLinuxSocket(accept(s.handler(), (struct sockaddr *)&addr, &len));
        /**
         * settings
         */
        SetRxTimeout(IO_TIMEOUT);
        SetTxTimeout(IO_TIMEOUT);
        /**
         * free results
         **/
        freeaddrinfo(result);
        return;
    }
    /**
     * fail
     **/
    freeaddrinfo(result);
    throw ResourceException(make_error_code(errc::no_such_device_or_address));
}
/**
 */
void SLinuxSocket::Connect(const string& host, uint16_t host_port, Type type, const string& local, uint16_t local_port) {
    /**
     * bind parameters
     */
    struct sockaddr_in baddr;
    memset(&baddr, 0, sizeof (baddr));
    baddr.sin_family = AF_UNSPEC;
    baddr.sin_port = htons(local_port);
    inet_pton(AF_INET, local.data(), &baddr.sin_addr);
    /**
     * connect parameters
     */
    struct addrinfo hints;
    memset(&hints, 0, sizeof (struct addrinfo));
    hints.ai_family = AF_UNSPEC;            // Allow IPv4 or IPv6 
    hints.ai_socktype = MAP_TYPE[type];         // socket type
    hints.ai_flags = 0;                 //
    hints.ai_protocol = 0;              // Any protocol
    /**
     * get info
     */
    struct addrinfo *result;
    if (getaddrinfo(host.c_str(), to_string(host_port).c_str(), &hints, &result) != 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
    /**
     * connect
     */
    int i = 0;
    for (auto rp = result; rp != NULL; rp = rp->ai_next, ++i) {
        SLinuxSocket s(socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol));
        /**
         * bind
         */
        if (!local.empty() && local_port) {
            if (bind(s.handler(), (struct sockaddr*) &baddr, sizeof (baddr)) < 0) {
                continue;
            }
        }
        /**
         * settings
         */
        s.SetRxTimeout(IO_TIMEOUT);
        s.SetTxTimeout(IO_TIMEOUT);
        /**
         * try to connect
         */
        if (connect(s.handler(), rp->ai_addr, rp->ai_addrlen) < 0) {
            continue;
        }
#ifdef __DEBUG__
        /**
         */
        char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
        if (getnameinfo(
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
        freeaddrinfo(result);
        /**
         * update
         **/
        *this = move(s);
        /**/
        return;
    }
    /**
     * fail
     **/
    freeaddrinfo(result);
    throw ResourceException(make_error_code(errc::no_such_device_or_address));
}
/**
 */
void SLinuxSocket::Connect(const string& host, Type type) {
    /**
     * connect parameters
     */
    struct sockaddr_un caddr;
    memset(&caddr, 0, sizeof (caddr));
    caddr.sun_family = PF_LOCAL;
    strncpy(caddr.sun_path, host.data(), sizeof(caddr.sun_path)-1);
    /**
     * create socket
     */
    SLinuxSocket s(socket(PF_LOCAL, MAP_TYPE[type], 0));    
    /**
     * settings
     */
    s.SetRxTimeout(IO_TIMEOUT);
    s.SetTxTimeout(IO_TIMEOUT);
    /**
     * connect
     */
    if (connect(s.handler(), (struct sockaddr*) &caddr, sizeof (caddr)) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
    /**
     * update
     **/
    *this = move(s);
}

void SLinuxSocket::Bind(const string& local, Type type) {
    /**
     * bind parameters
     */
    struct sockaddr_un baddr;
    memset(&baddr, 0, sizeof (baddr));
    baddr.sun_family = PF_LOCAL;
    strncpy(baddr.sun_path, local.data(), sizeof(baddr.sun_path) -1);
    /**
     * create socket
     */
    SLinuxSocket s(socket(PF_LOCAL, MAP_TYPE[type], 0));
    /**
     * options
     */
    unlink(local.data());
    /**
     * bind
     */        
    if (bind(s.handler(), (struct sockaddr*) &baddr, sizeof (baddr)) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }    
    /**
     * settings
     */
    s.SetRxTimeout(IO_TIMEOUT);
    s.SetTxTimeout(IO_TIMEOUT);
    /**
     * update
     **/
    *this = move(s);
}
/*---------------------------------------------------------------------------------------------------------------------*
 * IO functions
 *---------------------------------------------------------------------------------------------------------------------*/
Frame SLinuxSocket::Read(size_t size) {
    IFrame f(size);
    /**
     * receive
     */
    while (!f.Full()) {
        f.Insert(Receive(f.Data(), f.Size()));
    }
    return f;
}
SLinuxSocket& SLinuxSocket::Drain(OFrame&& f) {
    /**
     * send
     */
    while (!f.Empty()) {
        f.Remove(Send(f.Data(), f.Size()));
    }
    return *this;
}
SLinuxSocket& SLinuxSocket::Drain(const Frame& f) {
    /**
     * send
     */
    for (auto it = f.begin(), end = f.end(); it != end;) {
        it = next(it, Send(it.base(), distance(it, end)));
    }
    return *this;
}
/*---------------------------------------------------------------------------------------------------------------------*
 * Text IO functions
 *---------------------------------------------------------------------------------------------------------------------*/
SLinuxSocket& SLinuxSocket::operator>>(string& str) {
    /**
     * receive
     */
    for (auto it = str.begin(), end = str.end(); it != end; ++it) {
        register string::value_type c;
        /**
         * read
         */
        auto n = recv(__fd, &c, 1, MSG_WAITALL);
        if (n <= 0) {
            if (n < 0) {
                if (errno == EAGAIN) {
                    str.erase(it, end);
                    if (it == str.begin()) {
                        throw ResourceExceptionTIMEOUT();
                    }
                    break;
                }
                *this = SLinuxSocket();
                throw IResourceExceptionABORT(strerror(errno));
            }
            *this = SLinuxSocket();
            throw IResourceExceptionABORT();
        }
        /**
         * verify
         */
        if (iscntrl(c)) {
            /**
             * read end line
             */
            if (c == '\r') {
                recv(__fd, &c, 1, MSG_WAITALL);
                str.erase(it, end);
                break;
            }
            if(c == '\n') {
                str.erase(it, end);
                break;
            }
            continue;
        }
        /**
         * set
         */
        *it = c;
    }
    /**
     */
    return *this;
}
/**
 */
SLinuxSocket& SLinuxSocket::operator<<(const string& str) {
    /**
     * write
     */
    auto n = send(__fd, str.data(), str.size(), MSG_NOSIGNAL | MSG_DONTWAIT);
    if (n != int(str.size())) {
        *this = SLinuxSocket();
        throw OResourceExceptionABORT(make_error_code(errc(errno)));
    }
    /**
     */
    return *this;
}
/**
 */
size_t SLinuxSocket::Send(Frame::const_pointer p, Frame::size_type s) {
    auto n = send(__fd, p, s, MSG_NOSIGNAL);
    if (n <= 0) {
        if (n < 0) {
            *this = SLinuxSocket();
            throw OResourceExceptionABORT(strerror(errno));
        }
        *this = SLinuxSocket();
        throw OResourceExceptionABORT();
    }
    return n;
}
/**
 */
size_t SLinuxSocket::Receive(Frame::pointer p, Frame::size_type s) {
    auto n = recv(__fd, p, s, MSG_DONTWAIT);
    if (n <= 0) {
        if (n < 0) {
            if (errno == EAGAIN) {
                throw ResourceExceptionTIMEOUT();
            }
            *this = SLinuxSocket();
            throw IResourceExceptionABORT(strerror(errno));
        }
        *this = SLinuxSocket();
        throw IResourceExceptionABORT();
    }
    return n;
}