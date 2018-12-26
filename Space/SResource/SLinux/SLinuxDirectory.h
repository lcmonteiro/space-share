/* 
 * Container:   SLinuxDirectory.h
 * Author:      Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SLINUXDIRECTORY_H
#define SLINUXDIRECTORY_H
/**
 * std
 */
#include <sstream>
/**
 * local
 */
#include "SLinuxFile.h"
/**
 */
class SLinuxDirectory : public SLinuxResource {
public:
	/**
	 * constructors
	 */
	SLinuxDirectory() = default;
	
	SLinuxDirectory(const string& path) : SLinuxResource(), __path(path) {
	} 
	/**
	 * destructor
	 */
	virtual ~SLinuxDirectory() = default;
	/**
	 * move operator(swap)
	 */
	SLinuxDirectory& operator=(SLinuxDirectory && res) = default;
protected:
	using SLinuxResource::SLinuxResource;
	/**
	 */
	string __path;
};
/**
 */
class SILinuxDirectory : public SLinuxDirectory {
public:
	/**
	 * constructors
	 */
	SILinuxDirectory() = default;

	SILinuxDirectory(const string& path);

	SILinuxDirectory(SILinuxDirectory&& res) = default;
	/**
	 * destructor
	 */
	virtual ~SILinuxDirectory() = default;
	/**
	 * move operator(swap)
	 */
	SILinuxDirectory& operator=(SILinuxDirectory && res) = default;
	/**
	 * get resource
	 */
	SILinuxFile getResource();
protected:
	using SLinuxDirectory::SLinuxDirectory;
private:
	/**
	 * mark file to receive on inotify
	 */
	void __mark(string name);
};
/**
 */
class SOLinuxDirectory : public SLinuxDirectory {
public:
	/**
	 * constructors
	 */
	SOLinuxDirectory() = default;

	SOLinuxDirectory(const string& path, size_t capacity = 0);

	SOLinuxDirectory(SOLinuxDirectory&& res) = default;
	/**
	 * destructor
	 */
	virtual ~SOLinuxDirectory() = default;
	/**
	 * swap
	 */
	SOLinuxDirectory& operator=(SOLinuxDirectory && res) = default;
	/**
	 * get resource
	 */
	SOLinuxFile getResource();
	SOLinuxFile getResource(const string& name);
protected:
	using SLinuxDirectory::SLinuxDirectory;
	/**
	 * settings
	 */
	size_t __capacity;
	/**
	 * context
	 */
	size_t __position;
};

#endif /* SLINUXDIRECTORY_H */

