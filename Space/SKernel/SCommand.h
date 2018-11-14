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
template<class Key, class Val> 
class SCommand {
        const char* Syntax = "-(\\w+)|--(\\w+)=(\\w+)";
public:
        /**
         * -------------------------------------------------------------------------------------------------------------
         * definitions
         * -------------------------------------------------------------------------------------------------------------
         */
        using Group   = map<Key, Val>;
        using Groups  = vector<Group>;
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
        SCommand(string line) : __opts() {
                using Wrapper = std::reference_wrapper<Group>;
                // parse loop
                regex exp(Syntax); 
                for (auto i = sregex_iterator(line.begin(), line.end(), exp), end = sregex_iterator(); i != end;) {
                        // insert group
                        auto& group = __insert(__transform<Key>(i->str(1)));
                        // fill group
                        for (++i; (i != end) && i->str(2).size() && i->str(3).size(); ++i) {        
                                __insert(group, __transform<Key>(i->str(2)), __transform<Val>(i->str(3)));
                        }                                
                }
        }
        /**
         * -------------------------------------------------------------------------------------------------------------
         * access
         * -------------------------------------------------------------------------------------------------------------
         */
        inline const Groups& at(const Key& k) const {
                return __opts.at(k); 
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
        /**
         * -------------------------------------------------------------------------------------------------------------
         * Peek  
         * -------------------------------------------------------------------------------------------------------------
         */        
        template <class T=string>
        static inline T Peek(const Group& opt, const Key& id) {
                T val;
                istringstream(opt.at(id)) >> val;
                return val;
        }
        template <class T>
        static inline T Peek(const Group& opt, const Key& id, const T& def) {
                try {
                        return Peek<T>(opt, id);
                } catch (...) {
                        return def;
                }
        }
        template <class T>
        static inline T Peek(const Group& opt, const Key& id1, const Key& id2, const T& def) {
                try {
                        return Peek<T>(opt, id1);
                } catch (...) {
                        return Peek<T>(opt, id2, def);
                }
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
        static inline Group& __insert(Options& opts, const Key& key){
                auto it = opts.find(key);
                if (it != opts.end()) {
                        it->second.emplace_back(Group());
                } else {
                        it = opts.insert(it, typename Options::value_type(key, Groups(1))); 
                }
                return it->second.back();
        }
        static inline void __insert(Group& group, const Key& key, const Val& val){
                group[key] = val;
        }
        /**
         * -------------------------------------------------------------------------------------------------------------
         * helpers
         * -------------------------------------------------------------------------------------------------------------
         */
        template <class T>
        static inline T __transform(string& s) {
                T val;
                istringstream(s) >> val;
                return val;
        }
};
#endif /* SCOMMAND_H */
