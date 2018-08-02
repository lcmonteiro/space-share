/* 
 * Container:  SIDirConnector.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SIDIRCONNECTORCODED_H
#define SIDIRCONNECTORCODED_H
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
class SIDirConnector : public SInputConnector {
public:
	/**
	 * constructor
	 */
	SIDirConnector(const string address);
	/**
	 * destructor
	 */
	virtual ~SIDirConnector() = default;
	/**
	 * inline overrides
	 */
	inline Resource& GetResource() override {
		return __res;
	}
protected:
	/*-------------------------------------------------------------------------------------------------------------*
	 * IO functions
	 *-------------------------------------------------------------------------------------------------------------*/
	Document _read() override;
	/**/
	list<Document> _drain() override;
	/*-------------------------------------------------------------------------------------------------------------*
	 * control functions
	 *-------------------------------------------------------------------------------------------------------------*/
	inline void _open() override {
		__res = SIDirectoryResource(__uri);
	}
	inline bool _good() override {
		return __res.Valid();
	}
	inline void _close() override {
		__res = SIDirectoryResource();
	}
private:
	/**
	 * resource 
	 */
	SIDirectoryResource __res;
	/**
	 * properties
	 */
	string __file;
};
/**
 * End namespace Message
 */
}
/**
 * End namespace Encoded
 */
}
#endif /* SIDIRCONNECTORCODED_H */

