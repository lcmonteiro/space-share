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
#include "MDefault.h" 
/**
 *-------------------------------------------------------------------------------------------------
 * Module name space
 *-------------------------------------------------------------------------------------------------
 */
namespace Module {
/**
 */
template<class I, class D, class O>
class MSpread : public MDefault {
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
    using IRoad = SRoadMonitor<SConnector::Key, I>;
    using ORoad = SRoad<SConnector::Key, O>;
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
    MSpread(const Command& cmd): MDefault(cmd), 
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
     * --------------------------------------------------------------------------------------------
     * Variables
     * --------------------------------------------------------------------------------------------
     * inputs
     */
    IRoad __in;
    /**
     * outputs
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
     */
    void __Init() {
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
    void __Process(const TimePoint& end) override {
        // procces commands
        auto ProcessCmd = [this]() {
            UpdateFunction(
                __func, UpdateOutputs(__out, UpdateInputs(__in, ReadCommand()))
            );
        };
        // state machine
        INFO("Process:" 
           << "{ energy:" << SEnergy::Get() << ", input:" << Status(__in) << " }"
        );
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
                        if(Monitor(end, ProcessCmd, &__in)) {
                            SResourceMonitor m (&__in);
                            while(m.Good()) {
                                for(auto& i : Wait(m, end)) {
                                    __func->Process(__in, __out);
                                }
                            }
                        }                        
                    } catch (MonitorExceptionTIMEOUT & ex) {
                        __func->Drain(__in, __out);
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
            WARNING("OUT={ " << Status(__out) << " }");
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
};
}
#endif /* MSPREAD_H */

