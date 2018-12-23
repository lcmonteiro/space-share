/* 
 * Container:   SFileResource.h
 * Author:      Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SFILERESOURCE_H
#define SFILERESOURCE_H
/*---------------------------------------------------------------------------------------------------------------------*
 * linux platform 
 *---------------------------------------------------------------------------------------------------------------------*/
#ifdef __linux__
/**
 */
#include "SLinux/SLinuxFile.h"
/**
 */
class SFileResource : public SLinuxFile {
public:
        using SLinuxFile::SLinuxFile;
};
/**
 */
class SIFileResource : public SILinuxFile {
public:
        using SILinuxFile::SILinuxFile;
};
/**
 */
class SOFileResource : public SOLinuxFile {
public:
        /**
	 * constructors
	 */
	SOFileResource() : SOLinuxFile() {       
        }
	SOFileResource(const string& path) : SOLinuxFile(path) {
        }
        SOFileResource(SOLinuxFile&& file) : SOLinuxFile(move(file)) {
        }
};
/**
 */
#endif
/**
 */
#endif /* SFILERESOURCE_H */

