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
 * space linux
 */
#include "SResourceHandler.h"
#include "SMonitorHandler.h"
#include "SNativeResource.h"
/**
 * space
 */
#include "SLocalResource.h"
/**
 * definitions
 */
#define INIT_IO_TIMEOUT   10000     // us
/**
 * namespaces 
 */
using namespace std;
/**
 * ------------------------------------------------------------------------------------------------
 * BASE general interfaces
 * ------------------------------------------------------------------------------------------------
 * Check
 * ----------------------------------------------------------------------------
 */
bool SLocalResource::good() {
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
SLocalResource& SLocalResource::timeout_tx(int timeout) {
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
SLocalResource& SLocalResource::timeout_rx(int timeout) {
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
 * ------------------------------------------------------------------------------------------------
 * Inputs
 * ------------------------------------------------------------------------------------------------
 * Fill
 * ----------------------------------------------------------------------------
 */
template<>
SLocalResource& SLocalResource::fill(IOFrame& f) {
    while (!f.full()) {
        f.insert(SNativeResource::Receive(
            handler<SResourceHandler>()->fd(), f.idata(), f.isize()));
    }
    return *this;
}
template<>
SLocalResource& SLocalResource::fill(Frame& f) {
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
SLocalResource& SLocalResource::read(IOFrame& f) {
    f.insert(SNativeResource::Receive(
        handler<SResourceHandler>()->fd(), f.idata(), f.isize()));
    return *this;
}
template<>
SLocalResource& SLocalResource::read(Frame& f) {
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
SLocalResource& SLocalResource::drain(T& f) {
    while (!f.empty()) {
        f.remove(SNativeResource::Send(
            handler<SResourceHandler>()->fd(), f.data(), f.size()));
    }
    return *this;
}
template<typename T>
SLocalResource& SLocalResource::drain(const T& f) {
    for (auto it = f.begin(), end = f.end(); it != end;) {
        it = next(it, SNativeResource::Send(
            handler<SResourceHandler>()->fd(), it.base(), distance(it, end)));
    }
    return *this;
}
template SLocalResource& SLocalResource::drain(Frame&);
template SLocalResource& SLocalResource::drain(IOFrame&);
template SLocalResource& SLocalResource::drain(const Frame&);
template SLocalResource& SLocalResource::drain(const IOFrame&);
/**
 * ----------------------------------------------------------------------------
 * Write
 * ----------------------------------------------------------------------------
 */
template<typename T>
SLocalResource& SLocalResource::write(T& f) {
    f.remove(SNativeResource::Send(
        handler<SResourceHandler>()->fd(), f.data(), f.size()));
    return *this;
}
template<typename T>
SLocalResource& SLocalResource::write(const T& f) {
    SNativeResource::Send(
        handler<SResourceHandler>()->fd(), f.data(), f.size());
    return *this;
}
template SLocalResource& SLocalResource::write(Frame&);
template SLocalResource& SLocalResource::write(IOFrame&);
template SLocalResource& SLocalResource::write(const Frame&);
template SLocalResource& SLocalResource::write(const IOFrame&);
/**
 * ------------------------------------------------------------------------------------------------
 * MESSAGE general interfaces
 * ------------------------------------------------------------------------------------------------
 * Bind
 * ----------------------------------------------------------------------------
 */
Message::SLocalResource& Message::SLocalResource::bind(const string& local) {
    /**
     * bind parameters
     */
    struct sockaddr_un baddr;
    memset(&baddr, 0, sizeof (baddr));
    baddr.sun_family  = PF_LOCAL;
    baddr.sun_path[0] = '\0';
    /**
     * set location
     */
    strncpy(&baddr.sun_path[1], local.data(), sizeof(baddr.sun_path) - 2);
    /**
     * create a linux handler
     */
    auto h = make_shared<SResourceHandler>(
        ::socket(PF_LOCAL, SOCK_DGRAM, 0)
    );
    /**
     * bind
     */        
    if (::bind(h->fd(), (struct sockaddr*) &baddr, sizeof (baddr)) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
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
 * ----------------------------------------------------------------------------
 * Wait
 * ----------------------------------------------------------------------------
 */
Message::SLocalResource& Message::SLocalResource::wait(
    const string& local, chrono::seconds timeout
) {
    /**
     * bind parameters
     */
    struct sockaddr_un baddr;
    memset(&baddr, 0, sizeof (baddr));
    baddr.sun_family  = PF_LOCAL;
    baddr.sun_path[0] = '\0';
    /**
     * connect parameters
     */
    struct sockaddr_un caddr;
    socklen_t len = sizeof(caddr);    
    /**
     * set location
     */
    strncpy(&baddr.sun_path[1], local.data(), sizeof(baddr.sun_path) - 2);
    /**
     * create a linux handler
     */
    auto h = make_shared<SResourceHandler>(
        ::socket(PF_LOCAL, SOCK_DGRAM, 0)
    );
    /**
     * bind
     */        
    if (::bind(h->fd(), (struct sockaddr*) &baddr, sizeof (baddr)) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
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
     * wait for data 
     */
    SStaticMonitorHandler({h}).wait(timeout);
    /**
     * get address and connect
     */
    if (::recvfrom(h->fd(), nullptr, 0, MSG_PEEK,(struct sockaddr *)&caddr, &len) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
    if (::connect(h->fd(), (struct sockaddr *)&caddr, len) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
    /**
     * save handler
     */
    handler(h);
    return *this;
}
/**
 * ----------------------------------------------------------------------------
 * Link
 * ----------------------------------------------------------------------------
 */
Message::SLocalResource& Message::SLocalResource::link(const string& local) {
    /**
     * connect parameters
     */
    struct sockaddr_un caddr;
    memset(&caddr, 0, sizeof(caddr));
    caddr.sun_family  = PF_LOCAL;
    caddr.sun_path[0] = '\0';
    /**
     * set location
     */
    strncpy(&caddr.sun_path[1], local.data(), sizeof(caddr.sun_path) - 2);
    /**
     * create a linux handler
     */
    auto h = make_shared<SResourceHandler>(
        ::socket(PF_LOCAL, SOCK_DGRAM, 0)
    );
    /**
     * connect
     */        
    if (::connect(h->fd(), (struct sockaddr*) &caddr, sizeof(caddr)) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }    
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
 * ------------------------------------------------------------------------------------------------
 * STREAM general interfaces
 * ------------------------------------------------------------------------------------------------
 * Wait
 * ----------------------------------------------------------------------------
 */
Stream::SLocalResource& Stream::SLocalResource::wait(
    const string& local, chrono::seconds timeout
) {
    /**
     * accept parameters
     */
    struct sockaddr_storage addr;
    socklen_t len = sizeof(addr);  
    /**
     * bind parameters
     */
    struct sockaddr_un baddr;
    ::memset(&baddr, 0, sizeof(baddr));
    baddr.sun_family  = PF_LOCAL;
    baddr.sun_path[0] = '\0';
    /**
     * set location
     */
    ::strncpy(&baddr.sun_path[1], local.data(), sizeof(baddr.sun_path) - 2);
    /**
     * create a linux handler
     */
    auto s = make_shared<SResourceHandler>(
        ::socket(PF_LOCAL, SOCK_SEQPACKET, 0)
    );
    /**
     * bind & listen
     */        
    if (::bind(s->fd(), (struct sockaddr*) &baddr, sizeof (baddr)) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
    if (::listen(s->fd(), 1) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
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
 * ----------------------------------------------------------------------------
 * Link
 * ----------------------------------------------------------------------------
 */
Stream::SLocalResource& Stream::SLocalResource::link(const string& local) {
    /**
     * connect parameters
     */
    struct sockaddr_un caddr;
    memset(&caddr, 0, sizeof(caddr));
    caddr.sun_family  = PF_LOCAL;
    caddr.sun_path[0] = '\0';
    /**
     * set location
     */
    strncpy(&caddr.sun_path[1], local.data(), sizeof(caddr.sun_path) - 2);
    /**
     * create a linux handler
     */
    auto h = make_shared<SResourceHandler>(
        ::socket(PF_LOCAL, SOCK_SEQPACKET, 0)
    );
    /**
     * bind
     */        
    if (::connect(h->fd(), (struct sockaddr*) &caddr, sizeof(caddr)) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }    
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
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */