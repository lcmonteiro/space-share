/** 
 * File:   MProcess.h
 * Author: Luis Monteiro
 *
 * Created on January 26, 2017, 5:59 PM
 */
#ifndef SMODULE_PROCESS_H
#define SMODULE_PROCESS_H
/**
 */
#include <tuple>
#include <chrono>
/**
 */
#include "MProperties.h"
/**
 * space
 */
#include "SKernel/SProcess.h"
#include "SKernel/SConnector.h"
#include "SKernel/SLocation.h"
#include "SMonitor/SRoadMonitor.h"
#include "SMonitor/SCommandMonitor.h"
#include "SResource/SLocalResource.h"
/**
 * 
 */
namespace SModule {  
/**
 */
class Process : public SProcess {
public:
        /**
         * -------------------------------------------------------------------------------------------------------------
         * Definitions
         * -------------------------------------------------------------------------------------------------------------
         * state type
         */
        typedef enum { OPEN = 0, OWAIT, IWAIT, PROCESS, UPDATE } State;
        /**
         * function type
         */
        typedef function<int(const Group&, const Groups&, const Groups&)> Function;
        /**
         * module configuration definition 
         *      0 - module settings, 
         *      1 - function settings, 
         *      2 - input settings, 
         *      3 - output settings
         */
        typedef tuple<Group, Group, Groups, Groups> Config;        
        /**
         * -------------------------------------------------------------------------------------------------------------
         * Constructor
         * -------------------------------------------------------------------------------------------------------------
         */
        Process(const Key& uri, const Config& conf) 
        : SProcess(uri, get<0>(conf), get<1>(conf), get<2>(conf), get<3>(conf)), __state(OPEN) {
        }
        /**
         * default constructors
         */
        Process()          = default;
        Process(Process&&) = default;
        /**
         * -------------------------------------------------------------------------------------------------------------
         * Destructor
         * -------------------------------------------------------------------------------------------------------------
         */
        virtual ~Process() = default;
        /**
         * -------------------------------------------------------------------------------------------------------------
         * Check state
         * -------------------------------------------------------------------------------------------------------------
         */
        inline State GetState(void) {
                return __state;
        }
        inline bool IsState(State s) {
                return __state == s;
        }
protected:
        /**
         * -------------------------------------------------------------------------------------------------------------
         * Execute
         * -------------------------------------------------------------------------------------------------------------
         */
        int Execute(const Key& func, const Group& opt, const Groups& in_opt, const Groups& out_opt) override {
                static map<Key, Function> funcs({
                        {Properties::DECODE_Y, [this](const Group& f, const Groups& i, const Groups& o) {
                                return Ypsilon<Decoded::IOConnector, Decoded::IConnector, Decoded::OConnector>(f, i, o);
                        }},
                        {Properties::ENCODE, [this](const Group& f, const Groups& i, const Groups& o) {
                                return Transform<Decoded::IConnector, Container, Encoded::OConnector>(f, i, o);
                        }},
                        {Properties::ENCODE_Y, [this](const Group& f, const Groups& i, const Groups& o) {
                                return Ypsilon<Encoded::IOConnector, Encoded::IConnector, Encoded::OConnector>(f, i, o);
                        }},
                        {Properties::DECODE, [this](const Group& f, const Groups& i, const Groups& o) {
                                return Transform<Encoded::IConnector, Document, Decoded::OConnector>(f, i, o);
                        }}
                });
               return funcs.at(func)(opt, in_opt, out_opt);
        }
        /**
         * -------------------------------------------------------------------------------------------------------------
         * Attributes
         * -------------------------------------------------------------------------------------------------------------
         */
        inline void SetState(State s) {
                __state = s;
        }
private:
        /**
         * -------------------------------------------------------------------------------------------------------------
         * Communication
         * -------------------------------------------------------------------------------------------------------------
         * command link
         */
        typedef SCommandMonitor<Command, Message::SLocalResource> CommandMonitor;
        /**
         * -------------------------------------------------------------------------------------------------------------
         * Processes 
         * -------------------------------------------------------------------------------------------------------------
         * function state 
         */
        State __state;
        /**
         * transform process
         */
        template<class I, class D, class O>
        int Transform(const Group& opt, const Groups& i_opt, const Groups& o_opt);
        /**
         * transform process
         */
        template<class IO, class I, class O>
        int Ypsilon(const Group& opt, const Groups& i_opt, const Groups& o_opt);
        /**
         * --------------------------------------------------------------------------------------------------------------
         * Helpers
         * --------------------------------------------------------------------------------------------------------------
         * update resource
         */
        template<class R>
        R& Update(chrono::milliseconds timeout, R& r) {
                using Clock = chrono::steady_clock;
                using Engine = default_random_engine;
                using Distribuition = uniform_int_distribution<>;
                /**
                 * waiting loop 
                 */
                Engine gen{random_device{}()}; Distribuition dis{100, 500};
                for (auto now = Clock::now(), end = now + timeout; now < end; now = Clock::now()) {
                        try {
                                r.Update();
                        } catch(SRoadExceptionDETACHED<R>& e){
                                STask::Sleep(chrono::milliseconds(dis(gen)));
                                continue;
                        }
                        return r;
                }
                r.Update();
                return r;
        }
        template<class R1, class R2>
        void Update(chrono::milliseconds timeout, R1& r1, R2 r2) {
                using Clock = chrono::steady_clock;
                using Engine = default_random_engine;
                using Distribuition = uniform_int_distribution<>;
                /**
                 * waiting loop 
                 */
                Engine gen{random_device{}()}; Distribuition dis{100, 500};
                for (auto now = Clock::now(), end = now + timeout; now < end; now = Clock::now()) {
                        try {
                                r1.Update();
                                r2.Update();
                        } catch(SRoadExceptionDETACHED<R1>& e){
                                STask::Sleep(chrono::milliseconds(dis(gen)));
                                continue;
                        } catch(SRoadExceptionDETACHED<R2>& e){
                                STask::Sleep(chrono::milliseconds(dis(gen)));
                                continue;  
                        } 
                        return;
                }
                r1.Update();
                r2.Update();
        }
        /**
         * verify function
         */
        template<class F>
        bool Dead(F& func, size_t& energy){
                if (func->Dead()) {
                        if (--energy == 0) {
                                func->Recover();
                                return true;
                        }
                        func->Recover();
                }
                return false;
        }
        /**
         * kill process check
         */
        template<class F>
        bool Kill(F& func, size_t& energy){
                if (IsState(PROCESS)) {
                        if (--energy == 0) {
                                func->Recover();
                                return true;
                        }
                        func->Recover();
                }
                return false;
        }
        /**
         * -------------------------------------------------------------------------------------------------------------
         * Utilities
         * -------------------------------------------------------------------------------------------------------------
         * full status
         */
        template<class T>
        string Status(T& r);
        /**
         * status summary 
         */
        template<class T>
        string Summary(T& r);
};
}
#endif /* SMODULE_PROCESS_H */

