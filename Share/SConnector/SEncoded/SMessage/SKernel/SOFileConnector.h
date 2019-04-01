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
    SOFileConnector(const SText address);
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
    void _Write(const Document& container) override;
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
        return __res.Good();
    }
    inline void _Close() override {
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

