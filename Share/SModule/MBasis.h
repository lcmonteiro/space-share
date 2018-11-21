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
     * monitor
     * ----------------------------------------------------------------------------------------------------------------
     */
    SCommandMonitor<Command, Message::SLocalResource> __monitor;
    /**
     * processe comand 
     */
    template<class I, class F, class O>
    void ProcessCommand(I& input, F& func, O& output) {
        /**
         * unserialize command
         */
        auto cmd = __monitor.Read();
        /**
         * update inputs
         */
        for(auto& o : cmd["I"]) {     
            using Key = typename I::Key;
            try {
                auto& in = input.Find(o[URI]);
                // set energy
                // in->SetEnergy(o.get<int>(ENERGY));
            } catch(range_error&) {
                using Builder = typename Module::Input::Builder<typename I::Object>;
                // build a new object
                input.Insert(o[URI], Builder::Build(o));
            }
        }
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
        /**
         * update outputs
         */
        for(auto& o : cmd["O"]) {       
            using Key = typename O::Key;
            try {
                auto& out = output.Find(o[URI]);
                // set energy
                //out->SetEnergy(o[ENERGY]);
            } catch(range_error&) {
                using Builder = typename Output::Builder<typename O::Object>;
                // build a new object
                output.Insert(o[URI], Builder::Build(o));
            }
        } 
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

