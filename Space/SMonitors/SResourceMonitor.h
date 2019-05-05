/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SResourceMonitor.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SRESOURCEMONITOR_H
#define SRESOURCEMONITOR_H
/**
 * std
 */
#include <chrono>
/**
 * space
 */
#include "SResource.h"
#include "SMonitor.h"
/**
 * -------------------------------------------------------------------------------------------------
 * Default Adapters 
 * -------------------------------------------------------------------------------------------------
 */
namespace Monitor {
namespace Resource {
struct SDirect {
	template<typename T>
	static inline SMonitor::Handler GetHandler(T obj) {
		return obj->SResource::handler();
	}
};
struct SIndirect {
	template<typename T>
	static inline SMonitor::Handler GetHandler(T obj) {
		return obj->resource().handler();
	}
};
}}
/**
 * -------------------------------------------------------------------------------------------------
 * Resource Monitor
 * -------------------------------------------------------------------------------------------------
 */
template<typename Adapt = Monitor::Resource::SDirect, typename Base = Monitor::SStatic>
class SResourceMonitor : public Base {
public:
    using Time = std::chrono::milliseconds; 
    /**
     * ------------------------------------------------------------------------
     * Defaults
     * ------------------------------------------------------------------------ 
     */
    SResourceMonitor(SResourceMonitor &&)            = default;
    SResourceMonitor& operator=(SResourceMonitor &&) = default;
    /**
     * ------------------------------------------------------------------------
     * Constructors
     * ------------------------------------------------------------------------
     * Template 
     */
    template<typename T, typename... Args>
    SResourceMonitor(Time timeout, T arg, Args... args) 
    : SResourceMonitor(timeout) {
        insert(arg, args...);
    }
    template<typename T, typename... Args>
    SResourceMonitor(T arg, Args... args)
    : SResourceMonitor(Time(0), arg, std::forward<Args>(args)...) {
    }
    /**
     * main
     */
    SResourceMonitor(const Time& timeout=Time::zero()) 
    : Base(), __timeout(timeout) {
    }
    /**
     * ------------------------------------------------------------------------
     * Interface
     * ------------------------------------------------------------------------
     * Insert
     * ----------------------------------------------------
     */
    template<typename T>
    size_t insert(T obj) {
        return Base::insert(Adapt::GetHandler(obj));
    }
    /**
     * ----------------------------------------------------
     * check
     * ----------------------------------------------------
     */
    inline bool good() {
        return (__timeout != Time::zero()) && Base::size();
    }
    /**
     * ----------------------------------------------------
     * wait
     * ----------------------------------------------------
     */
    inline std::list<size_t> wait(const Time& timeout) {
        return Base::wait(timeout);
    }
    inline std::list<size_t> wait() {
        return Base::wait(__timeout);
    }
    /**
     * ----------------------------------------------------
     * Check
     * ----------------------------------------------------
     */
    inline std::list<size_t> check(const Time& timeout) {
        try {
            return Base::Wait(timeout);
        } catch(MonitorExceptionTIMEOUT& ) {
            return {};
        }
    }
    inline std::list<size_t> Check() {
        try {
            return Base::Wait(__timeout);
        } catch(MonitorExceptionTIMEOUT& ) {
            return {};
        }
    } 
protected:
    using Handler  = SResource::pHandler<>;
    /**
     * ------------------------------------------------------------------------
     * Helpers
     * ------------------------------------------------------------------------
     * parse template
     * ----------------------------------------------------
     */
    template<typename T, typename... Args>
    void insert(T first, Args... args) {
        insert(first); insert(args...);
    }
private:
    /**
     * ------------------------------------------------------------------------
     * Variables
     * ------------------------------------------------------------------------
     * timeout
     */
    Time __timeout;
};
/**
 * -------------------------------------------------------------------------------------------------
 * End
 * -------------------------------------------------------------------------------------------------
 */
#endif /* SRESOURCEMONITOR_H */

