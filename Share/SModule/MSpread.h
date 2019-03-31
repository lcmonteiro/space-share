/**
 * --------------------------------------------------------------------------------------------------------------------
 * File:   MSpread.h
 * Author: Luis Monteiro
 *
 * Created on November 16, 2018, 5:59 PM
 * --------------------------------------------------------------------------------------------------------------------
 */
#ifndef MSPREAD_H
#define MSPREAD_H
/**
 * Module
 */
#include "MBase.h" 
/**
 *---------------------------------------------------------------------------------------------------------------------
 * Module name space
 *---------------------------------------------------------------------------------------------------------------------
 */
namespace Module {
/**
 */
template<class I_CON, class DOC, class O_CON>
class MSpread : public MBase {
    /**
     * --------------------------------------------------------------------------------------------
     * Helpers
     * --------------------------------------------------------------------------------------------
     * exception types
     * ------------------------------------------------------------------------
     */
    using IRoadExceptionDETACHED = SRoadExceptionDETACHED<I_CON>;
    using ORoadExceptionDETACHED = SRoadExceptionDETACHED<O_CON>;
    /**
     * ------------------------------------------------------------------------
     * builders
     * ------------------------------------------------------------------------
     */
    using IBuilder = Input::Builder<I_CON>;
    using FBuilder = Spread::Builder<I_CON, DOC, O_CON>;
    using OBuilder = Output::Builder<O_CON>; 
    /** 
     * ------------------------------------------------------------------------
     * connector types
     * ------------------------------------------------------------------------
     */
    using IRoad = SRoadMonitor<SConnector::Key, I_CON>;
    using ORoad = SRoad<SConnector::Key, O_CON>;
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
    MSpread(MSpread&&)            = default;
    MSpread& operator=(MSpread&&) = default;
    /**
     * ------------------------------------------------------------------------
     * constructor
     * ------------------------------------------------------------------------
     */
    MSpread(const Command& cmd): MBase(cmd[Command::MODULE].Head(), {
        {Command::FUNCTION, cmd[Command::FUNCTION]},
        {Command::INPUT,    cmd[Command::INPUT]   },
        {Command::OUTPUT,   cmd[Command::OUTPUT]  },
    }), __in(), __out(), __func() {}
    /**
     * ------------------------------------------------------------------------
     * destructor
     * ------------------------------------------------------------------------
     */
    virtual ~MSpread() { Attach(); }
protected:
    /**
     * ------------------------------------------------------------------------
     * Variables
     * ------------------------------------------------------------------------
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
     * ------------------------------------------------------------------------
     */
    void __ProcessCommand(const Command& cmd) {
        // create and insert inputs -----------------------
        for(auto& o: cmd[Command::INPUT]) {
            try {
                __in.Insert(o[IO::URI], IBuilder::Build(o));
            } catch (std::out_of_range&) {
                __UpdateRoad(__in, o);
            }
        }
        // create and insert outputs ----------------------
        for(auto o: cmd[Command::OUTPUT]) {
            try {
                __out.Insert(o[IO::URI], OBuilder::Build(o));
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
            << "state: "     << state              << ", "
            << "energy:"     << SEnergy::Get()     << ", "
            << "inputs:"     << __GetStatus(__in)  << ", "
            << "outputs:"    << __GetStatus(__out) << "  "
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
                    return __ProcessWAIT(end, __out, IWAIT);
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
                    __out.Update(); __in.Update();
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
         * out road detach --------------------------------
         */
        catch (ORoadExceptionDETACHED & ex) {
            WARNING("OUT = " << __out.Status());
            if(PLAY == state) {
                SEnergy::Decay();
            }
            __func->Recover();
            __in.Reset();
            return OWAIT;
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
        ResourceMonitor m (&__in);

        // first ------------------------------------------
        try { 
            for(auto& i : m.Wait(Clock::Remaining(end))) {
                __func->Process(__in, __out);
            }
        } catch (MonitorExceptionTIMEOUT & ex) {
            __func->Drain(__in, __out);
            __func->Decay();
            return UPDATE;
        }
        // reamaining -------------------------------------
        try { 
            do {
                for(auto& i : m.Wait(Clock::Remaining(end))) {
                    __func->Process(__in, __out);
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
#endif /* MSPREAD_H */

