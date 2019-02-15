/* 
 * File:   SIFileConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 11, 2016, 12:47 AM
 */
#ifndef SIFILECONNECTORCODED_H
#define SIFILECONNECTORCODED_H
/**
 * Space 
 */
#include "SFileResource.h"
#include "SContainer.h"
#include "SAddress.h"
/**
 * Share 
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
 * ------------------------------------------------------------------------------------------------
 * IFileConnector
 * ------------------------------------------------------------------------------------------------
 */
class SIFileConnector : public SInputConnector {
public:
    /**
     * constructor
     */
    SIFileConnector(const SText address);
    /**
     * destructor
     */
    virtual ~SIFileConnector() = default;
    /**
     * inline overrides
     */
    inline Resource& GetResource() override {
        return __res;
    }
protected:
    /**
	 * -----------------------------------------------------
	 * IO functions
	 * -----------------------------------------------------
	 * read
	 */
    Document _Read() override;
    /**
	 * ----------------------------------------------------
	 * control functions
	 * ----------------------------------------------------
	 * open, good and close
	 */
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

