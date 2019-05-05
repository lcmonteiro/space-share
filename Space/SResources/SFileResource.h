/**
 * ------------------------------------------------------------------------------------------------
 * File:   SFileResource.h
 * Author: Luis Monteiro
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
     * check
     */
    bool good() const;
    /**
     * ------------------------------------------------------------------------
     * Properties
     * ------------------------------------------------------------------------
     * size
     */
    size_t size();
    /**
     * position
     */
    size_t position();
    /**
	 * location
	 */
	SText path() const; 
    /**
     * ------------------------------------------------------------------------
     * IO functions
     * ------------------------------------------------------------------------
     * fill and read frame
     */
    template<typename T> SFileResource& fill (T& f);
    template<typename T> SFileResource& read (T& f);
    /**
     * drain and write frame
     */
    template<typename T> SFileResource& drain (T& f);
    template<typename T> SFileResource& write (T& f);
    template<typename T> SFileResource& drain (const T& f);
    template<typename T> SFileResource& write (const T& f);
    /**
     * flush
     */
    SFileResource& flush();
    /**
     * ------------------------------------------------------------------------
     * Global
     * ------------------------------------------------------------------------
     * link file
     */
    static const std::string& Link(
        const std::string& from, const std::string& to);
    /**
     * base name
     */
    static std::string BaseName(const std::string& pathname);
    /**
      * temporary dir
      */
    static std::string PathTemp();
protected:
    /**
     * ------------------------------------------------------------------------
     * Constructor
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
     * Constructors
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
     * Constructors
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
