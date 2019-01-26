/**
 * File: SLinuxTask.cpp
 * Author: Monteiro
 *
 * Created on November 26, 2016, 12:37 PM
 **
 * std
 */
#include <mutex>
#include <map>
#include <iostream>
/**
 * space
 */
#include "STask.h"
#include "SMonitorHandler.h"
/**
 * ------------------------------------------------------------------------------------------------
 * tasks data base - declaration
 * ------------------------------------------------------------------------------------------------
 * static variables 
 */
static map<thread::id, STask*> __tasks;
static STask __main;
static mutex __mutex;
/**
 * methods
 */
void   __insert(thread::id id, STask* p_task);
STask* __find  (thread::id id);
void   __remove(thread::id id);
/**
 * ------------------------------------------------------------------------
 * manager tasks 
 * ------------------------------------------------------------------------
 * init / end
 */
void STask::__Init(thread::id id) {
    __insert(id, this);
}
/**
 */
void STask::__End(thread::id  id) {
    /**
     * interrupt thread
     */
    if (joinable()) {
        try {
            Interrupt();
        #ifdef __DEBUG__
            cout << __func__ << "::" << __LINE__ << "::join(" << get_id() << ")" << endl;
        #endif
            Join();
        } catch(...) {
        #ifdef __DEBUG__
            cout << __func__ << "::" << __LINE__ << "::detach(" << get_id() << ")" << endl;
        #endif
            Detach();
        }
        __remove(get_id());
    }
}
/*
 * ------------------------------------------------------------------------------------------------
 * public - global
 * ------------------------------------------------------------------------------------------------ 
 * enable main task
 */
STask& STask::Enable() {
    __insert(this_thread::get_id(), &__main); 
    return __main;
}
/**
 * get current task
 */
STask& STask::Instance() {
    return *__find(this_thread::get_id());
}
/**
 * sleep current task
 */
bool STask::Sleep(chrono::milliseconds timeout) {
    SStaticMonitorHandler().Wait(timeout);
    return true;
}
/**
 * ------------------------------------------------------------------------------------------------
 * tasks data base - implementation 
 * ------------------------------------------------------------------------------------------------
 **
 * definitions
 */
typedef lock_guard<std::mutex> guard_t;
/**
 * insert task
 */
void __insert(thread::id id, STask* task) {
    // create guard
    guard_t lock(__mutex);
    // insert
    __tasks[id] = task;
}
/**
 */
STask* __find(thread::id id) {
    // create guard
    guard_t lock(__mutex);
    // find by id
    return __tasks.at(id);
}
/**
 */
void __remove(thread::id id) {
    // create guard
    guard_t lock(__mutex);
    // disable
    __tasks[id] = &__main;
}
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */