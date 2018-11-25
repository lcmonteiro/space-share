/** 
 * File:   MSpliter.h
 * Author: Luis Monteiro
 *
 * Created on January 26, 2017, 5:59 PM
 */
#ifndef MSPLITER_H
#define MSPLITER_H
/**
 * Module
 */
#include "MDefault.h"
/**
 *----------------------------------------------------------------------------------------------------------------------
 * Module name space
 *----------------------------------------------------------------------------------------------------------------------
 */
namespace Module {
/**
 */
template<class IO, class I, class O>
class MSpliter : public MDefault {
    /**
     * exception types
     */
    using IORoadExceptionDETACHED = SRoadExceptionDETACHED<IO>;
    using IRoadExceptionDETACHED  = SRoadExceptionDETACHED<I>;
    using ORoadExceptionDETACHED  = SRoadExceptionDETACHED<O>;
    /**
     * builders 
     */
    using IOBuilder = IOput::Builder<IO>;
    using IBuilder  = Input::Builder<I>;
    using OBuilder  = Output::Builder<O>;
    using FBuilder  = Spliter::Builder<IO, I, O>; 
    /** 
     * connector types
     */
    using IORoad = SRoadMonitor<SConnector::Key, IO>;
    using IRoad  = SRoadMonitor<SConnector::Key, I>;
    using ORoad  = SRoad<SConnector::Key, O>; 
    /**
     * function type
     */
    using Function = typename FBuilder::Pointer;
public:   
    using MDefault::MDefault;
protected:
    /**
     * -----------------------------------------------------------------------------------------------------------------
     * Variables
     * -----------------------------------------------------------------------------------------------------------------
     * input/output
     */
    IORoad __io;
    /**
     * input
     */
    IRoad __in;
    /**
     * input
     */
    ORoad __out;
    /**
     */
    Function __func;
    /**
     * -----------------------------------------------------------------------------------------------------------------
     * Execute
     * -----------------------------------------------------------------------------------------------------------------
     * init execution
     */
    void __init() {
        // create and insert input/outputs
        for(auto& o: __cmd["X"]) {
            __in.Insert(o[Properties::URI], IBuilder::Build(o));
        }
        // create and insert inputs
        for(auto& o: __cmd["I"]) {
            __in.Insert(o[Properties::URI], IBuilder::Build(o));
        }
        // create and insert outputs
        for(auto o: __cmd["O"]) {
            __out.Insert(o[Properties::URI], OBuilder::Build(o));
        }
        // create and assigned function
        __func = FBuilder::Build(__cmd["F"][0]);
    }
    /**
     * process execution
     */
    void __process(const TimePoint& end) override {
        // procces commands
        auto ProcessCmd = [this]() {
            UpdateFunction(
                //UpdateIOputs(__io,
                __func, UpdateOutputs(__out, UpdateInputs(__in, ReadCommand()))
                //)
            );
        };
        // state machine
        INFO("Process={ energy:" << SEnergy::Get() << ", inputs:" << Status(__in) << " }");
        try {
            switch(GetState()) {
                default: {
                    SetState(OPEN);
                    break;
                }
                case OPEN: {
                    __out.Open();
                    SetState(OWAIT);
                    break;
                }
                case OWAIT: {
                    Update(end, ProcessCmd, &__out);
                    __in.Open();
                    SetState(IWAIT);
                    break;
                }
                case IWAIT: {
                    Update(end, ProcessCmd, &__in);
                    SetState(PROCESS);
                    break;
                }
                case PROCESS: {
                    try { 
                        if(Monitor(end, ProcessCmd, &__in)){
                            try{
                                while(Clock::now() < end) {
                                    __func->Process(__io, __in, __out);
                                }
                            } catch (MonitorExceptionTIMEOUT & ex) {
                                //TODO: print
                            }
                        }                        
                    } catch (MonitorExceptionTIMEOUT & ex) {
                        //__func->Drain(__out);
                        __func->Decay();
                    }
                    SetState(UPDATE);
                    break;
                }
                case UPDATE : {
                    Update(end, ProcessCmd, &__in, &__out);
                    SetState(PROCESS);
                    break;
                }
            }
        }
        // state machine exceptions
        catch (ORoadExceptionDETACHED & ex) {
            WARNING("OUT = { " << Status(__out) << " }");
            if(IsState(PROCESS)) {
                SEnergy::Decay();
            }
            __func->Recover();
            __in.Close();
            SetState(OWAIT);
        } catch (IRoadExceptionDETACHED & ex) {
            WARNING("IN = {" << Status(__in) << " }");
            if(IsState(PROCESS)) {
                SEnergy::Decay();
            }
            __func->Recover();
            SetState(IWAIT);
        } catch (FunctionExceptionDEAD& ex) {
            SEnergy::Decay();
            __func->Recover();
        }
    }

