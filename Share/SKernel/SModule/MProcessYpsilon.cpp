/*
 * File:   MProcessYpsilon.cpp
 * Author: Luis Monteiro
 *
 * Created on January 26, 2017, 5:59 PM
 **
 * ---------------------------------------------------------------------------------------------------------------------
 * Includes
 * ---------------------------------------------------------------------------------------------------------------------
 **
 * Module
 */
#include "MProcess.h"
#include "MConnectors.h"
#include "MFunctions.h"
/**
 * Space Kernel
 */
#include "SHash.h"
/**
 * Space Resource
 */
#include "SResourceMonitor.h"
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * Main function
 * ---------------------------------------------------------------------------------------------------------------------
 */
template<class IO, class I, class O>
int SModule::Process::Ypsilon(const Function& opt, const Inputs& in_opt, const Outputs& out_opt) {
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
    using IOBuilder = SIOput::Builder<IO>;
    using IBuilder  = SInput::Builder<I>;
    using YBuilder  = SYpsilon::Builder<IO, I, O>;
    using OBuilder  = SOutput::Builder<O>;  
    /**
     * input timeout 
     */
    chrono::milliseconds timeout(Command::Peek(opt, Properties::TIMEOUT, 1000));
    /**
     * process delay
     */
    chrono::milliseconds delay(Command::Peek(opt, Properties::DELAY, 10));
    /**
     */
    STask::Sleep(delay);
    /**
     * configure IO
     */
    IOLocation io;
    io.Insert(IOBuilder::Build(opt));
    /**
     * configure input
     */
    ILocation in;
    for(auto& o: in_opt) {
        in.Insert(IBuilder::Build(o));
    }
    /**
     * configure output
     */
    OLocation out;
    for(auto& o: out_opt) {
        out.Insert(OBuilder::Build(o));
    }
    /**
     * configure function
     */
    auto func = YBuilder::Build(opt);
    /**
     * process
     */
    auto energy = Command::Peek(opt, Properties::ENERGY, size_t(1));
    /**
     * main loop 
     */
    while (STask::Sleep()) {
        try {
            /**
             * process
             */
            switch(GetState()) {
                default: {
                    SetState(OPEN);
                }
                case OPEN: {
                   /*------------------------------------------------------------------------------*
                    * OPEN State
                    *------------------------------------------------------------------------------*/
                    io.Open();
                    SetState(OWAIT);
                }
                case OWAIT: {
                    /*-----------------------------------------------------------------------------*
                     * OWAIT State
                     *-----------------------------------------------------------------------------*/
                    io.Update(timeout);
                    in.Open();
                    out.Open();
                    SetState(IWAIT);
                }
                case IWAIT: {
                    /*-----------------------------------------------------------------------------*
                     * IWAIT State
                     *-----------------------------------------------------------------------------*/
                    in.Update(timeout);
                    out.Update(timeout);
                    SetState(PROCESS);
                }
                case PROCESS: {
                    /*-----------------------------------------------------------------------------*
                     * PROCESS State
                     *-----------------------------------------------------------------------------*/
                    func->Process(io.Update(timeout), in.Update(timeout), out.Update(timeout));
                }
            }
            /**
             */
        } catch (IOLocationExceptionDETACHED & ex) {
            /**
             * log
             */
            INFO(ex.what());
            /**
             */
            if(Kill(func, energy)){
                WARNING("Exit = { what: " << ex.what() << " }");
                return -1;
            }
            in.Close();
            out.Close();
            SetState(OWAIT);
        } catch (OLocationExceptionDETACHED & ex) {
            /**
             * log
             */
            INFO("Exception = { what:" << ex.what() << " }");
            /**
             */
            if(Kill(func, energy)){
                WARNING("Exit = { what: " << ex.what() << " }");
                return -1;
            }
            SetState(IWAIT);
        }  catch (ILocationExceptionDETACHED & ex) {
            /**
             * log
             */
            INFO(ex.what());
            /**
             */
            if(Kill(func, energy)){
                WARNING("Exit = { what: " << ex.what() << " }");
                return -1;
            }
            SetState(IWAIT);
        } catch (MonitorExceptionTIMEOUT & ex) {
            /**
             * log
             */
            INFO(ex.what());
            /**
             */
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
/**
 * template implementations
 */
template int SModule::Process::Ypsilon<Decoded::IOConnector, Decoded::IConnector, Decoded::OConnector>(
    const SProcess::Function& opt, const SProcess::Inputs& in_opt, const SProcess::Outputs& out_opt
);
template int SModule::Process::Ypsilon<Encoded::IOConnector, Encoded::IConnector, Encoded::OConnector>(
    const SProcess::Function& opt, const SProcess::Inputs& in_opt, const SProcess::Outputs& out_opt
);
