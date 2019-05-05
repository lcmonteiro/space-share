/**
 * ------------------------------------------------------------------------------------------------
 * File:   SBaseModule.h
 * Author: Luis Monteiro
 *
 * Created on November 16, 2017, 5:59 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SBASEMODULE_H
#define SBASEMODULE_H
/**
 * module 
 */
#include "SHelpers/SConnectors.h"
#include "SHelpers/SFunctions.h"
/**
 * space
 */
#include "SClock.h"
#include "SRoadMonitor.h" 
/**
 * ------------------------------------------------------------------------------------------------
 * Extend Module Properties
 * ------------------------------------------------------------------------------------------------
 */
namespace Module {
using Property = const SText;
Property URI     = "uri";
Property ENERGY  = "energy";
Property VERBOSE = "verbose";
Property DELAY   = "delay";
Property TIMEOUT = "timeout";
}
/**
 * ------------------------------------------------------------------------------------------------
 *  Base Module
 * ------------------------------------------------------------------------------------------------
 */
class SBaseModule : public SModule {  
protected:
    using Clock            = SClock<>;
    using Timer            = Clock::Alarm;
    using ResourceMonitor  = SResourceMonitor<>;
    /**
     * ------------------------------------------------------------------------
     * Constructors
     * ------------------------------------------------------------------------
     **
     * default
     */
    SBaseModule(SBaseModule&&)            = default;
    SBaseModule& operator=(SBaseModule&&) = default;
    /** 
     * main
     */
    SBaseModule(const Command::Group& conf, const Command& cmd) 
        /**
         * configure
         */
    : SModule (
        conf.get(Module::URI, Val{}),   
        conf.get(Module::ENERGY,  1),  
        conf.get(Module::VERBOSE, 0)    
    ), __delay(
        conf.get(Module::DELAY,   0)    
    ), __timeout(
        conf.get(Module::TIMEOUT, 1000) 
    ) {  
        /**
         * added initial cmd
         */
        insert(cmd);            
    }
    /**
     * ------------------------------------------------------------------------
     * Callbacks
     * ------------------------------------------------------------------------
     */
    virtual State _process_machine(const State&, const Clock::Pointer&) = 0;
    virtual void  _process_command(const Command&                     ) = 0;
    /**
     * ------------------------------------------------------------------------
     * Execute
     * ------------------------------------------------------------------------
     */
    int _execute() override {
        Timer t(__delay, __timeout);
        /**
         * set in open state
         */
        state(OPEN);
        /**
         * run the precess
         */
        INFO("OPEN = {}");
        try {
            for(t.wait(); t.yield(); t.snooze()) {
                /**
                 * procces commands
                 */
                for(auto& c : _commands()) {
                    _process_command(c);
                }
                /**
                 * procces machine
                 */
                state(_process_machine(state(), t.trigger()));
            }
        }  catch (std::exception& ex) {
            /**
             * set in close state
             */
            state(CLOSE);
            ERROR("CLOSE = { what: " << ex.what() << " }");
            return -1;
        } catch (...) {
            /**
             * set in close state
             */
            state(CLOSE);
            ERROR("CLOSE = { }");
            return -1;
        }
        /**
         * set in close state
         */
        state(CLOSE);
        INFO("CLOSE = { }");
        return 0;
    }
    /**
     * ------------------------------------------------------------------------
     * Helpers
     * ------------------------------------------------------------------------
     * wait 
     */
    template<typename ROAD>
    inline State _process_wait(const Clock::Pointer& end, ROAD& r, State next) {
         for(Timer t(end, Clock::Distance(100)); !t.active(); t.sleep()) {
            try {
                r.update(); return next;
            } catch(RoadDetached& e) { }
        } 
        r.update(); return next;
    }
    /**
     * status
     */
    template<typename ROAD>
    std::string _status(ROAD& r) {
        std::ostringstream out;
        for (auto i = r.begin(), e = r.end(); i != e; ++i) {
            out << i->second->uri() << ' ';
        }
        return out.str();
    }
    /**
     * update
     */
    template<typename ROAD>
    void _update_road(ROAD& r, const Command::Group& o) {
         try { r.nominal(o.get<size_t>(Module::IO::NOMINAL)); } catch(...) {}
         try { r.minimum(o.get<size_t>(Module::IO::MINIMUM)); } catch(...) {}
    }
    private:
    /**
     * ------------------------------------------------------------------------
     * Variables
     * ------------------------------------------------------------------------
     * process delay
     */
    Clock::Distance __delay;
    /**
     * process max period
     */
    Clock::Distance __timeout;
};
/**
 *-------------------------------------------------------------------------------------------------
 * End
 *-------------------------------------------------------------------------------------------------
 */
#endif /* SBASEMODULE_H */

