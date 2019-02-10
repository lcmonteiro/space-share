/* 
 * File:   SCommand.h
 * Author: Luis Monteiro
 *
 * Created on April 14, 2018, 12:03 AM
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
 *-------------------------------------------------------------------------------------------------
 * command
 *-------------------------------------------------------------------------------------------------
 */
template<class K, class V>
class SCommand {
    const char* Syntax = "-(\\w+)|--(\\w+)=(\\w+)";
public:
    using Key = K;
    using Val = V;
    /**
     * ------------------------------------------------------------------------
     * definitions
     * ------------------------------------------------------------------------
     */
    class Group : public std::map<Key, Val> {
        using std::map<Key, Val>::at;
    public:
        using std::map<Key, Val>::map;
        // get
        inline const Val& operator[](const Key& k) const {
            return at(k);
        }
        // extra
        template <class T=Val>
        inline const T Get(const Key& k) const {
            T val;
            std::istringstream(at(k)) >> val;
            return val;
        }
        template <class T>
        inline const T Get(const Key& k, const T& d) const {
            try {
                return Get<T>(k);
            } catch (...) {
                return d;
            }
        }
        template <class T>
        inline const T Get(const Key& k1, const Key& k2, const T& d) const {
            try {
                return Get<T>(k1);
            } catch (...) {
                return Get<T>(k2, d);
            }
        }
        // set
        inline void Set(const Key& k, const Val& v) {
            at(k) = v;
        }
    };
    class Groups: public std::vector<Group> {
        using std::vector<Group>::at;
    public:
        using std::vector<Group>::vector;
        // change
        inline const Group& operator[](size_t i) const {
            return at(i);
        }
        // head
        inline const Group& Head() const {
            return at(0);
        }
    };
    using Options = std::map<Key, Groups>;
    /**
     * ------------------------------------------------------------------------
     * constructures
     * ------------------------------------------------------------------------
     * default
     */
    SCommand()                = default;
    SCommand(SCommand&&)      = default;
    SCommand(const SCommand&) = default;
    /***
     * main
     */
    SCommand(std::initializer_list<typename Options::value_type> o)
    :__opts(o) {}
    /***
     * unserialize
     */
    SCommand(const std::string& line) : __opts() {
        using Wrapper = std::reference_wrapper<Group>;
        // parse loop
        std::regex exp(Syntax);
        for (auto 
            i   = std::sregex_iterator(line.begin(), line.end(), exp),
            end = std::sregex_iterator(); 
            i != end;
        ) {
            // insert group
            auto& group = __Insert(
                __opts, __Transform<Key>(i->str(1))
            );
            // fill group
            for (++i; (i != end) && i->str(2).size() && i->str(3).size(); ++i) {
                __Insert(
                    group, __Transform<Key>(i->str(2)), __Transform<Val>(i->str(3))
                );
            }
        }
    }
    /**
     * ------------------------------------------------------------------------
     * Access
     * ------------------------------------------------------------------------
     */
    inline const Groups& operator[](const Key& k) const {
        return __opts.at(k);
    }
    /**
     * ------------------------------------------------------------------------
     * Tools
     * ------------------------------------------------------------------------
     */
    inline SCommand& Swap(const Key& k1, const Key& k2) {
        swap(__opts.at(k1),__opts.at(k2));
        return *this;
    }
    inline SCommand& Update(const Key& k1, const Key& k2, const Val& val) {
        for(auto& g : __opts.at(k1)) {
            g.Set(k2, val);
        }
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Serialize
     * ------------------------------------------------------------------------
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
     * ------------------------------------------------------------------------
     * objects
     * ------------------------------------------------------------------------
     */
    Options __opts;
private:
    /**
     * ------------------------------------------------------------------------
     * insert
     * ------------------------------------------------------------------------
     */
    static inline Group& __Insert(Options& opts, const Key& key){
        auto it = opts.find(key);
        if (it != opts.end()) {
            it->second.emplace_back(Group());
        } else {
            it = opts.insert(it, typename Options::value_type(key, Groups(1)));
        }
        return it->second.back();
    }
    static inline void __Insert(Group& group, const Key& key, const Val& val){
        group.emplace(key, val);
    }
    /**
     * ------------------------------------------------------------------------
     * helpers
     * ------------------------------------------------------------------------
     */
    template <class T>
    static inline T __Transform(const std::string& s) {
        T val;
        std::istringstream(s) >> val;
        return val;
    }
};
/**
 *-------------------------------------------------------------------------------------------------
 * end
 *-------------------------------------------------------------------------------------------------
 */
#endif /* SCOMMAND_H */
