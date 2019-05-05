/**
 * ------------------------------------------------------------------------------------------------
 * File:   SRoad.h
 * Author: Luis Monteiro
 *
 * Created on February 22, 2017, 10:34 PM
 * ------------------------------------------------------------------------------------------------
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
    SRoadException(std::error_code ec) 
    : std::system_error(ec) {}
    SRoadException(std::error_code ec, const std::string& what) 
    : system_error(ec, what) {}
    /**
     * destructor
     */
    virtual ~SRoadException() = default;
} RoadException;
/**
 * ----------------------------------------------------------------------------
 * Exception Timeout
 * ----------------------------------------------------------------------------
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
 * ----------------------------------------------------------------------------
 * Exception Detached
 * ----------------------------------------------------------------------------
 */
typedef class SRoadExceptionDetached : public SRoadException {
public:
    using SRoadException::SRoadException;
    /**
     * constructor
     */
    SRoadExceptionDetached() 
    : SRoadException(std::make_error_code(std::errc::resource_unavailable_try_again)) {
    }
    SRoadExceptionDetached(const std::string& what) 
    : SRoadException(std::make_error_code(std::errc::resource_unavailable_try_again), what) {
    }
} RoadDetached;
/**
 * ----------------------------------------------------------------------------
 * Exception Dead
 * ----------------------------------------------------------------------------
 */
typedef class SRoadExceptionDead : public SRoadException {
public:
    using SRoadException::SRoadException;
    /**
     * constructor
     */
    SRoadExceptionDead() 
    : SRoadException(std::make_error_code(std::errc::no_such_device)) {
    }
    SRoadExceptionDead(const std::string& what) 
    : SRoadException(std::make_error_code(std::errc::no_such_device), what) {
    }
} RoadDead;
/**
 * ------------------------------------------------------------------------------------------------
 * Exceptions Templates 
 * ------------------------------------------------------------------------------------------------
 * Timeout
 */
template<class T>
class SRoadExceptionTIMEOUT : public SRoadExceptionTimeout {
public:
    using SRoadExceptionTimeout::SRoadExceptionTimeout;
};
/**
 * detached
 */
