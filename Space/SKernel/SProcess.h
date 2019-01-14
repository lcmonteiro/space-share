/** 
 * File:   SProcess.h
 * Author: Luis Monteiro
 *
 * Created on January 20, 2017, 11:34 AM
 */
#ifndef SPROCESS_H
#define SPROCESS_H
/**
 */
#include "SLog.h"
#include "STask.h"
#include "SAddress.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Process template
 * S=settings type
 * ------------------------------------------------------------------------------------------------
 */
template<class S>
class SProcess : protected SLog {
    /**
     * ------------------------------------------------------------------------
     * Private types
     * ------------------------------------------------------------------------
     */
    using Task     = STask;
public:   
    using Settings = S;
    /**
     * ------------------------------------------------------------------------
     * Constructors
     * ------------------------------------------------------------------------
     * main constructor
     */
    SProcess(const Settings& set, const SAddress uri={}, uint8_t verbose = 0)
    : SLog(verbose), __set(set), __uri(uri), __worker() {  
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
            } catch (exception& ex) {
                ERROR("Exit= " << ex.what());
                return -1;
            } catch (...) {
                ERROR("Exit= ");
                return -1;
            }
        });
    }
    /**
     * ------------------------------------------------------------------------
     * Attach 
     * ------------------------------------------------------------------------
     */
    void Attach() {
        __worker = Task();
    }
protected:
    /**
     * ------------------------------------------------------------------------
     * Variables
     * ------------------------------------------------------------------------
     * settings 
     */
    Settings __set;
    /**
     * uri
     */
    SAddress __uri;
    /**
     * worker task
     */
    Task __worker;
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

