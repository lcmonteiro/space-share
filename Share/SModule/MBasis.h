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
    MBasis(const Command& cmd): SModule(cmd), __cmd(__uri) {}
protected:
    /**
     * monitor
     */
    SCommandMonitor<Command, Message::SLocalResource> __cmd;
    /**
     * processe comand 
     */
    template<class C, class I, class F, class O>
    void ProcessCommand(C& cmd, I& input, F& func, O& output) {
        /**
         * unserialize command
         */
        auto options = cmd.Read();
        /**
         * update inputs
         */
        for(auto& o : options["I"]) {     
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
        for(auto& o : options["F"]) {
            try {
                // set energy
                //func->SetEnergy(o[ENERGY]);
            } catch (range_error& ){
            
            }
        }
        /**
         * update outputs
         */
        for(auto& o : options["O"]) {       
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

