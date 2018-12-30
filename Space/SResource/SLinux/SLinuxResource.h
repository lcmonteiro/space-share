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
 * space
 */
#include "SContainer.h"
#include "SResource.h"
/**
 */
using namespace std;
/**
 * ------------------------------------------------------------------------------------------------
 * Linux Resource
 * ------------------------------------------------------------------------------------------------
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
    bool Valid() const;
    /**
	 * get location
	 */
	string Path() const;
    /**
     * ----------------------------------------------------
     * IO functions
     * ----------------------------------------------------
     * Read frame
     */        
    Frame Read(size_t size);
    /**
     * fill frame
     */
    template<class F>
    SLinuxResource& Fill(F& f) {
        f.Insert(Read(f.Data(), f.Size()));
        return *this;
    }
    /**
     * drain Frame 
     */
    SLinuxResource& Drain(OFrame&& f);
    SLinuxResource& Drain(const Frame& f);
    /**
     * flush Output
     */
    SLinuxResource& Flush();
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
    inline int _Handler() const {
        return __h;
    }
    inline string _HandlerPath() const {
	    ostringstream os;
	    os << "/proc/self/fd/" << _Handler();
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
    size_t __Write(Frame::const_pointer p, Frame::size_type s);
    /**
     * read resource
     */
    size_t __Read(Frame::pointer p, Frame::size_type s);
};

#endif /* SLINUXRESOURCE_H */