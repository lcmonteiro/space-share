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
     * serialize 
     */
    friend std::ostream &operator<<(std::ostream &out, const SVariable &var) {
       if(!var.empty()) {
            out << "[";
            for(auto& v : var){
                out << v.first << v.second;
            }
            out << "]";
        }
        return out;
    }
    friend std::istream &operator>>(std::istream &in, SVariable &var) {
        static std::locale l(in.getloc(), new SCType({'[',']'}));
        //
        in.imbue(l);
        while(in.good()){    
            Key k;
            in >> k;
            switch(in.get()) {
                case '[' :{
                    var.emplace(k, SVariable());
                    in >> var[k];
                    break;
                }
                case ']' :{
                    var.emplace(k, SVariable());
                    return in;
                }
                default:;
            }
        }
        return in;
    }
};
#endif /* SVARIABLE_H */
