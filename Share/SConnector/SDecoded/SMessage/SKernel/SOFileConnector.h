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
    inline bool _good() override{
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

