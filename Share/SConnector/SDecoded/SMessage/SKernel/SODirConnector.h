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
class SODirConnector : public SOutputConnector {
public:
    /**
     * constructor
     */
    SODirConnector(const string address);
    /**
     * destructor
     */
    virtual ~SODirConnector() = default;
    /**
     */
protected:
    /*-----------------------------------------------------------------------------------------*
     * IO functions
     *------------------------------------------------------------------------------------------*/
    void _write(const Container& container) override;
    /*-----------------------------------------------------------------------------------------*
     * control functions
     *-----------------------------------------------------------------------------------------*/
    inline void _open() override {
        __dir = SODirectoryResource(__uri, 1);
    }
    inline bool _good() override {
        return __dir.Valid();
    }
    inline void _close() override {
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

