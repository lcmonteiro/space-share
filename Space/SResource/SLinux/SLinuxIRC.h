/* 
 * Container: SLinuxIRC.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SLINUXIRC_H
#define SLINUXIRC_H
/**
 * C++ 
 */
#include <chrono>
#include <thread>
/**
 * Space Resource Linux
 */
#include "SLinuxResourceMonitor.h"
/**
 * Local
 */
#include "SLinuxSocket.h"
/**
 */
class SLinuxIRC : public SLinuxSocket {
    /**
     * parameters
     */
    static const int MAX_LINE_SZ = 512;
    /**
     */
public:
    /**
     * process types
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
     * constructors
     */
    SLinuxIRC() = default;
    
    SLinuxIRC(SLinuxIRC&& res) : SLinuxSocket() {
        SLinuxResource::operator=(move(res));
    }
    /**
     * destructor
     */
    virtual ~SLinuxIRC();
    /**
     * move
     */
    inline SLinuxIRC& operator=(SLinuxIRC && res) = default;
    /**
     * connect
     */
    void Connect(const string& host, uint16_t port, int tx_timeout = 5, int rx_timeout = 5);
    /**
     * join
     */
    void Join(string user, string channel, int timeout = 100);
    /**
     * send frame
     */
    SLinuxIRC& Send(const Frame& frame);
    /**
     * receive
     */
    SLinuxIRC& Receive(Frame& frame);
    SLinuxIRC& Receive(Frame& frame, const chrono::seconds& time);
    /**
     * read frame
     */
    Frame Read();
    /**
     * keep
     */
    inline void Keep() {
        while (SLinuxResourceMonitor::Wait(*this, chrono::hours{24}).valid()) {
            string line(MAX_LINE_SZ, ' ');
            Process(line);
        }
    }    
protected:
    using SLinuxSocket::SLinuxSocket;
    using SLinuxSocket::Connect;
    /**
     */
    TYPE Process(string& line);
    /**
     */
    string WaitFor(TYPE type, const chrono::system_clock::time_point& end);
private:
    string __name;
    string __nick;
    string __channel;
};
/**
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
 */
#endif /* SLINUXIRC_H */

