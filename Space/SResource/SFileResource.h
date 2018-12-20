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
/*---------------------------------------------------------------------------------------------------------------------*
 * cross platform 
 *---------------------------------------------------------------------------------------------------------------------*/
#include <SRandom.h>
#include <cstdlib>
/** 
 */
template<size_t CHUNK=0x1000>
class SRandomFileResource : public SOFileResource {
public:
        /**
	 * constructors
	 */
	SRandomFileResource() = default;
        /**
         * main constructor
         */
	SRandomFileResource(const string& path, size_t n) : SOFileResource(path) {
                auto d = div(int(n), int(CHUNK));
                for(size_t i=0; i<d.quot; ++i) {
                        Drain(SRandom::RFrame(CHUNK));
                }
                Drain(SRandom::RFrame(d.rem)).Flush();
        }
};
/**
 */
#endif /* SFILERESOURCE_H */

