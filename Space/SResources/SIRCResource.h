/**
 * ------------------------------------------------------------------------------------------------- 
 * File:   SIRCResource.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 * -------------------------------------------------------------------------------------------------
 */
#ifndef SIRCRESOURCE_H
#define SIRCRESOURCE_H
/**
 * Space
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
     * Process Types
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
     * Constructors
     * ------------------------------------------------------------------------
     */
    SIRCResource()                   = default;
    SIRCResource(SIRCResource&& res) = default;
    /**
     * ------------------------------------------------------------------------
     * destructor
     * ------------------------------------------------------------------------
     */
    virtual ~SIRCResource();
    /**
     * ------------------------------------------------------------------------
     * operatores
     * ------------------------------------------------------------------------
     * move
     * ----------------------------------------------------
     */
    SIRCResource& operator=(SIRCResource &&) = default;
    /**
     * ------------------------------------------------------------------------
     * Interfaces
     * ------------------------------------------------------------------------
     * Connect
     * ----------------------------------------------------
     */
    void connect(
        const SText& host, 
        uint16_t port, 
        int tx_timeout = 5, 
        int rx_timeout = 5 );
    /**
     * ----------------------------------------------------
     * Join
     * ----------------------------------------------------
     */
    void join(
        SText user, 
        SText channel, 
        int timeout = 100);
    /**
     * ----------------------------------------------------
     * Send Frame
     * ----------------------------------------------------
     */
    template<typename T>
    SIRCResource& write(const T& frame);
    /**
     * ----------------------------------------------------
     * Receive Frame
     * ----------------------------------------------------
     */
    SIRCResource& read(Frame& frame);
    /**
     * with timeout
     */
    SIRCResource& read(
        Frame& frame, 
        const std::chrono::seconds& time);
    /**
     * ----------------------------------------------------
     * keep - processing
     * ---------------------------------------------------
     */
    void keep();    
protected:
    using Super::Super;
    using Super::link;
    /**
     * ------------------------------------------------------------------------
     * Internal
     * ------------------------------------------------------------------------
     * process line
     * ----------------------------------------------------
     */
    TYPE _process(SText& line);
    /**
     * ----------------------------------------------------
     * wait for message type 
     * ----------------------------------------------------
     */
    SText _wait_for(
        TYPE type, 
        const std::chrono::system_clock::time_point& end);
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

