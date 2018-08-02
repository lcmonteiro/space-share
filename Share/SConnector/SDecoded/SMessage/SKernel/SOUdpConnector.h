/* 
 * Container:   SUdpConnector.h
 * Author:      Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SOUDPSTREAMSOCKET_H
#define SOUDPSTREAMSOCKET_H
/**
 * Space
 */
#include "SResource/SSocketResource.h"
//
#include "SKernel/SContainer.h"
#include "SKernel/SAddress.h"
#include "SKernel/SConnector.h"
/**
 * Begin namespace Decoded
 */
namespace Decoded {
/**
 * Begin namespace Message
 */
namespace Message {
/**
 */
class SOUdpConnector : public Decoded::SOutputConnector {
public:
	/**
	 * constructor
	 */
	SOUdpConnector(const string address, const string local);
	/**
	 * destructor
	 */
	virtual ~SOUdpConnector() = default;
protected:
	/*-------------------------------------------------------------------------------------------------------------*
	 * IO functions
	 *-------------------------------------------------------------------------------------------------------------*/
        /**
         * write data
         */
	void _write(const Container& container) override;
	/*-------------------------------------------------------------------------------------------------------------*
	 * control functions
	 *-------------------------------------------------------------------------------------------------------------*/
        /**
         * open resource
         */
	void _open() override;
	/**
	 * inline
	 */
	inline bool _good() override{
		return __res.Good();
	}
	inline void _close() override {
		__res = SSocketResource();
	}
private:
	/**
	 * resource 
	 */
	SSocketResource __res;
	/**
	 * configurations
	 */
	Address __local;
};
/**
 * End namespace Message
 */
}
/**
 * End namespace Decoded
 */
}
#endif /* SOUDPSTREAMSOCKET_H */

