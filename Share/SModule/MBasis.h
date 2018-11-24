/** 
 * File:   MBasis.h
 * Author: Luis Monteiro
 *
 * Created on November 16, 2017, 5:59 PM
 */
#ifndef MBASIS
#define MBASIS
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
class MBasis : public SModule {  
public:   
    /**
     * -------------------------------------------------------------------------------------------------------------
     * Constructors
     * -------------------------------------------------------------------------------------------------------------
     * main constructor
     */
    MBasis(const Command& cmd): SModule(cmd), __monitor(__uri){}
protected:
    /**
     * -----------------------------------------------------------------------------------------------------------------
     * Execute
     * -----------------------------------------------------------------------------------------------------------------
     */
    int Execute() override {
        INFO("INI = {}");
        __init();
        INFO("RUN = {}");
        while(true) {
            try {
                __process();
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
    virtual void __process() {}
    /**
     * ----------------------------------------------------------------------------------------------------------------
     * process command
     * ----------------------------------------------------------------------------------------------------------------
     */
    SCommandMonitor<Command, Message::SLocalResource> __monitor;
    /**
     * unserialize command
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
     * update resources 
     */
    template<class P, class... R>
    void Update(chrono::milliseconds timeout, P process, R&... resource) {
        using Clock = chrono::steady_clock;
        using Engine = default_random_engine;
        using Distribuition = uniform_int_distribution<>;
        /**
         * waiting loop 
         */
        auto gen = Engine{random_device{}()}; 
        auto dis = Distribuition{100, 500}; 
        auto end = Clock::now() + timeout; 
        do {
            try {
                auto x = {(resource.Update(),0)...};
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
     * 
     */
    template<class T>
    string Status(T& r) {
        ostringstream out;
        /**
         * get information 
         */
    //    auto info = r.Sizes();
    //    /**
    //     *  print good
    //     */
    //    size_t good = 0; 
    //    for (auto& s : info.first) {
    //        good += s;
    //        out << std::setw(2) << s << ' ';
    //    }
    //    out << '\t' << '\t';
    //    /**
    //     * print bad 
    //     */
    //    size_t bad = 0;
    //    for (auto& s : info.second) {
    //        bad += s;
    //        out << std::setw(2) << s << ' ';
    //    }
    //    out <<'\t' << '(' << good << '/' << bad << ')' << '\t' << float(good) / float(good + bad);
        /**/
        return out.str();
    }

    template<class T>
    string Summary(T& r) {
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
#endif /* MBASIS */

