/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SContainerMonitor.h
 * Author: Luis Monteiro
 *
 * Created on January 21, 2019, 12:37 PM
 * ------------------------------------------------------------------------------------------------
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
 * Default Adapters 
 * -------------------------------------------------------------------------------------------------
 */
namespace Monitor {
namespace Container {
struct SOne {
	template<typename T>
	static inline auto GetResource(T it) {
		return *it;
	}
    template<typename T>
	static inline auto GetLocation(T it) {
		return it;
	}
};
struct SPair {
	template<typename T>
	static inline auto GetResource(T it) {
		return it->second;
	}
    template<typename T>
	static inline auto GetLocation(T it) {
		return it;
	}
};
}}
/**
 * -------------------------------------------------------------------------------------------------
 * Container Monitor
 * -------------------------------------------------------------------------------------------------
 */
template<
    typename Container, 
    typename Adapter = Monitor::Container::SOne,
    typename Monitor = SResourceMonitor<Monitor::Resource::SIndirect, Monitor::SDynamic>
>
class SContainerMonitor : public Container, public Monitor {
public:
    using Location  = typename Container::Location;
    using Time      = typename Monitor::Time; 
    /**
     * ------------------------------------------------------------------------
     * Defaults
     * ------------------------------------------------------------------------ 
     */
    SContainerMonitor()                                = default;
    SContainerMonitor(SContainerMonitor &&)            = default;
    SContainerMonitor& operator=(SContainerMonitor &&) = default;
    /**
     * ------------------------------------------------------------------------
     * Constructors
     * ------------------------------------------------------------------------
     * template 
     */
    template<typename... Args>
    SContainerMonitor(Time timeout, Args... args)
    : Container(std::forward<Args>(args)...), Monitor(timeout), __rev(0) {}
    /**
     * ------------------------------------------------------------------------
     * Interfaces
     * ------------------------------------------------------------------------
     * Wait 
     * ----------------------------------------------------
     */
    inline std::list<Location> wait() {
        /**
         * update monitor
         */
        update();
        /**
         * wait and map
         */
        std::list<Location> res;
        for(auto& r : Monitor::wait()) {
            res.emplace_back(__map.at(r));
        }
        return res;
    }
    /**
     * ----------------------------------------------------
     * Update
     * ----------------------------------------------------
     */
    inline SContainerMonitor& update() {
        /**
         * reload if changed
         */
        if(_changed()) {
            static_cast<Monitor&>(*this) = Monitor();
            for(auto it = Container::begin(); Container::end() != it; ++it) {
                __map.emplace(
                    Monitor::insert(
                        Adapter::GetResource(it)), 
                        Adapter::GetLocation(it));
            }
        }
        /**
         * return itself
         */
        return *this;
    }
protected:
    /**
     * ------------------------------------------------------------------------
     * Helpers
     * ------------------------------------------------------------------------
     * Changed
     * ---------------------------------------------------- 
     */
    inline bool _changed() {
        if(Container::resvision() != __rev) {
            __rev = Container::resvision();
            return true;
        } else {
            return false;
        }
    }
private:
    using Map = std::map<size_t, Location>;
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
    Map __map;
};
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SCONTAINERMONITOR_H */

