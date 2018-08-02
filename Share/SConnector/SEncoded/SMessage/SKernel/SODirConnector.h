/* 
 * Container:   SODirConnector.h
 * Author:      Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SODIRSTREAM_H
#define SODIRSTREAM_H
/**
 * Space
 */
#include "SResource/SDirectoryResource.h"
/**
 */
#include "SKernel/SContainer.h"
#include "SKernel/SConnector.h"
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
	/*-------------------------------------------------------------------------------------------------------------*
	 * IO functions
	 *-------------------------------------------------------------------------------------------------------------*/
	void _write(const Document& container) override;
	/*-------------------------------------------------------------------------------------------------------------*
	 * control functions
	 *-------------------------------------------------------------------------------------------------------------*/
	inline void _open() override {
		__res = SODirectoryResource(__uri, __n);
	}
	inline bool _good() override {
		return __res.Valid();
	}
	inline void _close() override {
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

