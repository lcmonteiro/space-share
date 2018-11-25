/** 
 * File:   MDefault.h
 * Author: Luis Monteiro
 *
 * Created on November 16, 2017, 5:59 PM
 */
#ifndef MDEFAULT
#define MDEFAULT
/**
 * Builders
 */
#include "MConnectors.h"
#include "MFunctions.h"
/**
 * space monitor
 */
#include "SRoadMonitor.h"
#include "SCommandMonitor.h"
/**
 * space resource
 */
#include "SLocalResource.h"  
/**
 *----------------------------------------------------------------------------------------------------------------------
 * Module name space
 *----------------------------------------------------------------------------------------------------------------------
 */
namespace Module {
/**
 */
class MDefault : public SModule {  
public:   
    /**
     * -------------------------------------------------------------------------------------------------------------
     * Constructors
     * -------------------------------------------------------------------------------------------------------------
     * main constructor
     */
    MDefault(const Command& cmd): SModule(cmd), 
    // delay start
    __delay(
        cmd[""][0].get(Properties::DELAY, 10)
    ),
    // module max period
    __timeout(
        cmd[""][0].get(Properties::TIMEOUT, 1000)
    ),
    // monitor
    __monitor(__uri){}
protected:
    using Clock     = chrono::steady_clock;
    using TimePoint = Clock::time_point;
    /**
     * -----------------------------------------------------------------------------------------------------------------
     * Variables
     * -----------------------------------------------------------------------------------------------------------------
     * process delay
     */
    chrono::milliseconds __delay;
    /**
     * process max period
     */
    chrono::milliseconds __timeout;
    /**
     * -----------------------------------------------------------------------------------------------------------------
     * Execute
     * -----------------------------------------------------------------------------------------------------------------
     */
    int Execute() override {
        INFO("INI = {}");
        // delay the process
        STask::Sleep(__delay);
        // init the process 
        __init();
        // run the precess
        INFO("RUN = {}");
        while(true) {
            TimePoint end = Clock::now() + __timeout;
            try {
                __process(end);
            }  catch (exception& ex) {
                ERROR("END = { what: " << ex.what() << " }");
                return -1;
            } catch (...) {
                ERROR("END = {}");
                return -1;
            }
        }
        INFO("END = {}");
        return 0;
    }
    virtual void __init() {}
    virtual void __process(const TimePoint& end) {}
    /**
     * ----------------------------------------------------------------------------------------------------------------
     * process command
     * ----------------------------------------------------------------------------------------------------------------
     */
    SCommandMonitor<Command, Message::SLocalResource> __monitor;
    /**
     * command unserialize 
     */
    inline Command ReadCommand() {
        return __monitor.Read();
    } 
    /**
     * update inputs
     */
    template<class I>
    Command UpdateInputs(I& input, Command&& cmd) { 
        for(auto& o : cmd["I"]) {     
            using Key = typename I::Key;
            try {
                auto& in = input.Find(o[URI]);
                // set energy
                in->SetEnergy(o.get<int>(ENERGY));
            } catch(range_error&) {
                using Builder = typename Module::Input::Builder<typename I::Object>;
                // build a new object
                input.Insert(o[URI], Builder::Build(o));
            }
        }
        return cmd;
    }
    /**
     * update outputs
     */
    template<class O>
    Command UpdateOutputs(O& output, Command&& cmd) {
        for(auto& o : cmd["O"]) {       
            using Key = typename O::Key;
            try {
                auto& out = output.Find(o[URI]);
                // set energy
                out->SetEnergy(o.get<int>(ENERGY));
            } catch(range_error&) {
                using Builder = typename Output::Builder<typename O::Object>;
                // build a new object
                output.Insert(o[URI], Builder::Build(o));
            }
        }
        return cmd; 
    }
    /**
     * update function
     */
    template<class F>
    Command UpdateFunction(F& func, Command&& cmd) {
        /**
         * update function
         */
        for(auto& o : cmd["F"]) {
            try {
                // set energy
                //func->SetEnergy(o[ENERGY]);
            } catch (range_error& ){
            
            }
        }
        return cmd;
    }
    /**
     * command monitor
     */
    template<class P, class... R>
    bool Monitor(const TimePoint& end, P process, R... resource) {
        auto timeout = chrono::duration_cast<chrono::milliseconds>(end-Clock::now());
        for(auto& i : SResourceMonitor(timeout, &__monitor, forward<R>(resource)...).Wait()) {
            switch(i) {
                case 1: {
                    // process commad
                    process();
                    break;
                }
                default: {
                    // process resources
                    return true;
                }
            }
        }
        return false; 
    }
    /**
     * update resources 
     */
    template<class P, class... R>
    void Update(const TimePoint& end, P process, R... resource) {
        using Engine = default_random_engine;
        using Distribuition = uniform_int_distribution<>;
        /**
         * waiting loop 
         */
        auto gen = Engine{random_device{}()}; 
        auto dis = Distribuition{100, 500}; 
        do {
            try {
                auto x = {(resource->Update(),0)...};
            } catch(RoadDetached& e) {
                // check if a command arrive in random time 
                try {
                    // wait    command
                    SResourceMonitor(chrono::milliseconds(dis(gen)), &__monitor).Wait();
                    // process commad
                    process();
                } catch(MonitorExceptionTIMEOUT& ) {
                    continue;
                }
            }
        } while(Clock::now() < end);
    }
    /**
     * get status summary of module
     */
    template<class T>
    string Status(T& r) {
        ostringstream out;
        /**
         *  print good
         */
        out << "Good: ";
        for (auto i = r.begin(), e = r.end(); i != e; ++i) {
            out << i->second->Uri() << ' ';
        }
        /**
         * print bad 
         */
    //    out << '\t' << "Bad: ";
    //    for (auto i = r.rbegin(), e = r.rend(); i != e; ++i) {
    //        out << i->second->Id() << ' ';        
    //    }
        /**/
        return out.str();
    }

};
}
#endif /* MDEFAULT */

