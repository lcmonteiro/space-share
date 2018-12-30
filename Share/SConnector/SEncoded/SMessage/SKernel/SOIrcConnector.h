/* 
 * Container:   SOIrcConnector.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SOIRCSTREAMCODED_H
#define SOIRCSTREAMCODED_H
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
class SOIrcConnector : public SOutputConnector {
public:
	/**
	 * constructor
	 */
	SOIrcConnector(const string address);
	/**
	 * destructor
	 */
	virtual ~SOIrcConnector() = default;
	/**
	 */
protected:
	/*-------------------------------------------------------------------------------------------------------------*
	 * IO functions
	 *-------------------------------------------------------------------------------------------------------------*/
	void _Write(const Document& container) override;
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
#endif /* SOIRCSTREAMCODED_H */

