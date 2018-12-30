/*
 * Container:   SLinuxMonitor.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SLINUXROADMONITOR_H
#define SLINUXROADMONITOR_H
/**
 * Linux std
 */
#include <poll.h>
/**
 * C++ std
 */
#include <chrono>
#include <vector>
#include <list>
/**
 * Space Kernel
 */
#include "SMonitor.h"
#include "SBimap.h"
/**
 * Space Resource Linux
 */
#include "SLinuxPoll.h"
/**
 */
template<class R>
class SLinuxRoadMonitor : public SMonitor {
public:
    /**
     * helpers
     */
    using Road     = R;
    using Location = typename Road::Location;
    /**
     * constructor
     */
    SLinuxRoadMonitor() = default;
    /**
     */
    SLinuxRoadMonitor(time_t timeout) : __timeout(timeout) {
    }
    /**
     * destructor
     */
    virtual ~SLinuxRoadMonitor() = default;
    /**
     * operator
     */
    SLinuxRoadMonitor& operator=(SLinuxRoadMonitor &&) = default;
    /**
     * -------------------------------------------------------------------------------------------------------------
     * interface
     * -------------------------------------------------------------------------------------------------------------
     * get resource
     */
    inline Resource& resource() {
        return __poll;
    }
    /**
     * get timeout
     */
    inline chrono::milliseconds GetTimeout(){
        return __timeout;
    }
    /**
     * update and wait
     */
    inline list<Location> Wait(Road& road) {
        return update(road).wait();
    }
    /**
     * wait
     */
    inline list<Location> Wait() {
        return wait();
    }
protected:
    /**
     * timeout
     */
    chrono::milliseconds __timeout;
private:
    /**
     * -------------------------------------------------------------------------------------------------------------
     * linux part
     * -------------------------------------------------------------------------------------------------------------
     **
     * definitions
     */
    struct compare {
        bool operator()(const Location& __x, const Location& __y) const {
            return __x->first < __y->first;
        }
    };
    using Bimap = SBimap<Location, SLinuxResource*, compare>;
    using Poll  = SLinuxPoll;
    /**
     * resource poll
     */
    Poll __poll;
    /**
     * map between location and resource
     */
    Bimap __map;
    /**
     * reload road
     */
    SLinuxRoadMonitor& update(Road& road) {
        //drain poll
        for(auto& e : __map) {
              __poll.Delete(e.second);
        }
        // clear resource map
        __map.clear();
        // update resource map
        for (auto l = road.begin(), e = road.end(); l != e; ++l) {
            __map.insert(l, static_cast<SLinuxResource*> (&l->second->resource()));
        }
        // fill resource poll
        for(auto& e : __map) {
              __poll.Insert(e.second);
        }
        return *this;
    }
    /**
     * wait
     */
    list<Location> wait() {
        list<Location> res;
        // wait and read
        for(auto& r : __poll.Poll(__timeout, __map.size())) {
            res.push_back(__map.rfind(r));
        }
        // return a list of changed resources
        return res;
    }
};
/**
 */
#endif /* SLINUXROADMONITOR_H */

