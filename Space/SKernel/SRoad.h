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
 * space 
 */
#include "SResourceMonitor.h"
#include "STask.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Exceptions
 * ------------------------------------------------------------------------------------------------
 */
typedef class SRoadException : public std::system_error {
public:
    /**
     * constructor
     */
    SRoadException(std::error_code ec) : std::system_error(ec) {
    }
    SRoadException(std::error_code ec, const string& what) : system_error(ec, what) {
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
    SRoadExceptionTimeout() 
    : SRoadException(std::make_error_code(std::errc::no_message)) {
    }
    SRoadExceptionTimeout(const std::string& what) 
    : SRoadException(std::make_error_code(std::errc::no_message), what) {
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
    SRoadExceptionDetached() 
    : SRoadException(std::make_error_code(std::errc::no_message)) {
    }
    SRoadExceptionDetached(const std::string& what) 
    : SRoadException(std::make_error_code(std::errc::no_message), what) {
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
    SRoadExceptionDead() 
    : SRoadException(std::make_error_code(std::errc::no_message)) {
    }
    SRoadExceptionDead(const std::string& what) 
    : SRoadException(std::make_error_code(std::errc::no_message), what) {
    }
} RoadDead;
/**
 * ------------------------------------------------------------------------------------------------
 * Exceptions Templates 
 * ------------------------------------------------------------------------------------------------
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
template<class KEY, class OBJ>
class SRoad {
public:

    /**
     * process states
     */
    typedef enum {Backup, Repairing, Running, Dead} State;
    /**
     * --------------------------------------------------------------------------------------------
     * helpers
     * --------------------------------------------------------------------------------------------
     */
    using Key      = KEY;
    using Object   = OBJ;
    using Road     = SRoad<Key, Object>;
    using Area     = std::map<Key, Object>;
    using Location = typename Area::iterator;
    /**
     * --------------------------------------------------------------------------------------------
     * defaults
     * --------------------------------------------------------------------------------------------
     */
    SRoad(SRoad&& )           = default;
    SRoad& operator=(SRoad&&) = default;
    /**
     * --------------------------------------------------------------------------------------------
     * constructors
     * --------------------------------------------------------------------------------------------
     **
     * main constructor
     * @param nominal
     * @param min
     */
    SRoad(size_t nominal = 1, size_t minimum = 1)
    : __nominal(nominal), __minimum(minimum), __revision(0) {
    }
    /**
     * --------------------------------------------------------------------------------------------
     * main interfaces
     * --------------------------------------------------------------------------------------------
     * detach
     * ------------------------------------------------------------------------
     */
    inline SRoad Detach() {
        return move(*this);
    }
    /**
     * ------------------------------------------------------------------------
     * insert an object
     * ------------------------------------------------------------------------
     */
    inline SRoad& Insert(Key k, Object o) {
        // remove the existing one ------------------------
        for(auto s : {Backup, Repairing, Running, Dead}) {
            __process[s].erase(k);
        }
        // insert a new one -------------------------------
        if (__Length({Repairing, Running}) < __nominal) {
            // main connector
            __process[Repairing].emplace(k, std::move(o));
        } else {
            // backup connector
            __process[Backup].emplace(k, std::move(o)); 
        }
        // update revision --------------------------------
        __UpdateResvision();
        
        // return self ------------------------------------
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * find an object
     * ------------------------------------------------------------------------
     */
    inline Object& Find(Key k) {
        for(auto& p : __process) {
            auto it = p.second.find(k);
            if(it != p.second.end()) {
                return it->second;
            }
        }
        throw range_error(__func__);
    }
    /**
     * ------------------------------------------------------------------------
     * iterator
     * ------------------------------------------------------------------------
     */
    inline Location begin() {
        return __process[Running].begin();
    }
    inline Location end() {
        return __process[Running].end();
    }
    /**
     * -----------------------------------------------------------------------
     * get road size
     * -----------------------------------------------------------------------
     */
    inline size_t Length() {
        size_t out = 0;
        for(auto& a : __process) {
            out += a.second.size();
        }
        return out;
    }
    /**
     * -----------------------------------------------------------------------
     * try to repair
     * -----------------------------------------------------------------------
     */
    inline void Repair(Location& it) {
        // update revision --------------------------------
        __UpdateResvision();

        //  repair connector ------------------------------
        it->second->Repair();
        
        // Jump to repairing queue ------------------------
        it = __Jump(it, Running, Repairing);
    }
    /**
     * ------------------------------------------------------------------------
     * update 
     * ------------------------------------------------------------------------
     */
    inline Road& Update() {
        // update areas -----------------------------------
        Area& rep = __process[Repairing];
        for (auto it = rep.begin(); it != rep.end();) {
            if (it->second->Good()) {
                // update revision
                __UpdateResvision();
                // __Jump to running 
                it = __Jump(it, Repairing, Running); 
                continue;
            }
            if (it->second->Inactive()) {
                it = __Jump(Backup, Repairing, __Jump(
                    it, Repairing, Dead
                ));
                continue;
            }
            ++it;
        }
        //waiting ---------------------------------------- 
        if (__Length({Running}) < __minimum) {
            throw SRoadExceptionDETACHED<Object>(Status());
        }
        // is dead ----------------------------------------
        if (__Length({Repairing, Running}) < __nominal) {
            throw SRoadExceptionDEAD<Object>(Status());
        }
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * block all connectors
     * ------------------------------------------------------------------------
     */
    inline void Close() {
        // repairing --------------------------------------
        Area& rep = __process[Repairing];
        for (auto it = rep.begin() , e = rep.end(); it != e;) {
            try {
                it->second->Break(); ++it;
            } catch(...) {
                it = __Jump(it, Repairing, Dead);
            }
        }
        // running ----------------------------------------
        Area& run = __process[Running];
        for (auto it = run.begin(), e = run.end(); it != e;) {
            try {
                it->second->Break(); ++it;
            } catch(...) {
                it = __Jump(it, Running, Dead);
            }
        }
        // update revision --------------------------------
        __UpdateResvision();
    }
    /**
     * ------------------------------------------------------------------------
     * enable all 
     * ------------------------------------------------------------------------
     */
    inline void Open() {
        // repairing --------------------------------------
        Area& rep = __process[Repairing];
        for (auto it = rep.begin(), e = rep.end(); it != e;) {
            try {
                it->second->Repair(); ++it;
            } catch(...) {
                it = __Jump(it, Repairing, Dead);
            }
        }
        // running ----------------------------------------
        Area& run = __process[Running];
        for (auto it = run.begin(), e = run.end(); it != e;) {
            try {
                it->second->Repair();
                it = __Jump(it, Running, Repairing);
            } catch(...) {
                it = __Jump(it, Running, Dead);
            }  
        }
        // update revision --------------------------------
        __UpdateResvision();
    }
    /**
     * ------------------------------------------------------------------------
     * reset all 
     * ------------------------------------------------------------------------
     */
    inline void Reset() {
        // close resources --------------------------------
        Close();

        // change context ---------------------------------
        STask::Sleep(std::chrono::milliseconds(10));

        // open resources ---------------------------------
        Open();

        // change context ---------------------------------
        STask::Sleep(std::chrono::milliseconds(10));
    }
    /**------------------------------------------------------------------------
     * diagnostic
     *-------------------------------------------------------------------------
     *  
     */
    inline std::map<State, size_t> Lengths() {
        map<State, size_t> out;
        for(auto& a : __process) {
            out[a.first] = a.second.size();
        }
        return out;
    }
    /**
     * status -> {'state':['uri1', 'uri2']}
     */
    inline std::string Status() {
        std::ostringstream out;
        out << "{ ";
        for(auto& p :__process) {
                out << "'" << p.first << "':[ ";
                for(auto&a :p.second){
                        out << "'" << a.first << "' ";
                }
                out << "] ";
        }
        out << "}";
        return out.str();
    }
    /**
     * revision
     */
    inline size_t Resvision() {
        return __revision;
    }
protected:
    /**
     * ------------------------------------------------------------------------
     * __Jumps
     * ------------------------------------------------------------------------
     */
    inline Location __Jump(const Location& pos, const State& from, const State& to) {
        // move to queue ----------------------------------
        __process[to][pos->first] = std::move(pos->second);

        // remove and update iterator ---------------------
        return __process[from].erase(pos);
    }
    inline Location __Jump(const State& from, const State& to, const Location& pos) {
        Location it = __process[from].begin();
        Location p = pos;
        if (it != __process[from].end()) {
            
            // move to queue ------------------------------
            p = __process[to].insert(
                p, std::pair<Key, Object>(it->first, it->second)
            );   
            // remove -------------------------------------
            __process[from].erase(it);
        }
        return p;
    }
    /**
     * ------------------------------------------------------------------------
     * others 
     * ------------------------------------------------------------------------
     **
     * update revision
     */
    inline void __UpdateResvision() {
        ++__revision;
    }
    /**
     * size
     */
    inline size_t __Length(std::initializer_list<State> states) {
        size_t n=0;
        for(auto s : states) n+= __process[s].size();
        return n;
    }
private:
    /**
     * ------------------------------------------------------------------------
     * variables
     * ------------------------------------------------------------------------
     **
     * process container
     */
    std::map<State, Area> __process;
    /**
     * process levels
     */
    size_t __nominal;
    size_t __minimum;
    /**
     * process revision
     */
    size_t __revision;
};
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SROAD_H */

