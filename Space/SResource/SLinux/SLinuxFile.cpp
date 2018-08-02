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
 */
#include "SLinuxFile.h"
/**
 * get file size
 */
size_t SLinuxFile::Size() {
	struct stat st;
	if (fstat(__fd, &st) < 0) {
		throw ResourceException(make_error_code(errc(errno)));
	}
	return st.st_size;
}
/**
 * get position
 */
size_t SLinuxFile::Position() {
	auto cur = lseek(__fd, 0, SEEK_CUR);
	if (cur < 0) {
		throw ResourceException(make_error_code(errc(errno)));
	}
	return size_t(cur);
}
/**
 */
SILinuxFile::SILinuxFile(const string& path) : SLinuxFile() {
	auto fd = open(path.data(), O_RDONLY);
	if (fd < 0) {
		throw ResourceException(make_error_code(errc(errno)));
	}
	/**/
	*this = SILinuxFile(fd);
}
/**
 * status
 */
bool SILinuxFile::Good(){
	auto cur = lseek(__fd, 0, SEEK_CUR);
	auto end = lseek(__fd, 0, SEEK_END);
	return end != lseek(__fd, cur, SEEK_SET);
}
/**
 */
SOLinuxFile::SOLinuxFile(const string& path) : SLinuxFile() {
	auto fd = open(path.data(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0) {
		throw ResourceException(make_error_code(errc(errno)));
	}
	/**/
	*this = SOLinuxFile(fd);
}