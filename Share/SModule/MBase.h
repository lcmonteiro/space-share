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
#include "SCommandMonitor.h"
#include "SLocalResource.h"  
/**
 *-------------------------------------------------------------------------------------------------
 * Module name space
 *-------------------------------------------------------------------------------------------------
 */
namespace Module {
/**
 */
class MBase : public SModule {  
public: 
    /**
     * --------------------------------------------------------------------------------------------
     * Identifires
     * --------------------------------------------------------------------------------------------
     * groups
     */
    const char* MODULE    = "M";
    const char* FUNCTION  = "F";
    const char* INOUT     = "X";
    const char* INPUT     = "I";
    const char* OUTPUT    = "O";
    /**
     * properties
     */
    const char* URI     = "uri";
    const char* ENERGY  = "energy";
    const char* VERBOSE = "verbose";
    const char* DELAY   = "delay";
    const char* TIMEOUT = "timeout";
protected:
    using Clock     = SClock<>;
    /**
     * --------------------------------------------------------------------------------------------
     * Constructors
     * --------------------------------------------------------------------------------------------
     * main constructor
     */
    MBase(
        SModule::Command::Group conf, SModule::Command cmd
    ) : SModule (
        conf.Get(URI, Val{}),   // default uri       -> {}
        conf.Get(ENERGY,  1),   // default energy    -> 1
        conf.Get(VERBOSE, 0)    // default verbosity -> 0
    ), __delay(
        conf.Get(DELAY, 0)      // default delay     -> 0
    ), __timeout(
        conf.Get(TIMEOUT, 1000) // default delay     -> 1s
    ) {  
        Insert(move(cmd));      // default command
    }
    /**
     * --------------------------------------------------------------------------------------------
     * Execute
     * --------------------------------------------------------------------------------------------
     */
    int Execute() override {
        // set in open state --------------------------------------------------
        SetState(OPEN);

        // delay the process --------------------------------------------------
        STask::Sleep(__delay);
        
        // run the precess ----------------------------------------------------
        INFO("RUN = {}");
        for(Clock::Alarm alarm(__timeout); STask::Sleep(); alarm.Snooze()){
            // procces commands -----------------------------------------------
            for(auto& c : __Commands()) {
                __ProcessCommand(c);
            }
            // procces machine -------------------------------------------------
            try {
                __ProcessMachine(alarm.Tigger());
            }  catch (exception& ex) {
                ERROR("END = { what: " << ex.what() << " }");
                return -1;
            } catch (...) {
                ERROR("END = {}");
                return -1;
            }
        }
        // set in close state
        SetState(CLOSE);
        INFO("END = {}");
        return 0;
    }
    virtual void __ProcessMachine(const Clock::Pointer&) {}
    virtual void __ProcessCommand(const Command&        ) {}
    /**
     * --------------------------------------------------------------------------------------------
     * Helpers
     * --------------------------------------------------------------------------------------------
     **
     * update resources 
     */
    template<class... R>
    void Update(const Clock::Pointer& end, R... resource) {
        for(Clock::Alarm a(end); !a.Active(); ){
            try {
                auto x = {(resource->Update(),0)...};
            } catch(RoadDetached& e) {
            }
        } 
    }
    /**
     * wait resources
     */
    inline vector<size_t> Wait(SResourceMonitor& monitor, const Clock::Pointer& end) {
        auto timeout = Clock::Remaining(end);
        if(timeout > Clock::Distance::zero()) {
            return monitor.Wait(timeout);
        }
        monitor = SResourceMonitor();
        return {};
    }
    /**
     * status
     */
    template<class T>
    string Status(T& r) {
        ostringstream out;
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

