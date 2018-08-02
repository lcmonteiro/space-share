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
#include <list>
#include <map>
#include <set>
/**
 */
using namespace std;
/**
 */
template <class KEY, class VAL>
class SCommand {
public:
        /**
         * -------------------------------------------------------------------------------------------------------------
         * definitions
         * -------------------------------------------------------------------------------------------------------------
         */
        using Filter  = set<KEY>;
        using Group   = map<KEY, VAL>;
        using Groups  = list<Group>;
        using Options = map<KEY, Groups>;
        /**
         * -------------------------------------------------------------------------------------------------------------
         * Unserialize
         * -------------------------------------------------------------------------------------------------------------
         */
        static Options Unserialize(Filter filter, string line) {
                using Wrapper = reference_wrapper<Group>;
                // options parsed
                Options options;
                // parse loop
                regex exp("-(\\w+)|--(\\w+)=(\\w+)"); 
                for (auto i = sregex_iterator(line.begin(), line.end(), exp), end = sregex_iterator(); i != end;) {
                        // check start group 
                        if (filter.count(i->str(1))) {
                                // insert group
                                auto& group = Insert(options, i->str(1));
                                // fill group
                                for (++i; (i != end) && i->str(2).size() && i->str(3).size(); ++i) {        
                                        Insert(group, i->str(2), i->str(3));
                                }
                                continue;
                        }
                        ++i;
                }
                return options;
        }
        /**
         * -------------------------------------------------------------------------------------------------------------
         * Serialize
         * -------------------------------------------------------------------------------------------------------------
         */
        static string Serialize(Filter filter, Options opts) {
                ostringstream out;
                for(auto& k : filter) {
                        auto it = opts.find(k);
                        if (it != opts.end()) {
                                for(auto& g : it->second){
                                        out << "-" << it->first << " ";
                                        for (auto&p : g){
                                                out << "--" << p.first << "=" << p.second << " ";
                                        }
                                }
                        } 
                }
                return out.str();
        }
        /**
         * -------------------------------------------------------------------------------------------------------------
         * Peek  
         * -------------------------------------------------------------------------------------------------------------
         */        
        template <class T>
        static inline T Peek(const Group& opt, const KEY& id) {
                T val;
                istringstream(opt.at(id)) >> val;
                return val;
        }
        template <class T>
        static inline T Peek(const Group& opt, const KEY& id, const T& def) {
                try {
                        return Peek<T>(opt, id);
                } catch (...) {
                        return def;
                }
        }
        template <class T>
        static inline T Peek(const Group& opt, const KEY& id1, const KEY& id2, const T& def) {
                try {
                        return Peek<T>(opt, id1);
                } catch (...) {
                        return Peek<T>(opt, id2, def);
                }
        }
private:
        /**
         * -------------------------------------------------------------------------------------------------------------
         * helpers
         * -------------------------------------------------------------------------------------------------------------
         */
        static inline Group& Insert(Options& opts, const KEY& key){
                auto it = opts.find(key);
                if (it != opts.end()) {
                        it->second.emplace_back(Group());
                } else {
                        it = opts.insert(it, typename Options::value_type(key, Groups(1))); 
                }
                return it->second.back();
        }
        static inline void Insert(Group& group, const KEY& key, const VAL& val){
                group[key] = val;
        }
};
#endif /* SCOMMAND_H */

