/**
 * ------------------------------------------------------------------------------------------------
 * File:   SProcess.h
 * Author: Luis Monteiro
 *
 * Created on January 20, 2017, 11:34 AM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SPROCESS_H
#define SPROCESS_H
/**
 * space
 */
#include "SLog.h"
#include "STask.h"
#include "SAddress.h"
#include "SQueue.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Process template
 * CMD  = command
 * DATA = data container
 * ------------------------------------------------------------------------------------------------
 */
template<class CMD, class DATA>
class SProcess : protected SLog {
    /**
     * ------------------------------------------------------------------------
     * Private types
     * ------------------------------------------------------------------------
     */
    using Task     = STask;
public:
    using Settings = DATA;
    using Command  = CMD;
    using Commands = SQueue<CMD>;
    /**
     * ------------------------------------------------------------------------
     * Constructors
     * ------------------------------------------------------------------------
     * main constructor
     */
    SProcess(const SAddress uri={}, uint8_t verbose = 0)
    : SLog(verbose), __uri(uri), __cmds(), __data(), __worker() {
    }
    /**
     * initial command constructor
     */
    SProcess(const Command& cmd, const SAddress uri={}, uint8_t verbose = 0)
    : SProcess(uri, verbose) {
	    __cmds.Insert(cmd);
    }
    /**
     * default constructors
     */
    SProcess()           = default;
    SProcess(SProcess&&) = default;
    /**
     * ------------------------------------------------------------------------
     * Destructor
     * ------------------------------------------------------------------------
     */
    virtual ~SProcess()  = default;
    /**
     * ------------------------------------------------------------------------
     * properties
     * ------------------------------------------------------------------------
     */
    inline  SProcess& Insert(const Command& cmd) {
        __cmds.Insert(cmd);
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Run
     * ------------------------------------------------------------------------
     */
    inline int Run() {
        return Execute();
    }
    /**
     * ------------------------------------------------------------------------
     * Detach 
     * ------------------------------------------------------------------------
     */
    inline void Detach() {
        __worker = Task([this]() {
            try {
                return Run();
            } catch (std::exception& ex) {
                ERROR("Unexpected Exit = " << ex.what());
                return -1;
            } catch (...) {
                ERROR("Unexpected Exit = ??");
                return -1;
            }
        });
    }
    /**
     * ------------------------------------------------------------------------
     * Attach
     * ------------------------------------------------------------------------
     */
    inline void Attach() {
        __worker = Task();
    }
    /**
     * ------------------------------------------------------------------------
     * Join
     * ------------------------------------------------------------------------
     */
    inline bool Join() {
        try {
            __worker.Join();
        } catch(...) {
            return false;
        }
        return true;
    }
protected:
    /**
     * ------------------------------------------------------------------------
     * properties
     * ------------------------------------------------------------------------
     */
    inline typename Commands::List __Commands() {
        return __cmds.Remove();
    }
    /**
     * ------------------------------------------------------------------------
     * Execute
     * ------------------------------------------------------------------------
     */
    virtual int Execute() = 0;
    /**
     * ------------------------------------------------------------------------
     * Logging
     * ------------------------------------------------------------------------
     */
    inline void __DEBUG(const std::string& msg) {
        SLog::__DEBUG(__uri, msg);
    }
    inline void __INFO(const std::string& msg) {
        SLog::__INFO(__uri, msg);
    }
    inline void __WARNING(const std::string& msg) {
        SLog::__WARNING(__uri, msg);
    }
    inline void __ERROR(const std::string& msg) {
        SLog::__ERROR(__uri, msg);
    }
    inline void __CRITITAL(const std::string& msg) {
        SLog::__CRITITAL(__uri, msg);
    }
private:
    /**
     * ------------------------------------------------------------------------
     * Variables
     * ------------------------------------------------------------------------
     * uri
     */
    SAddress __uri;
    /**
     * commands
     */
    Commands __cmds;
    /**
     * data
     */
    Settings __data;
    /**
     * worker task
     */
    Task __worker;
};

#endif /* SPROCESS_H */

