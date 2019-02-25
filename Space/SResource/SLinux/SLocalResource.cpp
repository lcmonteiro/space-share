/**
 * ------------------------------------------------------------------------------------------------
 * File:   SLinuxSocket.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 * ------------------------------------------------------------------------------------------------
 */
//#define __DEBUG__
/*
 * base linux
 */
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <sys/un.h>
/**
 * space linux
 */
#include "SResourceHandler.h"
#include "SMonitorHandler.h"
/**
 * space
 */
#include "SLocalResource.h"
/**
 * definitions
 */
#define INIT_IO_TIMEOUT   10000     // us
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
bool SLocalResource::Good() {
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
SLocalResource& SLocalResource::SetTxTimeout(int timeout) {
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
SLocalResource& SLocalResource::SetRxTimeout(int timeout) {
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
 * ------------------------------------------------------------------------------------------------
 * IO functions
 * ------------------------------------------------------------------------------------------------
 * Input
 * ----------------------------------------------------------------------------
 * fill
 */
template<>
SLocalResource& SLocalResource::Fill(IFrame& f) {
    while (!f.Full()) {
        f.Insert(__Recv(
            GetHandler<SResourceHandler>()->FD(), f.Data(), f.Size()
        ));
    }
    return *this;
}
template<>
SLocalResource& SLocalResource::Fill(Frame& f) {
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
SLocalResource& SLocalResource::Read(IFrame& f) {
    f.Insert(__Recv(
        GetHandler<SResourceHandler>()->FD(), f.Data(), f.Size())
    );
    return *this;
}
template<>
SLocalResource& SLocalResource::Read(Frame& f) {
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
template<>
SLocalResource& SLocalResource::Drain(OFrame& f) {
    // send loop ----------------------
    while (!f.Empty()) {
        f.Remove(__Send(
            GetHandler<SResourceHandler>()->FD(), f.Data(), f.Size()
        ));
    }
    return *this;
}
template<>
SLocalResource& SLocalResource::Drain(const Frame& f) {
    // send loop ----------------------
    for (auto it = f.begin(), end = f.end(); it != end;) {
        it = next(it, __Send(
            GetHandler<SResourceHandler>()->FD(), it.base(), distance(it, end)
        ));
    }
    return *this;
}
template<>
SLocalResource& SLocalResource::Drain(Frame& f) {
    // send loop ----------------------
    for (auto it = f.begin(), end = f.end(); it != end;) {
        it = next(it, __Send(
            GetHandler<SResourceHandler>()->FD(), it.base(), distance(it, end)
        ));
    }
    return *this;
}
/**
 * write
 */
template<>
SLocalResource& SLocalResource::Write(OFrame& f) {
    f.Remove(
        __Send(GetHandler<SResourceHandler>()->FD(), f.Data(), f.Size())
    );
    return *this;
}
template<>
SLocalResource& SLocalResource::Write(Frame& f) {
    f.Remove(
        __Send(GetHandler<SResourceHandler>()->FD(), f.Data(), f.Size())
    );
    return *this;
}
/**
 * ------------------------------------------------------------------------------------------------
 * MESSAGE general interfaces
 * ------------------------------------------------------------------------------------------------
 * Bind
 * ----------------------------------------------------------------------------
 */
Message::SLocalResource& Message::SLocalResource::Bind(const std::string& local) {
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
    if (::bind(h->FD(), (struct sockaddr*) &baddr, sizeof (baddr)) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
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
 * ----------------------------------------------------------------------------
 * Wait
 * ----------------------------------------------------------------------------
 */
Message::SLocalResource& Message::SLocalResource::Wait(
    const std::string& local, std::chrono::seconds timeout
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
    if (::bind(h->FD(), (struct sockaddr*) &baddr, sizeof (baddr)) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
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
     * wait for data 
     */
    SStaticMonitorHandler({h}).Wait(timeout);
    /**
     * get address and connect
     */
    if (::recvfrom(h->FD(), nullptr, 0, MSG_PEEK,(struct sockaddr *)&caddr, &len) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
    if (::connect(h->FD(), (struct sockaddr *)&caddr, len) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
    /**
     * save handler
     */
    SetHandler(h);
    return *this;
}
/**
 * ----------------------------------------------------------------------------
 * Link
 * ----------------------------------------------------------------------------
 */
Message::SLocalResource& Message::SLocalResource::Link(const std::string& local) {
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
    if (::connect(h->FD(), (struct sockaddr*) &caddr, sizeof(caddr)) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }    
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
 * ------------------------------------------------------------------------------------------------
 * STREAM general interfaces
 * ------------------------------------------------------------------------------------------------
 * wait
 * ----------------------------------------------------------------------------
 */
Stream::SLocalResource& Stream::SLocalResource::Wait(
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
    if (::bind(s->FD(), (struct sockaddr*) &baddr, sizeof (baddr)) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
    if (::listen(s->FD(), 1) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
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
 * ----------------------------------------------------------------------------
 * link
 * ----------------------------------------------------------------------------
 */
Stream::SLocalResource& Stream::SLocalResource::Link(const std::string& local) {
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
    if (::connect(h->FD(), (struct sockaddr*) &caddr, sizeof(caddr)) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }    
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