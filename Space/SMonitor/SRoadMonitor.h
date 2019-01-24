/* 
 * Container:   SRoadMonitor.h
 * Author: Luis Monteiro
 *
 * Created on January 21, 2019, 12:37 PM
 */
#ifndef SROADMONITOR_H
#define SROADMONITOR_H
/**
 * space
 */
#include "SContainerMonitor.h"
#include "SRoad.h"
/**
 * -------------------------------------------------------------------------------------------------
 * Road monitor
 * -------------------------------------------------------------------------------------------------
 */
template<
    typename KEY, 
    typename OBJ, 
    typename ADAPT=Monitor::SIndirect,
    typename BASE =Monitor::SDynamic
>
class SRoadMonitor 
: public SContainerMonitor<SRoad<KEY, OBJ>, SResourceMonitor<ADAPT, BASE>> {
    using Super = SContainerMonitor<SRoad<KEY, OBJ>, SResourceMonitor<ADAPT, BASE>>;
public:
    using Super::Super;
    using Road = SRoad<KEY, OBJ>;
};
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SROADMONITOR_H */

