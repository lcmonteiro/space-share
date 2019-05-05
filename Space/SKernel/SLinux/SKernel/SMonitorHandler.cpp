/**
 * ------------------------------------------------------------------------------------------------
 * File:   SMonitorHandler.cpp
 * Author: Luis Monteiro
 *
 * Created on January, 2019, 12:37 PM
 * ------------------------------------------------------------------------------------------------
 **
 * linux
 */
#include <sys/epoll.h>
/**
 * std
 */
#include <cstring>
/**
 * space 
 */
#include "STask.h"
#include "SMonitorHandler.h"
#include "SResourceHandler.h"
/**
 * namespace
 */
using namespace std;
/**
 * -------------------------------------------------------------------------------------------------
 * static monitor handler
 * -------------------------------------------------------------------------------------------------
 * constructor
 * ----------------------------------------------------------------------------
 */
SStaticMonitorHandler::SStaticMonitorHandler(initializer_list<Handler> handlers)
: SMonitorHandler() {
    for(auto& h :handlers) { insert(h); }
}
/**
 * ----------------------------------------------------------------------------
 *  helpers
 * ----------------------------------------------------------------------------
 */
SStaticMonitorHandler::Location SStaticMonitorHandler::_create(Handler h) {
    return {
        .fd = h->fd(), 
        .events = POLLIN | POLLERR | POLLHUP, 
        .revents = 0
    };
}
/**
 * ----------------------------------------------------------------------------
 *  Insert handler
 * ----------------------------------------------------------------------------
 */
size_t SStaticMonitorHandler::insert(Handler h) {
    /**
     * get current position
     */
    auto position = __handlers.size();
    /**
     * insert on resource native container
     */
    __locations.emplace_back(_create(h));
    /**
     * insert on handler container
     */
    __handlers.emplace_back(h);
    /**
     * return position
     */
    return position;
}
/**
 * ----------------------------------------------------------------------------
 *  Wait for active handlers
 * ----------------------------------------------------------------------------
 */
list<size_t> SStaticMonitorHandler::wait(const chrono::milliseconds& timeout) {
    auto handler = STask::Instance().resource().handler<SResourceHandler>();
    list<size_t> res;
    try {
        /**
         * insert this task
         */
        __locations.emplace_back(_create(handler));
        /**
         * check resources
         */
        res = _check(timeout);
        /**
         * remove this task
         */
        __locations.pop_back();
    } catch(...) {
        __locations.pop_back();
        throw;
    }
    /**
     * check timeout
     */
    if (res.empty()) {
        throw MonitorExceptionTIMEOUT();
    }
    /**
     * check this task
     */
    if (res.back() == __locations.size()) {
        throw MonitorExceptionCANCEL();
    }
    /**
     * return active positions
     */
    return res;
}
/**
 * ----------------------------------------------------------------------------
 * Check
 * ----------------------------------------------------------------------------
 */
list<size_t> SStaticMonitorHandler::_check(const chrono::milliseconds& timeout) {
    /**
     * wait
     */
    int r = 0;
    if ((r = poll(__locations.data(), __locations.size(), timeout.count())) < 0) {
        throw MonitorException(make_error_code(errc(errno)));
    }
    /**
     * check
     */
    list<size_t> res;
    for (size_t i = 0, n = r; (i < __locations.size()) && (res.size() < n); ++i) {
        if (__locations[i].revents & __locations[i].events) {
            res.emplace_back(i);
        }
        /**
         * clear event
         */
        __locations[i].revents = 0;
    }
    return res;
}
/**
 * -------------------------------------------------------------------------------------------------
 * Dynamic Monitor Handler
 * -------------------------------------------------------------------------------------------------
 * constructor
 * ----------------------------------------------------------------------------
 */
SDynamicMonitorHandler::SDynamicMonitorHandler(initializer_list<Handler> handlers)
: SMonitorHandler(), SResourceHandler(::epoll_create1(0)) {
    for(auto& h :handlers) { insert(h); }
}
/**
 * ----------------------------------------------------------------------------
 *  helpers
 * ----------------------------------------------------------------------------
 */
void SDynamicMonitorHandler::_insert(Handler h, size_t position) {
    /**
     * insert resource on container
     */
    ::epoll_event ev;
    ev.data.u64 = position;
    ev.events   = EPOLLIN | EPOLLERR | EPOLLHUP;
    if (epoll_ctl(
        fd(), EPOLL_CTL_ADD, h->fd(), &ev
    ) < 0) {
        throw ResourceExceptionABORT(strerror(errno));
    }
}
void SDynamicMonitorHandler::_remove(Handler h) {
    /**
     * remove resource from container
     */
    ::epoll_event ev;
    if (epoll_ctl(
        fd(), EPOLL_CTL_DEL, h->fd(), &ev
    ) < 0) {
        throw ResourceExceptionABORT(strerror(errno));
    }
}
/**
 * ----------------------------------------------------------------------------
 *  Insert handler
 * ----------------------------------------------------------------------------
 */
size_t SDynamicMonitorHandler::insert(Handler h) {
    /**
     * get reference
     */
    auto position = __handlers.size();
    /**
     * insert on resource container
     */
    _insert(h, position);
    /**
     * insert on handler container
     */
    __handlers.emplace_back(h);
    /**
     * return position
     */
    return position;
}
/**
 * ----------------------------------------------------------------------------
 *  Wait for active handlers
 * ----------------------------------------------------------------------------
 */
list<size_t> SDynamicMonitorHandler::wait(const chrono::milliseconds& timeout) {
    auto handler = STask::Instance().resource().handler<SResourceHandler>();
    list<size_t> res;
    try {
        /**
         * insert this task
         */
        _insert(handler, __handlers.size());
        /**
         * check resources
         */
        res = _check(timeout);
        /**
         * remove this task
         */
        _remove(handler);
    } catch(...) {
        /**
         * remove this task
         */
        _remove(handler);
        throw;
    }
    /**
     * check timeout
     */
    if (res.empty()) {
        throw MonitorExceptionTIMEOUT();
    }
    /**
     * check this task
     */
    if (res.back() == __handlers.size()) {
        throw MonitorExceptionCANCEL();
    }
    /**
     * return active positions
     */
    return res;
}
/**
 * ----------------------------------------------------------------------------
 * Check
 * ----------------------------------------------------------------------------
 */
list<size_t> SDynamicMonitorHandler::_check(const chrono::milliseconds& timeout) {
    /**
     * poll events
     */
    vector<epoll_event> events(__handlers.size());
    auto n = ::epoll_wait(
        fd(), events.data(), events.size(), timeout.count()
    );
    if (n < 0) {
        throw MonitorException(make_error_code(errc(errno)));
    }
    /** 
     * fill output
     */
    list<size_t> res;
    for (auto i = 0; i < n; ++i) {
        res.emplace_back(static_cast<int>(events[i].data.u64));
    }
    return res;
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */