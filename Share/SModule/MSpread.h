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
#include "MBase.h" 
/**
 *-------------------------------------------------------------------------------------------------
 * Module name space
 *-------------------------------------------------------------------------------------------------
 */
namespace Module {
/**
 */
template<class I, class D, class O>
class MSpread : public MBase {
    /**
     * ------------------------------------------------------------------------
     * exception types
     * ------------------------------------------------------------------------
     */
    using IRoadExceptionDETACHED = SRoadExceptionDETACHED<I>;
    using ORoadExceptionDETACHED = SRoadExceptionDETACHED<O>;
    /**
     * ------------------------------------------------------------------------
     * builders
     * ------------------------------------------------------------------------
     */
    using IBuilder = Input::Builder<I>;
    using FBuilder = Spread::Builder<I, D, O>;
    using OBuilder = Output::Builder<O>; 
    /** 
     * ------------------------------------------------------------------------
     * connector types
     * ------------------------------------------------------------------------
     */
    using IRoad = SRoadMonitor<SConnector::Key, I>;
    using ORoad = SRoad<SConnector::Key, O>;
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
    }) { }
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
     * ---------------------------------------------------------------------------
     */
    void __ProcessCommand(const Command& cmd) {
        // create and insert inputs -----------------------
        for(auto& o: cmd[Command::INPUT]) {
            __in.Insert(o[IO::URI], IBuilder::Build(o));
        }
        // create and insert outputs ----------------------
        for(auto o: cmd[Command::OUTPUT]) {
            __out.Insert(o[IO::URI], OBuilder::Build(o));
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
            << "energy:"     << SEnergy::Get() << ", "
            << "inputs:"     << Status(__in)   << ", "
            << "outputs:"    << Status(__out)  << "  "
            << "}"
        );
        /**
         * --------------------------------------------------------------------
         * state machine process
         * --------------------------------------------------------------------
         */
        try {
            switch(state) {
                // default --------------------------------
                default: {
                    return OPEN;
                }
                // open -----------------------------------
                case OPEN: {
                    __out.Open();
                    return OWAIT;
                }
                // out wait -------------------------------
                case OWAIT: {
                    return __ProcessOWAIT(end);
                }
                // in wait --------------------------------
                case IWAIT: {
                    return __ProcessIWAIT(end);
                }
                // play -----------------------------------
                case PLAY: {
                    return __ProcessPLAY(end);
                }
                // update ---------------------------------
                case UPDATE : {
                    __out.Update();
                    __in.Update();
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
            WARNING("OUT = { " << Status(__out) << " }");
            if(PLAY == state) {
                SEnergy::Decay();
            }
            __func->Recover();
            __in.Close();
            return OWAIT;
        }
        // in road detach --------------------------------- 
        catch (IRoadExceptionDETACHED & ex) {
            WARNING("IN = {" << Status(__in) << " }");
            if(PLAY == state) {
                SEnergy::Decay();
            }
            __func->Recover();
            return IWAIT;
        }
        // function dead ---------------------------------- 
        catch (FunctionExceptionDEAD& ex) {
            SEnergy::Decay();
            __func->Recover();
        }
        return state;
    }
    /**
     * --------------------------------------------------------------------------------------------
     * process states
     * --------------------------------------------------------------------------------------------
     * OWAIT
     * ------------------------------------------------------------------------
     */
    inline State __ProcessOWAIT(const Clock::Pointer& end) {
         for(Timer t(end, Clock::Distance(100)); !t.Active(); t.Sleep()) {
            try {
                __out.Update();
                __in.Open();
                return IWAIT;
            } catch(RoadDetached& e) { }
        } 
        __out.Update();
        __in.Open();
        return IWAIT;
    }
    /**
     * ------------------------------------------------------------------------
     * IWAIT
     * ------------------------------------------------------------------------
     */
    inline State __ProcessIWAIT(const Clock::Pointer& end) {
        for(Timer t(end, Clock::Distance(100)); !t.Active(); t.Sleep()) {
            try {
                __in.Update();
                return PLAY;
            } catch(RoadDetached& e) { }
        } 
        __in.Update();
        return PLAY; 
    }
    /**
     * ------------------------------------------------------------------------
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
 *-------------------------------------------------------------------------------------------------
 * end
 *-------------------------------------------------------------------------------------------------
 */
#endif /* MSPREAD_H */

