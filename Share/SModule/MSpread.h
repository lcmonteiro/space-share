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
     * exception types
     */
    using IRoadExceptionDETACHED = SRoadExceptionDETACHED<I>;
    using ORoadExceptionDETACHED = SRoadExceptionDETACHED<O>;
    /**
     * builder types
     */
    using IBuilder = Input::Builder<I>;
    using FBuilder = Spread::Builder<I, D, O>;
    using OBuilder = Output::Builder<O>; 
    /** 
     * connector types
     */
    using RoadMonitor = SRoadMonitor<SConnector::Key, I>;
    using Road        = SRoad<SConnector::Key, O>;
    /**
     * function type
     */
    using Function = typename FBuilder::Pointer;
public:
    /**
     * --------------------------------------------------------------------------------------------
     * constructor
     * --------------------------------------------------------------------------------------------
     */
    MSpread(const Command& cmd): MBasis(cmd), 
    // delay start
    __delay(
        cmd[""][0].get(Properties::DELAY, 10)
    ),
    // module energy 
    __energy(
        cmd[""][0].get(Properties::ENERGY, 1)
    ),
    // module time
    __timeout(
        cmd[""][0].get(Properties::TIMEOUT, 1000)
    ),
    // input connections
    __in(
        cmd[""][0].get(Properties::TIMEOUT, 10), 
        cmd[""][0].get(Properties::NOMINAL, cmd["I"].size()),
        cmd[""][0].get(Properties::MINIMUM, Properties::NOMINAL, cmd["I"].size())
    ),
    // output connections
    __out(
        cmd[""][0].get(Properties::NOMINAL, cmd["O"].size()),
        cmd[""][0].get(Properties::MINIMUM, Properties::NOMINAL, cmd["O"].size())
    ){}
