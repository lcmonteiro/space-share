/**
 * File:   SQueue.h
 * Author: Luis Monteiro
 *
 * Created on January 14, 2019, 6:23 PM
 */
#ifndef SQUEUE_H
#define SQUEUE_H
/**
 * std
 */
#include <list>
#include <mutex>
/**
 * ----------------------------------------------------------------------------
 * Queue Guard
 * ----------------------------------------------------------------------------
 */
class SQueueGuard {
public:
    SQueueGuard() {
	__locker.lock();
    }
    ~SQueueGuard(){
        __locker.unlock();
    }
private:
    mutex __locker;
};
/**
 * ----------------------------------------------------------------------------
 * Queue
 * ----------------------------------------------------------------------------
 */
template<class TYPE, class GUARD = SQueueGuard>
class SQueue {
public:
    using Type = TYPE;
    using List = list<TYPE>;
    /**
     * ----------------------------------------------------
     * default
     * ----------------------------------------------------
     * empty constructor
     */
     SQueue() = default;
    /**
     * move constructor
     */
    SQueue(SQueue&&) = default;
    /**
     * move operator
     */
    SQueue& operator=(SQueue&&) = default;
    /**
     * ----------------------------------------------------
     * insert
     * ----------------------------------------------------
     */
    inline void Insert(Type&& obj) {
        GUARD g;
        return __container.emplace_back(obj);
    }
    inline void Insert(Type obj) {
        GUARD g;
        return __container.emplace_back(obj);
    }
    /**
     * ----------------------------------------------------
     * remove
     * ----------------------------------------------------
     */
    inline List Remove() {
        GUARD g;
        return move(__container);
    }
    /**
     * ----------------------------------------------------
     * clear document
     * ----------------------------------------------------
     */
    inline void Clear() {
        GUARD g;
       __container.clear();
    }
protected:
    /**
     * container
     */
    List __container;
};
/**
 * ----------------------------------------------------------------------------
 * End
 * ----------------------------------------------------------------------------
 */
#endif /* SQUEUE_H */

