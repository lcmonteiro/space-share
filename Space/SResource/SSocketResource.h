/* 
 * Container:   SSocketResource.h
 * Author:      Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SSOCKETRESOURCE_H
#define SSOCKETRESOURCE_H
/*---------------------------------------------------------------------------------------------------------------------*
 * linux platform 
 *---------------------------------------------------------------------------------------------------------------------*/
#ifdef __linux__
/**
 */
#include "SLinux/SLinuxSocket.h"
/**
 */
class SSocketResource : public SLinuxSocket {
public:
        using SLinuxSocket::SLinuxSocket;
};
/**
 */
#endif
/**
 */
#endif /* SSOCKETRESOURCE_H */

