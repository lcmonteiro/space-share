/*
 * Container:   SLinuxEvent.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 **
 * linux
 */
#include <poll.h>
#include <unistd.h>
#include <sys/eventfd.h>
/**
 */
#include "SLinuxEvent.h"
/**
 */
SLinuxEvent::SLinuxEvent(int init) : SLinuxResource(eventfd(init, 0)) {
}
/**
 */
bool SLinuxEvent::Send() {
        return (eventfd_write (__fd, 1) == 0);
}
/**
 */
int SLinuxEvent::Clear() {
       eventfd_t val;
       eventfd_read(__fd, &val);
       return val;
}