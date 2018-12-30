/* 
 * File:   SBimap.h
 * Author: Luis MOnteiro
 *
 * Created on 15 de Maio de 2018, 11:16
 */
#ifndef SBIMAP_H
#define SBIMAP_H
/**
 * std
 */
#include <map>
/**
 */
using namespace std;
/**
 * ------------------------------------------------------------------------------------------------
 * Bimap key <-> val
 * ------------------------------------------------------------------------------------------------
 */
template <typename T1, typename T2, typename Compare1 = less<T1>, typename Compare2 = less<T2>>
class SBimap {     
public:
    typedef map<T1, T2, Compare1> map1;
    typedef map<T2, T1, Compare2> map2;
    /**
     * constructors
     */
    SBimap() = default;

    SBimap(SBimap&& v) = default;
    
    SBimap(const SBimap& v) = default;
    /**
     * operators
     */
    SBimap& operator=(const SBimap&) = default;
    
    SBimap& operator=(SBimap&&) = default;
    /**
     * quantity
     */
    bool Empty() {
        return _1.empty(); 
    }
    
    size_t Size() {
        return _1.size(); 
    }
    
    size_t Count(T1 v1) {
        return _1.count(v1); 
    }
    size_t Count2(T2 v2) {
        return _2.count(v2); 
    }
    /**
     * insert
     */
    SBimap& Insert(T1 v1, T2 v2) {
        _1[v1] = v2;
        _2[v2] = v1;
        return *this;
    }
    /**
     * erase
     */
    SBimap& Erase(T1 v1) {
        _2.erase(_1.at(v1));
        _1.erase(v1);
        return *this;
    }
    SBimap& Erase2(T2 v2) {
        _1.erase(_2.at(v2));
        _2.erase(v2);
        return *this;
    }
    SBimap& Clear() {
        _1.clear();
        _2.clear();
        return *this;
    }
    /**
     * find
     */
    T2 Find(T1 v1){
        return _1.at(v1);
    }
    T1 Find2(T2 v2){
        return _2.at(v2);
    }
    /**
     * std iterators
     */
    typename map1::const_iterator cbegin() {
        return _1.cbegin();
    }
    typename map1::iterator begin() {
        return _1.begin();
    }
    typename map1::iterator erase(typename map1::iterator* it){
        _2.erase(it->second);
        return _1.erase(it);
    }
    typename map1::iterator end() {
        return _1.end();
    }
    typename map1::const_iterator cend() {
        return _1.cend();
    }
    // 
    typename map2::const_iterator crbegin() {
        return _1.cbegin();
    }
    typename map2::iterator rbegin() {
        return _2.begin();
    }
    typename map2::iterator rerase(typename map2::iterator* it) {
        _1.erase(it->second);
        return _2.erase(it);
    }
    typename map2::iterator rend() {
        return _2.end();
    }
    typename map2::const_iterator crend() {
        return _2.cend();
    }
protected:
    map1 _1;
    map2 _2;
};

#endif /* SBIMAP_H */

