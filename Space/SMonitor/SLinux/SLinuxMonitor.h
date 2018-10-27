/**
 * Container:   SLinuxMonitor.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SLINUXMONITOR_H
#define SLINUXMONITOR_H
/**
 * linux std
 */
#include <poll.h>
/**
 * c++ std
 */
#include <chrono>
/**
 * linux
 */
#include "SLinuxTask.h"
/**
 * monitor
 */
#include "SMonitor.h"
/**
 */
class SLinuxMonitor: public SMonitor {
public:
    /**
     * constructor
     */
    SLinuxMonitor() = default;
    /**
     * destructor
     */
    virtual ~SLinuxMonitor() = default;
    /**
     * wait
     */
    static inline void Wait(const chrono::milliseconds& timeout) {
        Locations loc {};
        Check(loc, timeout);
    }
protected:
    /**
     * definitions
     */
    typedef pollfd Location;

    typedef vector<Location> Locations;
    /**
     * create location 
     */
    static inline Location CreateLocation(int handle) {
        return Location {
            .fd = handle, .events = POLLIN | POLLERR | POLLHUP, .revents = 0
        };
    }
    /**
     * check
     */
    static inline vector<size_t> Check(Locations& loc, const chrono::milliseconds& timeout) {
        vector<size_t> res;
        /**
         * wait
         */
        int r = 0;
        if ((r = poll(loc.data(), loc.size(), timeout.count())) < 0) {
            throw MonitorException(make_error_code(errc(errno)));
        }
        /**
         * check
         */
        for (size_t i = 0, n = r; (i < loc.size()) && (res.size() < n); ++i) {
            if (loc[i].revents & loc[i].events) {
                res.push_back(i);
            }
        }
        return res;
    }
};
/**
 */
#endif /* SLINUXMONITOR_H */

