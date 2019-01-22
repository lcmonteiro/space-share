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
        __Insert(arg, args...);
    }
    template<typename T, typename... Args>
    SResourceMonitor(T arg, Args... args)
    : SResourceMonitor(Time(0), arg, forward<Args>(args)...) {
    }
    /**
     * ------------------------------------------------------------------------
     * interface
     * ------------------------------------------------------------------------
     **
     * check
     */
    bool Good();
    /**
     * wait
     */
    vector<size_t> Wait(chrono::milliseconds timeout);
    inline vector<size_t> Wait() {
        return Wait(__timeout);
    }
    /**
     * check
     */
    vector<size_t> Check(chrono::milliseconds timeout);
    inline vector<size_t> Check() {
        return Check(__timeout);
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
     * templates
     */
    template<typename T, typename... Args>
    void __Insert(T first, Args... args) {
        __Insert(first); __Insert(args...);
    }
    template<typename T>
    void __Insert(T obj) {
        __Insert(ADAPT::GetHandler(obj));
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

