/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SProcess.h
 * Author: Luis Monteiro
 *
 * Created on January 20, 2017, 11:34 AM
 */
#ifndef SPROCESS_H
#define SPROCESS_H
/**
 * std
 */
#include <map>
#include <vector>
#include <functional>
#if __GNUC__ < 5
#include <cstdlib>
static int stoi(std::string s){
    return strtol(s.c_str(),0,10);
}
static double stod(std::string s){
    return strtod(s.c_str(),0);
}
#endif
/**
 */
#include "SLog.h"
#include "STask.h"
#include "SCommand.h"
/**
 */
class SProcess : protected SLog {
    /**
     * -------------------------------------------------------------------------------------------------------------
     * Private types
     * -------------------------------------------------------------------------------------------------------------
     */
    using Task = STask;
public:
    /**
     * -------------------------------------------------------------------------------------------------------------
     * Public types
     * -------------------------------------------------------------------------------------------------------------
     */
    using Key     = string;
    using Value   = string;
    using Command = SCommand<Key, Value>;   
    using Base    = Command::Group;
    using Function= Command::Group;
    using Input   = Command::Group;
    using Output  = Command::Group;
    using Inputs  = Command::Groups;
    using Outputs = Command::Groups;
    /**
     * -------------------------------------------------------------------------------------------------------------
     * Tags
     * -------------------------------------------------------------------------------------------------------------
     * log level
     */
    static constexpr const char* VERBOSE = "verbose";  
    /**
     * resource identifier
     */
    static constexpr const char* URI = "uri";   
    /**
     * resource type
     */
    static constexpr const char* TYPE = "type";   
    /**
     * -------------------------------------------------------------------------------------------------------------
     * Constructors
     * -------------------------------------------------------------------------------------------------------------
     * main constructor
     */
    SProcess(const Key& uri, Base opt, Function f_opt, Inputs i_opt, Outputs o_opt) 
    : SLog(Command::Peek(opt, VERBOSE,  0)), __uri(uri), 
        __f_typ(Command::Peek(opt, TYPE, string())), 
        __f_opt(move(f_opt)), 
        __i_opt(move(i_opt)), 
        __o_opt(move(o_opt)) {       
    }
    /**
     * default constructors
     */
    SProcess()       = default;
    SProcess(SProcess&&) = default;
    /**
     * -------------------------------------------------------------------------------------------------------------
     * Destructor 
     * -------------------------------------------------------------------------------------------------------------
     */
    virtual ~SProcess()  = default;
    /**
     * -------------------------------------------------------------------------------------------------------------
     * Run 
     * -------------------------------------------------------------------------------------------------------------
     */
    inline int Run() {
        /**
         * call execute callback 
         */
        return Execute(__f_typ, __f_opt, __i_opt, __o_opt);
    }
    /**
     * -------------------------------------------------------------------------------------------------------------
     * Detach 
     * -------------------------------------------------------------------------------------------------------------
     */
    inline void Detach() {
        __worker = Task([this]() {
            try {
                return Run();
            } catch (exception& ex) {
                ERROR("Exit= " << ex.what());
                return -1;
            } catch (...) {
                return -1;
            }
        });
    }
    /**
     * -------------------------------------------------------------------------------------------------------------
     * Attach 
     * -------------------------------------------------------------------------------------------------------------
     */
    void Attach() {
        __worker = Task();
    }
protected:
    /**
     * process uri
     */
    Key __uri;
    /**
     * module type
     */
    Key __f_typ;
    /**
     * worker task
     */
    Task __worker;
    /**
     * -------------------------------------------------------------------------------------------------------------
     * Options
     * -------------------------------------------------------------------------------------------------------------
     **
     * function options
     */
    Function __f_opt;
    /**
     * input options
     */
    Inputs __i_opt;
    /**
     * output options
     */
    Outputs __o_opt;
    /**
     * -------------------------------------------------------------------------------------------------------------
     * Execute
     * -------------------------------------------------------------------------------------------------------------
     */
    virtual int Execute(const Key& func, const Function& opt, const Inputs& i_opt, const Outputs& o_opt) = 0;
    /**
     * -------------------------------------------------------------------------------------------------------------
     * Utilities
     * -------------------------------------------------------------------------------------------------------------
     */
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
    /**
     * -------------------------------------------------------------------------------------------------------------
     * Logging
     * -------------------------------------------------------------------------------------------------------------
     */
    inline void __DEBUG(const string& msg) {
        SLog::__DEBUG(__uri, msg);
    }
    inline void __INFO(const string& msg) {
        SLog::__INFO(__uri, msg);
    }
    inline void __WARNING(const string& msg) {
        SLog::__WARNING(__uri, msg);
    }
    inline void __ERROR(const string& msg) {
        SLog::__ERROR(__uri, msg);
    }
    inline void __CRITITAL(const string& msg) {
        SLog::__CRITITAL(__uri, msg);
    }
};

#endif /* SPROCESS_H */