    /**
     * -----------------------------------------------------------------------------------------------------------------
     * Execute
     * -----------------------------------------------------------------------------------------------------------------
     */





    // int Execute() override {
    //     Command cmd;     
    //     /**
    //      * input timeout 
    //      */
    //     chrono::milliseconds timeout(cmd[""][0].get(Properties::TIMEOUT, 1000));
    //     /**
    //      * process delay
    //      */
    //     chrono::milliseconds delay(cmd[""][0].get(Properties::DELAY, 10));
    //     STask::Sleep(delay);
    //     /**
    //      * configure IOs
    //      */
    //     IOLocation io;
    //     for(auto& o: cmd["X"]) {
    //         io.Insert(IOBuilder::Build(o));
    //     }
    //     ILocation in;
    //     for(auto& o: cmd["I"]) {
    //         in.Insert(IBuilder::Build(o));
    //     }
    //     OLocation out;
    //     for(auto& o: cmd["O"]) {
    //         out.Insert(OBuilder::Build(o));
    //     }
    //     /**
    //      * configure function
    //      */
    //     auto func = YBuilder::Build(cmd["F"][0]);
    //     /**
    //      * start energy
    //      */
    //     auto energy = cmd["F"][0].get(Properties::ENERGY, size_t(1));
    //     /**
    //      * main loop 
    //      */
    //     while (STask::Sleep()) {
    //         try {
    //             /**------------------------------------------------------------------------------------
    //              * process
    //              *-----------------------------------------------------------------------------------**/
    //             switch(GetState()) {
    //                 default: {
    //                     SetState(OPEN);
    //                 }
    //                 case OPEN: {
    //                     io.Open();
    //                     SetState(OWAIT);
    //                 }
    //                 case OWAIT: {
    //                     io.Update(timeout);
    //                     in.Open();
    //                     out.Open();
    //                     SetState(IWAIT);
    //                 }
    //                 case IWAIT: {
    //                     in.Update(timeout);
    //                     out.Update(timeout);
    //                     SetState(PROCESS);
    //                 }
    //                 // case PROCESS: {
    //                 //     func->Process(io.Update(timeout), in.Update(timeout), out.Update(timeout));
    //                 // }
    //                 case PROCESS: {
    //                     try {                           
    //                         for(auto& i : SResourceMonitor(timeout, &__monitor, io, in).Wait()) {
    //                             switch(i){
    //                                 case 2:
    //                                 case 3: {
    //                                     while(true) {
    //                                         func->Process(io, in, out);    
    //                                     }
    //                                     break;
    //                                 }
    //                             }
    //                         }                        
    //                     } catch (MonitorExceptionTIMEOUT & ex) {
    //                         func->Decay();
    //                     }
    //                     SetState(UPDATE);
    //                 }
    //                 case UPDATE : {

    //                     io.Update(timeout);
    //                     in.Update(timeout);
    //                     out.Update(timeout);
                    
    //                     //Update(__timeout, __in, __out);
    //                     SetState(PROCESS);
    //                 }
    //             }
    //         } 
    //         /**----------------------------------------------------------------------------------------
    //          * exceptions
    //          *---------------------------------------------------------------------------------------**/
    //         catch (IOLocationExceptionDETACHED & ex) {
    //             INFO(ex.what());
    //             if(Kill(func, energy)){
    //                 WARNING("Exit = { what: " << ex.what() << " }");
    //                 return -1;
    //             }
    //             in.Close();
    //             out.Close();
    //             SetState(OWAIT);
    //         } catch (OLocationExceptionDETACHED & ex) {
    //             INFO("Exception = { what:" << ex.what() << " }");
    //             if(Kill(func, energy)){
    //                 WARNING("Exit = { what: " << ex.what() << " }");
    //                 return -1;
    //             }
    //             SetState(IWAIT);
    //         }  catch (ILocationExceptionDETACHED & ex) {
    //             INFO(ex.what());
    //             if(Kill(func, energy)){
    //                 WARNING("Exit = { what: " << ex.what() << " }");
    //                 return -1;
    //             }
    //             SetState(IWAIT);
    //         } catch (MonitorExceptionTIMEOUT & ex) {
    //             INFO(ex.what());
    //             if(Dead(func, energy)){
    //                 INFO("Exit = { what: " << ex.what() << " }");
    //                 return -1;
    //             }
    //         } catch (exception& ex) {
    //             ERROR("Exit = { what: " << ex.what() << " }");
    //             return -1;
    //         } catch (...) {
    //             ERROR("Exit = { }");
    //             return -1;
    //         }
    //         INFO("Process = { energy: " << energy << " }");
    //     }
    //     /**
    //      * Finish
    //      */
    //     INFO("Exit = { }");
    //     return 0;
    // }
};
}
#endif /* MSPLITER_H */

