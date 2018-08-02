/* 
 * Container:   SOIrcConnector.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SOIRCSTREAMCODED_H
#define SOIRCSTREAMCODED_H
/**
 * Space
 */
#include "SResource/SIRCResource.h"
//
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

