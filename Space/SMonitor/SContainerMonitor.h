/* 
 * Container:   SContainerMonitor.h
 * Author: Luis Monteiro
 *
 * Created on January 21, 2019, 12:37 PM
 */
#ifndef SCONTAINERMONITOR_H
#define SCONTAINERMONITOR_H
/**
 * std
 */
#include <chrono>
#include <map>
/**
 * space
 */
#include "SResourceMonitor.h"
#include "SRoad.h"
/**
 * -------------------------------------------------------------------------------------------------
 * Road monitor
 * -------------------------------------------------------------------------------------------------
 */
template<
    typename KEY, 
    typename OBJ, 
    typename MOTITOR=SResourceMonitor<SMonitor::SIndirect, SDynamicMonitor>
>
class SRoadMonitor : public SRoad<KEY, OBJ>, public MOTITOR {
    using Road    	= SRoad<KEY, OBJ>;
    using Monitor   = MOTITOR;
public:
    using Object    = OBJ;
    using Time      = std::chrono::milliseconds; 
    /**
     * ------------------------------------------------------------------------
     * defaults
     * ------------------------------------------------------------------------ 
     */
    SRoadMonitor()                           = default;
    SRoadMonitor(SRoadMonitor &&)            = default;
    SRoadMonitor& operator=(SRoadMonitor &&) = default;
    /**
     * ------------------------------------------------------------------------
     * constructors
     * ------------------------------------------------------------------------
     * template 
     */
    template<typename... Args>
    SRoadMonitor(Time timeout, Args... args)
    : Road(forward<Args>(args)...), Monitor(timeout), __rev(0) {}
    /**
     * ------------------------------------------------------------------------
     * interfaces
     * ------------------------------------------------------------------------
     * wait 
     */
    inline list<Object> Wait() {

        // reload if changed ------------------------------
        if(__Changed()) {
            *this = Monitor();
            for(auto& l : *this) {
                __map[Monitor::Insert(l->second)] = l->second;
            }
        }

        // wait and map -----------------------------------
        list<Object> res;
        for(auto& r : Monitor::Wait()) {
            res.emplace_back(__map.Find2(r));
        }
        return res;
    }
protected:
    /**
     * ------------------------------------------------------------------------
     * helpers
     * ------------------------------------------------------------------------
     * changed 
     */
    inline bool __Changed() {
        if(Road::Resvision() != __rev) {
            __rev = Road::Resvision();
            return true;
        } else {
            return false;
        }
    }
private:
    using Map  = map<size_t, Object>;
    /**
     * ------------------------------------------------------------------------
     * Variables
     * ------------------------------------------------------------------------
     * revision 
     */
    size_t __rev;
    /**
     * mapping
     */
    Map    __map;
};
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SCONTAINERMONITOR_H */

