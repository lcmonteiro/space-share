/**
 * ------------------------------------------------------------------------------------------------
 * File: STask.cpp
 * Author: Monteiro
 *
 * Created on November 26, 2016, 12:37 PM
 * ------------------------------------------------------------------------------------------------
 **
 * linux 
 */ 
 #include <sys/eventfd.h>
/**
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
 * Interrupt Task 
 * ------------------------------------------------------------------------------------------------
 * Constructor
 * ----------------------------------------------------------------------------
 */
STask::SInterrupt::SInterrupt(bool init) : SResource() {
    if(init) {
        handler(std::make_shared<SResourceHandler>(::eventfd(0, 0)));
    }
}
/**
 * ----------------------------------------------------------------------------
 * send interrupt
 * ----------------------------------------------------------------------------
 */
void STask::SInterrupt::send() {
    ::eventfd_write(handler<SResourceHandler>()->fd(), 1);
}
/**
 * ------------------------------------------------------------------------------------------------
 * Manager Tasks 
 * ------------------------------------------------------------------------------------------------
 * Init
 * --------------------------------------------------------
 */
void STask::_init(std::thread::id id) {
    __Insert(id, this);
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
        __Remove(id);
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
    __Insert(std::this_thread::get_id(), &__init); 
    return __init;
}
/**
 * --------------------------------------------------------
 * Current task
 * --------------------------------------------------------
 */
STask& STask::Instance() {
    return *__Find(std::this_thread::get_id());
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
STask           STask::__init(true);
/**
 * --------------------------------------------------------
 * Insert task
 * --------------------------------------------------------
 */
void STask::__Insert(std::thread::id id, STask* task) {
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
STask* STask::__Find(std::thread::id id) {    
    /**
     * find by id
     */
    for(auto i = 2; i; --i) {
        try {
            guard_t lock(__mutex);
            return __tasks.at(id);
        } catch(std::out_of_range& e) {
            /**
             * concurrency
             */ 
            std::this_thread::yield(); 
        }
    }
    /**
     * task not found
     */
    throw std::runtime_error("Task Not Found!!!");
}
/**
 * --------------------------------------------------------
 * Remove task
 * --------------------------------------------------------
 */
void STask::__Remove(std::thread::id id) {
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