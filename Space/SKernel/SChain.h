/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SChain.h
 * Author: Luis Monteiro
 *
 * Created on July 19, 2017, 6:23 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SCHAIN_H
#define SCHAIN_H
/**
 * std
 */
#include <list>
#include <map>
#include <stdbool.h>
/**
 * ------------------------------------------------------------------------------------------------
 * Chain
 * ------------------------------------------------------------------------------------------------
 */
template<class K, class D>
class SChain {
    /**
     * ------------------------------------------------------------------------
     * types
     * ------------------------------------------------------------------------
     */
    using Map       = std::map<K, D>;
    using List      = std::list<typename Map::iterator>;
    using Iterator  = typename List::iterator;
public:
    /**
     * ------------------------------------------------------------------------
     * defaults
     * ------------------------------------------------------------------------
     * move constructor
     */
    SChain(SChain&& chain) = default;
    /**
     * move operator 
     */
    SChain& operator=(SChain&& chain) = default;
    /**
     * ------------------------------------------------------------------------
     * constructor
     * ------------------------------------------------------------------------
     */
    SChain(size_t capacity = 10): __map(), __list(), __capacity(capacity) {
    }
    /**
     * ------------------------------------------------------------------------
     * iterators
     * ------------------------------------------------------------------------
     */
    inline Iterator begin() {
        return __list.begin();
    }
    inline Iterator end() {
        return __list.end();
    }
    inline Iterator erase(Iterator it) {
        __map.erase(*it); 
        return __list.erase(it);
    }
    /**
     * ------------------------------------------------------------------------
     * insert document 
     * ------------------------------------------------------------------------
     */
    SChain& Insert(K key, D&& doc) {
        /**
         * insert on map
         */
        auto r = __map.emplace(key, move(doc));
        /**
         * check insert
         */
        if(r.second) {
            /** 
             * insert on list and keep limit
             */
            for (
                __list.push_back(r.first); 
                __list.size() > __capacity; 
                __list.pop_front()
                ) {
                __map.erase(__list.front());
            }
        }
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * find document
     * ------------------------------------------------------------------------
     */
    inline D& Find(K key) {
        return __map.at(key);
    }
    /**
     * ------------------------------------------------------------------------
     * exist document
     * ------------------------------------------------------------------------
     */
    inline bool Exist(K key) {
        return __map.count(key) != 0;
    }
    /**
     * ------------------------------------------------------------------------
     * clear document
     * ------------------------------------------------------------------------
     */
    inline void Clear() {
        __map.clear();
        __list.clear();
    }
protected:
    /**
     * ------------------------------------------------------------------------
     * Variables
     * ------------------------------------------------------------------------
     **
     * map
     */
    Map __map;
    /**
     * list
     */
    List __list;
    /**
     * capacity
     */
    size_t __capacity;
};

#endif /* SCHAIN_H */

