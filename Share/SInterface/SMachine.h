/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SMachine.h
 * Author: Luis Monteiro
 *
 * Created on July 4, 2017, 11:51 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SMACHINE_H
#define SMACHINE_H
/**
 * Space
 */
#include "SLocalResource.h"
#include "SCommandMonitor.h"
/**
 * share - module
 */
#include "MBase.h"
/**
 */
class SMachine {
    using ResourceMonitor = SResourceMonitor<Monitor::Resource::SIndirect>;
public:
    /**
     * helper types
     */
    using Command = SModule::Command;
    using Key     = SModule::Key;
    using Val     = SModule::Val;
    /**
     * ------------------------------------------------------------------------
     * config object
     * ------------------------------------------------------------------------
     */
    class Config : public vector<Command> {
    public:
        using vector<Command>::vector;
        /**
         * add
         */
        inline Config& Add(const Command& cmd) {
            emplace_back(cmd);
            return *this;
        }
        /**
         * swap
         */
        inline Config& Swap(Key k1, Key k2) {
            for (auto& m : *this){
                m.Swap(k1, k2);
            }
            return *this;
        }
        /**
         * update
         */
        inline Config& Update(Key k1, Key k2, Val val) {
            for (auto& m : *this){
                m.Update(k1, k2, val);
            }
            return *this;
        }
    };
    /**
     * ------------------------------------------------------------------------
     * Defaults
     * ------------------------------------------------------------------------
     * constructor
     */
    SMachine(SMachine&& orig)       = default;
    /**
     * destructor 
     */
    virtual ~SMachine()             = default;
    /**
     * operators
     */
    SMachine& operator=(SMachine&&) = default;
    /**
     * ------------------------------------------------------------------------
     * Constructor
     * ------------------------------------------------------------------------
     * main constructor
     */
    SMachine(const SAddress& uri, const Config& conf = {});
    /**
     * ------------------------------------------------------------------------
     * Interface
     * ------------------------------------------------------------------------
     * process
     */
    bool Process(chrono::milliseconds timeout);
    /**
     * wait for all modules join
     */
    bool Join();
    /**
     * ------------------------------------------------------------------------
     * Checkup 
     * ------------------------------------------------------------------------
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
        return float(IsState(SModule::PLAY)) / __modules.size();
    }
    /**
     * bad
     * @return - bad rate
     */
    inline float Bad() {
        return 1.0 - Good();
    }
    /**
     * ------------------------------------------------------------------------
     * Utilities
     * ------------------------------------------------------------------------
     * print configuration
     */
//    void Print(const Config& conf);
protected:
    /**
     * ------------------------------------------------------------------------
     * Internal process
     * ------------------------------------------------------------------------
     **
     * process data
     */
    void ProcessData(const Command& cmd);
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
     * ------------------------------------------------------------------------
     * Variables
     * ------------------------------------------------------------------------
     * private definitions
     */ 
    using Modules = std::map<SModule::Key, SModule::Link>;
    using Monitor = SCommandMonitor<SModule::Command, Message::SLocalResource>;
    /**
     * machine uri
     */
    SAddress __uri;
    /**
     * machine modules
     */
    Modules __modules;
    /**
     * command monitor
     */
    Monitor __monitor;
    /**
     * ------------------------------------------------------------------------
     * Helpers
     * ------------------------------------------------------------------------
     * make to uri 
     */
    inline SAddress MakeURI(SAddress uri) {
        return (__uri + uri);
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SMACHINE_H */

