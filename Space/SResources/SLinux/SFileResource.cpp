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
#include "SResourceMediator.h"
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
bool SFileResource::Good() const {
	return SResourceMediator::IsFile(
        GetHandler<SResourceHandler>()->FD());
}
/**
 * ----------------------------------------------------------------------------
 * get file size
 * ----------------------------------------------------------------------------
 */
size_t SFileResource::Size() {
    return SResourceMediator::Length(
        GetHandler<SResourceHandler>()->FD());
}
/**
 * ----------------------------------------------------------------------------
 * get position
 * ----------------------------------------------------------------------------
 */
size_t SFileResource::Position() {
    auto cur = ::lseek(GetHandler<SResourceHandler>()->FD(), 0, SEEK_CUR);
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
SText SFileResource::Path() const {
	return SResourceMediator::Path(
        GetHandler<SResourceHandler>()->FD());
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
SFileResource& SFileResource::Fill(IOFrame& f) {
    while (!f.Full()) {
        f.Insert(SResourceMediator::Read(
            GetHandler<SResourceHandler>()->FD(), f.IData(), f.ISize()
        ));
    }
    return *this;
}
template<>
SFileResource& SFileResource::Fill(Frame& f) {
    for (auto it = f.begin(), end = f.end(); it != end;) {
        it = next(it, SResourceMediator::Read(
            GetHandler<SResourceHandler>()->FD(), it.base(), distance(it, end)
        ));
    }
    return *this;
}
/**
 * read
 */
template<>
SFileResource& SFileResource::Read(IOFrame& f) {
    f.Insert(SResourceMediator::Read(
        GetHandler<SResourceHandler>()->FD(), f.IData(), f.ISize())
    );
    return *this;
}
template<>
SFileResource& SFileResource::Read(Frame& f) {
    f.Insert(SResourceMediator::Read(
        GetHandler<SResourceHandler>()->FD(), f.Data(), f.Size())
    );
    return *this;
}
/**
 * ----------------------------------------------------------------------------
 * Output
 * ----------------------------------------------------------------------------
 * drain
 */
template<typename T>
SFileResource& SFileResource::Drain(T& f) {
    // send loop ----------------------
    while (!f.Empty()) {
        f.Remove(SResourceMediator::Write(
            GetHandler<SResourceHandler>()->FD(), f.Data(), f.Size()
        ));
    }
    return *this;
}
template<typename T>
SFileResource& SFileResource::Drain(const T& f) {
    // send loop ----------------------
    for (auto it = f.begin(), end = f.end(); it != end;) {
        it = next(it, SResourceMediator::Write(
            GetHandler<SResourceHandler>()->FD(), it.base(), distance(it, end)
        ));
    }
    return *this;
}
template SFileResource& SFileResource::Drain(Frame&);
template SFileResource& SFileResource::Drain(IOFrame&);
template SFileResource& SFileResource::Drain(const Frame&);
template SFileResource& SFileResource::Drain(const IOFrame&);
/**
 * write
 */
template<typename T>
SFileResource& SFileResource::Write(T& f) {
    f.Remove(
        SResourceMediator::Write(GetHandler<SResourceHandler>()->FD(), f.Data(), f.Size())
    );
    return *this;
}
template<typename T>
SFileResource& SFileResource::Write(const T& f) {
    SResourceMediator::Write(GetHandler<SResourceHandler>()->FD(), f.Data(), f.Size());
    return *this;
}
template SFileResource& SFileResource::Write(Frame&);
template SFileResource& SFileResource::Write(IOFrame&);
template SFileResource& SFileResource::Write(const Frame&);
template SFileResource& SFileResource::Write(const IOFrame&);

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
string SFileResource::TmpPath() {
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
    SetHandler(make_shared<SResourceHandler>(
        ::open(path.data(), O_RDONLY)
    ));
}
SIFileResource::SIFileResource(const string& path, const SFileResource& link) 
: SIFileResource(
    Link(path, link.Path())
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
    SetHandler(make_shared<SResourceHandler>(
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
 * End
 * ------------------------------------------------------------------------------------------------
 */ 