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
#include "SLocalResource.h"
#include "SCommandMonitor.h"
/**
 * Share Kernel
 */
#include "SModule.h"
/**
 */
class SMachine {
public:
    /**
     * machine identification
     */
    using Command = SModule::Command;
    using Key     = SModule::Key;
    /**
     * -----------------------------------------------------------------------------------------------------------------
     * Constructors / Destructor
     * -----------------------------------------------------------------------------------------------------------------
     * main constructor
     */
    SMachine(const Key& uri, const vector<SModule::Command> conf = {});
    /**
     * move constructor
     */
    SMachine(SMachine&& orig) = default;
    /**
     * destructor 
     */
    virtual ~SMachine() = default;
    /**
     * -----------------------------------------------------------------------------------------------------------------
     * Interface
     * -----------------------------------------------------------------------------------------------------------------
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
    inline int IsState(SModule::State s) {
        int n = 0;
        for(auto& m:__modules){
            n += m.second->IsState(s) ? 1 : 0;
        }
        return n;
    }
    /**
     * good
     * @return - good rate
     */
    inline float Good() {
        return float(IsState(SModule::PROCESS)) / __modules.size();
    }
    /**
     * bad
     * @return - bad rate
     */
    inline float Bad() {
        return 1.0 - Good();
    }
    /**
     * -----------------------------------------------------------------------------------------------------------------
     * Utilities
     * -----------------------------------------------------------------------------------------------------------------
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
    void ProcessData(Command cmd);
    /**
     * insert module
     */
    void InsertModule(Key id, const Command& cmd);
    /**
     * update module
     */
    void UpdateModule(Key id, const Command& cmd);
    /**
     * remove module
     */
    void RemoveModule(Key id);
private:
    /**
     * -----------------------------------------------------------------------------------------------------------------
     * Variables
     * -----------------------------------------------------------------------------------------------------------------
     * private definitions
     */ 
    using Modules = map<SModule::Key, unique_ptr<SModule>>;
    using Monitor = SCommandMonitor<SModule::Command, Message::SLocalResource>;
    /**
     * machine modules
     */
    Modules __modules;
    /**
     * command monitor
     */
    Monitor __monitor;
    /**
     * -----------------------------------------------------------------------------------------------------------------
     * Helpers
     * -----------------------------------------------------------------------------------------------------------------
     * make configuration
     */
    // inline Module::Config MakeConfig(Module::Command::Options opt) {
    //     return Module::Config {
    //         opt.at("M").front(), opt.at("F").front(), opt.at("I"), opt.at("O")
    //     };
    // }
    /**
     * make to uri 
     */
    inline SModule::Key MakeURI(SModule::Key uri) {
        return (__uri + "." + uri);
    }
};

#endif /* SMACHINE_H */

