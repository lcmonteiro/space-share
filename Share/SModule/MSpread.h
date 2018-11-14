// /** 
//  * File:   MProcess.h
//  * Author: Luis Monteiro
//  *
//  * Created on January 26, 2017, 5:59 PM
//  */
// #ifndef SMODULE_PROCESS_H
// #define SMODULE_PROCESS_H
// /**
//  */
// #include <tuple>
// #include <chrono>
// /**
//  */
// #include "MProperties.h"
// /**
//  * space kernel
//  */
// #include "SProcess.h"
// #include "SConnector.h"
// #include "SLocation.h"
// /**
//  * space monitor
//  */
// #include "SRoadMonitor.h"
// #include "SCommandMonitor.h"
// /**
//  * space resource
//  */
// #include "SLocalResource.h"
// /**
//  * 
//  */
// namespace SModule {  
// /**
//  */
// class Process : public SProcess {
// public:
//     /**
//      * -----------------------------------------------------------------------------------------------------------------
//      * Definitions
//      * -----------------------------------------------------------------------------------------------------------------
//      * state type
//      */
//     typedef enum { OPEN = 0, OWAIT, IWAIT, PROCESS, UPDATE } State;
//     /**
//      * function type
//      */
//     typedef function<int(const Function&, const Inputs&, const Outputs&)> pFunction;
//     /**
//      * module configuration definition 
//      *      0 - module settings, 
//      *      1 - function settings, 
//      *      2 - input settings, 
//      *      3 - output settings
//      */
//     typedef tuple<Base, Function, Inputs, Outputs> Config;    
//     /**
//      * -----------------------------------------------------------------------------------------------------------------
//      * Constructor
//      * -----------------------------------------------------------------------------------------------------------------
//      */
//     Process(const Key& uri, const Config& conf) 
//     : SProcess(uri, get<0>(conf), get<1>(conf), get<2>(conf), get<3>(conf)), __state(OPEN) {
//     }
//     /**
//      * default constructors
//      */
//     Process()          = default;
//     Process(Process&&) = default;
//     /**
//      * -----------------------------------------------------------------------------------------------------------------
//      * Destructor
//      * -----------------------------------------------------------------------------------------------------------------
//      */
//     virtual ~Process() = default;
//     /**
//      * -----------------------------------------------------------------------------------------------------------------
//      * Check state
//      * -----------------------------------------------------------------------------------------------------------------
//      */
//     inline State GetState(void) {
//         return __state;
//     }
//     inline bool IsState(State s) {
//         return __state == s;
//     }
// protected:
//     /**
//      * -----------------------------------------------------------------------------------------------------------------
//      * Execute
//      * -----------------------------------------------------------------------------------------------------------------
//      */
//     int Execute(const Key& func, const Function& opt, const Inputs& in_opt, const Outputs& out_opt) override {
//         static map<Key, pFunction> funcs({
//             {Properties::DECODE_Y, [this](const Function& f, const Inputs& i, const Outputs& o) {
//                 return Ypsilon<Decoded::IOConnector, Decoded::IConnector, Decoded::OConnector>(f, i, o);
//             }},
//             {Properties::ENCODE, [this](const Function& f, const Inputs& i, const Outputs& o) {
//                 return Transform<Decoded::IConnector, Container, Encoded::OConnector>(f, i, o);
//             }},
//             {Properties::ENCODE_Y, [this](const Function& f, const Inputs& i, const Outputs& o) {
//                 return Ypsilon<Encoded::IOConnector, Encoded::IConnector, Encoded::OConnector>(f, i, o);
//             }},
//             {Properties::DECODE, [this](const Function& f, const Inputs& i, const Outputs& o) {
//                 return Transform<Encoded::IConnector, Document, Decoded::OConnector>(f, i, o);
//             }}
//         });
//         return funcs.at(func)(opt, in_opt, out_opt);
//     }
//     /**
//      * -----------------------------------------------------------------------------------------------------------------
//      * Attributes
//      * -----------------------------------------------------------------------------------------------------------------
//      */
//     inline void SetState(State s) {
//         __state = s;
//     }
// private:
//     /**
//      * -----------------------------------------------------------------------------------------------------------------
//      * Communication
//      * -----------------------------------------------------------------------------------------------------------------
//      * command link
//      */
//     typedef SCommandMonitor<Command, Message::SLocalResource> CommandMonitor;
//     /**
//      * -----------------------------------------------------------------------------------------------------------------
//      * Processes 
//      * -----------------------------------------------------------------------------------------------------------------
//      * function state 
//      */
//     State __state;
//     /**
//      * transform process
//      */
//     template<class I, class D, class O>
//     int Transform(const Function& opt, const Inputs& i_opt, const Outputs& o_opt);
//     /**
//      * transform process
//      */
//     template<class IO, class I, class O>
//     int Ypsilon(const Function& opt, const Inputs& i_opt, const Outputs& o_opt);
//     /**
//      * -----------------------------------------------------------------------------------------------------------------
//      * Helpers
//      * -----------------------------------------------------------------------------------------------------------------
//      * update resource
//      */
//     template<class R>
//     R& Update(chrono::milliseconds timeout, R& r) {
//         using Clock = chrono::steady_clock;
//         using Engine = default_random_engine;
//         using Distribuition = uniform_int_distribution<>;
//         /**
//          * waiting loop 
//          */
//         Engine gen{random_device{}()}; Distribuition dis{100, 500};
//         for (auto now = Clock::now(), end = now + timeout; now < end; now = Clock::now()) {
//             try {
//                 r.Update();
//             } catch(RoadDetached& e){
//                 STask::Sleep(chrono::milliseconds(dis(gen)));
//                 continue;
//             }
//             return r;
//         }
//         r.Update();
//         return r;
//     }
//     template<class R1, class R2>
//     void Update(chrono::milliseconds timeout, R1& r1, R2 r2) {
//         using Clock = chrono::steady_clock;
//         using Engine = default_random_engine;
//         using Distribuition = uniform_int_distribution<>;
//         /**
//          * waiting loop 
//          */
//         auto gen = Engine{random_device{}()}; 
//         auto dis = Distribuition{100, 500}; 
//         auto end = Clock::now() + timeout; 
//         do {
//             try {
//                 r1.Update();
//                 r2.Update();
//             } catch(RoadDetached& e){
//                 STask::Sleep(chrono::milliseconds(dis(gen)));
//                 continue;
//             }
//         } while(Clock::now() < end);
//     }
//     /**
//      * verify function
//      */
//     template<class F>
//     bool Dead(F& func, size_t& energy){
//         if (func->Dead()) {
//             if (--energy == 0) {
//                 func->Recover();
//                 return true;
//             }
//             func->Recover();
//         }
//         return false;
//     }
//     /**
//      * kill process check
//      */
//     template<class F>
//     bool Kill(F& func, size_t& energy){
//         if (IsState(PROCESS)) {
//             if (--energy == 0) {
//                 func->Recover();
//                 return true;
//             }
//             func->Recover();
//         }
//         return false;
//     }
//     /**
//      * -----------------------------------------------------------------------------------------------------------------
//      * Utilities
//      * -----------------------------------------------------------------------------------------------------------------
//      * full status
//      */
//     template<class T>
//     string Status(T& r);
//     /**
//      * status summary 
//      */
//     template<class T>
//     string Summary(T& r);
// };
// }
// #endif /* SMODULE_PROCESS_H */

