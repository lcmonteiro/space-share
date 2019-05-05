/* 
 * File:   STestBasic.h
 * Author: Luis Monteiro
 *
 * Created on September 26, 2015, 11:20 AM
 */
#ifndef STESTBASIC_H
#define	STESTBASIC_H
/**
 */
#include "SBufferShare.h"
/**
 */
class STestBasic {
public:
    STestBasic() = default;
    /**
     */
    virtual ~STestBasic() = default;
    /**
     * run test 
     */
    int operator() (
        int iterations, 
        int frameSize, 
        int redundancy, 
        int minBufferSize, 
        int maxBufferSize );
private:
    /**
     *  
     */
    Frame Random(int min, int max);
};
#endif	/* STESTBASIC_H */
