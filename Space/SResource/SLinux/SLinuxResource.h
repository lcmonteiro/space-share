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
    SLinuxResource(int fd);
    
    SLinuxResource() : __fd(-1) {
    }
    SLinuxResource(SLinuxResource&& res) : SLinuxResource() {
        swap(__fd, res.__fd);
    }
    /**
     * destructor
     */
    virtual ~SLinuxResource();
    /**
     * move operator(swap)
     */
    inline SLinuxResource& operator=(SLinuxResource && res) {
        swap(__fd, res.__fd);
        return *this;
    }
    /**
     * check resource
     */
    bool Valid();
    /**
     * -------------------------------------------------------------------------------------------------------------
     * IO functions
     * -------------------------------------------------------------------------------------------------------------
     **
     * read frame
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
    friend class SLinuxResourceMonitor;
    friend class SLinuxSocket;
    friend class SLinuxPoll;
    /**
     * handler    
     */
    int __fd;
    /**
     * get native handler
     */
    inline int GetHandler() {
        return __fd;
    }
private:
    /**
     */
    size_t Write(Frame::const_pointer p, Frame::size_type s);
    /**
     */
    size_t Read(Frame::pointer p, Frame::size_type s);        
};

#endif /* SLINUXRESOURCE_H */