/* 
 * Container:  SIOIrcConnector.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SIOIRCCONNECTORCODED_H
#define SIOIRCCONNECTORCODED_H
/**
 * C++ std
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
class SIOIrcConnector : public SInOutputConnector {
public:
	/**
	 * constructor
	 */
	SIOIrcConnector(const string address);
	/**
	 * destructor
	 */
	virtual ~SIOIrcConnector() = default;
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
	/**/
	void _write(const Document& container) override;
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
	/**
	 * container
	 */
	IDocument __container;
};
/**
 * End namespace Message
 */
}
/**
 * End namespace Encoded
 */
}
#endif /* SIOIRCCONNECTORCODED_H */

