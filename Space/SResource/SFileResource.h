/**
 * ------------------------------------------------------------------------------------------------
 * File:   SFileResource.h
 * Author:      Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SFILERESOURCE_H
#define SFILERESOURCE_H
/**
 * space
 */
#include "SResource.h"
#include "SText.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Base
 * ------------------------------------------------------------------------------------------------
 */
class SFileResource : public SResource {
public:
    /**
     * ------------------------------------------------------------------------
     * Defaults
     * ------------------------------------------------------------------------
     */
    SFileResource()                           = default;
    SFileResource(SFileResource&&)            = default;
    SFileResource& operator=(SFileResource&&) = default;
    /**
     * ------------------------------------------------------------------------
     * Interfaces
     * ------------------------------------------------------------------------
     * check resource
     */
    bool Good() const;
    /**
     * ------------------------------------------------------------------------
     * Properties
     * ------------------------------------------------------------------------
     * get size
     */
    size_t Size(); 
    inline size_t size() { return Size(); } 
    /**
     * get position
     */
    size_t Position();
    /**
	 * get location
	 */
	SText Path() const; 
    /**
     * ------------------------------------------------------------------------
     * IO functions
     * ------------------------------------------------------------------------
     * fill and read frame
     */
    template<typename T> SFileResource& Fill (T& f);
    template<typename T> SFileResource& Read (T& f);
    /**
     * drain and write frame
     */
    template<typename T> SFileResource& Drain (T& f);
    template<typename T> SFileResource& Write (T& f);
    template<typename T> SFileResource& Drain (const T& f);
    template<typename T> SFileResource& Write (const T& f);
    /**
     * flush
     */
    SFileResource& Flush();
    /**
     * ------------------------------------------------------------------------
     * Global
     * ------------------------------------------------------------------------
     * link file
     */
    static const std::string& Link(const std::string& from, const std::string& to);
    /**
     * get base name
     */
    static std::string BaseName(const std::string& pathname);
    /**
      * get temporary dir
      */
    static std::string TmpPath();
protected:
    /**
     * ------------------------------------------------------------------------
     * constructor
     * ------------------------------------------------------------------------
     */
    using SResource::SResource;
};
/**
 * ------------------------------------------------------------------------------------------------
 * Input FileResource
 * ------------------------------------------------------------------------------------------------
 */
class SIFileResource : public SFileResource {
public:
    /**
     * constructors
     */
    SIFileResource() = default;
    SIFileResource(const std::string& path);
    SIFileResource(const std::string& path, const SFileResource& link);
};
/**
 * ------------------------------------------------------------------------------------------------
 * Output FileResource
 * ------------------------------------------------------------------------------------------------
 */
class SOFileResource : public SFileResource {
public:
    /**
     * constructors
     */
    SOFileResource() = default;
    SOFileResource(const std::string& path);
    SOFileResource(const std::string& path, const SFileResource& link);
};
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SFILERESOURCE_H */
