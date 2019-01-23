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
/**
 * space
 */
#include "SEventResource.h"
/**
 */
using namespace std;
using namespace std::this_thread;
/**
 * ------------------------------------------------------------------------------------------------*
 * task
 * ------------------------------------------------------------------------------------------------
 **/
class STask : public thread {
public:
    /**
     * ----------------------------------------------------
     * constructors / destructor
     * ----------------------------------------------------
     * default
     */
    STask()        = default;
    STask(STask&&) = default;
    /**
     * template
     */
    template<typename Func, typename... Args> explicit
    STask(Func&& f, Args&&... args) : thread(f, args...), __event(0) {
        __Init(get_id());
    }
    /**
     * destructor
     */
    virtual ~STask() {
        __End(get_id());
    }
    /**
     * ----------------------------------------------------
     * interface
     * ----------------------------------------------------
     * move operator
     */
    STask& operator=(STask&& t) = default;
    /**
     * check if joinable
     */
    inline bool Joinable() {
        return thread::joinable();
    }
    /**
     * wait for Join
     */
    inline void Join() {
        thread::join();
    }
    /**
     * detach from object
     */
    inline void Detach() {
        thread::detach();
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
     * ----------------------------------------------------------------------------------------
     * Global
     * ----------------------------------------------------------------------------------------
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
    static bool Sleep(chrono::milliseconds timeout = chrono::milliseconds(0));
protected:
    /**
     * event
     */
    SEventResource __event;
private:
    /**
     * ------------------------------------------------------------------------
     * manager tasks 
     * ------------------------------------------------------------------------
     * init / end
     */
    void __Init(thread::id id);
    void __End(thread::id  id);
};
/**
 * ------------------------------------------------------------------------------------------------*
 * end
 * ------------------------------------------------------------------------------------------------
 **/
#endif /* STASK_H */

