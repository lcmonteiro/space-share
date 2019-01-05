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
/**
 * space
 */
#include "SMonitor.h"
#include "SResource.h"
/**
 */
class SMonitorHandler: public SMonitor::SHandler {
public:
    using Handler  = SResource::pHandler<>;
    using Handlers = vector<Handler>;
    /**
     * ------------------------------------------------------------------------
     * constructors & destructor
     * ------------------------------------------------------------------------
     * main
     */
    SMonitorHandler(Handlers handlers);
    /**
     */
    SMonitorHandler() = default;
    /**
     */
    virtual ~SMonitorHandler() = default;
    /**
     * ------------------------------------------------------------------------
     * interfaces
     * ------------------------------------------------------------------------
     * wait 
     */
    vector<size_t> Wait(const chrono::milliseconds& timeout);
    /**
     */
protected:
    using Location  = pollfd;
    using Locations = vector<Location>;
    /**
     * public handlers
     */
    Handlers __handlers;
    /**
     * native locations
     */
    Locations __locations;
private:
    /**
     * ------------------------------------------------------------------------
     * Native processes
     * ------------------------------------------------------------------------
     **
     * create location 
     */
    Location __CreateLocation(Handler handle);
    /**
     * check a group of locations
     */
    vector<size_t> __Check(const chrono::milliseconds& timeout);
};
/**
 */
#endif /* SMONITORHANDLER_H */