protected:
    /**
     * -----------------------------------------------------------------------------------------------------------------
     * Variables
     * -----------------------------------------------------------------------------------------------------------------
     * module energy
     */
    size_t __energy;
    /**
     * process delay
     */
    chrono::milliseconds __delay;
    /**
     * process timeout
     */
    chrono::milliseconds __timeout;
    /**
     * inputs
     */
    RoadMonitor __in;
    /**
     * outputs
     */
    Road __out;
    /**
     */
    Function __pfunc;
    /**
     * -----------------------------------------------------------------------------------------------------------------
     * Execute
     * -----------------------------------------------------------------------------------------------------------------
     * init execution
     */
    void __init() {
        // delay the process
        STask::Sleep(__delay);
        // create and insert inputs
        for(auto& o: __cmd["I"]) {
            __in.Insert(o[Properties::URI], IBuilder::Build(o));
        }
        // create and insert outputs
        for(auto o: __cmd["O"]) {
            __out.Insert(o[Properties::URI], OBuilder::Build(o));
        }
        // create and assigned function
        __pfunc = FBuilder::Build(__cmd["F"][0]);
    }
    /**
     * process
     */
    void __process() override {
        // procces commands
        while(!SResourceMonitor(&__monitor).Check().empty()) {
            ProcessCommand(__in, __pfunc, __out);
        }
        // state machine
        INFO("Process={ energy:" << __energy << ", inputs:" << Status(__in) << " }");
        try {
            switch(GetState()) {
                default: {
                    SetState(OPEN);
                }
                case OPEN: {
                    __out.Open();
                    SetState(OWAIT);
                }
                case OWAIT: {
                    Update(__timeout, __out);
                    __in.Open();
                    SetState(IWAIT);
                }
                case IWAIT: {
                    Update(__timeout, __in);
                    SetState(PROCESS);
                }
                case PROCESS: {
                    try {                           
                        for(auto& i : SResourceMonitor(__timeout, &__monitor, &__in).Wait()) {
                            switch(i){
                                case 2: {
                                    while(true) {
                                        __pfunc->Process(__in, __out);    
                                    }
                                    break;
                                }
                            }
                        }                        
                    } catch (MonitorExceptionTIMEOUT & ex) {
                        __pfunc->Drain(Update(__timeout, __out));
                    }
                    SetState(UPDATE);
                }
                case UPDATE : {
                    Update(__timeout, __in, __out);
                    SetState(PROCESS);
                }
            }
        } catch (ORoadExceptionDETACHED & ex) {
            WARNING("OUT={ " << Status(__out) << " }");
            if(Kill(__pfunc, __energy)){
                WARNING("Exit={ what: " << ex.what() << ", summary: " << Summary(__in) << "}");
                throw;
            }
            __in.Close();
            SetState(OWAIT);
        }  catch (IRoadExceptionDETACHED & ex) {
            WARNING("IN = {" << Status(__in) << " }");
            if(Kill(__pfunc, __energy)){
                WARNING("Exit={ what: " << ex.what() << ", summary: " << Summary(__in) << "}");
                throw;
            }
            SetState(IWAIT);
        }
    }
    // int Execute(const Command& cmd) override {
    //     /**
    //      * input timeout
    //      */
    //     chrono::milliseconds timeout(cmd[""][0].get(Properties::TIMEOUT, 1000));
    //     /**
    //      * process delay
    //      */
    //     chrono::milliseconds delay(cmd[""][0].get(Properties::TIMEOUT, 10));
    //     STask::Sleep(delay);
    //     /**
    //      * configure inputs
    //      */
    //     RoadMonitor in(timeout, 
    //         cmd[""][0].get(Properties::NOMINAL, cmd["I"].size()), 
    //         cmd[""][0].get(Properties::MINIMUM, Properties::NOMINAL, cmd["I"].size())
    //     );
    //     for(auto& o: cmd["I"]) {
    //         in.Insert(o[Properties::URI], IBuilder::Build(o));
    //     }
    //     /**
    //      * configure outputs
    //      */
    //     Road out(
    //         cmd[""][0].get(Properties::NOMINAL, cmd["O"].size()), 
    //         cmd[""][0].get(Properties::MINIMUM, Properties::NOMINAL, cmd["O"].size())
    //     );
    //     for(auto o: cmd["O"]) {
    //         out.Insert(o[Properties::URI], OBuilder::Build(o));
    //     }
    //     /**
    //      * configure function
    //      */
    //     auto func = TBuilder::Build(cmd["F"][0]);
    //     /**
    //      * Process
    //      */
    //     auto energy = cmd[""][0].get(Properties::ENERGY, size_t(1));
    //     /**
    //      * main loop 
    //      */
    //     while (STask::Sleep()) {
    //         try {
    //             /**
    //              * ---------------------------------------------------------------------------------------------
    //              * process
    //              * ---------------------------------------------------------------------------------------------
    //              */
    //             switch(GetState()) {
    //                 default: {
    //                     SetState(OPEN);
    //                 }
    //                 case OPEN: {
    //                     out.Open();
    //                     SetState(OWAIT);
    //                 }
    //                 case OWAIT: {
    //                     /**
    //                      * check commands
    //                      */
    //                     if(!SResourceMonitor(&__cmd).Check().empty()) {
    //                         ProcessCommand(__cmd, in, func, out);
    //                     }
    //                     Update(timeout, out);
    //                     in.Open();
    //                     SetState(IWAIT);
    //                 }
    //                 case IWAIT: {
    //                     /**
    //                      * check commands
    //                      */
    //                     if(!SResourceMonitor(&__cmd).Check().empty()) {
    //                         ProcessCommand(__cmd, in, func, out);
    //                     }
    //                     Update(timeout, in);
    //                     SetState(PROCESS);
    //                 }
    //                 case PROCESS: {
    //                     /** 
    //                      * monitor commands and inputs
    //                      */
    //                     try { 
    //                         for(auto& i : SResourceMonitor(timeout, &__cmd, &in).Wait()) {
    //                             switch(i){
    //                                 case 1: {
    //                                     ProcessCommand(__cmd, in, func, out);
    //                                     break;
    //                                 }
    //                                 case 2: {
    //                                     func->Process(in, out);
    //                                     break;
    //                                 }
    //                             }
    //                         }                        
    //                     } catch (MonitorExceptionTIMEOUT & ex) {
    //                         func->Drain(Update(timeout, out));
    //                         SetState(UPDATE);
    //                         throw;
    //                     }
    //                     SetState(UPDATE);
    //                 }
    //                 case UPDATE : {
    //                     Update(timeout, in, out);
    //                     SetState(PROCESS);
    //                 }
    //             }
    //         } 
    //         /**----------------------------------------------------------------------------------------
    //          * exceptions
    //          *---------------------------------------------------------------------------------------**/
    //         catch (ORoadExceptionDETACHED & ex) {
    //             WARNING("OUT = {" << Status(out) << " }");
    //             if(Kill(func, energy)){
    //                 WARNING("Exit = { what: " << ex.what() << ", summary: " << Summary(in) << " }");
    //                 return -1;
    //             }
    //             in.Close();
    //             SetState(OWAIT);
    //         }  catch (IRoadExceptionDETACHED & ex) {
    //             WARNING("IN = {" << Status(in) << " }");
    //             if(Kill(func, energy)){
    //                 WARNING("Exit = { what: " << ex.what() << ", summary: " << Summary(in) << " }");
    //                 return -1;
    //             }
    //             SetState(IWAIT);
    //         } catch (MonitorExceptionTIMEOUT & ex) {
                
    //         } catch (exception& ex) {
    //             ERROR("Exit = { what: " << ex.what() << ", summary: " << Summary(in) << " }");
    //             return -1;
    //         } catch (...) {
    //             ERROR("Exit = { summary:" << Summary(in) << " }");
    //             return -1;
    //         }
    //         INFO("Process = { energy:" << energy << ", inputs:" << Status(in) << " }");
    //     }
    //     /**
    //      * Finish
    //      */
    //     INFO("Exit = { summary: " << Summary(in) << " }");
    //     return 0;
    // }
};
}
#endif /* MSPREAD_H */

