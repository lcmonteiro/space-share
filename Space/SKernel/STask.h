/** 
 * Stream: STask.h
 * Author: Monteiro
 *
 * Created on November 26, 2016, 12:37 PM
 */
#ifndef STASK_H
#define STASK_H
/**
 * std
 */
#include <thread>
#include <mutex>
#include <map>
/**
 * space
 */
#include "SEventResource.h"
/**
 * ------------------------------------------------------------------------------------------------
 * task
 * ------------------------------------------------------------------------------------------------
 **/
class STask : public std::thread {
public:
    using Time = std::chrono::milliseconds;
    /**
     * ----------------------------------------------------
     * defaults
     * ----------------------------------------------------
     */
    STask()                     = default;
    STask(STask&&)              = default;
    STask& operator=(STask&& t) = default;
    /**
     * ----------------------------------------------------
     * constructor
     * ----------------------------------------------------
     */
    template<typename Func, typename... Args> explicit
    STask(Func&& f, Args&&... args) 
    : std::thread(f, args...), __event(0) {
        __Init(std::this_thread::get_id());
    }
    /**
     * ----------------------------------------------------
     * destructor
     * ----------------------------------------------------
     */
    virtual ~STask() {
        __End(std::this_thread::get_id());
    }
    /**
     * ----------------------------------------------------
     * interface
     * ----------------------------------------------------
     * check if joinable
     */
    inline bool Joinable() {
        return std::thread::joinable();
    }
    /**
     * wait for Join
     */
    inline void Join() {
        std::thread::join();
    }
    /**
     * detach from object
     */
    inline void Detach() {
        std::thread::detach();
    }
    /**
     * interrupt thread
     */
    inline void Interrupt() {
        __event.Send();
    }
    /**
     * get resource
     */
    inline Resource& GetResource() {
        return __event;
    }
    /**
     * ------------------------------------------------------------------------
     * Global
     * ------------------------------------------------------------------------
     * enable main task
     */
    static STask& Enable(); 
    /**
     * get this instance
     */
    static STask& Instance();
    /**
     * sleep this task
     */
    static bool Sleep(const Time& timeout = Time::zero());
protected:
    /**
     * protected constructor
     */
    STask(int init): __event(init) {} 
    /**
     * ------------------------------------------------------------------------
     * manager tasks 
     * ------------------------------------------------------------------------
     * init / end
     */
    void __Init(std::thread::id id);
    void __End(std::thread::id  id);
private:
    /**
     * ------------------------------------------------------------------------
     * variables 
     * ------------------------------------------------------------------------
     * event
     */
    SEventResource __event;
    /**
     * ------------------------------------------------------------------------
     * tasks data base - declaration
     * ------------------------------------------------------------------------
     * static variables 
     */
    using DataBase = std::map<thread::id, STask*>; 
    using Mutex    = std::mutex; 
    static DataBase __tasks;
    static Mutex    __mutex;
    static STask    __init;
    /**
     * interfaces
     */
    static void   __Insert(std::thread::id id, STask* p_task);
    static STask* __Find  (std::thread::id id);
    static void   __Remove(std::thread::id id);
};
/**
 * ------------------------------------------------------------------------------------------------*
 * end
 * ------------------------------------------------------------------------------------------------
 **/
#endif /* STASK_H */

