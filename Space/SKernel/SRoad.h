/*
 * File:   SRoad.h
 * Author: Luis Monteiro
 *
 * Created on February 22, 2017, 10:34 PM
 */
#ifndef SROAD_H
#define SROAD_H
/**
 * std
 */
#include <system_error>
#include <algorithm>
#include <chrono>
#include <list>
/**
 * local 
 */
#include "STask.h"
/**
 */
using namespace std;
/*---------------------------------------------------------------------------------------------------------------------*
 * Exceptions
 *---------------------------------------------------------------------------------------------------------------------*/
typedef class SRoadException : public system_error {
public:
    /**
     * constructor
     */
    SRoadException(error_code ec) : system_error(ec) {
    }
    SRoadException(error_code ec, const string& what) : system_error(ec, what) {
    }
    /**
     * destructor
     */
    virtual ~SRoadException() = default;
} RoadException;
/**
 */
template<class T>
class SRoadExceptionTIMEOUT : public SRoadException {
public:
    using SRoadException::SRoadException;
    /**
     * constructor
     */
    SRoadExceptionTIMEOUT() : SRoadException(make_error_code(errc::no_message)) {
    }
    SRoadExceptionTIMEOUT(const string& what) : SRoadException(make_error_code(errc::no_message), what) {
    }
};
/**
 */
template<class T>
class SRoadExceptionDETACHED : public SRoadException {
public:
    using SRoadException::SRoadException;
    /**
     * constructor
     */
    SRoadExceptionDETACHED() : SRoadException(make_error_code(errc::no_message)) {
    }
    SRoadExceptionDETACHED(const string& what) : SRoadException(make_error_code(errc::no_message), what) {
    }
};
/**
 */
template<class T>
class SRoadExceptionDEAD: public SRoadException {
public:
    using SRoadException::SRoadException;
    /**
     * constructor
     */
    SRoadExceptionDEAD() : SRoadException(make_error_code(errc::no_message)) {
    }
    SRoadExceptionDEAD(const string& what) : SRoadException(make_error_code(errc::no_message), what) {
    }
};
/*---------------------------------------------------------------------------------------------------------------------*
 * Road
 *---------------------------------------------------------------------------------------------------------------------*/
template<class K, class T>
class SRoad {
public:
    /**
     * process states
     */
    typedef enum {Backup, Repairing, Running, Dead} State;
    /**
     * process 
     */
    using Key      = K;
    using Object   = T;
    using Area     = map<K, T>;
    using Road     = SRoad<K, T>;
    using Location = typename Area::iterator;
    /**
     * constructor
     */
    SRoad(uint32_t nominal, uint32_t min = 0) : __nominal(nominal), __min(min), __rev(0) {
    }
    /**
     * --------------------------------------------------------------------------------------------------------------
     * main interfaces
     * -------------------------------------------------------------------------------------------------------------
     * insert an object
     */
    void Insert(K key, T obj) {
        // remove the existing one
        for(auto s : {Backup, Repairing, Running, Dead}) {
            __process[s].erase(key);
        }
        // insert a new one
        if (__process[Repairing].size() < __nominal) {
            // start connector
            __process[Repairing][key] = obj;
        } else {
            // backup connector
            __process[Backup][key] = obj;  
        }
    }
    /**
     * find an object
     */
    T& Find(K key) {
        for(auto s : {Backup, Repairing, Running, Dead}) {
            try { 
                return __process[s].at(key); 
            } catch (range_error& ){}
        }
        throw range_error(__func__);
    }
    /**
     * iterator
     */
    inline Location begin() {
        return __process[Running].begin();
    }
    inline Location end() {
        return __process[Running].end();
    }
    /**
     * get road size
     */
    size_t Length() {
        return 0;
    }
    /**
     * try to repair
     */
    void Repair(Location& it) {
        /**
         * repair connector
         */
        it->second->Repair();
        /**
         * jump to repairing queue
         */
        it = jump(it, Running, Repairing);
    }
    /**
     * update 
     */
    Road& Update() {
        /**
         * update areas
         */
        Area& repairing = __process[Repairing];
        for (auto it = repairing.begin(); it != repairing.end();) {
            if (it->second->Good()) {
                it = jump(it, Repairing, Running);
                continue;
            }
            if (it->second->Inactive()) {
                it = jump(Backup, Repairing, jump(it, Repairing, Dead));
                continue;
            }
            ++it;
        }
        /**
         * waiting  
         */
        if (__process[Running].size() < __min) {
            throw SRoadExceptionDETACHED<T>(string(""));
        }
        /**
         * is dead 
         */
        if (__process[Repairing].size() + __process[Running].size() < __nominal) {
            throw SRoadExceptionDEAD<T>(string(""));
        }
        /** 
         */
        return *this;
    }
    /**
     * block all streams
     */
    void Close() {
        /**
         * repairing
         */
        Area& repairing = __process[Repairing];
        for (auto it = repairing.begin() , e = repairing.end(); it != e; ++it) {
            it->second->Break();
        }
        /**
         * running
         */
        Area& running = __process[Running];
        for (auto it = running.begin(), e = running.end(); it != e; ++it) {
            it->second->Break();
        }
        /**
         * change context
         */
        STask::Sleep(std::chrono::milliseconds(10));
    }
    /**
     * enable all streams
     */
    void Open() {
        /**
         * repairing
         */
        Area& repairing = __process[Repairing];
        for (auto it = repairing.begin() , e = repairing.end(); it != e; ++it) {
            it->second->Repair();
        }
        /**
         * running
         */
        Area& running = __process[Running];
        for (auto it = running.begin(), e = running.end(); it != e; it=jump(it, Running, Repairing)) {
            it->second->Repair();   
        }
        /**
         * change context
         */
        STask::Sleep(std::chrono::milliseconds(10));
    }
    /**
     * reset all streams
     */
    void Reset(){
        Close();
        Open();
    }
    /*-------------------------------------------------------------------------------------------------------------*
     * diagnostic
     *-------------------------------------------------------------------------------------------------------------*/
    inline map<State, size_t> Sizes() {
        map<State, size_t> out;
        for(auto& a : __process) {
            out[a.first] = a.second.size();
        }
        return out;
    }
    
protected:
    /**
     * get revision
     */
    size_t revision() {
        return __rev;
    }
    /**
     * jumps
     */
    Location jump(const Location& pos, const State& from, const State& to) {
        /**
         * move to queue
         */
        __process[to][pos->first] = move(pos->second);
        /**
         * remove and update iterator
         */
        return __process[from].erase(pos);
    }
    Location jump(const State& from, const State& to, const Location& pos) {
        Location it = __process[from].begin();
        Location p = pos;
        if (it != __process[from].end()) {
            using Value = typename Area::value_type;
            /**
             * move to queue
             */
            p = __process[to].insert(p, pair<K, T>(it->first, it->second));   
            /**
             * remove
             */
            __process[from].erase(it);
        }
        return p;
    }
private:
    /**
     * process container
     */
    map<State, Area> __process;
    /**
     * process levels
     */
    size_t __nominal;
    size_t __min;
    /**
     * process revision
     */
    size_t __rev;
};

#endif /* SROAD_H */

