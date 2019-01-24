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
    typename CONTAINER, 
    typename MOTITOR=SResourceMonitor<Monitor::SIndirect, Monitor::SDynamic>
>
class SContainerMonitor : public CONTAINER, public MOTITOR {
    using Container = CONTAINER;
    using Monitor   = MOTITOR;
public:
    using Object    = typename Container::Object;
    using Time      = std::chrono::milliseconds; 
    /**
     * ------------------------------------------------------------------------
     * defaults
     * ------------------------------------------------------------------------ 
     */
    SContainerMonitor()                                = default;
    SContainerMonitor(SContainerMonitor &&)            = default;
    SContainerMonitor& operator=(SContainerMonitor &&) = default;
    /**
     * ------------------------------------------------------------------------
     * constructors
     * ------------------------------------------------------------------------
     * template 
     */
    template<typename... Args>
    SContainerMonitor(Time timeout, Args... args)
    : Container(forward<Args>(args)...), Monitor(timeout), __rev(0) {}
    /**
     * ------------------------------------------------------------------------
     * interfaces
     * ------------------------------------------------------------------------
     * wait 
     */
    inline std::list<Object> Wait() {
        // reload if changed ------------------------------
        if(__Changed()) {
            static_cast<Monitor&>(*this) = Monitor();
            for(auto& l : *this) {
                __map.emplace(
                    Monitor::Insert(l.second), l.second
                );
            }
        }
        // wait and map -----------------------------------
        std::list<Object> res;
        for(auto& r : Monitor::Wait()) {
            res.emplace_back(__map.at(r));
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
        if(Container::Resvision() != __rev) {
            __rev = Container::Resvision();
            return true;
        } else {
            return false;
        }
    }
private:
    using Map = map<size_t, Object>;
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

