/* 
 * Container:  SIIrcConnector.h
 * Author: Luis Monteiro
 *
 * Created on November 26, 2015, 12:37 PM
 */
#ifndef SIIRCCONNECTORCODED_H
#define SIIRCCONNECTORCODED_H
/**
 * std
 */
#include <random>
/**
 * Space
 */
#include "SIRCResource.h"
#include "SContainer.h"
#include "SAddress.h"
#include "SChannel.h"
#include "STask.h"
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
 * IIrcConnector
 * ------------------------------------------------------------------------------------------------
 */
class SIIrcConnector : public SInputConnector {
public:
    /**
     * constructor
     */
    SIIrcConnector(const string address);
    /**
     * destructor
     */
    virtual ~SIIrcConnector() = default;
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
     * drain
     */
    list<Document> _Drain() override;
    /**
     * ----------------------------------------------------
     * control functions
     * ----------------------------------------------------
     * open
     */
    void _Open() override;
    /**
     * inline: good and close
     */
    inline bool _Good() override{
        return __res.Good();
    }
    inline void _Close() override {
        __res = SIRCResource();
    }
private:
    /**
     * resource 
     */
    SIRCResource __res;
};
/**
 * End namespace Message
 */
}
/**
 * End namespace Encoded
 */
}
#endif /* SIIRCCONNECTORCODED_H */

