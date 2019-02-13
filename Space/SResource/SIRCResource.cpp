/**
 * ------------------------------------------------------------------------------------------------
 * Container:   SIRCResource.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 * ------------------------------------------------------------------------------------------------
 **
 * Std
 */
#include <regex>
#include <iostream>
/**
 * Space 
 */
#include "SBase64.h"
#include "SRandom.h"
#include "SIRCResource.h"
#include "SResourceMonitor.h"
/**
 * definitions
 */
#define TOPIC_STR "share"
/**
 * ----------------------------------------------------------------------------
 * Connect
 * ----------------------------------------------------------------------------
 **/
void SIRCResource::Connect(
    const std::string& host, uint16_t port, int tx_timeout, int rx_timeout) {
    /**
     * connect
     */
    Super::Link(host, port);
    /**
     * configuration
     */
    SetTxTimeout(tx_timeout);
    SetRxTimeout(rx_timeout);
    SetNoDelay(true);
}
/**
 * ----------------------------------------------------------------------------
 * Join
 * ----------------------------------------------------------------------------
 */
void SIRCResource::Join(std::string user, std::string channel, int timeout) {
    auto end = std::chrono::system_clock::now() + std::chrono::seconds{timeout};
    /**
     * ----------------------------------------------------
     * validation
     * ----------------------------------------------------
     */
    if(user.empty()) {
        user = SRandom::Name(8);
    }
    /**
     * ----------------------------------------------------
     * functions
     * -----------------------------------------------------
     */
    auto register_func = [&](const std::string& user) {
        /**
         * set user and channel
         */
        __name = user, __nick = SRandom::Name(8),  __channel = channel;
        /**
         * Register
         */
#ifdef __TRACE__
        cout << endl;
        cout << "USER " << __name << " " << __name << " " << __name << ": streamshare \r\n";
        cout << "NICK " << __nick << "\r\n";
        cout << endl;
#endif
        *this << "USER " << __name << " " << __name << " " << __name << ": streamshare \r\n";
        *this << "NICK " << __nick << "\r\n";
        /**
         * wait for welcome
         */
        WaitFor(WELCOME, end);
        /**
         * wait initial messages
         */
        WaitFor(NONE, end);
    };
    /**
     */
    auto join_func = [&](const std::string& channel) {
        /**
         * set channel
         */
        __channel = channel;
        /**
         * Join
         */
#ifdef __TRACE__
        cout << endl ;
        cout << "JOIN #" << __channel << "\r\n";
        cout << endl;
#endif
        *this << "JOIN #" << __channel << "\r\n";
        /**
         * wait for Join
         */
        WaitFor(JOIN, end);
    };
    /**
     * ------------------------------------------------------------------------
     * process
     * ------------------------------------------------------------------------
     */
    try {
        /**
         * ------------------------------------------------
         * try
         * -----------------------------------------------
         * user register
         */
        register_func(user);
        /**
         * chennel join
         */
        join_func(channel);
    } catch (IRCExceptionUSER& ex) {
        /**
         * ------------------------------------------------
         * retry
         * ------------------------------------------------
         * user register
         */
        register_func(user + "_");
        /**
         * chanel join
         */
        join_func(channel);
    }
}
/**
 * ------------------------------------------------------------------------------------------------
 * IO functions
 * ------------------------------------------------------------------------------------------------
 * receive
 * ----------------------------------------------------------------------------
 */
SIRCResource& SIRCResource::Read(Frame& frame) {
    SText line(MAX_LINE_SZ, ' ');
    /**
     * process line
     */
    if (Process(line) == MSG) {
        /**
         * process message
         */
        frame = SBase64::Decode(line);
        return *this;
    }
    throw ResourceExceptionTIMEOUT();
}
SIRCResource& SIRCResource::Read(Frame& frame, const std::chrono::seconds& time) {
    frame = SBase64::Decode(
        WaitFor(MSG, std::chrono::system_clock::now() + time)
    );
    return *this;
}
/**
 * ----------------------------------------------------------------------------
 * Send
 * ----------------------------------------------------------------------------
 */
SIRCResource& SIRCResource::Write(const Frame& frame) {
    /**
     * write
     */
#ifdef __TRACE__
    cout << endl ;
    cout << "PRIVMSG #" << __channel << " :" << SBase64::Encode(frame) << "\r\n";
    cout << endl;
#endif
    *this << "PRIVMSG #" << __channel << " :" << SBase64::Encode(frame) << "\r\n";
    /**
     */
    return *this;
}
/**
 * ----------------------------------------------------------------------------
 * keep
 * ----------------------------------------------------------------------------
 */
void SIRCResource::Keep() {
    while (!SResourceMonitor<>(this).Wait(std::chrono::hours{24}).empty()) {
        SText line(MAX_LINE_SZ, ' ');
        Process(line);
    }
} 
/**
 * ----------------------------------------------------------------------------
 * process line
 * ----------------------------------------------------------------------------
 **/
