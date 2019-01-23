/**
 * Container:   SMonitorHandler.cpp
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
SStaticMonitor::SStaticMonitor(): SMonitor() {
    SMonitor::SetHandler(make_shared<SStaticMonitorHandler>());
}
/**
 * ----------------------------------------------------------------------------
 * size
 * ----------------------------------------------------------------------------
 */
size_t SStaticMonitor::Size() {
    return SMonitor::GetHandler<SStaticMonitorHandler>()->Size();
}
/**
 * ----------------------------------------------------------------------------
 * insert handler
 * ----------------------------------------------------------------------------
 */
size_t SStaticMonitor::Insert(Handler h) {
    return SMonitor::GetHandler<SStaticMonitorHandler>()->Insert(
        std::static_pointer_cast<SResourceHandler>(h)
    );
}
/**
 * ----------------------------------------------------------------------------
 *  wait for active handlers
 * ----------------------------------------------------------------------------
 */
std::list<size_t> SStaticMonitor::Wait(const Time& timeout) {
    return SMonitor::GetHandler<SStaticMonitorHandler>()->Wait(timeout);
}
/**
 * ------------------------------------------------------------------------------------------------
 * dynamic monitor
 * ------------------------------------------------------------------------------------------------
 * constructor
 * ----------------------------------------------------------------------------
 */
SDynamicMonitor::SDynamicMonitor() : SMonitor(), SResource() {
    auto p = make_shared<SDynamicMonitorHandler>();
    SResource::SetHandler(p);
    SMonitor::SetHandler(p);
}
/**
 * ----------------------------------------------------------------------------
 * size
 * ----------------------------------------------------------------------------
 */
size_t SDynamicMonitor::Size() {
    return SMonitor::GetHandler<SDynamicMonitorHandler>()->Size();
}
/**
 * ----------------------------------------------------------------------------
 * insert handler
 * ----------------------------------------------------------------------------
 */
size_t SDynamicMonitor::Insert(Handler h) {
    return SMonitor::GetHandler<SDynamicMonitorHandler>()->Insert(
        std::static_pointer_cast<SResourceHandler>(h)
    );
}
/**
 * ----------------------------------------------------------------------------
 *  wait for active handlers
 * ----------------------------------------------------------------------------
 */
std::list<size_t> SDynamicMonitor::Wait(const chrono::milliseconds& timeout) {
    return SMonitor::GetHandler<SDynamicMonitorHandler>()->Wait(timeout);
}
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */