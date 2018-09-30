/* 
 * File:   SOFileConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 10, 2016, 4:32 PM
 */
#ifndef SOFILESTREAMCODED_H
#define SOFILESTREAMCODED_H
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
 * Begin namespace Encoded
 */
namespace Encoded {
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
    void _write(const Document& container) override;
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
};
/**
 * End namespace Message
 */
}
/**
 * End namespace Encoded
 */
}
#endif /* SOFILESTREAMCODED_H */

