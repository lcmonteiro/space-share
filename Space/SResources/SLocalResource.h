/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SLocalResource.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SLOCALRESOURCE_H
#define SLOCALRESOURCE_H
/**
 * std
 */
#include <chrono>
/**
 * space
 */
#include "SResource.h"
#include "SContainer.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Base 
 * ------------------------------------------------------------------------------------------------
 */
class SLocalResource : public SResource {
public:
    /* ------------------------------------------------------------------------
     * general interfaces
     * ------------------------------------------------------------------------
     * status
     */
    bool good();
    /**
     * timeout
     */
    SLocalResource& timeout_rx(int timeout);
    SLocalResource& timeout_tx(int timeout);
    /**
     * ------------------------------------------------------------------------
     * IO functions
     * ------------------------------------------------------------------------
     * fill and read frame
     */
    template<typename T> SLocalResource& fill (T& f);
    template<typename T> SLocalResource& read (T& f);
    /**
     * drain and write frame
     */
    template<typename T> SLocalResource& drain (T& f);
    template<typename T> SLocalResource& write (T& f);
    template<typename T> SLocalResource& drain (const T& f);
    template<typename T> SLocalResource& write (const T& f);
protected:
    /**
     * ------------------------------------------------------------------------
     * Defaults
     * ------------------------------------------------------------------------
     */
    SLocalResource()                            = default;
    SLocalResource(SLocalResource&&)            = default;
    SLocalResource& operator=(SLocalResource&&) = default;
};
/**
 * ------------------------------------------------------------------------------------------------
 * Message
 * ------------------------------------------------------------------------------------------------
 */
namespace Message {
    class SLocalResource : public ::SLocalResource {
    public:
        /**
         * --------------------------------------------------------------------
         * Defaults
         * --------------------------------------------------------------------
         */
        SLocalResource()                            = default;
        SLocalResource(SLocalResource&&)            = default;
        SLocalResource& operator=(SLocalResource&&) = default;
        /**
         * --------------------------------------------------------------------
         * Connections
         * --------------------------------------------------------------------
         * bind
         */
        SLocalResource& bind(const std::string& local);
        /**
         * Wait
         */
        SLocalResource& wait(const std::string& local, std::chrono::seconds timeout);
        /**
         * Link
         */
        SLocalResource& link(const std::string& local);
        /**
         * --------------------------------------------------------------------
         * Detach
         * --------------------------------------------------------------------
         */
        inline SLocalResource detach() {
            return std::move(*this);
        }
    };
}
/**
 * ------------------------------------------------------------------------------------------------
 * Stream
 * ------------------------------------------------------------------------------------------------
 */
namespace Stream {
    class SLocalResource : public ::SLocalResource {
    public:
        /**
         * --------------------------------------------------------------------
         * Defaults
         * --------------------------------------------------------------------
         */
        SLocalResource()                            = default;
        SLocalResource(SLocalResource&&)            = default;
        SLocalResource& operator=(SLocalResource&&) = default;
        /**
         * --------------------------------------------------------------------
         * Connections
         * --------------------------------------------------------------------
         * Wait
         */
        SLocalResource& wait(
            const std::string& local, 
            std::chrono::seconds timeout=std::chrono::hours{24});
        /**
         * Link
         */
        SLocalResource& link(const std::string& local);
        /**
         * --------------------------------------------------------------------
         * Detach
         * --------------------------------------------------------------------
         */
        inline SLocalResource detach() {
            return std::move(*this);
        }
    };
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SLOCALRESOURCE_H */

