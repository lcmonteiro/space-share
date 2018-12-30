/* 
 * Container:   SIFileConnector.h
 * Author:      Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SIFILECONNECTORSOCKET_H
#define SIFILECONNECTORSOCKET_H
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
class SIFileConnector : public SInputConnector {
public:
    /**
     * constructor
     */
    SIFileConnector(const string address, const size_t nframesize);
    /**
     * destructor
     */
    virtual ~SIFileConnector() = default;
    /**
     * inline overrides
     */
    inline Resource& GetResource() override{
        return __res;
    }
protected:
    /*-----------------------------------------------------------------------------------------*
     * IO functions
     *------------------------------------------------------------------------------------------*/
    Container _Read() override;
    /*-----------------------------------------------------------------------------------------*
     * control functions
     *-----------------------------------------------------------------------------------------*/
    inline void _Open() override {
        __res = SIFileResource(__uri);
    }
    inline bool _Good() override{
        return __res.Good();
    }
    inline void _Close() override {
        __res = SIFileResource();
    }
private:
    /**
     * resource 
     */
    SIFileResource __res;
    /**
     * frame size
     */
    size_t __sframes;
};
/**
 * End namespace Message
 */
}
/**
 * End namespace Decoded
 */
}
#endif /* SIFILECONNECTORSOCKET_H */

