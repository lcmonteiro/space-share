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
    void SetRxTimeout(int timeout);
    void SetTxTimeout(int timeout);
    /**
     * behavior
     */
    void SetNoDelay(bool flag);
    /**
     * ------------------------------------------------------------------------
     * IO functions
     * ------------------------------------------------------------------------
     * fill frame
     */
    SRemoteResource& Fill(Frame& f);
    /**
     * drain frame
     */
    SRemoteResource& Drain(const Frame& f);
    /**
     * utils
     */
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
         * wait
         */
        inline void Wait(const string& host, uint16_t host_port);
        /**
         * link
         */
        inline void Link(const string& host, uint16_t host_port); 
    };
}
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SREMOTERESOURCE_H */

