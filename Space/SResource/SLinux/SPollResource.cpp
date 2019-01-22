/*
 * Container:   SPollResource.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 **
 * linux
 */
#include <unistd.h>
#include <sys/epoll.h>
/**
 * space linux
 */
#include "SResourceHandler.h"
/**
 * space
 */
#include "SPollResource.h"
/**
 */
SPollResource::SPollResource() : SResource() {
        /**
         * create a linux handler
         */
        auto h = make_shared<SResourceHandler>(
            ::epoll_create1(0)
        );
        /**
         * set handler
         */
        SetHandler(h);
}
/**
 * ------------------------------------------------------------------------------------------------
 * insert
 * ------------------------------------------------------------------------------------------------
 */
void SPollResource::Insert(SResource* r) {
    epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.data.ptr = r;
    ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;
    if (epoll_ctl(_Handler(), EPOLL_CTL_ADD, r->_Handler(), &ev) < 0) {
        throw ResourceExceptionABORT(strerror(errno));
    }
}
/**
 * ------------------------------------------------------------------------------------------------
 * delete
 * ------------------------------------------------------------------------------------------------
 */
void SPollResource::Delete(SResource* r) {
    if (epoll_ctl(_Handler(), EPOLL_CTL_DEL, r->_Handler(), NULL) < 0) {
        throw ResourceExceptionABORT(strerror(errno));
    }
}
/**
 * ------------------------------------------------------------------------------------------------
 * read 
 * ------------------------------------------------------------------------------------------------
 */
list<SResource*> SPollResource::__Wa(const chrono::milliseconds& timeout, size_t max) {
    list<SLinuxResource*> out;
    /**
     * poll events
     */
    vector<epoll_event> events(max);
    auto n = epoll_wait(_Handler(), events.data(), events.size(), timeout.count());
    if (n < 0) {
        throw ResourceExceptionABORT(strerror(errno));
    }
    /**
     * fill output
     */
    for (auto i = 0; i < n; ++i) {
        out.emplace_back(static_cast<SResource*>(events[i].data.ptr));
    }
    /**
     */
    return out;
}