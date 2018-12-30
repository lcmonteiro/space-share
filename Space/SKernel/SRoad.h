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
/**
 * ------------------------------------------------------------------------------------------------
 * Exceptions
 * ------------------------------------------------------------------------------------------------
 */
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
typedef class SRoadExceptionTimeout : public SRoadException {
public:
    using SRoadException::SRoadException;
    /**
     * constructor
     */
    SRoadExceptionTimeout() : SRoadException(make_error_code(errc::no_message)) {
    }
    SRoadExceptionTimeout(const string& what) : SRoadException(make_error_code(errc::no_message), what) {
    }
} RoadTimeout;
/**
 */
typedef class SRoadExceptionDetached : public SRoadException {
public:
    using SRoadException::SRoadException;
    /**
     * constructor
     */
    SRoadExceptionDetached() : SRoadException(make_error_code(errc::no_message)) {
    }
    SRoadExceptionDetached(const string& what) : SRoadException(make_error_code(errc::no_message), what) {
    }
} RoadDetached;
/**
 */
typedef class SRoadExceptionDead : public SRoadException {
public:
    using SRoadException::SRoadException;
    /**
     * constructor
     */
    SRoadExceptionDead() : SRoadException(make_error_code(errc::no_message)) {
    }
    SRoadExceptionDead(const string& what) : SRoadException(make_error_code(errc::no_message), what) {
    }
} RoadDead;
/**
 * ------------------------------------------------------------------------------------------------
 * Exceptions Templates 
 * -----------------------------------------------------------------------------------------------
 */
template<class T>
class SRoadExceptionTIMEOUT : public SRoadExceptionTimeout {
public:
    using SRoadExceptionTimeout::SRoadExceptionTimeout;
};
/**
 */
template<class T>
class SRoadExceptionDETACHED : public SRoadExceptionDetached {
public:
    using SRoadExceptionDetached::SRoadExceptionDetached;
};
/**
 */
template<class T>
class SRoadExceptionDEAD: public SRoadExceptionDead {
public:
    using SRoadExceptionDead::SRoadExceptionDead;
};
/**
 * ------------------------------------------------------------------------------------------------
 * Road
 * ------------------------------------------------------------------------------------------------
 */
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
    SRoad() = default;
    /**
     * main constructor
     * @param nominal
     * @param min
     */
    SRoad(size_t nominal, size_t minimum = 0): __nominal(nominal), __minimum(minimum), __revison(0) {
    }
    /**
     * operators
     */
    SRoad& operator=(SRoad &&) = default;
    /**
     * --------------------------------------------------------------------------------------------
     * main interfaces
     * --------------------------------------------------------------------------------------------
     * insert an object
     */
    inline void Insert(K key, T obj) {
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
    inline T& Find(K key) {
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
    inline size_t Length() {
        size_t out = 0;
        for(auto& a : __process) {
            out += a.second.size();
        }
        return out;
    }
    /**
     * try to repair
     */
    inline void Repair(Location& it) {
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
    inline Road& Update() {
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
        if (__process[Running].size() < __minimum) {
            throw SRoadExceptionDETACHED<T>(Status());
        }
        /**
         * is dead 
         */
        if (__process[Repairing].size() + __process[Running].size() < __nominal) {
            throw SRoadExceptionDEAD<T>(Status());
        }
        /** 
         */
        return *this;
    }
    /**
     * block all streams
     */
    inline void Close() {
        /**
         * repairing
         */
        Area& repairing = __process[Repairing];
        for (auto it = repairing.begin() , e = repairing.end(); it != e;) {
            try {
                it->second->Break(); ++it;
            } catch(...) {
                it = jump(it, Repairing, Dead);
            }
        }
        /**
         * running
         */
        Area& running = __process[Running];
        for (auto it = running.begin(), e = running.end(); it != e;) {
            try {
                it->second->Break(); ++it;
            } catch(...) {
                it = jump(it, Running, Dead);
            }
        }
    }
    /**
     * enable all streams
     */
    inline void Open() {
        /**
         * repairing
         */
        Area& repairing = __process[Repairing];
        for (auto it = repairing.begin() , e = repairing.end(); it != e;) {
            try {
                it->second->Repair(); ++it;
            } catch(...) {
                it = jump(it, Repairing, Dead);
            }
        }
        /**
         * running
         */
        Area& running = __process[Running];
        for (auto it = running.begin(), e = running.end(); it != e; ) {
            try {
                it->second->Repair();
                it = jump(it, Running, Repairing);
            } catch(...) {
                it = jump(it, Running, Dead);
            }
        }
    }
    /**
     * reset all streams
     */
    inline void Reset(){
        /**
         * close resources
         */
        Close();
        /**
         * change context
         */
        STask::Sleep(std::chrono::milliseconds(10));
        /**
         * open resources
         */
        Open();
        /**
         * change context
         */
        STask::Sleep(std::chrono::milliseconds(10));
    }
    /**--------------------------------------------------------------------------------------------
     * diagnostic
     *---------------------------------------------------------------------------------------------
     *  
     */
    inline map<State, size_t> Sizes() {
        map<State, size_t> out;
        for(auto& a : __process) {
            out[a.first] = a.second.size();
        }
        return out;
    }
    /**
     * status -> {'state':['uri1', 'uri2']}
     */
    inline string Status() {
        ostringstream out;
        out << '{';
        for(auto& p :__process) {
                out << "'" << p.first << "':[";
                for(auto&a :p.second){
                        out << "'" << a.first << "'";
                }
                out << "]";
        }
        out << "}";
        return out.str();
    }
    
protected:
    /**
     * get revision
     */
    inline size_t Resvision() {
        return __revison;
    }
    /**
     * jumps
     */
    inline Location jump(const Location& pos, const State& from, const State& to) {
        /**
         * move to queue
         */
        __process[to][pos->first] = move(pos->second);
        /**
         * remove and update iterator
         */
        return __process[from].erase(pos);
    }
    inline Location jump(const State& from, const State& to, const Location& pos) {
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
    size_t __minimum;
    /**
     * process revision
     */
    size_t __revison;
};

#endif /* SROAD_H */

