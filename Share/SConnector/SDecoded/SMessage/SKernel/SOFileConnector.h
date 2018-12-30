/* 
 * Container:   SOFileConnector.h
 * Author:      Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SOFILESTREAMSOCKET_H
#define SOFILESTREAMSOCKET_H
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
 * Begin namespace Decoded
 */
namespace Decoded {
/**
 * Begin namespace Message
 */
namespace Message {
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
    void _Write(const Container& container) override;
    /**
	 * ----------------------------------------------------
	 * control functions
	 * ----------------------------------------------------
	 * open, good and close
	 */
    inline void _Open() override {
        __res = SOFileResource(__uri);
    }
    inline bool _Good() override{
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
    /**
     */
    Buffer __buffer;
    /**
     */
    Frame __path;
    /**
     */
    filesize_t __size;
};
/**
 * End namespace Message
 */
}
/**
 * End namespace Decoded
 */
}
#endif /* SOFILESTREAMSOCKET_H */