SIRCResource::TYPE SIRCResource::Process(SText& line) {
    /**
     * commands
     */
    static const string WELCOME_TAG(" 001 ");
    static const string PING_TAG("PING ");
    static const string JOIN_TAG(" JOIN ");
    static const string MSG_TAG(" PRIVMSG ");
    static const string TOPIC_TAG(" 332 ");
    static const string NOTICE_TAG(" NOTICE ");
    /**
     * errors
     */
    static const string USER_ERROR_TAG(" 433 ");
    static const string JOIN_ERROR_TAG(" 477 ");
    static const string ERROR_TAG("ERROR ");
    /**
     */
    static const string VERSION_TAG(": VERSION");
    /**
     * try to read line
     */
    try {
        *this >> line;
    } catch (ResourceExceptionTIMEOUT& ex) {
        return NONE;
    }
#ifdef __TRACE__
    cout << "<:" << line << endl;
#endif
    /**
     * is MGS;
     */
    auto n = line.find(MSG_TAG);
    if (n != string::npos) {
        /**
         * verify channel
         */
        auto nn = line.find(__channel, n);
        if (nn != string::npos) {
            /**
             * erase header "PRIVMSG #channel :"
             */
            line.erase(0, nn + __channel.size() + 2);
            /**
             * MSG
             */
            return MSG;
        }
        /**
         * is version query 
         */
        n = line.find(VERSION_TAG, n);
        if (n != string::npos) {
            /**
             * version response
             */
#ifdef __TRACE__
            cout << endl;
            cout << "NOTICE " << line.substr(1, line.find("!") - 1) << " : VERSION Telnet version 0.1" << "\r\n";
            cout << endl;
#endif
            *this << "NOTICE " << line.substr(1, line.find("!") - 1) << " : VERSION Telnet version 0.1" << "\r\n";
        }
    }
    /**
     * is ping
     */
    n = line.find(PING_TAG);
    if (n != string::npos) {
        /**
         * pong
         */
#ifdef __TRACE__
        cout << endl;
        cout << "PONG " << line.substr(n + PING_TAG.size()) << "\r\n";
        cout << endl;
#endif
        *this << "PONG " << line.substr(n + PING_TAG.size()) << "\r\n";
        /**
         */
        return PING;
    }
    /**
     * is JOIN
     */
    n = line.find(JOIN_TAG);
    if (n != string::npos) {
        /**
         * verify user
         */
        n = line.find(__channel, n);
        if (n != string::npos) {
            /**
             * Welcome
             */
            return JOIN;
        }
    }
    /**
     * is Welcome
     */
    n = line.find(WELCOME_TAG);
    if (n != string::npos) {
        /**
         * verify user
         */
        n = line.find(__nick, n);
        if (n != string::npos) {
            /**
             * Welcome
             */
            return WELCOME;
        }
    }
    /**
     * is Topic 
     */
    n = line.find(TOPIC_TAG);
    if (n != string::npos) {
        /**
         * verify channel
         */
        n = line.find(__channel, n);
        if (n != string::npos) {
            /**
             * erase header "TOPIC #channel :"
             */
            line.erase(0, n + __channel.size() + 2);
            /**
             * MSG
             */
            return TOPIC;
        }
    }
    /**
     * is NOTICE;
     */
    n = line.find(NOTICE_TAG);
    if (n != string::npos) {
        /**
         * verify user
         */
        auto nn = line.find(__nick, n);
        if (nn != string::npos) {
            /**
             * ping
             */
            auto nnn = line.find("PONG", nn);
            if (nnn != string::npos) {
                /**
                 * 
                 */
                std::smatch sm;
                if (std::regex_search(line.cbegin() + nnn, line.cend(), sm, std::regex("PONG (\\S+) "))) {
#ifdef __TRACE__
                    cout << endl;
                    cout << "PONG " << sm[1].str() << "\r\n";
                    cout << endl;
#endif
                    *this << "PONG " << sm[1].str() << "\r\n";
                }
            }

        }
        /**
         * banned
         */
        if (line.find("*** You're banned", n) != string::npos) {
            throw IRCExceptionBANNED(line);
        }
        if (line.find("*** You're not welcome", n) != string::npos) {
            throw IRCExceptionBANNED(line);
        }
    }
    /**
     * is USER ERROR
     */
    n = line.find(USER_ERROR_TAG);
    if (n != string::npos) {
        throw IRCExceptionUSER(line);
    }
    /**
     * is JOIN ERROR
     */
    n = line.find(JOIN_ERROR_TAG);
    if (n != string::npos) {
        throw IRCExceptionJOIN(line);
    }
    /**
     * is ERROR 
     */
    n = line.find(ERROR_TAG);
    if (n != string::npos) {
        if (line.find("banned") != string::npos) {
            throw IRCExceptionBANNED(line);
        }
        throw ResourceExceptionABORT(line);
    }
    /**
     */
    return OTHER;
}
/**
 * ----------------------------------------------------------------------------
 * wait for message type 
 * ----------------------------------------------------------------------------
 */
std::string SIRCResource::WaitFor(TYPE type, const std::chrono::system_clock::time_point& end) {
    while(chrono::system_clock::now() < end) {
        SText line(MAX_LINE_SZ, ' ');
        /**
         * wait for next message
         */
        if (Process(line) == type) {
            return line;
        }
    }
    throw ResourceExceptionTIMEOUT(string("WaitFor::msg::type=") + to_string(type));
}