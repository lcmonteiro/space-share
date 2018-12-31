/* 
 * Container:   SLinuxSocket.h
 * Author:      Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SLINUXSOCKET_H
#define SLINUXSOCKET_H
/**
 * std
 */
#include <sstream>
#include <condition_variable>
/**
 * local
 */
#include "SLinuxResource.h"
/**
 */
class SLinuxSocket : public SLinuxResource {
public:
    /**
     * definitions
     */
    typedef enum {
        STREAM, DGRAM
    } Type;
    /**
     * constructors
     */
    SLinuxSocket() = default;
    /**
     */
    SLinuxSocket(SLinuxSocket&& res) = default;
    /**
     * destructor
     */
    virtual ~SLinuxSocket();
    /**
     * move operator
     */
    inline SLinuxSocket& operator=(SLinuxSocket && res) = default;
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
    /**
     * ----------------------------------------------------------------------------------------
     * link functions
     * ----------------------------------------------------------------------------------------
     **
     * bind
     */
    void Bind(const string& local, Type type);
    /**
     * wait connection
     */
    void Wait(const string& host, uint16_t port, Type type);
    /**
     * connect to local
     */
    void Connect(const string& host, Type type);
    /**
     * connect to host
     */
    void Connect(
    	const string& host, 
		uint16_t      host_port, 
		Type          type, 
		const string& local = "", 
		uint16_t      local_port = 0
    );
    /**
     * ----------------------------------------------------------------------------------------
     * IO functions
     * ----------------------------------------------------------------------------------------
     * read frame
     */
    Frame Read(size_t size);
    /**
     * fill frame
     */
    template<class F>
    SLinuxSocket& Fill(F& f) {
    f.Insert(__receive(f.Data(), f.Size()));
    return *this;
    }
    /**
     * drain frame
     */
    SLinuxSocket& Drain(OFrame&& f);
    SLinuxSocket& Drain(const Frame& f);
    /**
     * ----------------------------------------------------------------------------------------
     * Text IO functions
     * ----------------------------------------------------------------------------------------
     */
    template <class V>
    inline SLinuxSocket& operator<<(V v) {
    ostringstream os;
    os << v;
    return *this << os.str();
    }
    template <class V>
    inline SLinuxSocket& operator>>(V& v) {
    string s(sizeof (v));
    *this >> s;
    istringstream(s) >> v;
    return *this;
    }
    SLinuxSocket& operator>>(string& str);
    SLinuxSocket& operator<<(const string& str);
    /**
     * utilities
     */
protected:
    using SLinuxResource::SLinuxResource;
private:
    /**
     * linux interface
     */
    size_t __send(Frame::const_pointer p, Frame::size_type s);
    /**
     */
    size_t __receive(Frame::pointer p, Frame::size_type s);
};

#endif /* SLINUXSOCKET_H */

