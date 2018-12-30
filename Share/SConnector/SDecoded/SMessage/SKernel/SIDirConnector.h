/* 
 * Container:  SIDirConnector.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SIDIRCONNECTOR_H
#define SIDIRCONNECTOR_H
/**
 * Space Resource
 */
#include "SDirectoryResource.h"
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
class SIDirConnector : public SInputConnector {
public:
    /**
     * constructor
     */
    SIDirConnector(const string address, const string file);
    /**
     * destructor
     */
    virtual ~SIDirConnector() = default;
    /**
     * inline overrides
     */
    inline Resource& resource() override {
        return __res;
    }
protected:
    /*-----------------------------------------------------------------------------------------*
     * IO functions
     *-----------------------------------------------------------------------------------------*/
    Container _read() override;
    /*-----------------------------------------------------------------------------------------*
     * control functions
     *-----------------------------------------------------------------------------------------*/
    void _open() override;
    /**
     * inline control overrides
     */
    inline bool _good() override {
        return __res.valid();
    }
    inline void _close() override {
        __res = SDirectoryResource();
    }
private:
    /**
     * resource 
     */
    SDirectoryResource __res;
    /**
     * properties
     */
    string __file;
};
/**
 * End namespace Message
 */
}
/**
 * End namespace Decoded
 */
}
#endif /* SIDIRCONNECTOR_H */

