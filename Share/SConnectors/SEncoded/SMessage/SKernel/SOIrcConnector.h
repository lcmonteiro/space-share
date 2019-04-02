/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SOIrcConnector.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SOIRCSTREAMCODED_H
#define SOIRCSTREAMCODED_H
/**
 * Space
 */
#include "SIRCResource.h"
#include "SContainer.h"
#include "SAddress.h"
#include "SChannel.h"
#include "STask.h"
/**
 * Share
 */
#include "SConnector.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Begin namespace Encoded & Message
 * ------------------------------------------------------------------------------------------------
 */
namespace Encoded {
namespace Message {
/**
 * ------------------------------------------------------------------------------------------------
 * OIrcConnector
 * ------------------------------------------------------------------------------------------------
 */
class SOIrcConnector : public SOutputConnector {
public:
	/**
	 * constructor
	 */
	SOIrcConnector(const std::string address);
	/**
	 * destructor
	 */
	virtual ~SOIrcConnector() = default;
	/**
	 */
protected:
	/**
	 * -----------------------------------------------------
	 * IO functions
	 * -----------------------------------------------------
	 * write
	 */
	void _Write(const Document& container) override;
	/**
	 * ----------------------------------------------------
	 * control functions
	 * ----------------------------------------------------
	 * open, good and close
	 */
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
}}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Encoded & Message
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SOIRCSTREAMCODED_H */

