/*
 * File:   SVariable.h
 * Author: Luis Monteiro
 *
 * Created on November 2, 2018, 10:34 PM
 */
#ifndef SVARIABLE_H
#define SVARIABLE_H
/**
 * std
 */
#include <iostream>
#include <map>
/**
 */
#include "SCType.h"
/**
 */
template <typename Key>
class SVariable : public std::map<Key, SVariable<Key>>
{
    using Map = std::map<Key, SVariable<Key>>;
  public:
    /**
     * public types
     */
    using Type = Key;
    /**
     * constructors
     */
    using Map::Map;

    SVariable() = default;

    SVariable(const Key &k) : Map() {
        this->atemplace(k, SVariable());
    }
    template <typename = std::enable_if_t<std::is_base_of<std::string, Key>::value>>
    SVariable(const char *k) : Map() {
        this->emplace(k, SVariable());
    }
    /**
     * operators 
     */
    operator Key() const {
        Key out{};
        for (auto &v : *this) out += v.first;
        return out;
    }
    /**
     * iostream operator
     */
    friend std::ostream &operator<<(std::ostream &out, const SVariable &var) {
        return __serialize(out, var);
    }
    friend std::istream &operator>>(std::istream &in, SVariable &var) {
        static std::locale l(in.getloc(), new SCType({'[',']'}));
        //
        in.imbue(l);
        //
        var = __unserialize(in);
        //
        return in;
    }
private:
    /**
     * serialize
     */
    static std::ostream& __serialize(std::ostream &out, const SVariable &var) {
        if(!var.empty()) {
            out << "[";
            for(auto& v : var){
                out << v.first;
                __serialize(out, v.second);
            }
            out << "]";
        }
        return out;
    }
    /**
     * unserialize
     */
    static SVariable __unserialize(std::istream &in) {
        SVariable var;
        while(in.good()){    
            Key k;
            in >> k;
            switch(in.get()) {
                case '[' :{
                    var.emplace(k, __unserialize(in));
                    break;
                }
                case ']' :{
                    var.emplace(k, SVariable());
                    return var;
                }
                default:;
            }
        }
        return var;
    }
};
#endif /* SVARIABLE_H */
