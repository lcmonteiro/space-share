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
	 * get size
	 */
	size_t size(); 
	/**
	 * get position
	 */
	size_t position(); 
	/**
	 * --------------------------------------------------------------------------------------------
	 * static functions
	 * --------------------------------------------------------------------------------------------
	 * get base name
	 */
	static string BaseName(const string& pathname){
		return {std::find_if(pathname.rbegin(), pathname.rend(),
			[](char c) {return c == '/'; }
		).base(), pathname.end()};
	}
	/**
 	 * get temporary dir
 	 */
	static string TmpPath();
	/**
	 * link file
	 */
	string Link(string from, string to);
};

class SILinuxFile : public SLinuxFile {
public:
	using SLinuxFile::SLinuxFile;
	using SLinuxFile::operator=;
	/**
	 * constructors
	 */
	SILinuxFile(const string& path);
	SILinuxFile(const string& path, const SLinuxFile& link);
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
	SOLinuxFile(const string& path, const SLinuxFile& link);
};

#endif /* SLINUXFILE_H */

