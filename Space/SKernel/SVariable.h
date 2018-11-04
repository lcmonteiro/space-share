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
 * helper
 */
#include "SHelper/SCType.h"
/**
 */
template <typename Key, char Enter='[', char Leave=']'>
class SVariable : public std::map<Key, SVariable<Key>>
{
    /**
     * private types
     */
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
     * get operator 
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
        in.imbue(__loc);
        return __unserialize(in, var);
    }
private:
    static std::locale __loc;
    /**
     * serialize
     */
    static std::ostream& __serialize(std::ostream &out, const SVariable &var) {
        if(!var.empty()) {
            out << Enter;
            for(auto& v : var){
                out << v.first;
                __serialize(out, v.second);
            }
            out << Leave;
        }
        return out;
    }
    /**
     * unserialize
     */
    static std::istream& __unserialize(std::istream& in, SVariable& var) {
        while(in.good()){    
            Key k;
            in >> k;
            switch(in.get()) {
                case Enter :{
                    var.emplace(k, SVariable());
                    // unserialize recursive 
                    __unserialize(in, var[k]);
                    break;
                }
                case Leave :{
                    var.emplace(k, SVariable());
                    return in;
                }
                default:;
            }
        }
        return in;
    }
};
template<typename Key, char Enter, char Leave> 
std::locale SVariable<Key, Enter, Leave>::__loc(std::locale(), new SCType({'[',']'}));

#endif /* SVARIABLE_H */
