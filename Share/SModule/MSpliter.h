/** 
 * File:   MSpliter.h
 * Author: Luis Monteiro
 *
 * Created on January 26, 2017, 5:59 PM
 */
#ifndef MSpliter_H
#define MSpliter_H
/**
 */
#include <tuple>
#include <chrono>
/**
 * Buildres
 */
#include "MConnectors.h"
#include "MFunctions.h"
/**
 * space kernel
 */
#include "SProcess.h"
#include "SConnector.h"
#include "SLocation.h"
/**
 * space monitor
 */
#include "SRoadMonitor.h"
#include "SCommandMonitor.h"
/**
 * space resource
 */
#include "SLocalResource.h"  
/**
 *----------------------------------------------------------------------------------------------------------------------
 * Module name space
 *----------------------------------------------------------------------------------------------------------------------
 */
namespace Module {
/**
 */
template<class IO, class I, class O>
class MSpliter : public SModule {
    /**
     * exceptions
     */
    using IOLocationExceptionDETACHED = SLocationExceptionDETACHED<IO>;
    using ILocationExceptionDETACHED  = SLocationExceptionDETACHED<I>;
    using OLocationExceptionDETACHED  = SLocationExceptionDETACHED<O>;
    /** 
     * connectors
     */
    using IOLocation = SLocation<IO>;
    using ILocation  = SLocation<I>;
    using OLocation  = SLocation<O>;
    /**
     * builders 
     */
    using IOBuilder = IOput::Builder<IO>;
    using IBuilder  = Input::Builder<I>;
    using OBuilder  = Output::Builder<O>;
    using YBuilder  = Spliter::Builder<IO, I, O>;  
public:   
    using SModule::SModule;
protected:
    /**
     * -----------------------------------------------------------------------------------------------------------------
     * Execute
     * -----------------------------------------------------------------------------------------------------------------
     */
    int Execute(const Command& cmd) override {

    }

    int Spliter(const Group& fn_opt, const Groups& in_opt, const Groups& io_opt, const Groups& out_opt) {
        /**
         * input timeout 
         */
        chrono::milliseconds timeout(Command::Peek(fn_opt, Properties::TIMEOUT, 1000));
        /**
         * process delay
         */
        chrono::milliseconds delay(Command::Peek(fn_opt, Properties::DELAY, 10));
        STask::Sleep(delay);
        /**
         * configure IOs
         */
        IOLocation io;
        for(auto& o: in_opt) {
            io.Insert(IOBuilder::Build(o));
        }
        ILocation in;
        for(auto& o: in_opt) {
            in.Insert(IBuilder::Build(o));
        }
        OLocation out;
        for(auto& o: out_opt) {
            out.Insert(OBuilder::Build(o));
        }
        /**
         * configure function
         */
        auto func = YBuilder::Build(fn_opt);
        /**
         * start energy
         */
        auto energy = Command::Peek(fn_opt, Properties::ENERGY, size_t(1));
        /**
         * main loop 
         */
        while (STask::Sleep()) {
            try {
                /**------------------------------------------------------------------------------------
                 * process
                 *-----------------------------------------------------------------------------------**/
                switch(GetState()) {
                    default: {
                        SetState(OPEN);
                    }
                    case OPEN: {
                        io.Open();
                        SetState(OWAIT);
                    }
                    case OWAIT: {
                        io.Update(timeout);
                        in.Open();
                        out.Open();
                        SetState(IWAIT);
                    }
                    case IWAIT: {
                        in.Update(timeout);
                        out.Update(timeout);
                        SetState(PROCESS);
                    }
                    case PROCESS: {
                        func->Process(io.Update(timeout), in.Update(timeout), out.Update(timeout));
                    }
                }
            } 
            /**----------------------------------------------------------------------------------------
             * exceptions
             *---------------------------------------------------------------------------------------**/
            catch (IOLocationExceptionDETACHED & ex) {
                INFO(ex.what());
                if(Kill(func, energy)){
                    WARNING("Exit = { what: " << ex.what() << " }");
                    return -1;
                }
                in.Close();
                out.Close();
                SetState(OWAIT);
            } catch (OLocationExceptionDETACHED & ex) {
                INFO("Exception = { what:" << ex.what() << " }");
                if(Kill(func, energy)){
                    WARNING("Exit = { what: " << ex.what() << " }");
                    return -1;
                }
                SetState(IWAIT);
            }  catch (ILocationExceptionDETACHED & ex) {
                INFO(ex.what());
                if(Kill(func, energy)){
                    WARNING("Exit = { what: " << ex.what() << " }");
                    return -1;
                }
                SetState(IWAIT);
            } catch (MonitorExceptionTIMEOUT & ex) {
                INFO(ex.what());
                if(Dead(func, energy)){
                    INFO("Exit = { what: " << ex.what() << " }");
                    return -1;
                }
            } catch (exception& ex) {
                ERROR("Exit = { what: " << ex.what() << " }");
                return -1;
            } catch (...) {
                ERROR("Exit = { }");
                return -1;
            }
            INFO("Process = { energy: " << energy << " }");
        }
        /**
         * Finish
         */
        INFO("Exit = { }");
        return 0;
    }
};
}
#endif /* MSpliter_H */

