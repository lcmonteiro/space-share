/* 
 * Container:  SIDirConnector.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SIDIRCONNECTORCODED_H
#define SIDIRCONNECTORCODED_H
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
 * ------------------------------------------------------------------------------------------------
 * IDirConnector
 * ------------------------------------------------------------------------------------------------
 */
class SIDirConnector : public SInputConnector {
public:
	/**
	 * constructor
	 */
	SIDirConnector(const SText address);
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
	/**
	 * -----------------------------------------------------
	 * IO functions
	 * -----------------------------------------------------
	 * read
	 */
	Document _Read() override;
	/**
	 * drain
	 */
	std::list<Document> _Drain() override;
	/**
	 * ----------------------------------------------------
	 * control functions
	 * ----------------------------------------------------
	 * open, good and close
	 */
	inline void _Open() override {
		__res = SIDirectoryResource(__uri);
	}
	inline bool _Good() override {
		return __res.Valid();
	}
	inline void _Close() override {
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
	std::string __file;
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

