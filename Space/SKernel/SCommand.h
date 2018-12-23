/* 
 * File:   SCommand.h
 * Author: Luis Monteiro
 *
 * Created on April 14, 2018, 12:03 AM
 */
#ifndef SCOMMAND_H
#define SCOMMAND_H
/**
 */
#include <string>
#include <regex>
#include <vector>
#include <map>
/**
 */
using namespace std;
/**
 */
template<class K, class V> 
class SCommand {
        const char* Syntax = "-(\\w+)|--(\\w+)=(\\w+)";
public:
        using Key = K;
        using Val = V;
        /**
         * -------------------------------------------------------------------------------------------------------------
         * definitions
         * -------------------------------------------------------------------------------------------------------------
         */
        class Group : public map<Key, Val> {
                using map<Key, Val>::at;
        public:
                using map<Key, Val>::map;
                // change
                inline const Val& operator[](const Key& k) const {
                        return at(k); 
                }
                // extra
                template <class T=Val>
                inline const T get(const Key& k) const {
                        T val;
                        istringstream(at(k)) >> val;
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
        };
        class Groups: public vector<Group> {
                using vector<Group>::at;
        public:
                using vector<Group>::vector;
                // change
                inline const Group& operator[](size_t i) const {
                        return at(i); 
                }
        };
        using Options = map<Key, Groups>;
        /**
         * -------------------------------------------------------------------------------------------------------------
         * constructure
         * -------------------------------------------------------------------------------------------------------------
         * default
         */
        SCommand() = default;

        SCommand(SCommand&&) = default;
        
        SCommand(const SCommand&) = default;
        /***
         * main
         */
        SCommand(initializer_list<typename Options::value_type> o):__opts(o){}
        /***
         * unserialize
         */
        SCommand(const string& line) : __opts() {
                using Wrapper = std::reference_wrapper<Group>;
                // parse loop
                regex exp(Syntax); 
                for (auto i = sregex_iterator(line.begin(), line.end(), exp), end = sregex_iterator(); i != end;) {
                        // insert group
                        auto& group = __Insert(__opts, __Transform<Key>(i->str(1)));
                        // fill group
                        for (++i; (i != end) && i->str(2).size() && i->str(3).size(); ++i) {        
                                __Insert(group, __Transform<Key>(i->str(2)), __Transform<Val>(i->str(3)));
                        }                                
                }
        }
        /**
         * -------------------------------------------------------------------------------------------------------------
         * Access
         * -------------------------------------------------------------------------------------------------------------
         */
        inline const Groups& operator[](const Key& k) const {
                return __opts.at(k); 
        }
        /**
         * -------------------------------------------------------------------------------------------------------------
         * Tools
         * -------------------------------------------------------------------------------------------------------------
         */
        inline SCommand& Swap(const Key& k1, const Key& k2) {
                swap(__opts.at(k1),__opts.at(k2));
                return *this; 
        }
        /**
         * -------------------------------------------------------------------------------------------------------------
         * Serialize
         * -------------------------------------------------------------------------------------------------------------
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
         * -------------------------------------------------------------------------------------------------------------
         * objects
         * -------------------------------------------------------------------------------------------------------------
         */
        Options __opts;
private:
        /**
         * -------------------------------------------------------------------------------------------------------------
         * insert
         * -------------------------------------------------------------------------------------------------------------
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
         * -------------------------------------------------------------------------------------------------------------
         * helpers
         * -------------------------------------------------------------------------------------------------------------
         */
        template <class T>
        static inline T __Transform(const string& s) {
                T val;
                istringstream(s) >> val;
                return val;
        }
};
#endif /* SCOMMAND_H */
