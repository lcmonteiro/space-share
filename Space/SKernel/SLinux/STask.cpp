/**
 * File: SLinuxTask.cpp
 * Author: Monteiro
 *
 * Created on November 26, 2016, 12:37 PM
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
 * manager tasks 
 * ------------------------------------------------------------------------------------------------
 * init
 * --------------------------------------------------------
 */
void STask::__Init(std::thread::id id) {
    __Insert(id, this);
}
/**
 * --------------------------------------------------------
 * end - interrupt thread if is running 
 * --------------------------------------------------------
 */
void STask::__End(std::thread::id  id) {
    if (joinable()) {
        try {
            Interrupt();
        #ifdef __DEBUG__
            cout << __func__ << "::" 
                 << __LINE__ << "::join(" << get_id() << ")" 
            << endl;
        #endif
            Join();
        } catch(...) {
        #ifdef __DEBUG__
            cout << __func__ << "::" 
                 << __LINE__ << "::detach(" << get_id() << ")" 
            << endl;
        #endif
            Detach();
        }
        __Remove(id);
    }
}
/*
 * ------------------------------------------------------------------------------------------------
 * public - global
 * ------------------------------------------------------------------------------------------------ 
 * enable init task
 * --------------------------------------------------------
 */
STask& STask::Enable() {
    __Insert(std::this_thread::get_id(), &__init); 
    return __init;
}
/**
 * --------------------------------------------------------
 * get current task
 * --------------------------------------------------------
 */
STask& STask::Instance() {
    return *__Find(std::this_thread::get_id());
}
/**
 * --------------------------------------------------------
 * sleep current task
 * --------------------------------------------------------
 */
bool STask::Sleep(const Time& timeout) {
    SStaticMonitorHandler().Wait(timeout);
    return true;
}
/**
 * ------------------------------------------------------------------------------------------------
 * tasks data base - implementation 
 * ------------------------------------------------------------------------------------------------
 * definitions
 * --------------------------------------------------------
 */
typedef std::lock_guard<std::mutex> guard_t;
/**
 * --------------------------------------------------------
 * variables
 * --------------------------------------------------------
 */
STask::DataBase STask::__tasks;
STask::Mutex    STask::__mutex;
STask           STask::__init(0);
/**
 * --------------------------------------------------------
 * insert task
 * --------------------------------------------------------
 */
void STask::__Insert(std::thread::id id, STask* task) {
    // create guard -------------------
    guard_t lock(__mutex);
    // insert -------------------------
    __tasks[id] = task;
}
/**
 * --------------------------------------------------------
 * find task
 * --------------------------------------------------------
 */
STask* STask::__Find(std::thread::id id) {    
    // find by id ---------------------
    try {
        guard_t lock(__mutex);
        return __tasks.at(id);
    } catch(std::out_of_range& e) {
        // concurrency ---------------- 
        std::this_thread::yield(); 
    }
    // try again ----------------------
    {
        guard_t lock(__mutex);
        return __tasks.at(id);
    }
}
/**
 * --------------------------------------------------------
 * remove task
 * --------------------------------------------------------
 */
void STask::__Remove(std::thread::id id) {
    // create guard -------------------
    guard_t lock(__mutex);
    // disable ------------------------
    __tasks[id] = &__init;
}
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */