/* 
 * Container:   SContainerMonitor.h
 * Author: Luis Monteiro
 *
 * Created on January 21, 2019, 12:37 PM
 */
#ifndef SCONTAINERMONITOR_H
#define SCONTAINERMONITOR_H
/**
 * C++
 */
#include <chrono>
/**
 * kernel
 */
#include "SRoad.h"
/*------------------------------------------------------------------------------------------------*
 * ContainerMonitor 
 *------------------------------------------------------------------------------------------------*/
template<class CONTAINER>
class SContainerMonitor : public SRoad<K, T>, public M<SRoad<K, T>> {
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
    SContainerMonitorT() = default;
    /**
     * main constructor
     * @param timeout
     * @param nominal
     * @param min
     */
    SContainerMonitorT(time_t timeout, size_t nominal = 0, size_t min = 0)
    : Road(nominal, min), Monitor(timeout), __rev(0) {
    }
    /**
     * destructor
     */
    virtual ~SContainerMonitorT() = default;
    /**
     * operators
     */
    SContainerMonitorT& operator=(SContainerMonitorT &&) = default;
    /**
     * update and wait
     */
    list<Location> Wait() {
        return changed() ? Monitor::Wait(*this) : Monitor::Wait();
    }
protected:
    inline bool changed() {
        if(Road::Resvision() != __rev) {
            __rev = Road::Resvision();
            return true;
        }
        return false;
    }
private:
    size_t __rev;
};

/*------------------------------------------------------------------------------------------------*
 * linux platform 
 *------------------------------------------------------------------------------------------------*/
#ifdef __linux__
/**
 */
#include "SLinuxContainerMonitor.h"
/**
 */
template<class K, class T>
class SContainerMonitor : public SContainerMonitorT<K, T, SLinuxContainerMonitor> {
    using SContainerMonitorT<K, T, SLinuxContainerMonitor>::SContainerMonitorT;
};
/**
 */
#endif
/**
 */
#endif /* SCONTAINERMONITOR_H */

