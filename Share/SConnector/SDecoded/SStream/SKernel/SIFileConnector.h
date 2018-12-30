/* 
 * Container:   SIFileConnector.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SIFILECONNECTORDATA_H
#define SIFILECONNECTORDATA_H
/**
 * Space
 */
#include "SResource/SFileResource.h"
//
#include "SKernel/SContainer.h"
#include "SKernel/SConnector.h"
/**
 * Begin namespace 
 */
namespace Decoded {
/**
 * Begin namespace Stream
 */
namespace Stream {
/**
 */
class SIFileConnector : public SInputConnector {
public:
	/**
	 * constructor
	 */
	SIFileConnector(const string address, const size_t nframes, const size_t nframesize);
	/**
	 * destructor
	 */
	virtual ~SIFileConnector() = default;
	/**
	 * inline overrides
	 */
	inline Resource& resource() override {
		return __res;
	}
protected:
	/*-------------------------------------------------------------------------------------------------------------*
	 * IO functions
	 *-------------------------------------------------------------------------------------------------------------*/
	Container _read() override;
	/**/
	list<Container> _drain() override;
	/*-------------------------------------------------------------------------------------------------------------*
	 * control functions
	 *-------------------------------------------------------------------------------------------------------------*/
	inline void _open() override {
		__res = SIFileResource(__uri);
	}
	inline bool _good() override{
		return __res.Good();
	}
	inline void _close() override {
		__res = SIFileResource();
	}
private:
	/**
	 * containers
	 */
	Container __container;
	/**/
	IFrame __buffer;
	/**
	 * resource 
	 */
	SIFileResource __res;
};
/**
 * End namespace Stream
 */
}
/**
 * End namespace Decoded
 */
}
/**
 */
#endif /* SIFILECONNECTORDATA_H */

