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
 * default adapters 
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
}
}
/**
 * -------------------------------------------------------------------------------------------------
 * ContainerMonitor
 * -------------------------------------------------------------------------------------------------
 */
template<
    typename CONTAINER, 
    typename ADAPTER=Monitor::Container::SOne,
    typename MOTITOR=SResourceMonitor<Monitor::Resource::SIndirect, Monitor::SDynamic>
>
class SContainerMonitor : public CONTAINER, public MOTITOR {
    using Container = CONTAINER;
    using Monitor   = MOTITOR;
public:
    using Location  = typename Container::Location;
    using Time      = typename Monitor::Time; 
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
    inline std::list<Location> Wait() {
        // reload if changed ------------------------------
        if(__Changed()) {
            static_cast<Monitor&>(*this) = Monitor();
            for(auto it = Container::begin(); Container::end() != it; ++it) {
                __map.emplace(
                    Monitor::Insert(ADAPTER::GetResource(it)), ADAPTER::GetLocation(it)
                );
            }
        }
        // wait and map -----------------------------------
        std::list<Location> res;
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
    using Map = map<size_t, Location>;
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
 * end
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SCONTAINERMONITOR_H */

