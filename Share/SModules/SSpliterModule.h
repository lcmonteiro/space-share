/**
 * -------------------------------------------------------------------------------------------------------------------- 
 * File:   SSpliterModule.h
 * Author: Luis Monteiro
 *
 * Created on January 26, 2017, 5:59 PM
 * --------------------------------------------------------------------------------------------------------------------
 */
#ifndef SSPLITERMODULE_H
#define SSPLITERMODULE_H
/**
 * Module
 */
#include "SBaseModule.h"
/**
 *---------------------------------------------------------------------------------------------------------------------
 * Module name space
 *---------------------------------------------------------------------------------------------------------------------
 */
namespace Module {
/**
 */
template<class IO_CON, class I_CON, class O_CON>
class SSpliterModule : public SBaseModule {
    /**
     * --------------------------------------------------------------------------------------------
     * Helpers
     * --------------------------------------------------------------------------------------------
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
    using IOBuilder = Module::IOput::Builder<IO_CON>;
    using IBuilder  = Module::Input::Builder<I_CON>;
    using OBuilder  = Module::Output::Builder<O_CON>;
    using FBuilder  = Module::Spliter::Builder<IO_CON, I_CON, O_CON>; 
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
     * --------------------------------------------------------------------------------------------
     * Interfaces
     * --------------------------------------------------------------------------------------------
     * defaults
     * ------------------------------------------------------------------------
     */
    SSpliterModule(SSpliterModule&&)            = default;
    SSpliterModule& operator=(SSpliterModule&&) = default;
    /**
     * ------------------------------------------------------------------------
     * constructor
     * ------------------------------------------------------------------------
     */
    SSpliterModule(const Command& cmd): SBaseModule(cmd[Command::MODULE].Head(), {
        {Command::FUNCTION, cmd[Command::FUNCTION]},
        {Command::INOUT,    cmd[Command::INOUT]   },
        {Command::INPUT,    cmd[Command::INPUT]   },
        {Command::OUTPUT,   cmd[Command::OUTPUT]  },
    }), __io(), __in(), __out(), __func() {}
    /**
     * ------------------------------------------------------------------------
     * destructor
     * ------------------------------------------------------------------------
     */
    virtual ~SSpliterModule() { Attach(); }
protected:
    /**
     * --------------------------------------------------------------------------------------------
     * Variables
     * --------------------------------------------------------------------------------------------
     * input/output
     * --------------------------------
     */
    IORoad __io;
    /**
     * --------------------------------
     * input
     * --------------------------------
     */
    IRoad __in;
    /**
     * --------------------------------
     * output
     * --------------------------------
     */
    ORoad __out;
    /**
     * --------------------------------
     * function
     * --------------------------------
     */
    Function __func;
    /**
     * --------------------------------------------------------------------------------------------
     * Execute
     * --------------------------------------------------------------------------------------------
     * process command
     * ------------------------------------------------------------------------
     */
    void __ProcessCommand(const Command& cmd) {
        // create and insert input/outputs ----------------
        for(auto& o: cmd[Command::INOUT]) {
            try {
                __io.Insert(o[Module::IO::URI], IOBuilder::Build(o));
            } catch (std::out_of_range&) {
                __UpdateRoad(__io, o);
            }
        }
        // create and insert inputs -----------------------
        for(auto& o: cmd[Command::INPUT]) {
            try {
                __in.Insert(o[Module::IO::URI], IBuilder::Build(o));
            } catch (std::out_of_range&) {
                __UpdateRoad(__in, o);
            }
        }
        // create and insert outputs ----------------------
        for(auto o: cmd[Command::OUTPUT]) {
            try {
                __out.Insert(o[Module::IO::URI], OBuilder::Build(o));
            } catch (std::out_of_range&) {
                __UpdateRoad(__out, o);
            }
        }
        // create and insert outputs ----------------------
        for(auto o: cmd[Command::FUNCTION]) {
            __func = FBuilder::Build(o);
        }
    }
    /**
     * --------------------------------------------------------------------------------------------
     * process machine
     * --------------------------------------------------------------------------------------------
     */
    State __ProcessMachine(const State& state, const Clock::Pointer& end) override {
        // log info -----------------------------------------------------------
        INFO("Process={ "
            << "state: "      << state               << ", "
            << "energy: "     << SEnergy::Get()      << ", "
            << "inputs: "     << __GetStatus(__in)   << ", "
            << "outputs: "    << __GetStatus(__out)  << ", "
            << "in|outputs: " << __GetStatus(__io)   << " "
            << "}"
        );
        /**
         * --------------------------------------------------------------------
         * state machine process
         * --------------------------------------------------------------------
         */
        try {
            switch(state) {
                // open -----------------------------------
                case OPEN: {
                    return OWAIT;
                }
                // out wait -------------------------------
                case OWAIT: {
                    return __ProcessWAIT(end, __out, IOWAIT);
                }
                // in wait --------------------------------
                case IOWAIT: {
                    return __ProcessWAIT(end, __io, IWAIT);
                }
                // in wait --------------------------------
                case IWAIT: {
                    return __ProcessWAIT(end, __in, PLAY);
                }
                // play -----------------------------------
                case PLAY: {
                    return __ProcessPLAY(end);
                }
                // update ---------------------------------
                case UPDATE : {
                    __out.Update(); 
                    __io.Update(); 
                    __in.Update();
                    return PLAY;
                }
                // default --------------------------------
                default: {
                    return OPEN;
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
            WARNING("OUT = " << __out.Status());
            if(PLAY == state) {
                SEnergy::Decay();
            }
            __func->Recover();
            __in.Reset();
            __io.Reset();
            return OWAIT;
        } 
        // io road detach ---------------------------------
        catch (IORoadExceptionDETACHED & ex) {
            WARNING("IO = " << __io.Status());
            if(PLAY == state) {
                SEnergy::Decay();
            }
            __func->Recover();
            __in.Reset();
            return IOWAIT;
        }
        // in road detach ---------------------------------
        catch (IRoadExceptionDETACHED & ex) {
            WARNING("IN = " << __in.Status());
            if(PLAY == state) {
                SEnergy::Decay();
            }
            __func->Recover();
            return IWAIT;
        }
        // function dead ---------------------------------- 
        catch (FunctionExceptionDEAD& ex) {
            WARNING("FUNC");
            SEnergy::Decay();
            __func->Recover();
        }
        return state;
    }
    /**
     * --------------------------------------------------------------------------------------------
     * process states
     * --------------------------------------------------------------------------------------------
     * PLAY
     * ------------------------------------------------------------------------
     */
    inline State __ProcessPLAY(const Clock::Pointer& end) {
        ResourceMonitor m (&__io, &__in);

        // first ------------------------------------------
        try {
            for(auto& i : m.Wait(Clock::Remaining(end))) {
                switch(i) {
                    case 0: __func->Process(__io, __out); break;
                    case 1: __func->Process(__in, __io);  break;
                }
            }
        } catch (MonitorExceptionTIMEOUT & ex) {
            __func->Drain(__io, __in, __out);
            __func->Decay();
            return UPDATE;
        }
        // remaining --------------------------------------
        try { 
            do {
                for(auto& i : m.Wait(Clock::Remaining(end))) {
                    switch(i) {
                        case 0: __func->Process(__io, __out); break;
                        case 1: __func->Process(__in, __io);  break;
                    }
                }                
            } while(Clock::Remaining(end) > Clock::Distance::zero());
        } catch (MonitorExceptionTIMEOUT & ex) { }

        // return state -----------------------------------
        return UPDATE;
    }
};
}
/**
 *---------------------------------------------------------------------------------------------------------------------
 * End
 *---------------------------------------------------------------------------------------------------------------------
 */
#endif /* SSPLITERMODULE_H */

