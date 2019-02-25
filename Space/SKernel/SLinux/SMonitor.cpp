/**
 * File:   SMonitorHandler.cpp
 * Author: Luis Monteiro
 *
 * Created on January, 2019, 12:37 PM
 ***
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
 * ------------------------------------------------------------------------------------------------
 * static monitor
 * ------------------------------------------------------------------------------------------------
 * constructor
 * ----------------------------------------------------------------------------
 */
Monitor::SStatic::SStatic(): SMonitor() {
    SMonitor::SetHandler(make_shared<SStaticMonitorHandler>());
}
/**
 * ----------------------------------------------------------------------------
 * size
 * ----------------------------------------------------------------------------
 */
size_t Monitor::SStatic::Size() {
    return SMonitor::GetHandler<SStaticMonitorHandler>()->Size();
}
/**
 * ----------------------------------------------------------------------------
 * insert handler
 * ----------------------------------------------------------------------------
 */
size_t Monitor::SStatic::Insert(Handler h) {
    return SMonitor::GetHandler<SStaticMonitorHandler>()->Insert(
        std::static_pointer_cast<SResourceHandler>(h)
    );
}
/**
 * ----------------------------------------------------------------------------
 *  wait for active handlers
 * ----------------------------------------------------------------------------
 */
std::list<size_t> Monitor::SStatic::Wait(const Time& timeout) {
    return SMonitor::GetHandler<SStaticMonitorHandler>()->Wait(timeout);
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
    SResource::SetHandler(p);
    SMonitor::SetHandler(p);
}
/**
 * ----------------------------------------------------------------------------
 * size
 * ----------------------------------------------------------------------------
 */
size_t Monitor::SDynamic::Size() {
    return SMonitor::GetHandler<SDynamicMonitorHandler>()->Size();
}
/**
 * ----------------------------------------------------------------------------
 * insert handler
 * ----------------------------------------------------------------------------
 */
size_t Monitor::SDynamic::Insert(Handler h) {
    return SMonitor::GetHandler<SDynamicMonitorHandler>()->Insert(
        std::static_pointer_cast<SResourceHandler>(h)
    );
}
/**
 * ----------------------------------------------------------------------------
 *  wait for active handlers
 * ----------------------------------------------------------------------------
 */
std::list<size_t> Monitor::SDynamic::Wait(const chrono::milliseconds& timeout) {
    return SMonitor::GetHandler<SDynamicMonitorHandler>()->Wait(timeout);
}
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */