/* 
 * File:  SIDirConnector.h
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
 * Share
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
class SIDirConnector : public SInputConnector {
public:
    /**
     * constructor
     */
    SIDirConnector(const SText address, const SText file);
    /**
     * destructor
     */
    virtual ~SIDirConnector() = default;
    /**
     * inline overrides
     */
    inline Resource& GetResource() override {
        return __res;
    }
protected:
    /*-----------------------------------------------------------------------------------------*
     * IO functions
     *-----------------------------------------------------------------------------------------*/
    Document _Read() override;
    /**
	 * ----------------------------------------------------
	 * control functions
	 * ----------------------------------------------------
	 * open, good and close
	 */
    void _Open() override;
    /**
     * inline control overrides
     */
    inline bool _Good() override {
        return __res.Valid();
    }
    inline void _Close() override {
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
    std::string __file;
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

