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
 * swap names
 */
#include <iostream>
void SLinuxFile::swap(SLinuxFile& file) {
	auto p1 = path();
	auto p2 = file.path();

	if (unlink(p1.c_str()) < 0) {
	 	throw ResourceException(make_error_code(errc(errno)));
	}
	cout << getpid() << " " << _handler_path() << p1 << endl;
	// if (unlink(p2.c_str()) < 0) {
	//  	throw ResourceException(make_error_code(errc(errno)));
	// }
	if (linkat(AT_FDCWD, _handler_path().c_str(), AT_FDCWD, p1.c_str(), AT_SYMLINK_FOLLOW) < 0) {
		throw ResourceException(make_error_code(errc(errno)), _handler_path() + p1);
	}


	// auto p = path();
	// if (unlink(p.c_str()) < 0) {
	// 	throw ResourceException(make_error_code(errc(errno)));
	// }
	// ostringstream os;
	// os << "/proc/self/fd/" << _handler();
	// if (link(p.c_str(), "/tmp/test1232") < 0) {
	// 	throw ResourceException(make_error_code(errc(errno)));
	// }
	// if(symlink ("/tmp/test1232", os.str().c_str()) < 0) {
	// 	throw ResourceException(make_error_code(errc(errno)));
	// }
	// // template
	// auto t = tmpdir() + "/swap-XXXXXX";
	// // data
	// vector<char> tmp(p1.begin(), p1.end());
	// tmp.resize(PATH_MAX);
	// // lock
	// auto h = mkstemp(tmp.data());

	// auto p1 = string("/tmp/test1232");

	// auto p2 = this->path();
	// auto p3 = file.path();
	// for(auto& a : vector<pair<const string&, const string&>>{
	// 	{p2, p1}, {p3, p2}, {p1, p3}
	// }) {
	// 	if (link(a.first.c_str(), a.second.c_str()) < 0) {
	// 		throw ResourceException(make_error_code(errc(errno)));
	// 	}
	// 	if (unlink(a.first.c_str()) < 0) {
	// 		throw ResourceException(make_error_code(errc(errno)));
	// 	}
	// }

	// dup2(_handler(), file._handler());

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
/**
 * status
 */
bool SILinuxFile::Good(){
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