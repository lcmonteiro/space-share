/**
 * ------------------------------------------------------------------------------------------------
 * File:   SSpreadModule.h
 * Author: Luis Monteiro
 *
 * Created on November 16, 2018, 5:59 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SSPREADMODULE_H
#define SSPREADMODULE_H
/**
 * module
 */
#include "SBaseModule.h" 
/**
 *-------------------------------------------------------------------------------------------------
 * Spread Module
 *-------------------------------------------------------------------------------------------------
 */
namespace Module {
template<typename Input, typename Data, typename Output>
class SSpreadModule : public SBaseModule {
    /**
     * ------------------------------------------------------------------------
     * Helpers
     * ------------------------------------------------------------------------
     * exception types
     */
    using IRoadExceptionDETACHED = SRoadExceptionDETACHED<Input>;
    using ORoadExceptionDETACHED = SRoadExceptionDETACHED<Output>;
    /**
     * builders
     */
    using IBuilder = Module::Input::Builder<Input>;
    using FBuilder = Module::Spread::Builder<Input, Data, Output>;
    using OBuilder = Module::Output::Builder<Output>; 
    /** 
     * connector types
     */
    using IRoad = SRoadMonitor<SConnector::Key, Input>;
    using ORoad = SRoad<SConnector::Key, Output>;
    /**
     * function type
     */
    using Function = typename FBuilder::Pointer;
public:
    /**
     * ------------------------------------------------------------------------
     * Constructors
     * ------------------------------------------------------------------------
     * default
     */
    SSpreadModule(SSpreadModule&&)            = default;
    SSpreadModule& operator=(SSpreadModule&&) = default;
    /**
     * main
     */
    SSpreadModule(const Command& cmd)
    : SBaseModule(cmd[Command::MODULE].head(), {
        {Command::FUNCTION, cmd[Command::FUNCTION]},
        {Command::INPUT,    cmd[Command::INPUT]   },
        {Command::OUTPUT,   cmd[Command::OUTPUT]  },
    }), __in(), __out(), __func() {}
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
     * ------------------------------------------------------------------------
     * Execute - Process Command
     * ------------------------------------------------------------------------
     */
    void _process_command(const Command& cmd) override {
        /**
         * create and insert inputs
         */
        for(auto& o: cmd[Command::INPUT]) {
            try {
                __in.insert(o[Module::IO::URI], IBuilder::Build(o));
            } catch (std::out_of_range&) {
                _update_road(__in, o);
            }
        }
        /**
         * create and insert outputs
         */
        for(auto o: cmd[Command::OUTPUT]) {
            try {
                __out.insert(o[Module::IO::URI], OBuilder::Build(o));
            } catch (std::out_of_range&) {
                _update_road(__out, o);
            }
        }
        /**
         * create and insert outputs
         */
        for(auto o: cmd[Command::FUNCTION]) {
            __func = FBuilder::Build(o);
        }
    }
    /**
     * ------------------------------------------------------------------------
     * Execute - Process Machine
     * ------------------------------------------------------------------------
     */
    State _process_machine(const State& state, const Clock::Pointer& end) override {
        /**
         * log info
         */
        INFO("Process={ "
            << "state: "     << state              << ", "
            << "energy:"     << SEnergy::get()     << ", "
            << "inputs:"     << _status(__in)  << ", "
            << "outputs:"    << _status(__out) << "  "
            << "}"
        );
        /**
         * ------------------------------------------------
         * state machine process
         * ------------------------------------------------
         */
        try {
            switch(state) {
                case OPEN: {
                    return OWAIT;
                }
                case OWAIT: {
                    return _process_wait(end, __out, IWAIT);
                }
                case IWAIT: {
                    return _process_wait(end, __in, PLAY);
                }
                case PLAY: {
                    return _process_play(end);
                }
                case UPDATE : {
                    __out.update(); 
                    __in.update();
                    return PLAY;
                }
                default: {
                    return OPEN;
                }
            }
        }
        /**
         * ------------------------------------------------
         * state machine exceptions
         * ------------------------------------------------
         * out road detach
         */
        catch (ORoadExceptionDETACHED & ex) {
            WARNING("OUT = " << __out.status());
            if(PLAY == state) {
                SEnergy::decay();
            }
            __func->recover();
            __in.reset();
            return OWAIT;
        }
        /**
         * in road detach
         */
        catch (IRoadExceptionDETACHED & ex) {
            WARNING("IN = " << __in.status());
            if(PLAY == state) {
                SEnergy::decay();
            }
            __func->recover();
            return IWAIT;
        }
        /**
         * function dead
         */ 
        catch (FunctionExceptionDEAD& ex) {
            WARNING("FUNC");
            SEnergy::decay();
            __func->recover();
        }
        return state;
    }
    /**
     * ------------------------------------------------------------------------
     * process states
     * ------------------------------------------------------------------------
     * PLAY
     */
    inline State _process_play(const Clock::Pointer& end) {
        ResourceMonitor m (&__in);
        /**
         * first
         */
        try { 
            for(auto& i : m.wait(Clock::Remaining(end))) {
                __func->process(__in, __out);
            }
        } catch (MonitorExceptionTIMEOUT & ex) {
            __func->drain(__in, __out);
            __func->decay();
            return UPDATE;
        }
        /**
         * remaining
         */
        try { 
            do {
                for(auto& i : m.wait(Clock::Remaining(end))) {
                    __func->process(__in, __out);
                }           
            } while(Clock::Remaining(end) > Clock::Distance::zero());
        } catch (MonitorExceptionTIMEOUT & ex) { }
        /**
         * return state
         */
        return UPDATE;
    }
};
}
/**
 *-------------------------------------------------------------------------------------------------
 * End
 *-------------------------------------------------------------------------------------------------
 */
#endif /* SSPREADMODULE_H */

