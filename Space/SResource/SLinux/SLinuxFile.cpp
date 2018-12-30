/*
 * Container:   SLinuxFile.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
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
/**
 * space
 */
#include "SLinuxFile.h"
/**
 * get file size
 */
size_t SLinuxFile::size() {
	struct stat st;
	if (fstat(_handler(), &st) < 0) {
		throw ResourceException(make_error_code(errc(errno)));
	}
	return st.st_size;
}
/**
 * get position
 */
size_t SLinuxFile::position() {
	auto cur = lseek(_handler(), 0, SEEK_CUR);
	if (cur < 0) {
		throw ResourceException(make_error_code(errc(errno)));
	}
	return size_t(cur);
}
/**
 * link file
 */
string SLinuxFile::Link(string from, string to) {
	unlink(from.c_str());
	if (link(to.c_str(), from.c_str()) < 0) {
	 	throw ResourceException(make_error_code(errc(errno)));
	}
	return from;
}
/**
 * get temporary directory
 */
string SLinuxFile::TmpPath() {
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
    return string(ptr);
}
/**
 * create ILinuxFile
 */
SILinuxFile::SILinuxFile(const string& path) 
: SLinuxFile(
	open(path.data(), O_RDONLY)
) {}
SILinuxFile::SILinuxFile(const string& path, const SLinuxFile& link) 
: SILinuxFile(
	Link(path, link.path())
) {}
/**
 * status
 */
bool SILinuxFile::good() {
	auto cur = lseek(_handler(), 0, SEEK_CUR);
	auto end = lseek(_handler(), 0, SEEK_END);
	return end != lseek(_handler(), cur, SEEK_SET);
}
/**
 * create OLinuxFile
 */
SOLinuxFile::SOLinuxFile(const string& path) 
: SLinuxFile(
	open(path.data(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
) {}
SOLinuxFile::SOLinuxFile(const string& path, const SLinuxFile& link) 
: SOLinuxFile(
	Link(path, link.path())
) {}