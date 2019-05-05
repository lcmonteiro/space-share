/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SBimap.h
 * Author: Luis Monteiro
 *
 * Created on 15 de Maio de 2018, 11:16
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SBIMAP_H
#define SBIMAP_H
/**
 * std
 */
#include <map>
/**
 * ------------------------------------------------------------------------------------------------
 * Bimap key <-> val
 * ------------------------------------------------------------------------------------------------
 */
template <
    typename T1, 
    typename T2, 
    typename Compare1 = std::less<T1>, 
    typename Compare2 = std::less<T2>>
class SBimap {     
public:
    using Map1 = std::map<T1, T2, Compare1>;
    using Map2 = std::map<T2, T1, Compare2>;
    /**
     * ------------------------------------------------------------------------
     * Constructors
     * ------------------------------------------------------------------------
     */
    SBimap() = default;

    SBimap(SBimap&& v) = default;
    
    SBimap(const SBimap& v) = default;
    /**
     * ------------------------------------------------------------------------
     * Operators
     * ------------------------------------------------------------------------
     */
    SBimap& operator=(const SBimap&) = default;
    
    SBimap& operator=(SBimap&&) = default;
    /**
     * ------------------------------------------------------------------------
     * Quantity
     * ------------------------------------------------------------------------
     */
    bool empty() {
        return _1.empty(); 
    }
    size_t size() {
        return _1.size(); 
    }
    size_t count(T1 v1) {
        return _1.count(v1); 
    }
    size_t count2(T2 v2) {
        return _2.count(v2); 
    }
    /**
     * ------------------------------------------------------------------------
     * Insert
     * ------------------------------------------------------------------------
     */
    SBimap& insert(T1 v1, T2 v2) {
        _1[v1] = v2;
        _2[v2] = v1;
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Erase
     * ------------------------------------------------------------------------
     */
    SBimap& erase(T1 v1) {
        _2.erase(_1.at(v1));
        _1.erase(v1);
        return *this;
    }
    SBimap& erase2(T2 v2) {
        _1.erase(_2.at(v2));
        _2.erase(v2);
        return *this;
    }
    SBimap& clear() {
        _1.clear();
        _2.clear();
        return *this;
    }
    /**
     * ------------------------------------------------------------------------
     * Find
     * ------------------------------------------------------------------------
     */
    T2 find(T1 v1){
        return _1.at(v1);
    }
    T1 find2(T2 v2){
        return _2.at(v2);
    }
    /**
     * ------------------------------------------------------------------------
     * std iterators
     * ------------------------------------------------------------------------
     * forward
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
    /**
     * backware
     */
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
    /**
     * ------------------------------------------------------------------------
     * Variables
     * ------------------------------------------------------------------------
     */ 
    Map1 _1;
    Map2 _2;
};
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */ 
#endif /* SBIMAP_H */

