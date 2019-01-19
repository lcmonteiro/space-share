/**
 * File:   SClock.h
 * Author: Luis Monteiro
 *
 * Created on January 19, 2019, 11:23 AM
 */
#ifndef SCLOCK_H
#define SCLOCK_H
/**
 * std
 */
#include <chrono>
/**
 * ------------------------------------------------------------------------------------------------
 * SClock 
 * ------------------------------------------------------------------------------------------------
 */
template <class CLOCK = std::chrono::steady_clock, class DURATION=std::chrono::milliseconds>
class SClock {
public:
    using Pointer  = typename CLOCK::time_point;
    using Distance = DURATION;
    /**
     * --------------------------------------------------------------------------------------------
     * Alarm 
     * --------------------------------------------------------------------------------------------
     */
    class Alarm {
    public:
        Alarm(const Pointer& end, const Distance& period=Distance::zero())
        : __end(end), __period(period) {
        }
        Alarm(const Distance& delay, const Distance& period)
        : Alarm(CLOCK::now() + delay, period) {
        }
        Alarm(const Distance& period)
        : Alarm(period,period) {
        }
        /**
         * snooze
         */
        inline Alarm& Snooze() {
            __end = CLOCK::now() + __period;
        }
        /**
         * end point
         */
        inline Pointer Tigger() {
            return __end;
        }
        /**
         * active
         **/
        inline bool Active() {
            return CLOCK::now() > __end;
        }
    private:
        Pointer  __end;
        Distance __period;
    };
    /**
     * --------------------------------------------------------------------------------------------
     * helpers 
     * --------------------------------------------------------------------------------------------
     */
    static inline Distance Remaining(const Pointer& end) {
        return chrono::duration_cast<DURATION>(end-CLOCK::now());
    }


};
/**
 * ------------------------------------------------------------------------------------------------
 * end 
 * ------------------------------------------------------------------------------------------------
 */
#endif