/*
 * Container:   SLinuxResource.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 */
#include <sys/fcntl.h>
#include <unistd.h>
#include <string.h>
/**
 * space
 */
#include "SLinuxResourceMonitor.h"
/**
 * local
 */
#include "SLinuxResource.h"
/**
 * constructor
 */
SLinuxResource::SLinuxResource(int fd) : __h(fd) {
    if (__h < 0) {
        throw system_error(make_error_code(errc::no_such_file_or_directory));
    }
}
/**
 * destructor
 */
SLinuxResource::~SLinuxResource() {
    if (__h > 0) {
       ::close(__h);
    }
}
/**
 * check resource
 */
bool SLinuxResource::Valid() const {
    return ::fcntl(__h, F_GETFL) != -1 || errno != EBADF;
}
/**
 * get file path
 */
string SLinuxResource::Path() const {
	vector<char> out;
	//read real path
	int len = 0;
	do {
		out.resize(out.size() + 0x100);
		if((len = ::readlink(_HandlerPath().data(), out.data(), out.size())) < 0) {
			throw ResourceException(make_error_code(errc(errno)));	
		}
	} while(out.size()==len);
	// return path as string
	return string(out.data());
}
/**
 * ------------------------------------------------------------------------------------------------
 * IO functions
 * ------------------------------------------------------------------------------------------------
 **/
Frame SLinuxResource::Read(size_t size) {
    IFrame f(size);
    /**
     * read 
     */
    while (!f.Full()) {
        f.Insert(__Read(f.data(), f.size()));
    }
    return f;
}
SLinuxResource& SLinuxResource::Drain(OFrame&& f) {
    while (!f.Empty()) {
        f.Remove(__Write(f.Data(), f.Size()));
    }
    return *this;
}
SLinuxResource& SLinuxResource::Drain(const Frame& f) {
    for (auto it = f.begin(), end = f.end(); it != end;) {
        it = next(it, __Write(it.base(), distance(it, end)));
    }
    return *this;
}
/**
 */
SLinuxResource& SLinuxResource::Flush() {
    ::fsync(__h);
    return *this;
}
/**
 * native IO functions
 */
size_t SLinuxResource::__Write(Frame::const_pointer p, Frame::size_type s) {
    auto n = ::write(__h, p, s);
    if (n <= 0) {
        if (n < 0) {
            *this = SLinuxResource();
            throw OResourceExceptionABORT(strerror(errno));
        }
        *this = SLinuxResource();
        throw OResourceExceptionABORT();
    }
    return n;
}
/**
 */
size_t SLinuxResource::__Read(Frame::pointer p, Frame::size_type s) {
    auto n = ::read(__h, p, s);
    if (n <= 0) {
        if (n < 0) {
            *this = SLinuxResource();
            throw IResourceExceptionABORT(strerror(errno));
        }
        *this = SLinuxResource();
        throw IResourceExceptionABORT();
    }
    return n;
}