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
    }), __io(), __in(), __out(), __func() {}
    /**
     * ------------------------------------------------------------------------
     * destructor
     * ------------------------------------------------------------------------
     */
    virtual ~MSpliter() { Attach(); }
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
     * process command
     * ---------------------------------------------------------------------------
     */
    void __ProcessCommand(const Command& cmd) {
        // create and insert input/outputs ----------------
        for(auto& o: cmd[Command::INOUT]) {
            try {
                __io.Insert(o[IO::URI], IOBuilder::Build(o));
            } catch (...) {
                __UpdateRoad(__io, o);
            }
        }
        // create and insert inputs -----------------------
        for(auto& o: cmd[Command::INPUT]) {
            try {
                __in.Insert(o[IO::URI], IBuilder::Build(o));
            } catch (...) {
                __UpdateRoad(__in, o);
            }
        }
        // create and insert outputs ----------------------
        for(auto o: cmd[Command::OUTPUT]) {
            try {
                __out.Insert(o[IO::URI], OBuilder::Build(o));
            } catch (...) {
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
                // default ----------------------------------------------------
                default: {
                    return OPEN;
                }
                // open -------------------------------------------------------
                case OPEN: {
                    return OWAIT;
                }
                // out wait ---------------------------------------------------
                case OWAIT: {
                    return __ProcessWAIT(end, __out, IOWAIT);
                }
                // in wait ----------------------------------------------------
                case IOWAIT: {
                    return __ProcessWAIT(end, __io, IWAIT);
                }
                // in wait ----------------------------------------------------
                case IWAIT: {
                    return __ProcessWAIT(end, __in, PLAY);
                }
                // play -------------------------------------------------------
                case PLAY: {
                    return __ProcessPLAY(end);
                }
                // update -----------------------------------------------------
                case UPDATE : {
                    //return __ProcessUpdate(__out, __io, __in, PLAY);
                    __out.Update(); __io.Update(); __in.Update();
                    return PLAY;
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
        // io road detach --------------------------------------------------------
        catch (IORoadExceptionDETACHED & ex) {
            WARNING("IO = " << __io.Status());
            if(PLAY == state) {
                SEnergy::Decay();
            }
            __func->Recover();
            __in.Reset();
            return IOWAIT;
        }
        // in road detach --------------------------------------------------------
        catch (IRoadExceptionDETACHED & ex) {
            WARNING("IN = " << __in.Status());
            if(PLAY == state) {
                SEnergy::Decay();
            }
            __func->Recover();
            return IWAIT;
        }
        // function dead ------------------------------------------------------- 
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
        // reamaining -------------------------------------
        try { 
            do {
                for(auto& i : m.Wait(Clock::Remaining(end))) {
                    switch(i) {
                        case 1: __func->Process(__io, __out); break;
                        case 2: __func->Process(__in, __io);  break;
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
 *-------------------------------------------------------------------------------------------------
 * end
 *-------------------------------------------------------------------------------------------------
 */
#endif /* MSPLITER_H */

