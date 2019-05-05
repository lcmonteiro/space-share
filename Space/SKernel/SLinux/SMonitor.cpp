/**
 * ------------------------------------------------------------------------------------------------
 * File:   SMonitorHandler.cpp
 * Author: Luis Monteiro
 *
 * Created on January, 2019, 12:37 PM
 * ------------------------------------------------------------------------------------------------
 **
 * linux
 */
#include <sys/epoll.h>
/**
 * std
 */
#include <cstring>
/**
 * space 
 */
#include "SMonitorHandler.h"
#include "SResourceHandler.h"
/**
 * namespaces 
 */
using namespace std;
/**
 * ------------------------------------------------------------------------------------------------
 * static monitor
 * ------------------------------------------------------------------------------------------------
 * constructor
 * ----------------------------------------------------------------------------
 */
Monitor::SStatic::SStatic(): SMonitor() {
    SMonitor::handler(make_shared<SStaticMonitorHandler>());
}
/**
 * ----------------------------------------------------------------------------
 * size
 * ----------------------------------------------------------------------------
 */
size_t Monitor::SStatic::size() {
    return SMonitor::handler<SStaticMonitorHandler>()->size();
}
/**
 * ----------------------------------------------------------------------------
 * insert handler
 * ----------------------------------------------------------------------------
 */
size_t Monitor::SStatic::insert(Handler h) {
    return SMonitor::handler<SStaticMonitorHandler>()->insert(
        static_pointer_cast<SResourceHandler>(h)
    );
}
/**
 * ----------------------------------------------------------------------------
 *  wait for active handlers
 * ----------------------------------------------------------------------------
 */
list<size_t> Monitor::SStatic::wait(const Time& timeout) {
    return SMonitor::handler<SStaticMonitorHandler>()->wait(timeout);
}
/**
 * ------------------------------------------------------------------------------------------------
 * dynamic monitor
 * ------------------------------------------------------------------------------------------------
 * constructor
 * ----------------------------------------------------------------------------
 */
Monitor::SDynamic::SDynamic(): SMonitor(), SResource() {
    auto p = make_shared<SDynamicMonitorHandler>();
    SResource::handler(p);
    SMonitor::handler(p);
}
/**
 * ----------------------------------------------------------------------------
 * size
 * ----------------------------------------------------------------------------
 */
size_t Monitor::SDynamic::size() {
    return SMonitor::handler<SDynamicMonitorHandler>()->size();
}
/**
 * ----------------------------------------------------------------------------
 * insert handler
 * ----------------------------------------------------------------------------
 */
size_t Monitor::SDynamic::insert(Handler h) {
    return SMonitor::handler<SDynamicMonitorHandler>()->insert(
        static_pointer_cast<SResourceHandler>(h)
    );
}
/**
 * ----------------------------------------------------------------------------
 *  wait for active handlers
 * ----------------------------------------------------------------------------
 */
list<size_t> Monitor::SDynamic::wait(const chrono::milliseconds& timeout) {
    return SMonitor::handler<SDynamicMonitorHandler>()->wait(timeout);
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */