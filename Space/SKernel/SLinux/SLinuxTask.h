/* 
 * Stream: SLinuxTask.h
 * Author: Monteiro
 *
 * Created on November 26, 2016, 12:37 PM
 */
#ifndef SLINUXTASK_H
#define SLINUXTASK_H
/**
 */
//#define __DEBUG__
/**
 */
#include <thread>
/**
 * space kernel linux
 */
#include "SLinuxEvent.h"
/**
 */
#ifdef __DEBUG__
#include <iostream>
#endif
/**
 */
using namespace std;
using namespace std::this_thread;
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * thread
 * ---------------------------------------------------------------------------------------------------------------------
 */
class SLinuxTask : public thread {
public:
    /**
     * default constructor
     */
    SLinuxTask() = default;
    /**
     * move constructor
     */
    SLinuxTask(SLinuxTask&& t) = default;
    /**
     * template constructor
     */
    template<typename Func, typename... Args> explicit
    SLinuxTask(Func&& f, Args&&... args) : thread(f, args...), __event(0) {
        __Insert(get_id(), this);
    }
    /**
     * destructor
     */
    virtual ~SLinuxTask() {
        /**
         * interrupt thread
         */
        if (joinable()) {
            try {
                Interrupt();
#ifdef __DEBUG__
                cout << __func__ << "::" << __LINE__ << "::join(" << get_id() << ")" << endl;
#endif
                join();
            } catch(...) {
#ifdef __DEBUG__
                cout << __func__ << "::" << __LINE__ << "::detach(" << get_id() << ")" << endl;
#endif
                detach();
            }
            __Remove(get_id());
        }
    }
    /**
     * move operator
     */
    SLinuxTask& operator=(SLinuxTask&& t) = default;
    /**
     * base function 
     */
    using thread::joinable;
    using thread::join;
    using thread::detach;
    /**
     * Extention
     * interrupt thread
     */
    inline void Interrupt() {
        __event.Send();
    }
    /**
     * get resource
     */
    inline Resource& resource() {
        return __event;
    }
    /**
     * -------------------------------------------------------------------------------------------------------------
     * Global
     * -------------------------------------------------------------------------------------------------------------
     * enable main task
     */
    static SLinuxTask& Enable(); 
    /**
     * get this instance
     */
    static SLinuxTask& Instance();
    /**
     * sleep this task
     */
    static bool Sleep(chrono::milliseconds timeout = chrono::milliseconds(0));
protected:
    friend class SLinuxMonitor;
    /**
     * event
     */
    SLinuxEvent __event;
    /**
     * linux resource
     */
    inline SLinuxResource& GetLinuxResource() {
        return __event;
    }
    /**
     * --------------------------------------------------------------------------------------------
     * manager tasks 
     * --------------------------------------------------------------------------------------------
     * insert task
     */
    static void __Insert(thread::id, SLinuxTask*);
    /**
     * find task
     */ 
    static SLinuxTask* __Find(thread::id);
    /**
     * remove task
     */
    static void __Remove(thread::id);
};
/**
 */
#endif /* SLINUXTASK_H */

