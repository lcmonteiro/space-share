/** 
 * File:   MSpread.h
 * Author: Luis Monteiro
 *
 * Created on November 16, 2018, 5:59 PM
 */
#ifndef MSPREAD_H
#define MSPREAD_H
/**
 * Module
 */
#include "MBasis.h" 
/**
 *----------------------------------------------------------------------------------------------------------------------
 * Module name space
 *----------------------------------------------------------------------------------------------------------------------
 */
namespace Module {
/**
 */
template<class I, class D, class O>
class MSpread : public MBasis {
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
    using IBuilder = Input::Builder<I>;
    using TBuilder = Spread::Builder<I, D, O>;
    using OBuilder = Output::Builder<O>;  
public:   
    using MBasis::MBasis;
protected:
    /**
     * -----------------------------------------------------------------------------------------------------------------
     * Execute
     * -----------------------------------------------------------------------------------------------------------------
     */
    int Execute(const Command& cmd) override {
        /**
         * input timeout
         */
        chrono::milliseconds timeout(cmd[""][0].get(Properties::TIMEOUT, 1000));
        /**
         * process delay
         */
        chrono::milliseconds delay(cmd[""][0].get(Properties::TIMEOUT, 10));
        STask::Sleep(delay);
        /**
         * configure inputs
         */
        RoadMonitor in(timeout, 
            cmd[""][0].get(Properties::NOMINAL, cmd["I"].size()), 
            cmd[""][0].get(Properties::MINIMUM, Properties::NOMINAL, cmd["I"].size())
        );
        for(auto& o: cmd["I"]) {
            in.Insert(o[Properties::URI], IBuilder::Build(o));
        }
        /**
         * configure outputs
         */
        Road out(
            cmd[""][0].get(Properties::NOMINAL, cmd["O"].size()), 
            cmd[""][0].get(Properties::MINIMUM, Properties::NOMINAL, cmd["O"].size())
        );
        for(auto o: cmd["O"]) {
            out.Insert(o[Properties::URI], OBuilder::Build(o));
        }
        /**
         * configure function
         */
        auto func = TBuilder::Build(cmd["F"][0]);
        /**
         * Process
         */
        auto energy = cmd[""][0].get(Properties::ENERGY, size_t(1));
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
                        out.Open();
                        SetState(OWAIT);
                    }
                    case OWAIT: {
                        /**
                         * check commands
                         */
                        if(!SResourceMonitor(&__cmd).Check().empty()) {
                            ProcessCommand(__cmd, in, func, out);
                        }
                        Update(timeout, out);
                        in.Open();
                        SetState(IWAIT);
                    }
                    case IWAIT: {
                        /**
                         * check commands
                         */
                        if(!SResourceMonitor(&__cmd).Check().empty()) {
                            ProcessCommand(__cmd, in, func, out);
                        }
                        Update(timeout, in);
                        SetState(PROCESS);
                    }
                    case PROCESS: {
                        /** 
                         * monitor commands and inputs
                         */
                        try {                           
                            for(auto& i : SResourceMonitor(timeout, &__cmd, &in).Wait()) {
                                switch(i){
                                    case 1: {
                                        ProcessCommand(__cmd, in, func, out);
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
                        Update(timeout, in, out);
                        SetState(PROCESS);
                    }
                }
            } 
            /**----------------------------------------------------------------------------------------
             * exceptions
             *---------------------------------------------------------------------------------------**/
            catch (ORoadExceptionDETACHED & ex) {
                WARNING("OUT = {" << Status(out) << " }");
                if(Kill(func, energy)){
                    WARNING("Exit = { what: " << ex.what() << ", summary: " << Summary(in) << " }");
                    return -1;
                }
                in.Close();
                SetState(OWAIT);
            }  catch (IRoadExceptionDETACHED & ex) {
                WARNING("IN = {" << Status(in) << " }");
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
};
}
#endif /* MSPREAD_H */

