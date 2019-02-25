/**
 * ------------------------------------------------------------------------------------------------
 * File:   SDirectoryResource.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 * ------------------------------------------------------------------------------------------------
 **
 * linux
 */
#include <sys/inotify.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
/**
 * space linux
 */
#include "SResourceHandler.h"
/**
 * Space
 */
#include "SDirectoryResource.h"
#include "SText.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Helpers
 * ------------------------------------------------------------------------------------------------
 */
static bool __mark(const SText& name) {
	auto fd = ::open(name.data(), O_RDWR);
	if (fd < 0) {
		close(fd);
		return false;
	}
	char tmp[10];
	auto r = ::read(fd, tmp, sizeof(tmp));
	if (r < 0) {
		close(fd);
		return false;
	}
	::lseek(fd, 0, SEEK_SET);
	auto w = ::write(fd, tmp, r);
	if (w < 0) {
		::close(fd);
		return false;
	}
	::close(fd);
	return true;
}
/**
 * ------------------------------------------------------------------------------------------------
 * Base
 * ------------------------------------------------------------------------------------------------
 **
 * status
 */
bool SDirectoryResource::Valid() {
    return ::fcntl(GetHandler<SResourceHandler>()->FD(), F_GETFL) != -1 || errno != EBADF;
}
/**
 * ------------------------------------------------------------------------------------------------
 * Input DirectoryResource
 * ------------------------------------------------------------------------------------------------
 */
SIDirectoryResource::SIDirectoryResource(const std::string& path) : SDirectoryResource(path) {
	/**
	 * open file watch
	 */
	auto fd = ::inotify_init();
	if (fd < 0) {
		throw IResourceExceptionABORT(::strerror(errno));
	}
	/**
	 * register directory
	 */
	if (::inotify_add_watch(fd, path.data(), IN_CLOSE_WRITE | IN_MOVED_TO) < 0) {
		throw IResourceExceptionABORT(::strerror(errno));
	}
	/**
	 * create resource
	 */
	SetHandler(std::make_shared<SResourceHandler>(fd));
	/**
	 * mark files
	 */
	for (auto i = 0; __mark(SText(__path, "/", i)); ++i);
}
/**
 */
SIFileResource SIDirectoryResource::GetResource() {
	char buf[sizeof (struct inotify_event) + 0x400] __attribute__((aligned(__alignof__(struct inotify_event))));
	/**
	 * read raw data
	 */
	int len = 0;
	for (int s = sizeof(struct inotify_event); (len <= 0) && (s < 0x400); s += sizeof(struct inotify_event)) {
		len = ::read(
			GetHandler<SResourceHandler>()->FD(), buf, sizeof (struct inotify_event) + s
		);
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
		return SIFileResource(SText(__path, "/", event->name));
	}
	throw ResourceExceptionTIMEOUT();
}	
/**
 * ------------------------------------------------------------------------------------------------
 * Output DirectoryResource
 * ------------------------------------------------------------------------------------------------
 */
SODirectoryResource::SODirectoryResource(
	const std::string& path, size_t capacity
) : SDirectoryResource(path), __capacity(capacity ? capacity : (capacity - 1)), __position(0) {
	/**
	 * create directory
	 */
	::mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
	/**
	 * create resource
	 */
	SetHandler(std::make_shared<SResourceHandler>(
        ::open(path.data(), O_RDONLY)
    ));
}
/**
 * ----------------------------------------------------------------------------
 * get resources
 * ----------------------------------------------------------------------------
 */
SOFileResource SODirectoryResource::GetResource() {
	return SOFileResource(SText(__path, "/", __position++ % __capacity));
}
SOFileResource SODirectoryResource::GetResource(const std::string& name) {
	return SOFileResource(SText(__path, "/", name));
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */