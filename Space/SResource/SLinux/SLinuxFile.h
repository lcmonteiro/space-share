/* 
 * Container:   SLinuxFile.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SLINUXFILE_H
#define SLINUXFILE_H
/**
 * std
 */
#include <sstream>
#include <algorithm>
/**
 * local
 */
#include "SLinuxResource.h"
/**
 */
class SLinuxFile : public SLinuxResource {
public:
	/**
	 * constructors
	 */
	using SLinuxResource::SLinuxResource;
	using SLinuxResource::operator=;
	/**
	 * get file size
	 */
	size_t Size(); 
	/**
	 * get position
	 */
	size_t Position(); 
	/**
	 * --------------------------------------------------------------------------------------------
	 * static functions
	 * --------------------------------------------------------------------------------------------
	 * get base name
	 */
	static string Basename(const string& pathname){
		return {std::find_if(pathname.rbegin(), pathname.rend(),
			[](char c) {return c == '/'; }
		).base(), pathname.end()};
	}
};

class SILinuxFile : public SLinuxFile {
public:
	using SLinuxFile::SLinuxFile;
	using SLinuxFile::operator=;
	/**
	 * constructors
	 */
	SILinuxFile(const string& path);
	/**
	 * status
	 */
	bool Good();
};

class SOLinuxFile : public SLinuxFile {
public:
	using SLinuxFile::SLinuxFile;
	using SLinuxFile::operator=;
	/**
	 * constructors
	 */
	SOLinuxFile(const string& path);
};

#endif /* SLINUXFILE_H */

