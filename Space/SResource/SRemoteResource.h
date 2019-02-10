/* 
 * Container:   SRemoteResource.h
 * Author:      Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
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
#include "SContainer.h"
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
    bool Good();
    /**
     * timeout
     */
    SRemoteResource& SetRxTimeout(int timeout);
    SRemoteResource& SetTxTimeout(int timeout);
    /**
     * behavior
     */
    SRemoteResource& SetNoDelay(bool flag);
    /**
     * ------------------------------------------------------------------------
     * IO functions
     * ------------------------------------------------------------------------
     * fill and read frame
     */
    template<typename T> SRemoteResource& Fill (T& f);
    template<typename T> SRemoteResource& Read (T& f);
    /**
     * drain and write frame
     */
    template<typename T> SRemoteResource& Drain (T& f);
    template<typename T> SRemoteResource& Write (T& f);
    template<typename T> SRemoteResource& Drain (const T& f);
    template<typename T> SRemoteResource& Write (const T& f);
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
 * message
 * ------------------------------------------------------------------------------------------------
 */
namespace Message {
    class SRemoteResource : public ::SRemoteResource {
    public:
        /**
         * defaults
         */
        SRemoteResource()                             = default;
        SRemoteResource(SRemoteResource&&)            = default;
        SRemoteResource& operator=(SRemoteResource&&) = default;
        /**
         * wait
         */
        SRemoteResource& Wait(
            const string& host, uint16_t port, chrono::seconds timeout=chrono::hours{24}
        );
        /**
         * link
         */
        SRemoteResource& Link(
            const string& host, uint16_t host_port
        );
        /**
         * detach
         */
        inline SRemoteResource Detach() {
            return move(*this);
        }
    };
}
/**
 * ------------------------------------------------------------------------------------------------
 * stream
 * ------------------------------------------------------------------------------------------------
 */
namespace Stream {
    class SRemoteResource : public ::SRemoteResource {
    public:
        /**
         * defaults
         */
        SRemoteResource()                             = default;
        SRemoteResource(SRemoteResource&&)            = default;
        SRemoteResource& operator=(SRemoteResource&&) = default;
        /**
         * wait
         */
        SRemoteResource& Wait(
            const string& host, uint16_t port, chrono::seconds timeout=chrono::hours{24}
        );
        /**
         * link
         */
        SRemoteResource& Link(
            const string& host, uint16_t host_port
        );
        /**
         * detach
         */
        inline SRemoteResource Detach() {
            return move(*this);
        }
    };
}
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SREMOTERESOURCE_H */

