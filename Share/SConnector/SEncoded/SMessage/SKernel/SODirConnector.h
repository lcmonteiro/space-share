/* 
 * Container:   SODirConnector.h
 * Author:      Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SODIRSTREAM_H
#define SODIRSTREAM_H
/**
 * Space Resource
 */
#include "SDirectoryResource.h"
/**
 * Space Kernel
 */
#include "SContainer.h"
/**
 * Share Kernel
 */
#include "SConnector.h"
/**
 * Begin namespace Encoded
 */
namespace Encoded {
/**
 * Begin namespace Message
 */
namespace Message {
/**
 */
class SODirConnector : public SOutputConnector {
public:
	/**
	 * constructor
	 */
	SODirConnector(const string address, const uint32_t nfiles);
	/**
	 * destructor
	 */
	virtual ~SODirConnector() = default;
	/**
	 */
protected:
	/**
	 * -----------------------------------------------------
	 * IO functions
	 * -----------------------------------------------------
	 * read
	 */
	void _Write(const Document& container) override;
	/**
	 * ----------------------------------------------------
	 * control functions
	 * ----------------------------------------------------
	 * open, good and close
	 */
	inline void _Open() override {
		__res = SODirectoryResource(__uri, __n);
	}
	inline bool _Good() override {
		return __res.Valid();
	}
	inline void _Close() override {
		__res = SODirectoryResource();
	}
private:
	/**
	 * resource 
	 */
	SODirectoryResource __res;	
	/**
	 */
	size_t __n;
};
/**
 * End namespace Message
 */
}
/**
 * End namespace Encoded
 */
}
#endif /* SODIRSTREAMCODED_H */

