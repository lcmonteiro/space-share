/* 
 * Container:   SResourceMonitor.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SRESOURCEMONITOR_H
#define SRESOURCEMONITOR_H
/**
 */
#include "SResource.h"
/**
 * ------------------------------------------------------------------------------------------------
 * linux platform 
 * ------------------------------------------------------------------------------------------------
 **/
#ifdef __linux__
/**
 */
#include "SLinuxResourceMonitor.h"
/**
 */
class SResourceMonitor : public SLinuxResourceMonitor {
    using SLinuxResourceMonitor::SLinuxResourceMonitor;
};
/**
 */
#endif
/**
 */
#endif /* SRESOURCEMONITOR_H */

