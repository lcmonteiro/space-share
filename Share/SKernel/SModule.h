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
#include "SEnergy.h"
#include "SRoad.h"
/**
 * ---------------------------------------------------------------------------------------------------------------------*
 * exceptions 
 * ---------------------------------------------------------------------------------------------------------------------
 **/
typedef class SModuleException : public logic_error {
public:
    using logic_error::logic_error;
    /**
     * constructor
     */
    SModuleException(const string& msg):logic_error(msg){
    }
} ModuleException;

typedef class SModuleExceptionDead : public SModuleException {
public:
    using SModuleException::SModuleException;
    /**
     * constructor
     */
    SModuleExceptionDead(string s) : SModuleException(s) {
    }
} ModuleExceptionDEAD;
/**
 * ---------------------------------------------------------------------------------------------------------------------*
 * module 
 * ---------------------------------------------------------------------------------------------------------------------
 **/
class SModule : public SProcess<string, string>, public SEnergy<ModuleExceptionDEAD> {
public:   
    static constexpr const char* URI     = "uri";
    static constexpr const char* VERBOSE = "verbose";
    static constexpr const char* ENERGY  = "energy";
    /**
     * -----------------------------------------------------------------------------------------------------------------
     * Definitions
     * -----------------------------------------------------------------------------------------------------------------
     * state type
     */
    typedef enum {OPEN = 0, OWAIT, IWAIT, PROCESS, UPDATE} State;
    /**
     */
    using Key = string;
    using Val = string;
    /**
     */
    using Group  = Command::Group;
    using Groups = Command::Groups;
    /**
     * -------------------------------------------------------------------------------------------------------------
     * Constructors
     * -------------------------------------------------------------------------------------------------------------
     * main constructor
     */
    SModule(const Command& cmd):
        // derivate 
        SProcess(cmd[""][0][URI], cmd[""][0].get(VERBOSE, 0), cmd),
        SEnergy(cmd[""][0].get(ENERGY, 1)),
        // variable
        __state(OPEN) 
    {}
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
     * verify function
     */
    template<class F>
    bool Dead(F& func, size_t& energy){
        // if (func->Dead()) {
        //     if (--energy == 0) {
        //         func->Recover();
        //         return true;
        //     }
        //     func->Recover();
        // }
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
    void SUpdate(vector<T>& out, vector<T>& err) {
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
