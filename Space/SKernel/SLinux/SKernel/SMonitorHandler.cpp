/**
 * File:   SMonitorHandler.cpp
 * Author: Luis Monteiro
 *
 * Created on January, 2019, 12:37 PM
 ***
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
 * -------------------------------------------------------------------------------------------------
 * static monitor handler
 * -------------------------------------------------------------------------------------------------
 * constructor
 * ----------------------------------------------------------------------------
 */
SStaticMonitorHandler::SStaticMonitorHandler(std::initializer_list<Handler> handlers)
: SMonitorHandler() {
    for(auto& h :handlers) { Insert(h); }
}
/**
 * ----------------------------------------------------------------------------
 *  helpers
 * ----------------------------------------------------------------------------
 */
SStaticMonitorHandler::Location SStaticMonitorHandler::__Create(Handler h) {
    return {
        .fd = h->FD(), 
        .events = POLLIN | POLLERR | POLLHUP, 
        .revents = 0
    };
}
/**
 * ----------------------------------------------------------------------------
 *  Insert handler
 * ----------------------------------------------------------------------------
 */
size_t SStaticMonitorHandler::Insert(Handler h) {
    // get current position  ------------------------------
    auto position = __handlers.size();

    // insert on resource navive container ----------------
    __locations.emplace_back(__Create(h));

    // insert on handler container ------------------------
    __handlers.emplace_back(h);

    // return position ------------------------------------
    return position;
}
/**
 * ----------------------------------------------------------------------------
 *  Wait for active handlers
 * ----------------------------------------------------------------------------
 */
std::list<size_t> SStaticMonitorHandler::Wait(const chrono::milliseconds& timeout) {
    auto handler = STask::Instance().GetResource().GetHandler<SResourceHandler>();
    std::list<size_t> res;
    try {
        // insert this task -------------------------------
        __locations.emplace_back(__Create(handler));

        // check resources --------------------------------
        res = __Check(timeout);

        // remove this task -------------------------------
        __locations.pop_back();
    } catch(...) {
        __locations.pop_back();
        throw;
    }
    // check timeout --------------------------------------
    if (res.empty()) {
        throw MonitorExceptionTIMEOUT();
    }
    // check this task ------------------------------------
    if (res.back() == __locations.size()) {
        throw MonitorExceptionCANCEL();
    }
    // return active positions ----------------------------
    return res;
}
/**
 * ----------------------------------------------------------------------------
 * check
 * ----------------------------------------------------------------------------
 */
std::list<size_t> SStaticMonitorHandler::__Check(const chrono::milliseconds& timeout) {
    
    // wait -----------------------------------------------
    int r = 0;
    if ((r = poll(__locations.data(), __locations.size(), timeout.count())) < 0) {
        throw MonitorException(make_error_code(errc(errno)));
    }
    // check ----------------------------------------------
    std::list<size_t> res;
    for (size_t i = 0, n = r; (i < __locations.size()) && (res.size() < n); ++i) {
        if (__locations[i].revents & __locations[i].events) {
            res.emplace_back(i);
        }
        // clear event
        __locations[i].revents = 0;
    }
    return res;
}
/**
 * -------------------------------------------------------------------------------------------------
 * dynamic monitor handler
 * -------------------------------------------------------------------------------------------------
 * constructor
 * ----------------------------------------------------------------------------
 */
SDynamicMonitorHandler::SDynamicMonitorHandler(std::initializer_list<Handler> handlers)
: SMonitorHandler(), SResourceHandler(::epoll_create1(0)) {
    for(auto& h :handlers) { Insert(h); }
}
/**
 * ----------------------------------------------------------------------------
 *  helpers
 * ----------------------------------------------------------------------------
 */
void SDynamicMonitorHandler::__Insert(Handler h, size_t position) {
    // insert resource on container -----------------------
    ::epoll_event ev;
    ev.data.u64 = position;
    ev.events   = EPOLLIN | EPOLLERR | EPOLLHUP;
    if (epoll_ctl(
        FD(), EPOLL_CTL_ADD, h->FD(), &ev
    ) < 0) {
        throw ResourceExceptionABORT(strerror(errno));
    }
}
void SDynamicMonitorHandler::__Remove(Handler h) {
    // remove resource from container ---------------------
    ::epoll_event ev;
    if (epoll_ctl(
        FD(), EPOLL_CTL_DEL, h->FD(), &ev
    ) < 0) {
        throw ResourceExceptionABORT(strerror(errno));
    }
}
/**
 * ----------------------------------------------------------------------------
 *  Insert handler
 * ----------------------------------------------------------------------------
 */
size_t SDynamicMonitorHandler::Insert(Handler h) {

    // get reference --------------------------------------
    auto position = __handlers.size();

    // insert on resource container -----------------------
    __Insert(h, position);

    // insert on handler container ------------------------
    __handlers.emplace_back(h);

    // return position ------------------------------------
    return position;
}
/**
 * ----------------------------------------------------------------------------
 *  Wait for active handlers
 * ----------------------------------------------------------------------------
 */
std::list<size_t> SDynamicMonitorHandler::Wait(const chrono::milliseconds& timeout) {
    auto handler = STask::Instance().GetResource().GetHandler<SResourceHandler>();
    std::list<size_t> res;
    try {
        // insert this task -------------------------------
        __Insert(handler, __handlers.size());

        // check resources --------------------------------
        res = __Check(timeout);

        // remove this task -------------------------------
        __Remove(handler);
    } catch(...) {
        // remove this task -------------------------------
        __Remove(handler);
        throw;
    }
    // check timeout --------------------------------------
    if (res.empty()) {
        throw MonitorExceptionTIMEOUT();
    }
    // check this task ------------------------------------
    if (res.back() == __handlers.size()) {
        throw MonitorExceptionCANCEL();
    }
    // return active positions ----------------------------
    return res;
}
/**
 * ----------------------------------------------------------------------------
 * check
 * ----------------------------------------------------------------------------
 */
list<size_t> SDynamicMonitorHandler::__Check(const chrono::milliseconds& timeout) {
    
    // poll events ----------------------------------------
    vector<epoll_event> events(__handlers.size());
    auto n = ::epoll_wait(
        FD(), events.data(), events.size(), timeout.count()
    );
    if (n < 0) {
        throw MonitorException(make_error_code(errc(errno)));
    }
    // fill output ----------------------------------------
    list<size_t> res;
    for (auto i = 0; i < n; ++i) {
        res.emplace_back(static_cast<int>(events[i].data.u64));
    }
    return res;
}
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */