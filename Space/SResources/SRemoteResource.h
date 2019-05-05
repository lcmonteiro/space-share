/**
 * ------------------------------------------------------------------------------------------------
 * File:   SRemoteResource.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SREMOTERESOURCE_H
#define SREMOTERESOURCE_H
/**
 * std
 */
#include <chrono>
/**
 * space
 */
#include "SResource.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Base
 * ------------------------------------------------------------------------------------------------
 */
class SRemoteResource : public SResource {
public:
   /**
     * ------------------------------------------------------------------------
     * general interfaces
     * ------------------------------------------------------------------------
     **
     * status
     */
    bool good();
    /**
     * timeout
     */
    SRemoteResource& timeout_rx(int timeout);
    SRemoteResource& timeout_tx(int timeout);
    /**
     * behavior
     */
    SRemoteResource& delay(bool flag);
    /**
     * ------------------------------------------------------------------------
     * IO functions
     * ------------------------------------------------------------------------
     * fill and read frame
     */
    template<typename T> SRemoteResource& fill (T& f);
    template<typename T> SRemoteResource& read (T& f);
    /**
     * drain and write frame
     */
    template<typename T> SRemoteResource& drain (T& f);
    template<typename T> SRemoteResource& write (T& f);
    template<typename T> SRemoteResource& drain (const T& f);
    template<typename T> SRemoteResource& write (const T& f);
protected:
    /**
     * ------------------------------------------------------------------------
     * defaults
     * ------------------------------------------------------------------------
     */
    SRemoteResource()                             = default;
    SRemoteResource(SRemoteResource&&)            = default;
    SRemoteResource& operator=(SRemoteResource&&) = default;
};
/**
 * ------------------------------------------------------------------------------------------------
 * Message
 * ------------------------------------------------------------------------------------------------
 */
namespace Message {
    class SRemoteResource : public ::SRemoteResource {
    public:
        /**
         * --------------------------------------------------------------------
         * Defaults
         * --------------------------------------------------------------------
         */
        SRemoteResource()                             = default;
        SRemoteResource(SRemoteResource&&)            = default;
        SRemoteResource& operator=(SRemoteResource&&) = default;
        /**
         * --------------------------------------------------------------------
         * Connections
         * --------------------------------------------------------------------
         * bind
         */
        SRemoteResource& bind(
            const std::string& host,
            uint16_t port
        );
        /**
         * wait
         */
        SRemoteResource& wait(
            const std::string& host, 
            uint16_t port, 
            std::chrono::seconds timeout=std::chrono::hours{24}
        );
        /**
         * link
         */
        SRemoteResource& link(
            const std::string& host, 
            uint16_t port
        );
        /**
         * --------------------------------------------------------------------
         * Detach
         * --------------------------------------------------------------------
         */
        inline SRemoteResource detach() {
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
    class SRemoteResource : public ::SRemoteResource {
    public:
        /**
         * --------------------------------------------------------------------
         * Defaults
         * --------------------------------------------------------------------
         */
        SRemoteResource()                             = default;
        SRemoteResource(SRemoteResource&&)            = default;
        SRemoteResource& operator=(SRemoteResource&&) = default;
        /**
         * --------------------------------------------------------------------
         * Connections
         * --------------------------------------------------------------------
         * wait
         */
        SRemoteResource& wait(
            const std::string& host, 
            uint16_t port, 
            std::chrono::seconds timeout=std::chrono::hours{24}
        );
        /**
         * link
         */
        SRemoteResource& link(
            const std::string& host, 
            uint16_t port
        );
        /**
         * --------------------------------------------------------------------
         * Detach
         * --------------------------------------------------------------------
         */
        inline SRemoteResource detach() {
            return std::move(*this);
        }
    };
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SREMOTERESOURCE_H */

