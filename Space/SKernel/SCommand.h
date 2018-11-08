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
 * Filter Type
 */
#define COMMAND_T(_name_, _args_...) struct  _name_ {      \
        static bool Find(string k) {                       \
                static set<string> SET{_args_};            \
                return SET.count(k) > 0;                   \
        }                                                  \
}
/**
 * Variable
 */
#define COMMAND(_name_, _args_...)                         \
COMMAND_T(_f_##_name_, _args_);                            \
SCommand<_f_##_name_> _name_
/**
 */
template<class Filter> 
class SCommand {
        using Key = string;
        using Val = string;
public:
        /**
         * -------------------------------------------------------------------------------------------------------------
         * definitions
         * -------------------------------------------------------------------------------------------------------------
         */
        using Group   = map<Key, Val>;
        using Groups  = list<Group>;
        using Options = map<Key, Groups>;
        /**
         * -------------------------------------------------------------------------------------------------------------
         * constructure
         * -------------------------------------------------------------------------------------------------------------
         */
        SCommand() = default;

        SCommand(SCommand&&)=default;
        
        SCommand(const SCommand&)=default;
        
        SCommand(initializer_list<Options::value_type> p):__config(p){}
        /**
         * -------------------------------------------------------------------------------------------------------------
         * Operators
         * -------------------------------------------------------------------------------------------------------------
         */
        inline Groups& operator[](string tag) {
                return __config[tag]; 
        }
        /**
         * -------------------------------------------------------------------------------------------------------------
         * Unserialize
         * -------------------------------------------------------------------------------------------------------------
         */
        inline SCommand& Unserialize(string line) {
                using Wrapper = std::reference_wrapper<Group>;
                // parse loop
                regex exp("-(\\w+)|--(\\w+)=(\\w+)"); 
                for (auto i = sregex_iterator(line.begin(), line.end(), exp), end = sregex_iterator(); i != end;) {
                        // check start group 
                        if (Filter::Find(i->str(1))) {
                                // insert group
                                auto& group = Insert(__config, i->str(1));
                                // fill group
                                for (++i; (i != end) && i->str(2).size() && i->str(3).size(); ++i) {        
                                        Insert(group, i->str(2), i->str(3));
                                }
                                continue;
                        }
                        ++i;
                }
                return *this;
        }
        /**
         * -------------------------------------------------------------------------------------------------------------
         * Serialize
         * -------------------------------------------------------------------------------------------------------------
         */
        inline string Serialize() {
                ostringstream out;
                for(auto c : __config) {
                        for(auto& g : c.second){
                                out << "-" << c.first << " ";
                                for (auto&p : g){
                                        out << "--" << p.first << "=" << p.second << " ";
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
        Options __config;
private:
        /**
         * -------------------------------------------------------------------------------------------------------------
         * helpers
         * -------------------------------------------------------------------------------------------------------------
         */
        static inline Group& Insert(Options& opts, const Key& key){
                auto it = opts.find(key);
                if (it != opts.end()) {
                        it->second.emplace_back(Group());
                } else {
                        it = opts.insert(it, typename Options::value_type(key, Groups(1))); 
                }
                return it->second.back();
        }
        static inline void Insert(Group& group, const Key& key, const Val& val){
                group[key] = val;
        }
};
#endif /* SCOMMAND_H */
