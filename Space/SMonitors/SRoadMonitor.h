/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SRoadMonitor.h
 * Author: Luis Monteiro
 *
 * Created on January 21, 2019, 12:37 PM
 * ------------------------------------------------------------------------------------------------
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
    typename Key, 
    typename Obj, 
    typename Adapt = Monitor::Resource::SIndirect,
    typename Base  = Monitor::SDynamic
>
class SRoadMonitor 
: public SContainerMonitor<
    SRoad<Key, Obj>, Monitor::Container::SPair, SResourceMonitor<Adapt, Base>
> {
public:
    /**
     * ------------------------------------------------------------------------
     * Helpers
     * ------------------------------------------------------------------------
     */
    using Super = SContainerMonitor<
        SRoad<Key, Obj>, Monitor::Container::SPair, SResourceMonitor<Adapt, Base>>;
    using Road  = SRoad<Key, Obj>;
    /**
     * ------------------------------------------------------------------------
     * Constructor
     * ------------------------------------------------------------------------
     */
    using Super::Super;
    /**
     * ------------------------------------------------------------------------
     * Interfaces
     * ------------------------------------------------------------------------
     * Insert
     * ---------------------------------------------------- 
     */
    inline SRoadMonitor& insert(Key k, Obj o) {
        Road::insert(
            std::forward<Key>(k), 
            std::forward<Obj>(o));
        return *this;
    }
    /**
     * ----------------------------------------------------
     * Update
     * ----------------------------------------------------
     */
    inline SRoadMonitor& update() {
        Road::update();
        Super::update();
        return *this;
    }
    /**
     * ----------------------------------------------------
     * Detach
     * ----------------------------------------------------
     */
    inline SRoadMonitor detach() {
        return std::move(*this);
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SROADMONITOR_H */
