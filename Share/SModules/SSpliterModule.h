/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SSpliterModule.h
 * Author: Luis Monteiro
 *
 * Created on January 26, 2017, 5:59 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SSPLITERMODULE_H
#define SSPLITERMODULE_H
/**
 * module
 */
#include "SBaseModule.h"
/**
 *-------------------------------------------------------------------------------------------------
 * Module name space
 *-------------------------------------------------------------------------------------------------
 */
namespace Module {
/**
 */
template<class InOutput, class Input, class Output>
class SSpliterModule : public SBaseModule {
    /**
     * ------------------------------------------------------------------------
     * Helpers
     * ------------------------------------------------------------------------
     * exception types
     */
    using IORoadExceptionDETACHED = SRoadExceptionDETACHED<InOutput>;
    using IRoadExceptionDETACHED  = SRoadExceptionDETACHED<Input>;
    using ORoadExceptionDETACHED  = SRoadExceptionDETACHED<Output>;
    /**
     * builders 
     */
    using IOBuilder = Module::IOput::Builder<InOutput>;
    using IBuilder  = Module::Input::Builder<Input>;
    using OBuilder  = Module::Output::Builder<Output>;
    using FBuilder  = Module::Spliter::Builder<InOutput, Input, Output>; 
    /** 
     * connector types
     */
    using IORoad = SRoadMonitor<SConnector::Key, InOutput>;
    using IRoad  = SRoadMonitor<SConnector::Key, Input>;
    using ORoad  = SRoad<SConnector::Key, Output>; 
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
    SSpliterModule(SSpliterModule&&)            = default;
    SSpliterModule& operator=(SSpliterModule&&) = default;
    /**
     * main
     */
    SSpliterModule(const Command& cmd)
    : SBaseModule(cmd[Command::MODULE].head(), {
        {Command::FUNCTION, cmd[Command::FUNCTION]},
        {Command::INOUT,    cmd[Command::INOUT]   },
        {Command::INPUT,    cmd[Command::INPUT]   },
        {Command::OUTPUT,   cmd[Command::OUTPUT]  },
    }), __io(), __in(), __out(), __func() {}
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
     * function
     */
    Function __func;
    /**
     * ------------------------------------------------------------------------
     * Execute - process command
     * ------------------------------------------------------------------------
     */
    void _process_command(const Command& cmd) override {
        /**
         * create and insert input/outputs
         */
        for(auto& o: cmd[Command::INOUT]) {
            try {
                __io.insert(o[Module::IO::URI], IOBuilder::Build(o));
            } catch (std::out_of_range&) {
                _update_road(__io, o);
            }
        }
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
     * execute - process machine
     * ------------------------------------------------------------------------
     */
    State _process_machine(const State& state, const Clock::Pointer& end) override {
        /**
         * log info
         */
        INFO("Process={ "
            << "state: "      << state               << ", "
            << "energy: "     << SEnergy::get()      << ", "
            << "inputs: "     << _status(__in)   << ", "
            << "outputs: "    << _status(__out)  << ", "
            << "in|outputs: " << _status(__io)   << " "
            << "}");
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
                    return _process_wait(end, __out, IOWAIT);
                }
                case IOWAIT: {
                    return _process_wait(end, __io, IWAIT);
                }
                case IWAIT: {
                    return _process_wait(end, __in, PLAY);
                }
                case PLAY: {
                    return _process_play(end);
                }
                case UPDATE : {
                    __out.update(); 
                    __io.update(); 
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
            __io.reset();
            return OWAIT;
        } 
        /**
         * io road detach
         */
        catch (IORoadExceptionDETACHED & ex) {
            WARNING("IO = " << __io.status());
            if(PLAY == state) {
                SEnergy::decay();
            }
            __func->recover();
            __in.reset();
            return IOWAIT;
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
        ResourceMonitor m (&__io, &__in);
        /**
         * first
         */
        try {
            for(auto& i : m.wait(Clock::Remaining(end))) {
                switch(i) {
                    case 0: __func->process(__io, __out); break;
                    case 1: __func->process(__in, __io);  break;
                }
            }
        } catch (MonitorExceptionTIMEOUT & ex) {
            __func->drain(__io, __in, __out);
            __func->decay();
            return UPDATE;
        }
        /**
         * remaining
         */
        try { 
            do {
                for(auto& i : m.wait(Clock::Remaining(end))) {
                    switch(i) {
                        case 0: __func->process(__io, __out); break;
                        case 1: __func->process(__in, __io);  break;
                    }
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
#endif /* SSPLITERMODULE_H */
