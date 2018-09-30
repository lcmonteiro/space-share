/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SMachine.h
 * Author: root
 *
 * Created on July 4, 2017, 11:51 PM
 */
#ifndef SMACHINE_H
#define SMACHINE_H
/**
 * Space Kernel
 */
#include "STask.h"
#include "SLocalResource.h"
/**
 * Share Kernel
 */
#include "SModule.h"
/**
 */
class SMachine {
    using Channel = Message::SLocalResource;
public:
    /**
     * machine identification
     */
    using Key = Module::Key;
    /**
     * -------------------------------------------------------------------------------------------------------------
     * Constructors / Destructor
     * -------------------------------------------------------------------------------------------------------------
     * main constructors
     */
    SMachine(const Key& uri, const vector<Module::Config> conf = {});
    
    SMachine(const Key& uri, const vector<string> conf = {});
    /**
     * move constructor
     */
    SMachine(SMachine&& orig) = default;
    /**
     * destructor 
     */
    virtual ~SMachine() = default;
    /**
     * -------------------------------------------------------------------------------------------------------------
     * Interface
     * -------------------------------------------------------------------------------------------------------------
     * process
     */
    bool Process(chrono::milliseconds timeout);
    /**
     * -------------------------------------------------------------------------------------------------------------
     * Operators
     * -------------------------------------------------------------------------------------------------------------
     * move operator
     */
    SMachine& operator=(SMachine&& orig) = default;
    /**
     * -------------------------------------------------------------------------------------------------------------
     * Checkup 
     * -------------------------------------------------------------------------------------------------------------
     * check state
     * @param s - state
     * @return  - number of modules in that state 
     */
    inline int IsState(Module::State s) {
        int n = 0;
        for(auto& m:__modules){
            n += m.second.IsState(s) ? 1 : 0;
        }
        return n;
    }
    /**
     * good
     * @return - good rate
     */
    inline float Good() {
        return float(IsState(Module::PROCESS)) / __modules.size();
    }
    /**
     * bad
     * @return - bad rate
     */
    inline float Bad() {
        return 1.0 - Good();
    }
    /**
     * -------------------------------------------------------------------------------------------------------------
     * Utilities
     * -------------------------------------------------------------------------------------------------------------
     * print configuration
     */
//    void Print(const Config& conf);
protected:
    /**
     * machine uri
     */
    const Key __uri;
    /**
     * process data
     */
    void ProcessData(string line);
    /**
     * insert module
     */
    void InsertModule(Module::Key id, Module::Config config);
    /**
     * update module
     */
    void UpdateModule(Module::Key id, Module::Config config);
    /**
     * remove module
     */
    void RemoveModule(Module::Key id);
private:
    /**
     * -------------------------------------------------------------------------------------------------------------
     * Variables
     * -------------------------------------------------------------------------------------------------------------
     * private definitions
     */
    typedef map<Module::Key, Module> Modules; 
    /**
     * machine modules
     */
    Modules __modules;
    /**
     * link to machine
     */
    Channel __link;
    /**
     * -------------------------------------------------------------------------------------------------------------
     * Helpers
     * -------------------------------------------------------------------------------------------------------------
     * make configuration
     */
    inline Module::Config MakeConfig(Module::Command::Options opt) {
        return Module::Config {
            opt.at("M").front(), opt.at("F").front(), opt.at("I"), opt.at("O")
        };
    }
    /**
     * make to uri 
     */
    inline Module::Key MakeURI(Module::Key uri) {
        return (__uri + "." + uri);
    }
};

#endif /* SMACHINE_H */

