/* 
 * Container:   SResourceMonitor.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
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
 * resource monitor
 * -------------------------------------------------------------------------------------------------
 */
template<typename ADAPT = SMonitor::SDirect, typename BASE = SStaticMonitor>
class SResourceMonitor : public BASE {
public:
    using Time = std::chrono::milliseconds; 
    /**
     * ------------------------------------------------------------------------
     * constructors
     * ------------------------------------------------------------------------
     * template 
     */
    template<typename T, typename... Args>
    SResourceMonitor(Time timeout, T arg, Args... args) 
    : SResourceMonitor(timeout) {
        Insert(arg, args...);
    }
    template<typename T, typename... Args>
    SResourceMonitor(T arg, Args... args)
    : SResourceMonitor(Time(0), arg, std::forward<Args>(args)...) {
    }
    /**
     * ------------------------------------------------------------------------
     * interface
     * ------------------------------------------------------------------------
     **
     * insert
     */
    template<typename T>
    size_t Insert(T obj) {
        return BASE::Insert(ADAPT::GetHandler(obj));
    }
    /**
     * check
     */
    inline bool Good() {
        (__timeout != Time::zero()) && (BASE::Size() != 0);
    }
    /**
     * wait
     */
    inline std::list<size_t> Wait(const Time& timeout) {
        return BASE::Wait(timeout);
    }
    inline std::list<size_t> Wait() {
        return BASE::Wait(__timeout);
    }
    /**
     * check
     */
    inline std::list<size_t> Check(const Time& timeout) {
        try {
            return BASE::Wait(timeout);
        } catch(MonitorExceptionTIMEOUT& ) {
            return {};
        }
    }
    inline std::list<size_t> Check() {
        try {
            return BASE::Wait(__timeout);
        } catch(MonitorExceptionTIMEOUT& ) {
            return {};
        }
    } 
protected:
    using Handler  = SResource::pHandler<>;
    /**
     * ------------------------------------------------------------------------
     * constructor
     * ------------------------------------------------------------------------
     * build
     */
    SResourceMonitor(Time timeout) :BASE(), __timeout(timeout) {
    }
    /**
     * ------------------------------------------------------------------------
     * update
     * ------------------------------------------------------------------------
     * parse template
     */
    template<typename T, typename... Args>
    void Insert(T first, Args... args) {
        Insert(first); Insert(args...);
    }
    
private:
    /**
     * ------------------------------------------------------------------------
     * variables
     * ------------------------------------------------------------------------
     **
     * timeout
     */
    Time __timeout;
};
/**
 * -------------------------------------------------------------------------------------------------
 * end
 * -------------------------------------------------------------------------------------------------
 */
#endif /* SRESOURCEMONITOR_H */

