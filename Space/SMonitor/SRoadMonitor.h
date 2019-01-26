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
    typename ADAPT=Monitor::Resource::SIndirect,
    typename BASE =Monitor::SDynamic
>
class SRoadMonitor 
: public SContainerMonitor<
    SRoad<KEY, OBJ>, Monitor::Container::SPair, SResourceMonitor<ADAPT, BASE>
> {
public:
    /**
     * ------------------------------------------------------------------------
     * helpers
     * ------------------------------------------------------------------------
     */
    using Super = SContainerMonitor<
        SRoad<KEY, OBJ>, Monitor::Container::SPair, SResourceMonitor<ADAPT, BASE>
    >;
    using Road = SRoad<
        KEY, OBJ
    >;
    /**
     * ------------------------------------------------------------------------
     * constructor
     * ------------------------------------------------------------------------
     */
    using Super::Super;
    /**
     * ------------------------------------------------------------------------
     * interfaces
     * ------------------------------------------------------------------------
     */
    inline SRoadMonitor& Insert(KEY k, OBJ o) {
        Road::Insert(std::forward<KEY>(k), std::forward<OBJ>(o));
        return *this;
    }
    inline SRoadMonitor Detach() {
        return move(*this);
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SROADMONITOR_H */

