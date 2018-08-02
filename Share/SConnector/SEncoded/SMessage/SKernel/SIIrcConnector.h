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
 * Space
 */
#include "SResource/SIRCResource.h"
/**
 */
#include "SKernel/SContainer.h"
#include "SKernel/SAddress.h"
#include "SKernel/SChannel.h"
#include "SKernel/SConnector.h"
#include "SKernel/STask.h"
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
	Document _read() override;
	/**/
	list<Document> _drain() override;
	/*-------------------------------------------------------------------------------------------------------------*
	 * control functions
	 *-------------------------------------------------------------------------------------------------------------*/
	void _open() override;
	/**
	 * inline
	 */
	inline bool _good() override{
		return __res.Good();
	}
	inline void _close() override {
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

