/* 
 * Container:  SIIrcConnector.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SIIRCCONNECTORCODED_H
#define SIIRCCONNECTORCODED_H
/**
 * c++ std
 */
#include <random>
/**
 * Space Resource
 */
#include "SIRCResource.h"
/**
 * Space Kernel
 */
#include "SContainer.h"
#include "SAddress.h"
#include "SChannel.h"
#include "STask.h"
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
class SIIrcConnector : public SInputConnector {
public:
	/**
	 * constructor
	 */
	SIIrcConnector(const string address);
	/**
	 * destructor
	 */
	virtual ~SIIrcConnector() = default;
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
	Document _Read() override;
	/**/
	list<Document> _Drain() override;
	/*-------------------------------------------------------------------------------------------------------------*
	 * control functions
	 *-------------------------------------------------------------------------------------------------------------*/
	void _Open() override;
	/**
	 * inline
	 */
	inline bool _Good() override{
		return __res.Good();
	}
	inline void _Close() override {
		__res = SIRCResource();
	}
private:
	/**
	 * resource 
	 */
	SIRCResource __res;
};
/**
 * End namespace Message
 */
}
/**
 * End namespace Encoded
 */
}
#endif /* SIIRCCONNECTORCODED_H */

