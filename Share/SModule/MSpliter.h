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
 *-------------------------------------------------------------------------------------------------
 * Module name space
 *-------------------------------------------------------------------------------------------------
 */
namespace Module {
/**
 */
template<class IO, class I, class O>
class MSpliter : public MDefault {
    /**
     * ------------------------------------------------------------------------
     * exception types
     * ------------------------------------------------------------------------
     */
    using IORoadExceptionDETACHED = SRoadExceptionDETACHED<IO>;
    using IRoadExceptionDETACHED  = SRoadExceptionDETACHED<I>;
    using ORoadExceptionDETACHED  = SRoadExceptionDETACHED<O>;
    /**
     * ------------------------------------------------------------------------
     * builders 
     * ------------------------------------------------------------------------
     */
    using IOBuilder = IOput::Builder<IO>;
    using IBuilder  = Input::Builder<I>;
    using OBuilder  = Output::Builder<O>;
    using FBuilder  = Spliter::Builder<IO, I, O>; 
    /** 
     * ------------------------------------------------------------------------
     * connector types
     * ------------------------------------------------------------------------
     */
    using IORoad = SRoadMonitor<SConnector::Key, IO>;
    using IRoad  = SRoadMonitor<SConnector::Key, I>;
    using ORoad  = SRoad<SConnector::Key, O>; 
    /**
     * ------------------------------------------------------------------------
     * function type
     * ------------------------------------------------------------------------
     */
    using Function = typename FBuilder::Pointer;
public:   
    MSpliter(const Command& cmd): MBase() {
        InsertCommand(cmd);
    }
protected:
    /**
     * ------------------------------------------------------------------------
     * Variables
     * ------------------------------------------------------------------------
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
     * --------------------------------------------------------------------------------------------
     * Execute
     * --------------------------------------------------------------------------------------------
     * init execution
     * ---------------------------------------------------------------------------
     */
    void __ProcessCommand(const Command& cmd) {
        // create and insert input/outputs
        for(auto& o: cmd[Command::INOUT]) {
            __io.Insert(o[Properties::URI], IBuilder::Build(o));
        }
        // create and insert inputs
        for(auto& o: cmd[Command::IN]) {
            __in.Insert(o[Properties::URI], IBuilder::Build(o));
        }
        // create and insert outputs
        for(auto o: cmd[Command::OUT]) {
            __out.Insert(o[Properties::URI], OBuilder::Build(o));
        }
        // create and insert outputs
        for(auto o: cmd[Command::FUNC]) {
            __func = FBuilder::Build(__cmd["F"][0]);
        }
    }
    /**
     * --------------------------------------------------------------------------------------------
     * process execution
     * --------------------------------------------------------------------------------------------
     */
    void __Process(const TimePoint& end) override {
        // log info -----------------------------------------------------------
        INFO("Process={ "
            << "energy:" << SEnergy::Get() << ", "
            << "inputs:" << Status(__in)   << " "
            << "}"
        );
        // procces commands ---------------------------------------------------
        for(auto& c : FindCommand()) {
            ProcessCommand()
        }
        /**
         * --------------------------------------------------------------------
         * state machine process
         * --------------------------------------------------------------------
         */
        try {
            switch(GetState()) {
                // default ----------------------------------------------------
                default: {
                    SetState(OPEN);
                    break;
                }
                // open -------------------------------------------------------
                case OPEN: {
                    __out.Open();
                    SetState(OWAIT);
                    break;
                }
                // out wait --------------------------------------------------
                case OWAIT: {
                    Update(end, &__out);
                    __in.Open();
                    SetState(IWAIT);
                    break;
                }
                //  in wait ---------------------------------------------------
                case IWAIT: {
                    Update(end, ProcessCmd, &__in);
                    SetState(PROCESS);
                    break;
                }
                // process ----------------------------------------------------
                case PROCESS: {
                    try { 
                        SResourceMonitor m (&__io, &__in);
                        while(m.Good()) {
                            for(auto& i : Wait(m, end)) {
                                switch(i) {
                                    case 1: {
                                        __func->Process(__io, __out);
                                        break;
                                    }
                                    case 2: {
                                        __func->Process(__in, __io);
                                        break;
                                    }
                                }
                            }
                        }                  
                    } catch (MonitorExceptionTIMEOUT & ex) {
                        __func->Drain(__io, __in, __out);
                        __func->Decay();
                    }
                    SetState(UPDATE);
                    break;
                }
                // update -----------------------------------------------------
                case UPDATE : {
                    Update(end, &__in, &__out);
                    SetState(PROCESS);
                    break;
                }
            }
        }
        /**
         * --------------------------------------------------------------------
         * state machine exceptions
         * --------------------------------------------------------------------
         * out road detach
         */
        catch (ORoadExceptionDETACHED & ex) {
            WARNING("OUT = { " << Status(__out) << " }");
            if(IsState(PROCESS)) {
                SEnergy::Decay();
            }
            __func->Recover();
            __in.Close();
            SetState(OWAIT);
        } 
        // in road detach --------------------------------------------------------
        catch (IRoadExceptionDETACHED & ex) {
            WARNING("IN = {" << Status(__in) << " }");
            if(IsState(PROCESS)) {
                SEnergy::Decay();
            }
            __func->Recover();
            SetState(IWAIT);
        }
        // fuction dead ------------------------------------------------------- 
        catch (FunctionExceptionDEAD& ex) {
            SEnergy::Decay();
            __func->Recover();
        }
    }
};
}
#endif /* MSPLITER_H */

