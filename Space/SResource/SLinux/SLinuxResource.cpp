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
 */
#include "SMonitor/SLinux/SLinuxResourceMonitor.h"
/**
 */
#include "SLinuxResource.h"
/**
 * constructor
 */
SLinuxResource::SLinuxResource(int fd) : __fd(fd) {
	if (__fd < 0) {
		throw system_error(make_error_code(errc::no_such_file_or_directory));
	}
}
/**
 * destructor
 */
SLinuxResource::~SLinuxResource() {
	if (__fd > 0) {
		close(__fd);
	}
}
/**
 * check resource
 */
bool SLinuxResource::Valid() {
	return fcntl(__fd, F_GETFL) != -1 || errno != EBADF;
}
/*---------------------------------------------------------------------------------------------------------------------*
 * IO functions
 *---------------------------------------------------------------------------------------------------------------------*/
Frame SLinuxResource::Read(size_t size) {
	IFrame f(size);
	/**
	 * read 
	 */
	while (!f.Full()) {
		f.Insert(Read(f.data(), f.size()));
	}
	return f;
}
SLinuxResource& SLinuxResource::Drain(OFrame&& f) {
	while (!f.Empty()) {
		f.Remove(Write(f.Data(), f.Size()));
	}
	return *this;
}
SLinuxResource& SLinuxResource::Drain(const Frame& f) {
	for (auto it = f.begin(), end = f.end(); it != end;) {
		it = next(it, Write(it.base(), distance(it, end)));
	}
	return *this;
}
/**
 */
SLinuxResource& SLinuxResource::Flush(){
	fsync(__fd);
	return *this;
}
/**
 * native IO functions
 */
size_t SLinuxResource::Write(Frame::const_pointer p, Frame::size_type s){
	auto n = write(__fd, p, s);
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
size_t SLinuxResource::Read(Frame::pointer p, Frame::size_type s){
	auto n = read(__fd, p, s);
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