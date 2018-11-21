/* 
 * Container:   SRoadMonitor.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SROADMONITOR_H
#define SROADMONITOR_H
/**
 * C++
 */
#include <chrono>
/**
 * kernel
 */
#include "SRoad.h"
/*---------------------------------------------------------------------------------------------------------------------*
 * RoadMonitor template
 *---------------------------------------------------------------------------------------------------------------------*/
template<class K, class T, template<typename ...> class M>
class SRoadMonitorT : public SRoad<K, T>, public M<SRoad<K, T>> {
    /**
     * helpers
     */
    using Road    	= SRoad<K, T>;
    using Monitor   = M<SRoad<K, T>>;
    using Location  = typename SRoad<K, T>::Location;
public:
    /**
     * share types
     */
    using Key       = K;
    using Object    = T;
    /**
     * default constructor
     */
    SRoadMonitorT() = default;
    /**
     * main constructor
     * @param timeout
     * @param nominal
     * @param min
     */
    SRoadMonitorT(chrono::milliseconds timeout, uint32_t nominal = 0, uint32_t min = 0)
    : Road(nominal, min), Monitor(timeout), __rev(0) {
    }
    /**
     * destructor
     */
    virtual ~SRoadMonitorT() = default;
    /**
     * operators
     */
    SRoadMonitorT& operator=(SRoadMonitorT &&) = default;
    /**
     * update and wait
     */
    list<Location> Wait() {
        return changed() ? Monitor::Wait(*this) : Monitor::Wait();
    }
protected:
    inline bool changed() {
        if(Road::revision() != __rev) {
            __rev = Road::revision();
            return true;
        }
        return false;
    }
private:
    size_t __rev;
};

/*---------------------------------------------------------------------------------------------------------------------*
 * linux platform 
 *---------------------------------------------------------------------------------------------------------------------*/
#ifdef __linux__
/**
 */
#include "SLinuxRoadMonitor.h"
/**
 */
template<class K, class T>
class SRoadMonitor : public SRoadMonitorT<K, T, SLinuxRoadMonitor> {
    using SRoadMonitorT<K, T, SLinuxRoadMonitor>::SRoadMonitorT;
};
/**
 */
#endif
/**
 */
#endif /* SROADMONITOR_H */

