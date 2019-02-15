/**
 * ------------------------------------------------------------------------------------------------
 * Container:   SFileResource.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 * ------------------------------------------------------------------------------------------------
 **
 * linux
 */
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/stat.h>
/**
 * std
 */
#include <vector>
#include <algorithm>
/**
 * space linux
 */
#include "SResourceHandler.h"
/**
 * space
 */
#include "SFileResource.h"
#include "SFrame.h"
/**
 * ------------------------------------------------------------------------------------------------
 * linux interface
 * ------------------------------------------------------------------------------------------------
 */
static size_t __Write(int fd, Frame::const_pointer p, Frame::size_type s);
static size_t __Read (int fd, Frame::pointer       p, Frame::size_type s);
static SText  __Path (int fd);
/**
 * ------------------------------------------------------------------------------------------------
 * Base
 * ------------------------------------------------------------------------------------------------
 * get file size
 * ----------------------------------------------------------------------------
 */
size_t SFileResource::Size() {
    struct stat st;
    if (::fstat(GetHandler<SResourceHandler>()->FD(), &st) < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
    return st.st_size;
}
/**
 * ----------------------------------------------------------------------------
 * get position
 * ----------------------------------------------------------------------------
 */
size_t SFileResource::Position() {
    auto cur = ::lseek(GetHandler<SResourceHandler>()->FD(), 0, SEEK_CUR);
    if (cur < 0) {
        throw ResourceException(std::make_error_code(std::errc(errno)));
    }
    return size_t(cur);
}
/**
 * get file path
 */
SText SFileResource::Path() const {
	std::vector<char> out;
	//read real path
	int len = 0;
	do {
		out.resize(out.size() + 0x100);
		if((len = ::readlink(__Path(
            GetHandler<SResourceHandler>()->FD()
        ).data(), out.data(), out.size())) < 0) {
			throw ResourceException(std::make_error_code(std::errc(errno)));	
		}
	} while(out.size()==len);
	// return path as string
	return SText(out.data());
}
/**
 * ----------------------------------------------------------------------------
 * get base name
 * ----------------------------------------------------------------------------
 */
std::string SFileResource::BaseName(const std::string& path) {
    return {std::find_if(path.rbegin(), path.rend(),
        [](char c) {return c == '/'; }
    ).base(), path.end()};
}
/**
 * ------------------------------------------------------------------------------------------------
 * IO functions
 * ------------------------------------------------------------------------------------------------
 * fill and read frame
 * ----------------------------------------------------------------------------
 */
template<>
SFileResource& SFileResource::Read(IFrame& f) {
    while (!f.Full()) {
        f.Insert(__Read(
            GetHandler<SResourceHandler>()->FD(), f.data(), f.size()
        ));
    }
    return *this;
}
/**
 * ----------------------------------------------------------------------------
 * drain and write frame
 * ----------------------------------------------------------------------------
 */
template<>
SFileResource& SFileResource::Drain(OFrame& f) {
    while (!f.Empty()) {
        f.Remove(__Write(
            GetHandler<SResourceHandler>()->FD(), f.Data(), f.Size()
        ));
    }
    return *this;
}
template<>
SFileResource& SFileResource::Drain(const Frame& f) {
    for (auto it = f.begin(), end = f.end(); it != end;) {
        it = std::next(it, __Write(
            GetHandler<SResourceHandler>()->FD(), it.base(), std::distance(it, end)
        ));
    }
    return *this;
}
/**
 * ----------------------------------------------------------------------------
 * flush
 * ----------------------------------------------------------------------------
 */
SFileResource& SFileResource::Flush() {
    ::fsync(GetHandler<SResourceHandler>()->FD());
    return *this;
}
/**
 * ----------------------------------------------------------------------------
 * link file
 * ----------------------------------------------------------------------------
 */
const std::string& SFileResource::Link(const std::string& from, const std::string& to) {
    ::unlink(from.c_str());
    if (::link(to.c_str(), from.c_str()) < 0) {
         throw ResourceException(std::make_error_code(std::errc(errno)));
    }
    return from;
}
/**
 * ----------------------------------------------------------------------------
 * get temporary directory
 * ----------------------------------------------------------------------------
 */
string SFileResource::TmpPath() {
#ifdef __ANDROID__
    const char* default_tmp = "/data/local/tmp";
#else
    const char* default_tmp = "/tmp";
#endif
    const char* ptr = 0;
    (ptr = std::getenv("TMPDIR" )) ||
    (ptr = std::getenv("TMP"    )) ||
    (ptr = std::getenv("TEMP"   )) ||
    (ptr = std::getenv("TEMPDIR")) ||
    (ptr = default_tmp);
    return std::string(ptr);
}
/**
 * ------------------------------------------------------------------------------------------------
 * Input FileResource
 * ------------------------------------------------------------------------------------------------
 * create IFileResource
 * ----------------------------------------------------------------------------
 */
SIFileResource::SIFileResource(const std::string& path) 
: SFileResource() {
    SetHandler(std::make_shared<SResourceHandler>(
        ::open(path.data(), O_RDONLY)
    ));
}
SIFileResource::SIFileResource(const std::string& path, const SFileResource& link) 
: SIFileResource(
    Link(path, link.Path())
) {}
/**
 * ----------------------------------------------------------------------------
 * status
 * ----------------------------------------------------------------------------
 */
bool SIFileResource::Good() {
    auto cur = ::lseek(GetHandler<SResourceHandler>()->FD(), 0, SEEK_CUR);
    auto end = ::lseek(GetHandler<SResourceHandler>()->FD(), 0, SEEK_END);
    return ::lseek(GetHandler<SResourceHandler>()->FD(), cur, SEEK_SET) != end;
}
/**
 * ------------------------------------------------------------------------------------------------
 * Output FileResource
 * ------------------------------------------------------------------------------------------------
 * create OFileResource
 * ----------------------------------------------------------------------------
 */
SOFileResource::SOFileResource(const string& path) 
: SFileResource() {
    SetHandler(std::make_shared<SResourceHandler>(
        ::open(
            path.data(), 
            O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
        )
    ));
}
SOFileResource::SOFileResource(const string& path, const SFileResource& link) 
: SOFileResource(
    Link(path, link.Path())
) {}


/**
 * ------------------------------------------------------------------------------------------------
 * linux functions
 * ------------------------------------------------------------------------------------------------
 */
size_t __Write(int fd, Frame::const_pointer p, Frame::size_type s) {
    auto n = ::write(fd, p, s);
    if (n <= 0) {
        if (n < 0) {
            throw OResourceExceptionABORT(strerror(errno));
        }
        throw OResourceExceptionABORT();
    }
    return n;
}
/**
 */
size_t __Read(int fd, Frame::pointer p, Frame::size_type s) {
    auto n = ::read(fd, p, s);
    if (n <= 0) {
        if (n < 0) {
            throw IResourceExceptionABORT(strerror(errno));
        }
        throw IResourceExceptionABORT();
    }
    return n;
}
/**
 */
SText __Path(int fd) {
    std::ostringstream os;
    os << "/proc/self/fd/" << fd;
    return os.str();
}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */ 