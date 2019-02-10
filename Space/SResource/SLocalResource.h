/**
 * ------------------------------------------------------------------------------------------------ 
 * Container:   SLocalResource.h
 * Author:      Luis Monteiro
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
     **
     * status
     */
    bool Good();
    /**
     * timeout
     */
    SLocalResource& SetRxTimeout(int timeout);
    SLocalResource& SetTxTimeout(int timeout);
    /**
     * behavior
     */
    SLocalResource& SetNoDelay(bool flag);
    /**
     * ------------------------------------------------------------------------
     * IO functions
     * ------------------------------------------------------------------------
     * fill and read frame
     */
    template<typename T> SLocalResource& Fill (T& f);
    template<typename T> SLocalResource& Read (T& f);
    /**
     * drain and write frame
     */
    template<typename T> SLocalResource& Drain (T& f);
    template<typename T> SLocalResource& Write (T& f);
    template<typename T> SLocalResource& Drain (const T& f);
    template<typename T> SLocalResource& Write (const T& f);
protected:
    /**
     * ------------------------------------------------------------------------
     * defaults
     * ------------------------------------------------------------------------
     */
    SLocalResource()                            = default;
    SLocalResource(SLocalResource&&)            = default;
    SLocalResource& operator=(SLocalResource&&) = default;
};
/**
 * ------------------------------------------------------------------------------------------------
 * message
 * ------------------------------------------------------------------------------------------------
 */
namespace Message {
    class SLocalResource : public ::SLocalResource {
    public:
        /**
         * defaults
         */
        SLocalResource()                            = default;
        SLocalResource(SLocalResource&&)            = default;
        SLocalResource& operator=(SLocalResource&&) = default;
        /**
         * wait
         */
        SLocalResource& Wait(
            const std::string& host, std::chrono::seconds timeout=std::chrono::hours{24}
        );
        /**
         * link
         */
        SLocalResource& Link(const std::string& host);
        /**
         * detach
         */
        inline SLocalResource Detach() {
            return std::move(*this);
        }
    };
}
/**
 * ------------------------------------------------------------------------------------------------
 * stream
 * ------------------------------------------------------------------------------------------------
 */
namespace Stream {
    class SLocalResource : public ::SLocalResource {
    public:
        /**
         * defaults
         */
        SLocalResource()                            = default;
        SLocalResource(SLocalResource&&)            = default;
        SLocalResource& operator=(SLocalResource&&) = default;
        /**
         * wait
         */
        SLocalResource& Wait(
            const std::string& host, std::chrono::seconds timeout=std::chrono::hours{24}
        );
        /**
         * link
         */
        SLocalResource& Link(const std::string& host);
        /**
         * detach
         */
        inline SLocalResource Detach() {
            return std::move(*this);
        }
    };
}
/**
 * ------------------------------------------------------------------------------------------------
 * end
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SLOCALRESOURCE_H */

