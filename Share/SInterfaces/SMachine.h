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
#include "SBaseModule.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Extend module properties
 * ------------------------------------------------------------------------------------------------
 */
namespace Module {
using Property = const SText;
Property TYPE    = "type";
namespace Type {
    Properties ENCODE = "encode";
    Properties DECODE = "decode";
}
}
/**
 * ------------------------------------------------------------------------------------------------
 * SMachine
 * ------------------------------------------------------------------------------------------------
 */
class SMachine {
public:
    /**
     * ------------------------------------------------------------------------
     * helper types
     * ------------------------------------------------------------------------
     */
    using Command = SModule::Command;
    using Key     = SModule::Key;
    using Val     = SModule::Val;
    using Link    = SModule::Link;
    using Time    = std::chrono::milliseconds;
    /**
     * ------------------------------------------------------------------------
     * config object
     * ------------------------------------------------------------------------
     */
    class Config : public std::vector<Command> {
    public:
        using std::vector<Command>::vector;
        /**
         * ------------------------------------------------
         * add
         * ------------------------------------------------
         */
        inline Config& add(const Command& cmd) {
            emplace_back(cmd);
            return *this;
        }
        /**
         * ------------------------------------------------
         * swap
         * ------------------------------------------------
         */
        inline Config& swap(Key k1, Key k2) {
            for (auto& m : *this) {
                m.swap(k1, k2);
            }
            return *this;
        }
        /**
         * ------------------------------------------------
         * update
         * ------------------------------------------------
         */
        inline Config& update(Key k1, Key k2, Val val) {
            for (auto& m : *this){
                m.update(k1, k2, val);
            }
            return *this;
        }
    };
    /**
     * ------------------------------------------------------------------------
     * Constructores
     * ------------------------------------------------------------------------
     * defaults
     * ----------------------------------------------------
     */
    SMachine(SMachine&&) = default;
    /**
     * ----------------------------------------------------
     * main
     * ----------------------------------------------------
     */
    SMachine(const SAddress& uri, const Config& conf = {});
    /**
     * ------------------------------------------------------------------------
     * Operatores
     * ------------------------------------------------------------------------
     * move
     * ----------------------------------------------------
     */
    SMachine& operator=(SMachine&&) = default;
    /**
     * ------------------------------------------------------------------------
     * Interface
     * ------------------------------------------------------------------------
     * process
     * @timeout
     * ----------------------------------------------------
     */
    bool process(Time timeout);
    /**
     * ----------------------------------------------------
     * wait for all modules join
     * ----------------------------------------------------
     */
    void wait();
    /**
     * ------------------------------------------------------------------------
     * Checkup 
     * ------------------------------------------------------------------------
     * check state (greaten then)
     * @param s - state
     * @return  - number of modules in that state
     * ---------------------------------------------------- 
     */
    inline int state_gt(SModule::State s) {
        int n = 0;
        for(auto& m : __modules) {
            n += m.second->state_gt(s) ? 1 : 0;
        }
        return n;
    }
    /**
     * ----------------------------------------------------
     * good
     * @return - good rate
     * ----------------------------------------------------
     */
    inline float good() {
        return float(state_gt(SModule::PLAY)) / __modules.size();
    }
    /**
     * ------------------------------------------------------------------------
     * Utilities
     * ------------------------------------------------------------------------
     * print configuration
     * ----------------------------------------------------
     */
    static void Print(const Config& conf);
    /**
     * ----------------------------------------------------
     *  create module
     * ----------------------------------------------------
     */
    static Link CreateModule(const Command& cmd);
protected:
    /**
     * ------------------------------------------------------------------------
     * helper types
     * ------------------------------------------------------------------------
     */
    using CommandMonitor  = SCommandMonitor<Command, Message::SLocalResource>;
    using ResourceMonitor = SResourceMonitor<Monitor::Resource::SIndirect>;
    using Modules         = std::map<Key, Link>;
    /**
     * ------------------------------------------------------------------------
     * Internal process
     * ------------------------------------------------------------------------
     * process command
     * ----------------------------------------------------
     */
    void _process_cmd(const Command& cmd);
    /**
     * ----------------------------------------------------
     * insert module
     * ----------------------------------------------------
     */
    void _insert_module(Key id, const Command& cmd);
    /**
     * ----------------------------------------------------
     * update module
     * ----------------------------------------------------
     */
    void _update_module(Key id, const Command& cmd);
    /**
     * ----------------------------------------------------
     * remove module
     * ----------------------------------------------------
     */
    void _remove_module(Key id);
private:
    /**
     * ------------------------------------------------------------------------
     * Variables
     * ------------------------------------------------------------------------
     * machine uri
     * --------------------------------
     */
    SAddress __uri;
    /**
     * --------------------------------
     * machine modules
     * --------------------------------
     */
    Modules __modules;
    /**
     * --------------------------------
     * command monitor
     * --------------------------------
     */
    CommandMonitor __monitor;
    /**
     * ------------------------------------------------------------------------
     * Helpers
     * ------------------------------------------------------------------------
     * make to uri 
     * ----------------------------------------------------
     */
    inline SAddress __make_uri(SAddress uri) {
        return (__uri + uri);
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SMACHINE_H */

