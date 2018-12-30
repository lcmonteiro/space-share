/*
 * Container:   SLinuxPoll.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 **
 * linux
 */
#include <unistd.h>
#include <sys/epoll.h>
/**
 */
#include "SLinuxPoll.h"
/**
 */
SLinuxPoll::SLinuxPoll() : SLinuxResource(epoll_create1(0)) {
}
/**
 * insert
 */
void SLinuxPoll::Insert(SLinuxResource* r) {
        epoll_event ev;
        memset(&ev, 0, sizeof(ev));
        ev.data.ptr = r;
        ev.events = EPOLLIN | EPOLLERR | EPOLLHUP;
        if (epoll_ctl(_handler(), EPOLL_CTL_ADD, r->_handler(), &ev) < 0) {
                throw ResourceExceptionABORT(strerror(errno));
        }
}
/**
 * delete
 */
void SLinuxPoll::Delete(SLinuxResource* r) {
        if (epoll_ctl(_handler(), EPOLL_CTL_DEL, r->_handler(), NULL) < 0) {
                throw ResourceExceptionABORT(strerror(errno));
        }
}
/**
 * read 
 */
list<SLinuxResource*> SLinuxPoll::Poll(const chrono::milliseconds& timeout, size_t max) {
        list<SLinuxResource*> out;
        /**
         * poll events
         */
        vector<epoll_event> events(max);
        auto n = epoll_wait(_handler(), events.data(), events.size(), timeout.count());
        if (n < 0) {
                throw ResourceExceptionABORT(strerror(errno));
        }
        /**
         * fill output
         */
        for (auto i = 0; i < n; ++i) {
                out.emplace_back(static_cast<SLinuxResource*>(events[i].data.ptr));
        }
        /**
         */
        return out;
}