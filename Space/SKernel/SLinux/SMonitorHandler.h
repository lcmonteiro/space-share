/**
 * Container:   SMonitorHandler.h
 * Author: Luis Monteiro
 *
 * Created on January, 2019, 12:37 PM
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
 * -------------------------------------------------------------------------------------------------
 * monitor handler
 * -------------------------------------------------------------------------------------------------
 */
class SMonitorHandler: public SMonitor::SHandler {
public:
    using Handler  = SResource::pHandler<SResourceHandler>;
    using Handlers = vector<Handler>;
    /**
     * ------------------------------------------------------------------------
     * constructors & destructor
     * ------------------------------------------------------------------------
     * main
     */
    SMonitorHandler() = default;
    /**
     * ------------------------------------------------------------------------
     * interfaces
     * ------------------------------------------------------------------------
     * size 
     */
    inline size_t Size() {
        return __handlers.size();
    }
protected:
    /**
     * public handlers
     */
    Handlers __handlers;
};
/**
 * -------------------------------------------------------------------------------------------------
 * static monitor handler
 * -------------------------------------------------------------------------------------------------
 */
class SStaticMonitorHandler: public SMonitorHandler {
public:
    /**
     * ------------------------------------------------------------------------
     * constructors & destructor
     * ------------------------------------------------------------------------
     * main
     */
    SStaticMonitorHandler(initializer_list<Handler> handlers);
    /**
     */
    SStaticMonitorHandler() : SStaticMonitorHandler({}) {}
    /**
     */
    virtual ~SStaticMonitorHandler() = default;
    /**
     * ------------------------------------------------------------------------
     * interfaces
     * ------------------------------------------------------------------------
     * insert 
     */
    size_t Insert(Handler h);
    /**
     * wait
     */
    std::list<size_t> Wait(const chrono::milliseconds& timeout);
    /**
     */
protected:
    using Location  = pollfd;
    using Locations = vector<Location>;
    /**
     * ------------------------------------------------------------------------
     * native processes
     * ------------------------------------------------------------------------
     **
     * check a group of locations
     */
    std::list<size_t> __Check(const chrono::milliseconds& timeout);
private:
    /**
     * ------------------------------------------------------------------------
     * variables
     * ------------------------------------------------------------------------
     **
     * native locations
     */
    Locations __locations;
};
/**
 * -------------------------------------------------------------------------------------------------
 * dynamic monitor handler
 * -------------------------------------------------------------------------------------------------
 */
class SDynamicMonitorHandler: public SMonitorHandler, public SResourceHandler {
public:
    /**
     * ------------------------------------------------------------------------
     * constructors & destructor
     * ------------------------------------------------------------------------
     * main
     */
    SDynamicMonitorHandler(initializer_list<Handler> handlers);
    /**
     */
    SDynamicMonitorHandler() : SDynamicMonitorHandler({}) {}
    /**
     */
    virtual ~SDynamicMonitorHandler() = default;
    /**
     * ------------------------------------------------------------------------
     * interfaces
     * ------------------------------------------------------------------------
     * insert 
     */
    size_t Insert(Handler h);
    /**
     * wait
     */
    std::list<size_t> Wait(const chrono::milliseconds& timeout);
protected:
    using Handlers  = vector<Handler>;
    /**
     * ------------------------------------------------------------------------
     * native processes
     * ------------------------------------------------------------------------
     **
     * check a group of locations
     */
    std::list<size_t> __Check(const chrono::milliseconds& timeout);
};
/**
 * -------------------------------------------------------------------------------------------------
 * end 
 * -------------------------------------------------------------------------------------------------
 */
#endif /* SMONITORHANDLER_H */

