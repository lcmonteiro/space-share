/* 
 * Container:   SDirectoryResource.h
 * Author:      Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SDIRECTORYRESOURCE_H
#define SDIRECTORYRESOURCE_H
/**
 */
#include "SFileResource.h"
/**
 */
/*---------------------------------------------------------------------------------------------------------------------*
 * linux platform 
 *---------------------------------------------------------------------------------------------------------------------*/
#ifdef __linux__
/**
 */
#include "SLinux/SLinuxDirectory.h"

/**
 */
class SDirectoryResource : public SLinuxDirectory {
public:
        using SLinuxDirectory::SLinuxDirectory;
};
/**
 */
class SIDirectoryResource : public SILinuxDirectory {
public:
        using SILinuxDirectory::SILinuxDirectory;
};
/**
 */
class SODirectoryResource : public SOLinuxDirectory {
public:
        /**
         * constructors
         */
        SODirectoryResource() : SOLinuxDirectory() {
        }
        SODirectoryResource(const string& path) : SOLinuxDirectory(path, 0) {
        }
        SODirectoryResource(const string& path, size_t capacity) : SOLinuxDirectory(path, capacity) {
        }        
        /**
         * get resources
         */
        SOFileResource GetResource() {
                return SOFileResource(SOLinuxDirectory::GetResource());
        }
        SOFileResource resource(const string& name) {
                return SOFileResource(SOLinuxDirectory::resource(name));
        }
};
/**
 */
#endif
/**
 */
#endif /* SDIRECTORYRESOURCE_H */

