/**
 * ------------------------------------------------------------------------------------------------
 * File:   SQueue.h
 * Author: Luis Monteiro
 *
 * Created on January 14, 2019, 6:23 PM
 * ------------------------------------------------------------------------------------------------
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
    std::mutex __locker;
};
/**
 * ----------------------------------------------------------------------------
 * Queue
 * ----------------------------------------------------------------------------
 */
template<typename Type, typename Guard = SQueueGuard>
class SQueue {
public:
    using List = std::list<Type>;
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
    inline void insert(Type&& obj) {
        Guard g;
        return __container.emplace_back(obj);
    }
    inline void insert(Type obj) {
        Guard g;
        return __container.emplace_back(obj);
    }
    /**
     * ----------------------------------------------------
     * remove
     * ----------------------------------------------------
     */
    inline List remove() {
        Guard g;
        return move(__container);
    }
    /**
     * ----------------------------------------------------
     * clear document
     * ----------------------------------------------------
     */
    inline void clear() {
        Guard g;
       __container.clear();
    }
protected:
    /**
     * container
     */
    List __container;
};
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SQUEUE_H */

