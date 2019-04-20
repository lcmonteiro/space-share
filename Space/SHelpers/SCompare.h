/**
 * -------------------------------------------------------------------------------------------------------------------- 
 * File:   SCompare.h
 * Author: Luis Monteiro
 *
 * Created on January 14, 2017, 12:03 AM
 * --------------------------------------------------------------------------------------------------------------------
 */
#ifndef SCOMPARE_H
#define SCOMPARE_H
/**
 * space
 */
#include "SContainer.h"
#include "SFileResource.h"
/**
 * --------------------------------------------------------------------------------------------------------------------
 * Compare
 * --------------------------------------------------------------------------------------------------------------------
 */
class SCompare {
public:
    /**
     * --------------------------------------------------------------------------------------------
     * Compare File
     * --------------------------------------------------------------------------------------------
     **/
    template<size_t CHUNK=0x1000>
    static bool Files(SIFileResource f1, SIFileResource f2) {
        IOFrame aux1(CHUNK), aux2(CHUNK);
        // for each read frame ----------------------------
        do {
            f1.Read(aux1), f2.Read(aux2);
            // test frames --------------------------------
            if(aux1 != aux2) {
                return false;
            }
        } while(aux1.Full());
        // both files are equals --------------------------
        return true;
    }
};
/**
 * --------------------------------------------------------------------------------------------------------------------
 * End
 * --------------------------------------------------------------------------------------------------------------------
 */
#endif /* SCOMPARE_H */

