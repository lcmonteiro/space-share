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
	    __cmds.insert(cmd);
    }
    /**
     * default constructors
     */
    SProcess()           = default;
    SProcess(SProcess&&) = default;
    /**
     * ------------------------------------------------------------------------
     * properties
     * ------------------------------------------------------------------------
     */
    inline  SProcess& insert(const Command& cmd) {
        __cmds.insert(cmd);
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Run
     * ------------------------------------------------------------------------
     */
    inline int run() {
        return _execute();
    }
    /**
     * ------------------------------------------------------------------------
     * Start - Task 
     * ------------------------------------------------------------------------
     */
    inline void start() {
        __worker = Task([this]() {
            try {
                return run();
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
     * Stop - Task
     * ------------------------------------------------------------------------
     */
    inline void stop() {
        __worker = Task();
    }
    /**
     * ------------------------------------------------------------------------
     * Join - Task
     * ------------------------------------------------------------------------
     */
    inline void join() {
        __worker.join();
    }
protected:
    /**
     * ------------------------------------------------------------------------
     * Properties
     * ------------------------------------------------------------------------
     */
    inline typename Commands::List _commands() {
        return __cmds.remove();
    }
    /**
     * ------------------------------------------------------------------------
     * Execute
     * ------------------------------------------------------------------------
     */
    virtual int _execute() = 0;
    /**
     * ------------------------------------------------------------------------
     * Logging
     * ------------------------------------------------------------------------
     */
    inline void _debug  (const std::string& msg) { SLog::_debug  (__uri, msg); }
    inline void _info   (const std::string& msg) { SLog::_info   (__uri, msg); }
    inline void _warning(const std::string& msg) { SLog::_warning(__uri, msg); }
    inline void _error  (const std::string& msg) { SLog::_error  (__uri, msg); }
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
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SPROCESS_H */

