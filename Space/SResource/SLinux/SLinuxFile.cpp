/*
 * Container:   SLinuxFile.cpp
 * Author: Luis Monteiro
 *
 * Created on June 3, 2015, 10:12 AM
 */
/*
 * linux
 */
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
/**
 * std
 */
#include <vector>
/**
 */
#include "SLinuxFile.h"
/**
 * get file path
 */
string SLinuxFile::path() {
	vector<char> out;
	// build internal path
	ostringstream os;
	os << "/proc/self/fd/" << handler();
	//read real path
	int len = 0;
	do {
		out.resize(out.size() + 0x100);
		if((len = readlink(os.str().data(), out.data(), out.size())) < 0) {
			throw ResourceException(make_error_code(errc(errno)));	
		}
	} while(out.size()==len);
	// return path as string
	return string(out.data());
}
/**
 * get file size
 */
size_t SLinuxFile::size() {
	struct stat st;
	if (fstat(handler(), &st) < 0) {
		throw ResourceException(make_error_code(errc(errno)));
	}
	return st.st_size;
}
/**
 * get position
 */
size_t SLinuxFile::position() {
	auto cur = lseek(handler(), 0, SEEK_CUR);
	if (cur < 0) {
		throw ResourceException(make_error_code(errc(errno)));
	}
	return size_t(cur);
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
	auto cur = lseek(handler(), 0, SEEK_CUR);
	auto end = lseek(handler(), 0, SEEK_END);
	return end != lseek(handler(), cur, SEEK_SET);
}
/**
 * create OLinuxFile
 */
SOLinuxFile::SOLinuxFile(const string& path) 
: SLinuxFile(
	open(path.data(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
) {}