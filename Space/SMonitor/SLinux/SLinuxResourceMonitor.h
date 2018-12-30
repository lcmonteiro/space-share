/**
 * Container:   SLinuxResourceMonitor.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SLINUXRESOURCEMONITOR_H
#define SLINUXRESOURCEMONITOR_H
/**
 * linux std
 */
#include <poll.h>
/**
 * c++ std
 */
#include <chrono>
/**
 * monitor
 */
#include "SMonitor.h"
/**
 * linux
 */
#include "SLinuxResource.h"
#include "SLinuxMonitor.h"
/**
 */
class SLinuxResourceMonitor: public SLinuxMonitor {
public:
    /**
     * constructor
     */
    template<typename T, typename... Args>
    SLinuxResourceMonitor(chrono::milliseconds timeout, T arg, Args... args) : __timeout(timeout) {
           UpdateLocations(arg, args...);
    }
    /**
     * constructor
     */
    template<typename T, typename... Args>
    SLinuxResourceMonitor(T arg, Args... args)
    : SLinuxResourceMonitor(chrono::milliseconds(0), arg, forward<Args>(args)...) {
    }
    /**
     * default constructor
     */
    SLinuxResourceMonitor() = default;
    /**
     * destructor
     */
    virtual ~SLinuxResourceMonitor() = default;
    /**
     * move operator
     */ 
    SLinuxResourceMonitor& operator=(SLinuxResourceMonitor&&) = default;
    /**
     * check monitor
     */
    inline bool Good() {
        return !(__loc.empty() || __timeout < chrono::milliseconds::zero());
    }
    /**
     * ----------------------------------------------------------------------------------------
     * wait interface
     * ----------------------------------------------------------------------------------------
     * wait 
     */
    inline vector<size_t> Wait(chrono::milliseconds timeout) {
        return Wait(__loc, timeout);
    }
    inline vector<size_t> Wait() {
        return Wait(__loc, __timeout);
    }
    /**
     * check
     */
    inline vector<size_t> Check(chrono::milliseconds timeout) {
        return Check(__loc, timeout);
    }
    inline vector<size_t> Check() {
        return Check(__loc, __timeout);
    }
    /**
     * wait just one resource
     */
    static inline SLinuxResource& Wait(SLinuxResource& res, const chrono::milliseconds& timeout) {
        Locations loc {SLinuxMonitor::CreateLocation(res._Handler())};
        Wait(loc, timeout);
        return res;
    }
protected:
    /**
     * timeout
     */
    chrono::milliseconds __timeout;
    /**
     * create location
     */
    static inline Location CreateLocation(Resource& resource) {
        return SLinuxMonitor::CreateLocation(static_cast<SLinuxResource&> (resource)._Handler());
    }
    /**
     * check many resources
     */
    static inline vector<size_t> Check(Locations& loc, const chrono::milliseconds& timeout) {
        try {
            return Wait(loc, timeout);
        } catch(MonitorExceptionTIMEOUT& ) {
            return {};
        }
    }
    /**
     * wait for many resources
     */
    static inline vector<size_t> Wait(Locations& loc, const chrono::milliseconds& timeout) {
        vector<size_t> res;
        try {
            // insert this task
            loc.emplace_back(CreateLocation(SLinuxTask::Instance().GetResource()));
            // check resources
            res = SLinuxMonitor::Check(loc, timeout);
            // remove this task
            loc.pop_back();
        } catch(...) {
            // remove this task
            loc.pop_back();
            // re throw
            throw;
        }
        // check timeout
        if (res.empty()) {
            throw MonitorExceptionTIMEOUT();
        }
        // check this task
        if (res.back() == loc.size()) {
            throw MonitorExceptionCANCEL();
        }
        // return resource indexes
        return res;
    }
private:
    /**
     * ----------------------------------------------------------------------------------------
     * linux part
     * ----------------------------------------------------------------------------------------
     */
    template<typename T, typename... Args>
    void UpdateLocations(T first, Args... args) {
        UpdateLocations(first); UpdateLocations(args...);
    }
    template<typename T>
    void UpdateLocations(T loc) {
           __loc.emplace_back(CreateLocation(loc->GetResource()));
    }
    /**
     * handles
     */
    Locations __loc;
};
/**
 */
#endif /* SLINUXRESOURCEMONITOR_H */
