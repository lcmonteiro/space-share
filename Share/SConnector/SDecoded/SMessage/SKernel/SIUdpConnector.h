/* 
 * Container:   SIUdpConnector.h
 * Author:      Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SIUDPCONNECTORSOCKET_H
#define SIUDPCONNECTORSOCKET_H
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
class SIUdpConnector : public SInputConnector {
	typedef SIBreakFrame<1500> IBreakFrame;
public:
	/**
	 * constructor
	 */
	SIUdpConnector(
		const string address, 
		const string local,
		const size_t nnframes
	);
	/**
	 * destructor
	 */
	virtual ~SIUdpConnector() = default;
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
	/**
         * read data 
         */
        Container _read() override;
	/*-------------------------------------------------------------------------------------------------------------*
	 * control functions
	 *-------------------------------------------------------------------------------------------------------------*/
	/**
         * open resource
         */
        void _open() override;
	/**
	 * verify resource
	 */
	inline bool _good() override {
		return __res.Good();
	}
        /**
         * close resource
         */
	inline void _close() override {
		__res = SSocketResource();
	}
private:
	/**
	 * local address
	 */
	Address __local;
	/**
	 * buffer container
	 */
	Container __container;
	/**
         * buffer frame
         */
	IFrame __frame;
	/**
	 * resource 
	 */
	SSocketResource __res;
};
/**
 * End namespace Message
 */
}
/**
 * End namespace Decoded
 */
}
#endif /* SIUDPCONNECTORSOCKET_H */

