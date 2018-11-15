/** 
 * File:   SProcess.h
 * Author: Luis Monteiro
 *
 * Created on January 20, 2017, 11:34 AM
 */
#ifndef SMODULE_H
#define SMODULE_H
/**
 */
#include <random>
/**
 */
#include "SProcess.h"
#include "SRoad.h"
/**
 */
class SModule : public SProcess<string, string> {
    static constexpr const char* URI     = "uri";
    static constexpr const char* VERBOSE = "verbose";
public:   
    using Key = string;
    using Val = string;
    /**
     * -----------------------------------------------------------------------------------------------------------------
     * Definitions
     * -----------------------------------------------------------------------------------------------------------------
     * state type
     */
    typedef enum {OPEN = 0, OWAIT, IWAIT, PROCESS, UPDATE} State;
    /**
     * 
     */
    using Group  = Command::Group;
    using Groups = Command::Groups;
    /**
     * -------------------------------------------------------------------------------------------------------------
     * Constructors
     * -------------------------------------------------------------------------------------------------------------
     * main constructor
     */
    SModule(const Command& cmd)
    : SProcess(cmd[""][0][URI], cmd[""][0].get(VERBOSE, 0), cmd) {}
    /**
     * default constructors
     */
    SModule()           = default;
    SModule(SModule&&)  = default;
    /**
     * -------------------------------------------------------------------------------------------------------------
     * Destructor 
     * -------------------------------------------------------------------------------------------------------------
     */
    virtual ~SModule()  = default;
    /**
     * -----------------------------------------------------------------------------------------------------------------
     * Check state
     * -----------------------------------------------------------------------------------------------------------------
     */
    inline State GetState(void) {
        return __state;
    }
    inline bool IsState(State s) {
        return __state == s;
    }
protected:
    /**
     * -----------------------------------------------------------------------------------------------------------------
     * Attributes
     * -----------------------------------------------------------------------------------------------------------------
     */
    State __state;
    /**
     * setter
     */
    inline void SetState(State s) {
        __state = s;
    }
    /**
     * -----------------------------------------------------------------------------------------------------------------
     * Helpers
     * -----------------------------------------------------------------------------------------------------------------
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
            } catch(RoadDetached& e){
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
        auto gen = Engine{random_device{}()}; 
        auto dis = Distribuition{100, 500}; 
        auto end = Clock::now() + timeout; 
        do {
            try {
                r1.Update();
                r2.Update();
            } catch(RoadDetached& e){
                STask::Sleep(chrono::milliseconds(dis(gen)));
                continue;
            }
        } while(Clock::now() < end);
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
    template<class T>
    void Update(vector<T>& out, vector<T>& err) {
        for (auto o = out.begin(), e = err.begin(); o != out.end() && e != err.end(); ++o, ++e) {
            for (auto it = e->begin(); it != e->end();) {
                if (it->second->Good()) {
                    o->insert(*it);
                    it = e->erase(it);
                    continue;
                }
                ++it;
            }
        }
    }
    template<class T>
    size_t Size(vector<T>& vec) {
        auto n = 0;
        for (auto& e : vec) {
            n += e.size();
        }
        return n;
    }
    
};

#endif /* SMODULE */
