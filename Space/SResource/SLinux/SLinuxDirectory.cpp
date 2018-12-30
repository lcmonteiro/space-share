/*
 * Container:   SLinuxDirectory.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 */
/*
 * linux
 */
#include <sys/inotify.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
/**
 */
#include "SLinuxDirectory.h"
/**
 */
SILinuxDirectory::SILinuxDirectory(const string& path) : SLinuxDirectory(path) {
	/**------------------------------------------------------------------------------------------------------------*
	 * open file watch
	 *-------------------------------------------------------------------------------------------------------------*/
	auto fd = ::inotify_init();
	if (fd < 0) {
		throw IResourceExceptionABORT(strerror(errno));
	}
	/**------------------------------------------------------------------------------------------------------------*
	 * register directory
	 *-------------------------------------------------------------------------------------------------------------*/
	if (::inotify_add_watch(fd, path.c_str(), IN_CLOSE_WRITE | IN_MOVED_TO) < 0) {
		throw IResourceExceptionABORT(strerror(errno));
	}
	/**------------------------------------------------------------------------------------------------------------*
	 * create resource
	 *-------------------------------------------------------------------------------------------------------------*/
	*this = SILinuxDirectory(fd);
	/*-------------------------------------------------------------------------------------------------------------*
	 * mark files
	 *-------------------------------------------------------------------------------------------------------------*/
	try {
		for (auto i = 0; true; ++i) {
			__mark(__path + "/" + to_string(i));
		}
	}catch(...){}
}
/**
 */
SILinuxFile SILinuxDirectory::resource() {
	char buf[sizeof (struct inotify_event) + 0x400] __attribute__((aligned(__alignof__(struct inotify_event))));
	/**
	 * read raw data
	 */
	int len = 0;
	for (int s = sizeof (struct inotify_event); (len <= 0) && (s < 0x400); s += sizeof (struct inotify_event)) {
		len = ::read(_Handler(), buf, sizeof (struct inotify_event) + s);
	}
	if (len <= 0) {
		throw IResourceExceptionABORT(strerror(errno));
	}
	/**
	 * map event on raw data
	 */
	auto event = (const struct inotify_event *) buf;
	/**
	 * verify and open file
	 */
	if ((event->mask & (IN_CLOSE_WRITE | IN_MOVED_TO)) && event->len) {
		return SILinuxFile(string(__path + "/" + event->name));
	}
	throw ResourceExceptionTIMEOUT();
}
/**
 */	
void SILinuxDirectory::__mark(string name){
	auto fd = ::open(name.data(), O_RDWR);
	if (fd < 0) {
		close(fd);
		throw IResourceExceptionABORT(strerror(errno));
	}
	char tmp[10];
	auto r = ::read(fd, tmp, sizeof(tmp));
	if (r < 0) {
		close(fd);
		throw IResourceExceptionABORT(strerror(errno));
	}
	::lseek(fd, 0, SEEK_SET);
	auto w = ::write(fd, tmp, r);
	if (w < 0) {
		::close(fd);
		throw IResourceExceptionABORT(strerror(errno));
	}
	::close(fd);
}
/**
 */
SOLinuxDirectory::SOLinuxDirectory(
	const string& path, size_t capacity
) : SLinuxDirectory(path), __capacity(capacity ? capacity : (capacity - 1)), __position(0) {
	/*-------------------------------------------------------------------------------------------------------------*
	 * create directory
	 *-------------------------------------------------------------------------------------------------------------*/
	::mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
	/**------------------------------------------------------------------------------------------------------------*
	 * create resource
	 *-------------------------------------------------------------------------------------------------------------*/
	*this = SOLinuxDirectory(::open(path.c_str(), O_RDONLY));
}
/**
 */
SOLinuxFile SOLinuxDirectory::resource() {
	return SOLinuxFile(__path + "/" + to_string(__position++ % __capacity));
}

SOLinuxFile SOLinuxDirectory::resource(const string& name) {
	return SOLinuxFile(__path + "/" + name);
}