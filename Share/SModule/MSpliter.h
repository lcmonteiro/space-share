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
#include "MBase.h"
/**
 *-------------------------------------------------------------------------------------------------
 * Module name space
 *-------------------------------------------------------------------------------------------------
 */
namespace Module {
/**
 */
template<class IO_CON, class I_CON, class O_CON>
class MSpliter : public MBase {
    /**
     * ------------------------------------------------------------------------
     * exception types
     * ------------------------------------------------------------------------
     */
    using IORoadExceptionDETACHED = SRoadExceptionDETACHED<IO_CON>;
    using IRoadExceptionDETACHED  = SRoadExceptionDETACHED<I_CON>;
    using ORoadExceptionDETACHED  = SRoadExceptionDETACHED<O_CON>;
    /**
     * ------------------------------------------------------------------------
     * builders 
     * ------------------------------------------------------------------------
     */
    using IOBuilder = IOput::Builder<IO_CON>;
    using IBuilder  = Input::Builder<I_CON>;
    using OBuilder  = Output::Builder<O_CON>;
    using FBuilder  = Spliter::Builder<IO_CON, I_CON, O_CON>; 
    /** 
     * ------------------------------------------------------------------------
     * connector types
     * ------------------------------------------------------------------------
     */
    using IORoad = SRoadMonitor<SConnector::Key, IO_CON>;
    using IRoad  = SRoadMonitor<SConnector::Key, I_CON>;
    using ORoad  = SRoad<SConnector::Key, O_CON>; 
    /**
     * ------------------------------------------------------------------------
     * function type
     * ------------------------------------------------------------------------
     */
    using Function = typename FBuilder::Pointer;
public:   
    /**
     * ------------------------------------------------------------------------
     * defaults
     * ------------------------------------------------------------------------
     */
    MSpliter(MSpliter&&)            = default;
    MSpliter& operator=(MSpliter&&) = default;
    /**
     * ------------------------------------------------------------------------
     * constructor
     * ------------------------------------------------------------------------
     */
    MSpliter(const Command& cmd): MBase(cmd[Command::MODULE].Head(), {
        {Command::FUNCTION, cmd[Command::FUNCTION]},
        {Command::INOUT,    cmd[Command::INOUT]   },
        {Command::INPUT,    cmd[Command::INPUT]   },
        {Command::OUTPUT,   cmd[Command::OUTPUT]  },
    }) {    }
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
     * output
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
            __io.Insert(o[IO::URI], IOBuilder::Build(o));
        }
        // create and insert inputs
        for(auto& o: cmd[Command::INPUT]) {
            __in.Insert(o[IO::URI], IBuilder::Build(o));
        }
        // create and insert outputs
        for(auto o: cmd[Command::OUTPUT]) {
            __out.Insert(o[IO::URI], OBuilder::Build(o));
        }
        // create and insert outputs
        for(auto o: cmd[Command::FUNCTION]) {
            __func = FBuilder::Build(o);
        }
    }
    /**
     * --------------------------------------------------------------------------------------------
     * process execution
     * --------------------------------------------------------------------------------------------
     */
    void __ProcessMachine(const Clock::Pointer& end) override {
        // log info -----------------------------------------------------------
        INFO("Process={ "
            << "energy:"     << SEnergy::Get() << ", "
            << "inputs:"     << Status(__in)   << ", "
            << "outputs:"    << Status(__out)  << ", "
            << "in|outputs:" << Status(__io)   << "  "
            << "}"
        );
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
                    DEBUG("OPEN");
                    SetState(OWAIT);
                    break;
                }
                // out wait --------------------------------------------------
                case OWAIT: {
                    Update(end, &__out);
                    DEBUG("OWAIT");
                    __io.Open();
                    __in.Open();
                    SetState(IWAIT);
                    break;
                }
                //  in wait ---------------------------------------------------
                case IWAIT: {
                    Update(end, &__io, &__in);
                    DEBUG("IWAIT");
                    SetState(PROCESS);
                    break;
                }
                // process ----------------------------------------------------
                case PROCESS: {
                    try { 
                        ResourceMonitor m (&__io, &__in);
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

