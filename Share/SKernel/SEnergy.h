/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SEnergy.h
 * Author: Luis Monteiro
 *
 * Created on November 22, 2018, 9:49 AM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SENERGY_H
#define SENERGY_H
/**
 * ------------------------------------------------------------------------------------------------
 * Energy
 * ------------------------------------------------------------------------------------------------
 */
template <class EX>
class SEnergy {
public:
    /**
     * ----------------------------------------------------
     * constructor
     * ----------------------------------------------------
     */
    SEnergy(size_t energy=0)
    : __prev(energy), __curr(energy), __capacity(energy) {
    }
    /**
     * ----------------------------------------------------
     * inrefaces
     * ----------------------------------------------------
     * check if is empty
     */
    inline bool empty() {
        return (__curr == 0) && (__prev == 0);
    }
    /**
     * Get energy value
     */
    inline size_t Get() {
        return __prev;
    }
    /**
     * Set energy value
     */
    inline void Set(size_t energy) {
        if(energy > __capacity){
            __curr = __prev = __capacity = energy;
        } else {
            __curr = __prev = energy;
        }
    }
    /**
     * Decrement energy
     */
    inline void Decay() {
        // update previous
        __prev = __curr;
        // check and decrement current
        if(0 == __curr) {
            throw EX("no energy");
        } else {
            --__curr;
        }
    }
    /**
     * Cancel decay
     */
    inline void Cancel() {
        if(0 == __prev) {
            throw EX("no energy");
        } else {
            __curr = __prev;
        }
    }
    /**
     * Restore energy
     */
    inline void Restore() {
        __curr = __prev = __capacity;
    }
private:
    /**
     * ----------------------------------------------------
     * variables
     * ----------------------------------------------------
     */
    size_t __prev;
    size_t __curr;
    size_t __capacity;
};
/**
 * ------------------------------------------------------------------------------------------------
 * Energy
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SENERGY_H */

