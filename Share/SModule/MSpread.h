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
#include "MBasis.h" 
/**
 *----------------------------------------------------------------------------------------------------------------------
 * Module name space
 *----------------------------------------------------------------------------------------------------------------------
 */
namespace Module {
/**
 */
template<class I, class D, class O>
class MSpread : public MBasis {
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
    using RoadMonitor = SRoadMonitor<SConnector::Key, I>;
    using Road        = SRoad<SConnector::Key, O>;
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
    MSpread(const Command& cmd): MBasis(cmd), 
    // delay start
    __delay(
        cmd[""][0].get(Properties::DELAY, 10)
    ),
    // module period
    __timeout(
        cmd[""][0].get(Properties::TIMEOUT, 1000)
    ),
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
     * -----------------------------------------------------------------------------------------------------------------
     * Variables
     * -----------------------------------------------------------------------------------------------------------------
     * process delay
     */
    chrono::milliseconds __delay;
    /**
     * process period
     */
    chrono::milliseconds __timeout;
    /**
     * inputs
     */
    RoadMonitor __in;
    /**
     * outputs
     */
    Road __out;
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
        // delay the process
        STask::Sleep(__delay);
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
    void __process() override {
        // procces commands
        auto process = [this]() {
            UpdateFunction(__func, UpdateOutputs(__out, UpdateInputs(__in, ReadCommand())));
        };
        // state machine
        INFO("Process={ energy:" << SEnergy::Get() << ", inputs:" << Status(__in) << " }");
        try {
            switch(GetState()) {
                default: {
                    SetState(OPEN);
                }
                case OPEN: {
                    __out.Open();
                    SetState(OWAIT);
                }
                case OWAIT: {
                    Update(__timeout, process, __out);
                    __in.Open();
                    SetState(IWAIT);
                }
                case IWAIT: {
                    Update(__timeout, process, __in);
                    SetState(PROCESS);
                }
                case PROCESS: {
                    try {                           
                        for(auto& i : SResourceMonitor(__timeout, &__monitor, &__in).Wait()) {
                            switch(i) {
                                // procces commands
                                case 1: {
                                    ProcessCommand(__in, __func, __out);
                                    break;
                                }
                                case 2: {
                                    while(true) {
                                        __func->Process(__in, __out);    
                                    }
                                }
                            }
                        }                        
                    } catch (MonitorExceptionTIMEOUT & ex) {
                        __func->Drain(__out);
                        __func->Decay();
                    }
                    SetState(UPDATE);
                }
                case UPDATE : {
                    Update(__timeout, process, __in, __out);
                    SetState(PROCESS);
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

