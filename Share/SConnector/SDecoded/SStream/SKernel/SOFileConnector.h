/* 
 * Container:   SOFileConnector.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SOFILESTREAMDATA_H
#define SOFILESTREAMDATA_H
/**
 * Space
 */
#include "SResource/SFileResource.h"
//
#include "SKernel/SContainer.h"
#include "SKernel/SConnector.h"
/**
 * Begin namespace Data
 */
namespace Decoded {
/**
 * Begin namespace Data
 */
namespace Stream {
/**
 */
class SOFileConnector : public SOutputConnector {
public:
	/**
	 * constructor
	 */
	SOFileConnector(const string address);
	/**
	 * destructor
	 */
	virtual ~SOFileConnector() = default;
	/**
	 */
protected:
	/*-------------------------------------------------------------------------------------------------------------*
	 * IO functions
	 *-------------------------------------------------------------------------------------------------------------*/
	void _write(const Container& container) override;
	/*-------------------------------------------------------------------------------------------------------------*
	 * control functions
	 *-------------------------------------------------------------------------------------------------------------*/
	inline void _open() override {
		__res = SOFileResource(__uri);
	}
	inline bool _good() override {
		return __res.Valid();
	}
	inline void _close() override {
		__res = SOFileResource();
	}
private:
	/**
	 * resource 
	 */
	SOFileResource __res;
};
/**
 * End namespace Stream
 */
}
/**
 * End namespace Decoded
 */
}
#endif /* SOFILESTREAM_H */

