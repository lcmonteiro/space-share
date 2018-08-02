/**
 * File: SLinuxTask.cpp
 * Author: Monteiro
 *
 * Created on November 26, 2016, 12:37 PM
 */
/**
 */
#include <mutex>
#include <map>
#include <iostream>
/**
 */
#include "SLinuxTask.h"
#include "SMonitor/SLinux/SLinuxResourceMonitor.h"
/**
 * definitions
 */
typedef lock_guard<std::mutex> guard_t;
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * Global - Protected
 * ---------------------------------------------------------------------------------------------------------------------
 **
 * static variables 
 */
static map<thread::id, SLinuxTask*> __tasks;

static SLinuxTask __main;

static mutex __mutex;

void SLinuxTask::__Insert(thread::id id, SLinuxTask* task) {
        // create guard
        guard_t lock(__mutex);
        // insert
        __tasks[id] = task;
}

SLinuxTask* SLinuxTask::__Find(thread::id id) {
        // create guard
        guard_t lock(__mutex);
        // find by id
        return __tasks.at(id);
}

void SLinuxTask::__Remove(thread::id id) {
        // create guard
        guard_t lock(__mutex);
        // disable
        __tasks[id] = &__main;
}
/*
 * ---------------------------------------------------------------------------------------------------------------------
 * Public - Global
 * --------------------------------------------------------------------------------------------------------------------- 
 */
SLinuxTask& SLinuxTask::Enable() {
        __Insert(this_thread::get_id(), &__main); 
        return __main;
}

SLinuxTask& SLinuxTask::Instance() {
        return *__Find(this_thread::get_id());
}

bool SLinuxTask::Sleep(chrono::milliseconds timeout) {
        SLinuxMonitor::Wait(timeout);
        return true;
}
