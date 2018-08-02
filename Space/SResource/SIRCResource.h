/* 
 * Container:   SIRCResource.h
 * Author:      Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SIRCRESOURCE_H
#define SIRCRESOURCE_H
/*---------------------------------------------------------------------------------------------------------------------*
 * linux platform 
 *---------------------------------------------------------------------------------------------------------------------*/
#ifdef __linux__
/**
 */
#include "SLinux/SLinuxIRC.h"
/**
 */
class SIRCResource : public SLinuxIRC {
public:
        using SLinuxIRC::SLinuxIRC;
};
/**
 */
#endif
/**
 */
#endif /* SIRCRESOURCE_H */

