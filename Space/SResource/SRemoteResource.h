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
     * move operator
     */
    SRemoteResource& operator=(SRemoteResource && res) = default;
    /**
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
         * wait
         */
        inline void Wait(
            const string& host, uint16_t port, chrono::seconds timeout=chrono::hours{24}
        );
        /**
         * link
         */
        inline void Link(
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
 */
#endif /* SREMOTERESOURCE_H */

