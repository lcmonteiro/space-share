/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SDirectoryResource.h
 * Author:      Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SDIRECTORYRESOURCE_H
#define SDIRECTORYRESOURCE_H
/**
 */
#include "SFileResource.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Base
 * ------------------------------------------------------------------------------------------------
 */
class SDirectoryResource : public SResource {
public:
    /**
     * ------------------------------------------------------------------------
     * defaults
     * ------------------------------------------------------------------------
     **
     * constructor
     */
    SDirectoryResource() = default;
    /**
     * move operator(swap)
     */
    SDirectoryResource& operator=(SDirectoryResource &&) = default;
    /**
     * ------------------------------------------------------------------------
     * initialization 
     * ------------------------------------------------------------------------
     */
    SDirectoryResource(const std::string& path): SResource(), __path(path) {} 
    /**
     * --------------------------------------------------------------------
     * interfaces
     * --------------------------------------------------------------------
     **
     * status
     */
    bool Valid();
protected:
    /**
     * ------------------------------------------------------------------------
     * variables 
     * ------------------------------------------------------------------------
     ** 
     * directory path
     */
    std::string __path;
};
/**
 * ------------------------------------------------------------------------------------------------
 * Input DirectoryResource
 * ------------------------------------------------------------------------------------------------
 */
class SIDirectoryResource : public SDirectoryResource {
public:
    /**
     * ------------------------------------------------------------------------
     * defaults
     * ------------------------------------------------------------------------
     * constructors
     */
    SIDirectoryResource()                      = default;
    SIDirectoryResource(SIDirectoryResource&&) = default;
    /**
     * destructor
     */
    virtual ~SIDirectoryResource() = default;
    /**
     * operator
     */
    SIDirectoryResource& operator=(SIDirectoryResource&&) = default;
    /**
     * --------------------------------------------------------------------
     *  initilialization
     * --------------------------------------------------------------------
     */
    SIDirectoryResource(const std::string& path);
    /**
     * --------------------------------------------------------------------
     * interfaces
     * --------------------------------------------------------------------
     **
     * get resource
     */
    SIFileResource GetResource();
};
/**
 * ------------------------------------------------------------------------------------------------
 * Output DirectoryResource
 * ------------------------------------------------------------------------------------------------
 */
class SODirectoryResource : public SDirectoryResource {
public:
    /**
     * ------------------------------------------------------------------------
     * defaults
     * ------------------------------------------------------------------------
     * constructors
     */
    SODirectoryResource()                      = default;
    SODirectoryResource(SODirectoryResource&&) = default;
    /**
     * destructor
     */
    virtual ~SODirectoryResource() = default;
    /**
     * operator
     */
    SODirectoryResource& operator=(SODirectoryResource&&) = default;
    /**
     * --------------------------------------------------------------------
     *  initilialization
     * --------------------------------------------------------------------
     */
    SODirectoryResource(const std::string& path, size_t capacity);
    /**
     * --------------------------------------------------------------------
     * interfaces
     * --------------------------------------------------------------------
     **
     * get resource
     */
    SOFileResource GetResource();
    SOFileResource GetResource(const std::string& name);
private:
    /**
     * settings
     */
     size_t __capacity;
    /**
     * context
     */
     size_t __position;
};
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SDIRECTORYRESOURCE_H */

