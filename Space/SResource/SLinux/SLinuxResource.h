/* 
 * Container:   SLinuxResource.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SLINUXRESOURCE_H
#define SLINUXRESOURCE_H
/**
 * std
 */
#include <chrono>
/**
 * space kernel
 */
#include "SContainer.h"
#include "SResource.h"
/**
 */
using namespace std;
/**
 */
class SLinuxResource : public SResource {
public:
    /**
     * constructors
     */
    SLinuxResource() : __h(-1) {}

    SLinuxResource(SLinuxResource&& res): __h(-1) {
        *this = move(res);
    }
    /**
     * destructor
     */
    virtual ~SLinuxResource();
    /**
     * move operator
     */
    SLinuxResource& operator=(SLinuxResource && res) {
        swap(__h, res.__h);
        return *this;
    }
    /**
     * check resource
     */
    bool valid();
    /**
	 * get location
	 */
	string path();
    /**
     * -------------------------------------------------------------------------------------------------------------
     * IO functions
     * -------------------------------------------------------------------------------------------------------------
     **
     * read frame
     */        
    Frame read(size_t size);
    /**
     * fill frame
     */
    template<class F>
    SLinuxResource& fill(F& f) {
        f.Insert(read(f.Data(), f.Size()));
        return *this;
    }
    /**
     * drain Frame 
     */
    SLinuxResource& drain(OFrame&& f);
    SLinuxResource& drain(const Frame& f);
    /**
     * flush Output
     */
    SLinuxResource& flush();
protected:
    /**
     * friends classes
     */
    friend class SLinuxResourceMonitor;
    friend class SLinuxSocket;
    friend class SLinuxPoll;
    /**
     * constructor
     */
    SLinuxResource(int fd);
    /**
     * get native handlers
     */
    inline int _handler() {
        return __h;
    }
    inline string _handler_path() {
	    ostringstream os;
	    os << "/proc/self/fd/" << _handler();
        return os.str();
    }
private:
    /**
     * handler    
     */
    int __h;
    /**
     * write resource
     */
    size_t __write(Frame::const_pointer p, Frame::size_type s);
    /**
     * read resource
     */
    size_t __read(Frame::pointer p, Frame::size_type s);
};

#endif /* SLINUXRESOURCE_H */