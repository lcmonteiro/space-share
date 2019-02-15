/* 
 * Container:   SODirConnector.h
 * Author:      Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SODIRSTREAMSOCKET_H
#define SODIRSTREAMSOCKET_H
/**
 * Space Resource
 */
#include "SDirectoryResource.h"
#include "SFileResource.h"
/**
 * Share Kernel
 */
#include "SDocument.h"
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
class SODirConnector : public SOutputConnector {
public:
    /**
     * constructor
     */
    SODirConnector(const SText address);
    /**
     * destructor
     */
    virtual ~SODirConnector() = default;
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
        __dir = SODirectoryResource(__uri, 1);
    }
    inline bool _Good() override {
        return __dir.Valid();
    }
    inline void _Close() override {
        __dir = SODirectoryResource();
    }
private:
    /**
     * resource 
     */
    SODirectoryResource __dir;
    /**
     */
    Buffer __buffer;
    /**
     */
    Frame __path;
    /**
     */
    filesize_t __size;
    /**
     */
    SOFileResource __res;
};
/**
 * End namespace Message
 */
}
/**
 * End namespace Decoded
 */
}
#endif /* SODIRSTREAMSOCKET_H */