template<class T>
class SRoadExceptionDETACHED : public SRoadExceptionDetached {
public:
    using SRoadExceptionDetached::SRoadExceptionDetached;
};
/**
 * Dead
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
    typedef enum {Backlog, Repairing, Running, Dead} State;
    /**
     * ------------------------------------------------------------------------
     * Helpers
     * ------------------------------------------------------------------------
     */
    using Key      = KEY;
    using Object   = OBJ;
    using Road     = SRoad<Key, Object>;
    using Area     = std::map<Key, Object>;
    using Location = typename Area::iterator;
    /**
     * ------------------------------------------------------------------------
     * Defaults
     * ------------------------------------------------------------------------
     */
    SRoad(SRoad&& )           = default;
    SRoad& operator=(SRoad&&) = default;
    /**
     * ------------------------------------------------------------------------
     * Constructors
     * ------------------------------------------------------------------------
     **
     * main constructor
     * @param nominal
     * @param min
     */
    SRoad(size_t nominal = 1, size_t minimum = 1)
    : __nominal(nominal), __minimum(minimum), __revision(0) {}
    /**
     * ------------------------------------------------------------------------
     * Detach
     * ------------------------------------------------------------------------
     */
    inline SRoad detach() {
        return move(*this);
    }
    /**
     * ------------------------------------------------------------------------
     * Update Parameters 
     * ------------------------------------------------------------------------
     */
    inline SRoad& nominal(size_t nominal) {
        __nominal = nominal;
        return *this;
    }
    inline SRoad& minimum(size_t minimum) {
        __minimum = minimum;
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Insert Object
     * ------------------------------------------------------------------------
     */
    inline SRoad& insert(Key k, Object o) {
        /**
         * remove the existing one
         */
        for (auto& p: __process) {
            auto found = p.second.find(k);
            if(p.second.end() != found) {
                p.second.erase(found);
                if(Running == p.first) {
                    _update_resvision();
                }
            }
        }
        /**
         * insert on backlog
         */   
        __process[Backlog].emplace(k, std::move(o));
        /**
         * return itself
         */
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Find Object
     * ------------------------------------------------------------------------
     */
    inline Object& find(Key k) {
        for(auto& p : __process) {
            auto found = p.second.find(k);
            if(p.second.end() != found) {
                return found->second;
            }
        }
        throw std::range_error(__func__);
    }
    /**
     * ------------------------------------------------------------------------
     * Iterator
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
     * Size in Running State
     * -----------------------------------------------------------------------
     */
    inline size_t size() {
        return __process[Running].size();
    }
    /**
     * -----------------------------------------------------------------------
     * Size Total
     * -----------------------------------------------------------------------
     */
    inline size_t size_total() {
        size_t out = 0;
        for(auto& a : __process) {
            out += a.second.size();
        }
        return out;
    }
    /**
     * -----------------------------------------------------------------------
     * Try to Repair
     * -----------------------------------------------------------------------
     */
    inline void exception(Location& it) {
        /**
         * jump to backlog
         */
        it = _jump(it, Running, Backlog);
        /**
         * update revision
         */
        _update_resvision();
    }
    /**
     * ------------------------------------------------------------------------
     * Update 
     * ------------------------------------------------------------------------
     */
    inline Road& update() {
        Area& rep = __process[Repairing];
        /**
         * update areas
         */
        for (auto it = rep.begin(); it != rep.end();) {
            if (it->second->good()) {
                // update revision
                _update_resvision();
                // jump to running 
                it = _jump(it, Repairing, Running); 
                continue;
            }
            if (it->second->inactive()) {
                try {
                    it->second->build();
                } catch(...) {
                    it = _jump(it, Repairing, Dead);
                    continue;
                }
            }
            ++it;
        }
        /**
         * reload repairing queue (if needed)
         */
        int delta = (__nominal - _size({Repairing, Running})); 
        for(auto 
            it = rep.begin(); 
            (0 < delta) && (_jump(Backlog, Repairing, it) != it); 
            it = rep.begin()
        ) { --delta; rep.rbegin()->second->build(); }
        /**
         * is dead
         */
        if (0 < delta) {
            throw SRoadExceptionDEAD<Object>(status());
        }
        /**
         * keep waiting
         */ 
        if (_size({Running}) < __minimum) {
            throw SRoadExceptionDETACHED<Object>(status());
        }
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Reset All Connectors
     * ------------------------------------------------------------------------
     */
    inline void reset() {
        /**
         * repairing
         */
        Area& rep = __process[Repairing];
        for (auto it = rep.begin() , e = rep.end(); it != e;) {
            try {
                it->second->destroy();
                it = _jump(it, Repairing, Backlog);
            } catch(...) {
                it = _jump(it, Repairing, Dead);
            }
        }
        /**
         * running
         */
        Area& run = __process[Running];
        for (auto it = run.begin(), e = run.end(); it != e;) {
            try {
                it->second->destroy();
                it = _jump(it, Running, Backlog);
            } catch(...) {
                it = _jump(it, Repairing, Dead);
            }
            _update_resvision();
        }
    }
    /**
     * ------------------------------------------------------------------------
     * Diagnostic
     * ------------------------------------------------------------------------
     * Sizes
     * ----------------------------------------------------
     */
    inline std::map<State, size_t> sizes() {
        std::map<State, size_t> out;
        for(auto& a : __process) {
            out[a.first] = a.second.size();
        }
        return out;
    }
    /**
     * ----------------------------------------------------
     * status -> {'state':['uri1', 'uri2']}
     * ----------------------------------------------------
     */
    inline std::string status() {
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
     * ----------------------------------------------------
     * Revision
     * ----------------------------------------------------
     */
    inline size_t resvision() {
        return __revision;
    }
protected:
    /**
     * ------------------------------------------------------------------------
     * Jumps
     * ------------------------------------------------------------------------
     */
    inline Location _jump(const Location& pos, const State& from, const State& to) {
        /**
         * move to queue
         */
        __process[to][pos->first] = std::move(pos->second);
        /**
         * remove and update iterator
         */
        return __process[from].erase(pos);
    }
    inline Location _jump(const State& from, const State& to, const Location& pos) {
        Location it = __process[from].begin();
        Location p = pos;
        if (it != __process[from].end()) {
            /**
             * move
             */
            p = __process[to].insert(p, std::move(*it));   
            /**
             * remove
             */
            __process[from].erase(it);
        }
        return p;
    }
    /**
     * ------------------------------------------------------------------------
     * Updates
     * ------------------------------------------------------------------------
     */
    inline void _update_running() {
        Area& rep = __process[Repairing];
        for (auto it = rep.begin(); it != rep.end();) {
            if (it->second->Good()) {
                // update revision
                _update_resvision();
                // jump to running 
                it = _jump(it, Repairing, Running); 
            } else {
                ++it;
            }
        }
    }
    inline void _update_dead() {
        Area& rep = __process[Repairing];
        for (auto it = rep.begin(); it != rep.end();) {
            if (it->second->Good()) {
                // update revision
                _update_resvision();
                // jump to running 
                it = _jump(it, Repairing, Running); 
            } else {
                ++it;
            }
        }
    }
    /**
     * ------------------------------------------------------------------------
     * Others 
     * ------------------------------------------------------------------------
     **
     * update revision
     */
    inline void _update_resvision() {
        ++__revision;
    }
    /**
     * size
     */
    inline size_t _size(std::initializer_list<State> states) {
        size_t n=0;
        for(auto s : states) n+= __process[s].size();
        return n;
    }
private:
    /**
     * ------------------------------------------------------------------------
     * Variables
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
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SROAD_H */

