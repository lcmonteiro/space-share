/**
 * Container:   SMonitorHandler.cpp
 * Author: Luis Monteiro
 *
 * Created on January, 2019, 12:37 PM
 */
/**
 * space
 */
#include "SMonitorHandler.h"
#include "SResourceHandler.h"
/**
 * ----------------------------------------------------------------------------
 * constructor
 * ----------------------------------------------------------------------------
 */
SMonitorHandler::SMonitorHandler(Handlers handlers): __handlers(handlers) {
    for(auto h :__handlers) {
        __locations.emplace_back(__CreateLocation(h));
    }
}
/**
 * ----------------------------------------------------------------------------
 *  Wait for active handlers
 * ----------------------------------------------------------------------------
 */
vector<size_t> SMonitorHandler::Wait(const chrono::milliseconds& timeout) {
    vector<size_t> res;
    try {
        // insert this task -------------------------------
        //__localions.emplace_back(
        //    CreateLocation(SLinuxTask::Instance().GetResource())
        //);

        // check resources --------------------------------
        res = __Check(timeout);

        // remove this task -------------------------------
        //__locations.pop_back();
    } catch(...) {
        //__locations.pop_back();
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
 * 
 * ----------------------------------------------------------------------------
 */
SMonitorHandler::Location SMonitorHandler::__CreateLocation(Handler handle) {
    auto h = static_pointer_cast<SResourceHandler>(handle);
    return Location {
        .fd = h->FD(), .events = POLLIN | POLLERR | POLLHUP, .revents = 0
    };
}
/**
 * ----------------------------------------------------------------------------
 * check
 * ----------------------------------------------------------------------------
 */
vector<size_t> SMonitorHandler::__Check(const chrono::milliseconds& timeout) {
    vector<size_t> res;

    // wait -----------------------------------------------
    int r = 0;
    if ((r = poll(__locations.data(), __locations.size(), timeout.count())) < 0) {
        throw MonitorException(make_error_code(errc(errno)));
    }

    // check ----------------------------------------------
    for (size_t i = 0, n = r; (i < __locations.size()) && (res.size() < n); ++i) {
        if (__locations[i].revents & __locations[i].events) {
            res.push_back(i);
        }
        // clear event
        __locations[i].revents = 0;
    }
    return res;
}
