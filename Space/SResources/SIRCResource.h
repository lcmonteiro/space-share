/**
 * ------------------------------------------------------------------------------------------------- 
 * File:   SIRCResource.h
 * Author:      Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 * -------------------------------------------------------------------------------------------------
 */
#ifndef SIRCRESOURCE_H
#define SIRCRESOURCE_H
/**
 * Space resource
 */
#include "SRemoteResource.h"
#include "SExtensions/STextExtension.h"
/**
 * ------------------------------------------------------------------------------------------------
 * IRC Resource 
 * ------------------------------------------------------------------------------------------------
 **/
class SIRCResource : public STextExtension<Stream::SRemoteResource> {
    using Super = STextExtension<Stream::SRemoteResource>;
    /**
     * ------------------------------------------------------------------------
     * parameters
     * ------------------------------------------------------------------------
     */
    static const int MAX_LINE_SZ = 512;
public:
    /**
     * ------------------------------------------------------------------------
     * process types
     * ------------------------------------------------------------------------
     */
    typedef enum {
        NONE,
        WELCOME,
        PING,
        MSG,
        JOIN,
        TOPIC,
        OTHER
    } TYPE;
    /**
     * ------------------------------------------------------------------------
     * Defaults
     * ------------------------------------------------------------------------
     * constructor
     * ----------------------------------------------------
     */
    SIRCResource()                   = default;
    SIRCResource(SIRCResource&& res) = default;
    /**
     * ----------------------------------------------------
     * destructor
     * ----------------------------------------------------
     */
    virtual ~SIRCResource();
    /**
     * ----------------------------------------------------
     * operatores
     * ----------------------------------------------------
     */
    SIRCResource& operator=(SIRCResource &&) = default;
    /**
     * ------------------------------------------------------------------------
     * Interfaces
     * ------------------------------------------------------------------------
     * connect
     * ----------------------------------------------------
     */
    void Connect(
        const SText& host, uint16_t port, int tx_timeout = 5, int rx_timeout = 5
    );
    /**
     * ----------------------------------------------------
     * join
     * ----------------------------------------------------
     */
    void Join(SText user, SText channel, int timeout = 100);
    /**
     * ----------------------------------------------------
     * send frame
     * ----------------------------------------------------
     */
    template<typename T>
    SIRCResource& Write(const T& frame);
    /**
     * ----------------------------------------------------
     * receive frame
     * ----------------------------------------------------
     */
    SIRCResource& Read(Frame& frame);
    SIRCResource& Read(Frame& frame, const std::chrono::seconds& time);
    /**
     * ----------------------------------------------------
     * keep - processing
     * ---------------------------------------------------
     */
    void Keep();    
protected:
    using Super::Super;
    using Super::Link;
    /**
     * ------------------------------------------------------------------------
     * Internal
     * ------------------------------------------------------------------------
     * process line
     * ----------------------------------------------------
     */
    TYPE Process(SText& line);
    /**
     * ----------------------------------------------------
     * wait for message type 
     * ----------------------------------------------------
     */
    SText WaitFor(
        TYPE type, const std::chrono::system_clock::time_point& end
    );
private:
    /**
     * ------------------------------------------------------------------------
     * Variables
     * ------------------------------------------------------------------------
     */
    SText __name;
    SText __nick;
    SText __channel;
};
/**
 * ------------------------------------------------------------------------------------------------
 * Exceptions
 * ------------------------------------------------------------------------------------------------
 */
typedef class SIRCExceptionUSER : public SResourceExceptionABORT {
public:
    using SResourceExceptionABORT::SResourceExceptionABORT;
} IRCExceptionUSER;

typedef class SIRCExceptionJOIN : public SResourceExceptionABORT {
public:
    using SResourceExceptionABORT::SResourceExceptionABORT;
} IRCExceptionJOIN;

typedef class SIRCExceptionBANNED : public SResourceExceptionABORT {
public:
    using SResourceExceptionABORT::SResourceExceptionABORT;
} IRCExceptionBANNED;
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SIRCRESOURCE_H */
