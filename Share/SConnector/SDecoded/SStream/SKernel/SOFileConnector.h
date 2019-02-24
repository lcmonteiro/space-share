/* 
 * Container:   SOFileConnector.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SOFILESTREAMDATA_H
#define SOFILESTREAMDATA_H
/**
 * Space Resource
 */
#include "SFileResource.h"
/**
 * Space Kernel
 */
#include "SContainer.h"
/**
 * Share Kernel
 */
#include "SConnector.h"
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
    /**
	 * -----------------------------------------------------
	 * IO functions
	 * -----------------------------------------------------
	 * read
	 */
    void _Write(const Document& container) override;
    /**
	 * ----------------------------------------------------
	 * control functions
	 * ----------------------------------------------------
	 * open, good and close
	 */
    inline void _Open() override {
        __res = SOFileResource(__uri);
    }
    inline bool _Good() override {
        return __res.Valid();
    }
    inline void _Close() override {
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

