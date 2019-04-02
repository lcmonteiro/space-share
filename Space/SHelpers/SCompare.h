/* 
 * File:   SCompare.h
 * Author: Luis Monteiro
 *
 * Created on January 14, 2017, 12:03 AM
 */
#ifndef SCOMPARE_H
#define SCOMPARE_H
/**
 * std
 */
/**
 * space
 */
#include "SContainer.h"
#include "SFileResource.h"
/**
 */
using namespace std;
/**
 */
class SCompare {
public:
    /**
     * --------------------------------------------------------------------------------------------
     * Compare Frame
     * --------------------------------------------------------------------------------------------
     **/
	static bool Frames(const SFrame& f1, const SFrame& f2) {
        
        return true;
    }
    /**
     * --------------------------------------------------------------------------------------------
     * Compare File
     * --------------------------------------------------------------------------------------------
     **/
    template<size_t CHUNK=0x1000>
    static bool Files(const SIFileResource& f1, const SIFileResource& f2) {
        
        return true;
    }
};

#endif /* SCOMPARE_H */

