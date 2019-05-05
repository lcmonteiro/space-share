/**
 * ------------------------------------------------------------------------------------------------
 * File: STask.cpp
 * Author: Monteiro
 *
 * Created on November 26, 2016, 12:37 PM
 * ------------------------------------------------------------------------------------------------
 **
 * std
 */
#include <iostream>
/**
 * space
 */
#include "STask.h"
#include "SMonitorHandler.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Manager Tasks 
 * ------------------------------------------------------------------------------------------------
 * Init
 * --------------------------------------------------------
 */
void STask::_init(std::thread::id id) {
    _insert(id, this);
}
/**
 * --------------------------------------------------------
 * End - interrupt thread if is running 
 * --------------------------------------------------------
 */
void STask::_end(std::thread::id  id) {
    if (joinable()) {
        try {
            interrupt();
            #ifdef __DEBUG__
                cout << __func__ << "::" 
                    << __LINE__ << "::join(" << get_id() << ")" 
                << endl;
            #endif
            join();
        } catch(...) {
            #ifdef __DEBUG__
                cout << __func__ << "::" 
                    << __LINE__ << "::detach(" << get_id() << ")" 
                << endl;
            #endif
            detach();
        }
        _remove(id);
    }
}
/*
 * ------------------------------------------------------------------------------------------------
 * Global
 * ------------------------------------------------------------------------------------------------ 
 * Enable init task
 * --------------------------------------------------------
 */
STask& STask::Enable() {
    _insert(std::this_thread::get_id(), &__init); 
    return __init;
}
/**
 * --------------------------------------------------------
 * Current task
 * --------------------------------------------------------
 */
STask& STask::Instance() {
    return *_find(std::this_thread::get_id());
}
/**
 * --------------------------------------------------------
 * Sleep current task
 * --------------------------------------------------------
 */
bool STask::Sleep(const Time& timeout) {
    try {
        SStaticMonitorHandler().wait(timeout);
    } catch(const MonitorExceptionTIMEOUT& ){
        return true;
    }
    return false;
}
/**
 * ------------------------------------------------------------------------------------------------
 * Tasks data base - implementation 
 * ------------------------------------------------------------------------------------------------
 * Definitions
 * --------------------------------------------------------
 */
typedef std::lock_guard<std::mutex> guard_t;
/**
 * --------------------------------------------------------
 * Variables
 * --------------------------------------------------------
 */
STask::DataBase STask::__tasks;
STask::Mutex    STask::__mutex;
STask           STask::__init(0);
/**
 * --------------------------------------------------------
 * Insert task
 * --------------------------------------------------------
 */
void STask::_insert(std::thread::id id, STask* task) {
    /**
     * create guard
     */
    guard_t lock(__mutex);
    /**
     * insert
     */
    __tasks[id] = task;
}
/**
 * --------------------------------------------------------
 * Find task
 * --------------------------------------------------------
 */
STask* STask::_find(std::thread::id id) {    
    /**
     * find by id
     */
    try {
        guard_t lock(__mutex);
        return __tasks.at(id);
    } catch(std::out_of_range& e) {
        /**
         * concurrency
         */ 
        std::this_thread::yield(); 
    }
    /**
     * try again
     */
    try {
        guard_t lock(__mutex);
        return __tasks.at(id);
    } catch(std::out_of_range& e) {
        throw std::runtime_error("Task Not Found!!!");
    }
}
/**
 * --------------------------------------------------------
 * Remove task
 * --------------------------------------------------------
 */
void STask::_remove(std::thread::id id) {
    /**
     * create guard
     */
    guard_t lock(__mutex);
    /**
     * disable
     */
    __tasks[id] = &__init;
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */