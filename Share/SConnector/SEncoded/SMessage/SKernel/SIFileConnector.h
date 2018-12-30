/* 
 * File:   SIFileConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 11, 2016, 12:47 AM
 */
#ifndef SIFILECONNECTORCODED_H
#define SIFILECONNECTORCODED_H
/**
 * Space Resource
 */
#include "SFileResource.h"
/**
 * Space Kernel
 */
#include "SContainer.h"
#include "SAddress.h"
/**
 * Share Kernel
 */
#include "SConnector.h"
/**
 * Begin namespace Encoded
 */
namespace Encoded {
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
    SIFileConnector(const string address);
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
    /*-----------------------------------------------------------------------------------------*
     * IO functions
     *------------------------------------------------------------------------------------------*/
    Document _read() override;
    /*-----------------------------------------------------------------------------------------*
     * control functions
     *-----------------------------------------------------------------------------------------*/
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
     * resource 
     */
    SIFileResource __res;
};
/**
 * End namespace Message
 */
}
/**
 * End namespace Encoded
 */
}
#endif /* SIFILECONNECTORCODED_H */

