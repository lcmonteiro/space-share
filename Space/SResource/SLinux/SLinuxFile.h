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
	SLinuxFile() = default;
	/**
	 * destructor
	 */
	virtual ~SLinuxFile() = default;
	/**
	 * get file size
	 */
	size_t Size(); 
	/**
	 * get position
	 */
	size_t Position(); 
	/**
	 * get base name
	 */
	static string Basename(const string& pathname){
		return {std::find_if(pathname.rbegin(), pathname.rend(),
			[](char c) {return c == '/'; }
		).base(), pathname.end()};
	}
protected:
	using SLinuxResource::SLinuxResource;
};

class SILinuxFile : public SLinuxFile {
public:
	/**
	 * constructors
	 */
	SILinuxFile() = default;

	SILinuxFile(const string& path);

	SILinuxFile(SILinuxFile&& res) : SILinuxFile() {
		SLinuxResource::operator=(move(res));
	}
	/**
	 * destructor
	 */
	virtual ~SILinuxFile() = default;
	/**
	 * swap
	 */
	inline SILinuxFile& operator=(SILinuxFile && res) {
		swap(__fd, res.__fd);
		return *this;
	}
	/**
	 * status
	 */
	bool Good();
	/**
	 */
protected:
	using SLinuxFile::SLinuxFile;
};

class SOLinuxFile : public SLinuxFile {
public:
	/**
	 * constructors
	 */
	SOLinuxFile() = default;

	SOLinuxFile(const string& path);

	SOLinuxFile(SOLinuxFile&& res) : SOLinuxFile() {
		SLinuxResource::operator=(move(res));
	}
	/**
	 * destructor
	 */
	virtual ~SOLinuxFile() = default;
	/**
	 * swap
	 */
	inline SOLinuxFile& operator=(SOLinuxFile && res) {
		swap(__fd, res.__fd);
		return *this;
	}
protected:
	using SLinuxFile::SLinuxFile;
};

#endif /* SLINUXFILE_H */

