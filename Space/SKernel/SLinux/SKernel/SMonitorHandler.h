/**
 * ------------------------------------------------------------------------------------------------
 * File:   SMonitorHandler.h
 * Author: Luis Monteiro
 *
 * Created on January, 2019, 12:37 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SMONITORHANDLER_H
#define SMONITORHANDLER_H
/**
 * linux
 */
#include <poll.h>
/**
 * std
 */
#include <chrono>
#include <vector>
#include <list>
/**
 * space linux
 */
#include "SResourceHandler.h"
/**
 * space
 */
#include "SMonitor.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Monitor Handler
 * ------------------------------------------------------------------------------------------------
 */
class SMonitorHandler: public SMonitor::SHandler {
public:
    using Handler  = SResource::pHandler<SResourceHandler>;
    using Handlers = std::vector<Handler>;
    /**
     * ------------------------------------------------------------------------
     * Constructors & Destructor
     * ------------------------------------------------------------------------
     * main
     */
    SMonitorHandler() = default;
    /**
     * ------------------------------------------------------------------------
     * Interfaces
     * ------------------------------------------------------------------------
     * size 
     */
    inline size_t size() {
        return __handlers.size();
    }
protected:
    /**
     * public handlers
     */
    Handlers __handlers;
};
/**
 * ------------------------------------------------------------------------------------------------
 * Static Monitor Handler
 * ------------------------------------------------------------------------------------------------
 */
class SStaticMonitorHandler: public SMonitorHandler {
public:
    /**
     * ------------------------------------------------------------------------
     * Constructors & Destructor
     * ------------------------------------------------------------------------
     * main
     */
    SStaticMonitorHandler(std::initializer_list<Handler> handlers);
    /**
     * empty
     */
    SStaticMonitorHandler() : SStaticMonitorHandler({}) {}
    /**
     */
    virtual ~SStaticMonitorHandler() = default;
    /**
     * ------------------------------------------------------------------------
     * Interfaces
     * ------------------------------------------------------------------------
     * Insert 
     */
    size_t insert(Handler h);
    /**
     * Wait
     */
    std::list<size_t> wait(const std::chrono::milliseconds& timeout);
    /**
     */
protected:
    using Location  = pollfd;
    using Locations = std::vector<Location>;
    /**
     * ------------------------------------------------------------------------
     * Native Processes
     * ------------------------------------------------------------------------
     **
     * check a group of locations
     */
    std::list<size_t> _check(const std::chrono::milliseconds& timeout);
    /**
     * create a location
     */
    inline Location _create(Handler h);
    /**
     * ------------------------------------------------------------------------
     * Variables
     * ------------------------------------------------------------------------
     **
     * native locations
     */
    Locations __locations;
};
/**
 * ------------------------------------------------------------------------------------------------
 * Dynamic Monitor Handler
 * ------------------------------------------------------------------------------------------------
 */
class SDynamicMonitorHandler: public SMonitorHandler, public SResourceHandler {
public:
    /**
     * ------------------------------------------------------------------------
     * Constructors & Destructor
     * ------------------------------------------------------------------------
     * main
     */
    SDynamicMonitorHandler(std::initializer_list<Handler> handlers);
    /**
     * empty
     */
    SDynamicMonitorHandler() : SDynamicMonitorHandler({}) {}
    /**
     */
    virtual ~SDynamicMonitorHandler() = default;
    /**
     * ------------------------------------------------------------------------
     * Interfaces
     * ------------------------------------------------------------------------
     * Insert 
     */
    size_t insert(Handler h);
    /**
     * Wait
     */
    std::list<size_t> wait(const std::chrono::milliseconds& timeout);
protected:
    using Handlers  = std::vector<Handler>;
    /**
     * ------------------------------------------------------------------------
     * Native Processes
     * ------------------------------------------------------------------------
     **
     * check a group of locations
     */
    std::list<size_t> _check(const std::chrono::milliseconds& timeout);
    /**
     * insert handler
     */
    inline void _insert(Handler h, size_t position);
    /**
     * remove handler
     */
    inline void _remove(Handler h);
};
/**
 * ------------------------------------------------------------------------------------------------
 * End 
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SMONITORHANDLER_H */

