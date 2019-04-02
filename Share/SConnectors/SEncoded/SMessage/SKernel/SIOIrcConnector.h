/**
 * ------------------------------------------------------------------------------------------------ 
 * Container:  SIOIrcConnector.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SIOIRCCONNECTORCODED_H
#define SIOIRCCONNECTORCODED_H
/**
 * std
 */
#include <random>
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
 * IOIrcConnector
 * ------------------------------------------------------------------------------------------------
 */
class SIOIrcConnector : public SInOutputConnector {
public:
	/**
	 * constructor
	 */
	SIOIrcConnector(const std::string& address);
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
	/**
	 * -----------------------------------------------------
	 * IO functions
	 * -----------------------------------------------------
	 * read
	 */
	Document _Read() override;
	/**
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
	/**
	 * container
	 */
	IDocument __container;
};
}}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Encoded & Message
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SIOIRCCONNECTORCODED_H */

