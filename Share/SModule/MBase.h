/** 
 * File:   MBase.h
 * Author: Luis Monteiro
 *
 * Created on November 16, 2017, 5:59 PM
 */
#ifndef MBASE_H
#define MBASE_H
/**
 * module 
 */
#include "MConnectors.h"
#include "MFunctions.h"
/**
 * space
 */
#include "SClock.h"
#include "SRoadMonitor.h" 
/**
 *-------------------------------------------------------------------------------------------------
 * module namespace
 *-------------------------------------------------------------------------------------------------
 */
namespace Module {
using Property = const SText;
/**
 * ------------------------------------------------------------------------------------------------
 * properties
 * ------------------------------------------------------------------------------------------------
 */
Property URI     = "uri";
Property ENERGY  = "energy";
Property VERBOSE = "verbose";
Property DELAY   = "delay";
Property TIMEOUT = "timeout";
/**
 * ------------------------------------------------------------------------------------------------
 *  module base
 * ------------------------------------------------------------------------------------------------
 */
class MBase : public SModule {  
protected:
    using Clock            = SClock<>;
    using Timer            = Clock::Alarm;
    using ResourceMonitor  = SResourceMonitor<>;
    /**
     * ------------------------------------------------------------------------
     * defaults
     * ------------------------------------------------------------------------
     */
    MBase(MBase&&)            = default;
    MBase& operator=(MBase&&) = default;
    /**
     * --------------------------------------------------------------------------------------------
     * Constructors
     * --------------------------------------------------------------------------------------------
     * main constructor
     */
    MBase(const Command::Group& conf, const Command& cmd) 
    // configure --------------------------------------------------------------
    : SModule (
        conf.Get(URI, Val{}),   // default uri       -> {}
        conf.Get(ENERGY,  1),   // default energy    -> 1
        conf.Get(VERBOSE, 0)    // default verbosity -> 0
    ), __delay(
        conf.Get(DELAY, 0)      // default delay     -> 0
    ), __timeout(
        conf.Get(TIMEOUT, 1000) // default delay     -> 1s
    ) {  
        // added first cmd ----------------------------------------------------
        Insert(cmd);            
    }
    /**
     * --------------------------------------------------------------------------------------------
     * Execute
     * --------------------------------------------------------------------------------------------
     */
    int Execute() override {
        Timer t(__delay, __timeout);

        // set in open state --------------------------------------------------
        SetState(OPEN);
        
        // run the precess ----------------------------------------------------
        INFO("OPEN = {}");
        for(t.Wait(); t.Yield(); t.Snooze()) {
        
            // procces commands -----------------------------------------------
            for(auto& c : __Commands()) {
                __ProcessCommand(c);
            }
            // procces machine ------------------------------------------------
            try {
                SetState(__ProcessMachine(GetState(), t.Tigger()));
            }  catch (exception& ex) {
        
                // set in close state -----------------------------------------
                SetState(CLOSE);
                ERROR("CLOSE = { what: " << ex.what() << " }");
                return -1;
            } catch (...) {
        
                // set in close state -----------------------------------------
                SetState(CLOSE);
                ERROR("CLOSE = { }");
                return -1;
            }
        }
        // set in close state -------------------------------------------------
        SetState(CLOSE);
        INFO("CLOSE = { }");
        return 0;
    }
    virtual State __ProcessMachine(const State&, const Clock::Pointer&) = 0;
    virtual void  __ProcessCommand(const Command&                     ) = 0;
    /**
     * --------------------------------------------------------------------------------------------
     * Helpers
     * --------------------------------------------------------------------------------------------
     **
     * update resources 
     */
    template<class... R>
    void Update(const Clock::Pointer& end, R... resource) {
        for(Clock::Alarm a(end); !a.Active(); STask::Sleep()) {
            try {
                auto x = {(resource->Update(),0)...};
                return;
            } catch(RoadDetached& e) {
            }
        } 
    }
    /**
     * wait resources
     */
    inline std::list<size_t> Wait(ResourceMonitor& monitor, const Clock::Pointer& end) {
        auto timeout = Clock::Remaining(end);
        if(timeout > Clock::Distance::zero()) {
            return monitor.Wait(timeout);
        }
        return {};
    }
    /**
     * status
     */
    template<class T>
    std::string Status(T& r) {
        std::ostringstream out;
        for (auto i = r.begin(), e = r.end(); i != e; ++i) {
            out << i->second->Uri() << ' ';
        }
        return out.str();
    }
    private:
    /**
     * --------------------------------------------------------------------------------------------
     * Variables
     * --------------------------------------------------------------------------------------------
     * process delay
     */
    Clock::Distance __delay;
    /**
     * process max period
     */
    Clock::Distance __timeout;
};
}
/**
 *-------------------------------------------------------------------------------------------------
 * end
 *-------------------------------------------------------------------------------------------------
 */
#endif /* MBASE_H */

