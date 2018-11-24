/* 
 * File:   SEnergy.h
 * Author: Luis Monteiro
 *
 * Created on November 22, 2018, 9:49 AM
 */
#ifndef SENERGY_H
#define SENERGY_H
/**
 * std
 */

/**
 * Energy
 */
template <class EX>
class SEnergy {
public:
    /**
     * constructor
     */
    SEnergy(size_t energy=0):__energy(energy), __capacity(energy){
    }
    /**
     * Get energy value
     */
    inline size_t Get() {
        return __energy;
    }
    /**
     * Decrement energy
     */
    inline void Decay() {
        if(__energy--==0) throw EX("no energy");
    }
    /**
     * Restore energy
     */
    inline void Restore() {
        __energy = __capacity;
    }
protected:
    size_t __energy;
    size_t __capacity;
};

#endif /* SENERGY_H */

