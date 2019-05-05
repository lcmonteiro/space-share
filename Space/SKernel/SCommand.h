/**
 * -------------------------------------------------------------------------------------------------------------------- 
 * File:   SCommand.h
 * Author: Luis Monteiro
 *
 * Created on April 14, 2018, 12:03 AM
 * --------------------------------------------------------------------------------------------------------------------
 */
#ifndef SCOMMAND_H
#define SCOMMAND_H
/**
 * std
 */
#include <string>
#include <regex>
#include <vector>
#include <map>
/**
 *---------------------------------------------------------------------------------------------------------------------
 * Command
 *---------------------------------------------------------------------------------------------------------------------
 */
template<class K, class V>
class SCommand {
    const char* Syntax = "-(\\w+)|--(\\w+)=(\\w+)";
public:
    using Key = K;
    using Val = V;
    /**
     * --------------------------------------------------------------------------------------------
     * Definitions
     * --------------------------------------------------------------------------------------------
     */
    class Group : public std::map<Key, Val> {
        using std::map<Key, Val>::at;
    public:
        using std::map<Key, Val>::map;
        /**
         * --------------------------------------------------------------------
         * Get
         * --------------------------------------------------------------------
         */
        inline const Val& operator[](const Key& k) const {
            return at(k);
        }
        template <class T=Val>
        inline const T get(const Key& k) const {
            T val;
            std::istringstream(at(k)) >> val;
            return val;
        }
        template <class T>
        inline const T get(const Key& k, const T& d) const {
            try {
                return get<T>(k);
            } catch (...) {
                return d;
            }
        }
        template <class T>
        inline const T get(const Key& k1, const Key& k2, const T& d) const {
            try {
                return get<T>(k1);
            } catch (...) {
                return get<T>(k2, d);
            }
        }
        /**
         * --------------------------------------------------------------------
         * Set
         * --------------------------------------------------------------------
         */
        inline void set(const Key& k, const Val& v) {
            at(k) = v;
        }
    };
    class Groups: public std::vector<Group> {
        using std::vector<Group>::at;
    public:
        using std::vector<Group>::vector;
        /**
         * --------------------------------------------------------------------
         * Update
         * --------------------------------------------------------------------
         */
        inline const Group& operator[](size_t i) const {
            return at(i);
        }
        /**
         * --------------------------------------------------------------------
         * Head
         * --------------------------------------------------------------------
         */
        inline const Group& head() const {
            return at(0);
        }
    };
    using Options = std::map<Key, Groups>;
    /**
     * --------------------------------------------------------------------------------------------
     * Constructures
     * --------------------------------------------------------------------------------------------
     * default
     * ------------------------------------------------------------------------
     */
    SCommand()                = default;
    SCommand(SCommand&&)      = default;
    SCommand(const SCommand&) = default;
    /***
     * ------------------------------------------------------------------------
     * main
     * ------------------------------------------------------------------------
     */
    SCommand(std::initializer_list<typename Options::value_type> o)
    : __opts(o) {}
    /**
     * ------------------------------------------------------------------------
     * Unserialize
     * ------------------------------------------------------------------------
     */
    SCommand(const std::string& line) : __opts() {
        using Wrapper = std::reference_wrapper<Group>;
        /**
         * parse loop
         */
        std::regex exp(Syntax);
        for (auto 
            i   = std::sregex_iterator(line.begin(), line.end(), exp),
            end = std::sregex_iterator(); 
            i != end;
            ) {
            /**
             * insert group
             */
            auto& group = __insert(__opts, __transform<Key>(i->str(1)));
            /**
             * fill group
             */
            for (++i; (i != end) && i->str(2).size() && i->str(3).size(); ++i) {
                __insert(group, 
                    __transform<Key>(i->str(2)), 
                    __transform<Val>(i->str(3)));
            }
        }
    }
    /**
     * --------------------------------------------------------------------------------------------
     * Access
     * --------------------------------------------------------------------------------------------
     */
    inline const Groups& operator[](const Key& k) const {
        return __opts.at(k);
    }
    /**
     * --------------------------------------------------------------------------------------------
     * Tools
     * --------------------------------------------------------------------------------------------
     * swap
     * ------------------------------------------------------------------------
     */
    inline SCommand& swap(const Key& k1, const Key& k2) {
        std::swap(__opts.at(k1), __opts.at(k2));
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * update
     * ------------------------------------------------------------------------
     */
    inline SCommand& update(const Key& k1, const Key& k2, const Val& val) {
        for(auto& g : __opts.at(k1)) {
            g.set(k2, val);
        }
        return *this;
    }
    /**
     * --------------------------------------------------------------------------------------------
     * Serialize
     * --------------------------------------------------------------------------------------------
     */
    friend std::ostream &operator<<(std::ostream &out, const SCommand &cmd) {
        for(auto o : cmd.__opts) {
            for(auto& g : o.second){
                out << "-" << o.first << " ";
                for (auto&p : g){
                    out << "--" << p.first << "=" << p.second << " ";
                }
            }
        }
        return out;
    }
protected:
    /**
     * --------------------------------------------------------------------------------------------
     * Variable
     * --------------------------------------------------------------------------------------------
     */
    Options __opts;
private:
    /**
     * --------------------------------------------------------------------------------------------
     * Insert
     * --------------------------------------------------------------------------------------------
     */
    static inline Group& __insert(Options& opts, const Key& key) {
        auto it = opts.find(key);
        if (it != opts.end()) {
            it->second.emplace_back(Group());
        } else {
            it = opts.insert(it, typename Options::value_type(key, Groups(1)));
        }
        return it->second.back();
    }
    static inline void __insert(Group& group, const Key& key, const Val& val) {
        group.emplace(key, val);
    }
    /**
     * --------------------------------------------------------------------------------------------
     * Transform
     * --------------------------------------------------------------------------------------------
     */
    template <class T>
    static inline T __transform(const std::string& s) {
        T val;
        std::istringstream(s) >> val;
        return val;
    }
};
/**
 *---------------------------------------------------------------------------------------------------------------------
 * End
 *---------------------------------------------------------------------------------------------------------------------
 */
#endif /* SCOMMAND_H */
