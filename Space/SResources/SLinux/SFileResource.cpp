/**
 * ------------------------------------------------------------------------------------------------
 * File:   SFileResource.cpp
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
#include "SNativeResource.h"
/**
 * space
 */
#include "SFileResource.h"
#include "SFrame.h"
/**
 * namespaces 
 */
using namespace std;
/**
 * ------------------------------------------------------------------------------------------------
 * Base
 * ------------------------------------------------------------------------------------------------
 * check resource
 * ----------------------------------------------------------------------------
 */
bool SFileResource::good() const {
	return SNativeResource::IsFile(
        handler<SResourceHandler>()->fd());
}
/**
 * ----------------------------------------------------------------------------
 * get file size
 * ----------------------------------------------------------------------------
 */
size_t SFileResource::size() {
    return SNativeResource::Size(
        handler<SResourceHandler>()->fd());
}
/**
 * ----------------------------------------------------------------------------
 * get position
 * ----------------------------------------------------------------------------
 */
size_t SFileResource::position() {
    auto cur = ::lseek(handler<SResourceHandler>()->fd(), 0, SEEK_CUR);
    if (cur < 0) {
        throw ResourceException(make_error_code(errc(errno)));
    }
    return size_t(cur);
}
/**
 * ----------------------------------------------------------------------------
 * get file path
 * ----------------------------------------------------------------------------
 */
SText SFileResource::path() const {
	return SNativeResource::Path(
        handler<SResourceHandler>()->fd());
}
/**
 * ----------------------------------------------------------------------------
 * get base name
 * ----------------------------------------------------------------------------
 */
string SFileResource::BaseName(const string& path) {
    return {find_if(path.rbegin(), path.rend(),
        [](char c) {return c == '/'; }
    ).base(), path.end()};
}
/**
 * ------------------------------------------------------------------------------------------------
 * IO functions
 * ------------------------------------------------------------------------------------------------
 * Input
 * ----------------------------------------------------------------------------
 * fill
 */
template<>
SFileResource& SFileResource::fill(IOFrame& f) {
    while (!f.full()) {
        f.insert(SNativeResource::Read(
            handler<SResourceHandler>()->fd(), f.idata(), f.isize()));
    }
    return *this;
}
template<>
SFileResource& SFileResource::fill(Frame& f) {
    for (auto it = f.begin(), end = f.end(); it != end;) {
        it = next(it, SNativeResource::Read(
            handler<SResourceHandler>()->fd(), it.base(), distance(it, end)));
    }
    return *this;
}
/**
 * read
 */
template<>
SFileResource& SFileResource::read(IOFrame& f) {
    f.insert(SNativeResource::Read(
        handler<SResourceHandler>()->fd(), f.idata(), f.isize()));
    return *this;
}
template<>
SFileResource& SFileResource::read(Frame& f) {
    f.insert(SNativeResource::Read(
        handler<SResourceHandler>()->fd(), f.data(), f.size()));
    return *this;
}
/**
 * ----------------------------------------------------------------------------
 * Output
 * ----------------------------------------------------------------------------
 * drain
 */
template<typename T>
SFileResource& SFileResource::drain(T& f) {
    while (!f.empty()) {
        f.remove(SNativeResource::Write(
            handler<SResourceHandler>()->fd(), f.data(), f.size()));
    }
    return *this;
}
template<typename T>
SFileResource& SFileResource::drain(const T& f) {
    for (auto it = f.begin(), end = f.end(); it != end;) {
        it = next(it, SNativeResource::Write(
            handler<SResourceHandler>()->fd(), it.base(), distance(it, end)));
    }
    return *this;
}
template SFileResource& SFileResource::drain(Frame&);
template SFileResource& SFileResource::drain(IOFrame&);
template SFileResource& SFileResource::drain(const Frame&);
template SFileResource& SFileResource::drain(const IOFrame&);
/**
 * write
 */
template<typename T>
SFileResource& SFileResource::write(T& f) {
    f.remove(
        SNativeResource::Write(handler<SResourceHandler>()->fd(), f.data(), f.size())
    );
    return *this;
}
template<typename T>
SFileResource& SFileResource::write(const T& f) {
    SNativeResource::Write(handler<SResourceHandler>()->fd(), f.data(), f.size());
    return *this;
}
template SFileResource& SFileResource::write(Frame&);
template SFileResource& SFileResource::write(IOFrame&);
template SFileResource& SFileResource::write(const Frame&);
template SFileResource& SFileResource::write(const IOFrame&);
/**
 * ----------------------------------------------------------------------------
 * Flush
 * ----------------------------------------------------------------------------
 */
SFileResource& SFileResource::flush() {
    ::fsync(handler<SResourceHandler>()->fd());
    return *this;
}
/**
 * ----------------------------------------------------------------------------
 * link file
 * ----------------------------------------------------------------------------
 */
const string& SFileResource::Link(const string& from, const string& to) {
    ::unlink(from.c_str());
    if (::link(to.c_str(), from.c_str()) < 0) {
         throw ResourceException(make_error_code(errc(errno)));
    }
    return from;
}
/**
 * ----------------------------------------------------------------------------
 * get temporary directory
 * ----------------------------------------------------------------------------
 */
string SFileResource::PathTemp() {
#ifdef __ANDROID__
    const char* default_tmp = "/data/local/tmp";
#else
    const char* default_tmp = "/tmp";
#endif
    const char* ptr = 0;
    (ptr = getenv("TMPDIR" )) ||
    (ptr = getenv("TMP"    )) ||
    (ptr = getenv("TEMP"   )) ||
    (ptr = getenv("TEMPDIR")) ||
    (ptr = default_tmp);
    return string(ptr);
}
/**
 * ------------------------------------------------------------------------------------------------
 * Input FileResource
 * ------------------------------------------------------------------------------------------------
 * create IFileResource
 * ----------------------------------------------------------------------------
 */
SIFileResource::SIFileResource(const string& path) 
: SFileResource() {
    handler(make_shared<SResourceHandler>(
        ::open(path.data(), O_RDONLY)
    ));
}
SIFileResource::SIFileResource(const string& path, const SFileResource& link) 
: SIFileResource(
    Link(path, link.path())
) {}
/**
 * ------------------------------------------------------------------------------------------------
 * Output FileResource
 * ------------------------------------------------------------------------------------------------
 * create OFileResource
 * ----------------------------------------------------------------------------
 */
SOFileResource::SOFileResource(const string& path) 
: SFileResource() {
    handler(make_shared<SResourceHandler>(
        ::open(
            path.data(), 
            O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
        )
    ));
}
SOFileResource::SOFileResource(const string& path, const SFileResource& link) 
: SOFileResource(
    Link(path, link.path())
) {}
/**
 * ------------------------------------------------------------------------------------------------
 * End
 * ------------------------------------------------------------------------------------------------
 */ 