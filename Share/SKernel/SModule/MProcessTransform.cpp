/*
 * File:   MProcessTransform.cpp
 * Author: Luis Monteiro
 *
 * Created on January 26, 2017, 5:59 PM
 **
 * ---------------------------------------------------------------------------------------------------------------------
 * Includes
 * ---------------------------------------------------------------------------------------------------------------------
 **
 * Module
 */
#include "MProcess.h"
#include "MConnectors.h"
#include "MFunctions.h"
/**
 * space kernel
 */
#include "SHash.h"
#include "SResourceMonitor.h"
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * Helpers
 * ---------------------------------------------------------------------------------------------------------------------
 * process command
 */
namespace SModule {
    template<class C, class I, class F, class O>
    void ProcessCommand(C& cmd, I& input, F& func, O& output) {
        using Command = typename C::Command;
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
                auto& in = input.Find(Command::template Peek<Key>(o, Properties::URI));
                // set energy
                in->SetEnergy(Command::template Peek<int>(o, Properties::ENERGY));
            } catch(range_error&) {
                using Builder = typename SInput::Builder<typename I::Object>;
                // build a new object
                input.Insert(Command::template Peek<Key>(o, Properties::URI), Builder::Build(o));
            }
        }
        /**
         * update function
         */
        for(auto& o : options["F"]) {
            try {
                // set energy
                func->SetEnergy(Command::template Peek<int>(o, Properties::ENERGY));
            } catch (range_error& ){
            
            }
        }
        /**
         * update outputs
         */
        for(auto& o : options["O"]) {       
            using Key = typename O::Key;
            try {
                auto& out = output.Find(Command::template Peek<Key>(o, Properties::URI));
                // set energy
                out->SetEnergy(Command::template Peek<int>(o, Properties::ENERGY));
            } catch(range_error&) {
                using Builder = typename SOutput::Builder<typename O::Object>;
                // build a new object
                output.Insert(Command::template Peek<Key>(o, Properties::URI), Builder::Build(o));
            }
        } 
    }
}
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * Main function
 * ---------------------------------------------------------------------------------------------------------------------
 */
template<class I, class D, class O>
int SModule::Process::Transform(const Function& opt, const Inputs& in_opt, const Outputs& out_opt) {
    /**
     * exceptions
     */
    using IRoadExceptionDETACHED = SRoadExceptionDETACHED<I>;
    using ORoadExceptionDETACHED = SRoadExceptionDETACHED<O>;
    /** 
     * connectors
     */
    using RoadMonitor = SRoadMonitor<SConnector::Key, I>;
    using Road        = SRoad<SConnector::Key, O>;
    /**
     * builders 
     */
    using IBuilder = SInput::Builder<I>;
    using TBuilder = STransform::Builder<I, D, O>;
    using OBuilder = SOutput::Builder<O>;
    /**
     * command monitor
     */
    CommandMonitor cmd(__uri, {"I", "O"});
    /**
     * input timeout
     */
    chrono::milliseconds timeout(Command::Peek(opt, Properties::TIMEOUT, 1000));
    /**
     * process delay
     */
    chrono::milliseconds delay(Command::Peek(opt, Properties::TIMEOUT, 10));
    /**
     */
    STask::Sleep(delay);
    /**
     * configure inputs
     */
    RoadMonitor in(timeout, 
        Command::Peek(opt, Properties::NOMINAL, in_opt.size()), 
        Command::Peek(opt, Properties::MINIMUM, Properties::NOMINAL, in_opt.size())
    );
    for(auto& o: in_opt) {
        in.Insert(Command::Peek<Key>(o, Properties::URI), IBuilder::Build(o));
    }
    /**
     * configure outputs
     */
    Road out(
        Command::Peek(opt, Properties::NOMINAL, in_opt.size()), 
        Command::Peek(opt, Properties::MINIMUM, Properties::NOMINAL, in_opt.size())
    );
    for(auto o: out_opt){
        out.Insert(Command::Peek<Key>(o, Properties::URI), OBuilder::Build(o));
    }
    /**
     * configure function
     */
    auto func = TBuilder::Build(opt);
    /**
     * Process
     */
    auto energy = Command::Peek(opt, Properties::ENERGY, size_t(1));
    /**
     * main loop 
     */
    while (STask::Sleep()) {
        try {
            /**
             * ---------------------------------------------------------------------------------------------
             * process
             * ---------------------------------------------------------------------------------------------
             */
            switch(GetState()) {
                default: {
                    SetState(OPEN);
                }
                case OPEN: {
                       /**
                    * ------------------------------------------------------------------------------
                    * OPEN State
                    * ------------------------------------------------------------------------------
                    */
                    out.Open();
                    SetState(OWAIT);
                }
                case OWAIT: {
                    /**
                     * -----------------------------------------------------------------------------
                     * OWAIT State
                     * -----------------------------------------------------------------------------
                     * check commands
                     */
                    if(!SResourceMonitor(&cmd).Check().empty()) {
                        ProcessCommand(cmd, in, func, out);
                    }
                    Update(timeout, out);
                    in.Open();
                    SetState(IWAIT);
                }
                case IWAIT: {
                    /**
                     * -----------------------------------------------------------------------------
                     * IWAIT State
                     * -----------------------------------------------------------------------------
                     * check commands
                     */
                    if(!SResourceMonitor(&cmd).Check().empty()) {
                        ProcessCommand(cmd, in, func, out);
                    }
                    Update(timeout, in);
                    SetState(PROCESS);
                }
                case PROCESS: {
                    /** 
                     * -----------------------------------------------------------------------------
                     * PROCESS State
                     * -----------------------------------------------------------------------------
                     * monitor commands and inputs
                     */
                    try {                           
                        for(auto& i : SResourceMonitor(timeout, &cmd, &in).Wait()) {
                            switch(i){
                                case 1: {
                                    ProcessCommand(cmd, in, func, out);
                                    break;
                                }
                                case 2: {
                                    func->Process(in, out);
                                    break;
                                }
                            }
                        }                        
                    } catch (MonitorExceptionTIMEOUT & ex) {
                        func->Drain(Update(timeout, out));
                        SetState(UPDATE);
                        throw;
                    }
                    SetState(UPDATE);
                }
                case UPDATE : {
                    /** 
                     * -----------------------------------------------------------------------------
                     * UPDATE State
                     * -----------------------------------------------------------------------------
                     * update IO
                     */
                    Update(timeout, in, out);
                    /**
                     */
                    SetState(PROCESS);
                }
            }
            /**
             */
        } catch (ORoadExceptionDETACHED & ex) {
            /**
             * log out status 
             */
            WARNING("OUT = {" << Status(out) << " }");
            /**
             */
            if(Kill(func, energy)){
                WARNING("Exit = { what: " << ex.what() << ", summary: " << Summary(in) << " }");
                return -1;
            }
            in.Close();
            SetState(OWAIT);
        }  catch (IRoadExceptionDETACHED & ex) {
            /**
             * log in status 
             */
            WARNING("IN = {" << Status(in) << " }");
            /**
             */
            if(Kill(func, energy)){
                WARNING("Exit = { what: " << ex.what() << ", summary: " << Summary(in) << " }");
                return -1;
            }
            SetState(IWAIT);
        } catch (MonitorExceptionTIMEOUT & ex) {
            
        } catch (exception& ex) {
            ERROR("Exit = { what: " << ex.what() << ", summary: " << Summary(in) << " }");
            return -1;
        } catch (...) {
            ERROR("Exit = { summary:" << Summary(in) << " }");
            return -1;
        }
        INFO("Process = { energy:" << energy << ", inputs:" << Status(in) << " }");
    }
    /**
     * Finish
     */
    INFO("Exit = { summary: " << Summary(in) << " }");
    return 0;
}
/**
 * template implementations
 */
template int SModule::Process::Transform<Decoded::IConnector, Container, Encoded::OConnector>(
    const SProcess::Function& opt, const SProcess::Inputs& in_opt, const SProcess::Outputs& out_opt
);
template int SModule::Process::Transform<Encoded::IConnector, Document, Decoded::OConnector>(
    const SProcess::Function& opt, const SProcess::Inputs& in_opt, const SProcess::Outputs& out_opt
);
/**
 * -------------------------------------------------------------------------------------------------------------
 * Utilities
 * -------------------------------------------------------------------------------------------------------------
 * full status
 */
template<class T>
string SModule::Process::Status(T& r) {
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
string SModule::Process::Summary(T& r) {
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