/** 
 * File:   SFileConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 2, 2016, 2:13 PM
 */
#ifndef SFILESTREAMCODED_H
#define SFILESTREAMCODED_H
/**
 * Space Kernel
 */
#include "SContainer.h"
/**
 * Share Kernel
 */
#include "SConnector.h"
/**
 * Message Kernel
 */
#include "SKernel/SIFileConnector.h"
#include "SKernel/SOFileConnector.h"
/**
 * Begin namespace Encoded
 */
namespace Encoded {
/**
 * Begin namespace Message
 */
namespace Message {
/**
 * Input FILE Connector coded template
 */
template<class T>
class SIFileConnectorT : public T {
public:
    /**
     * make
     */
    template<typename...Args>
    static IConnector Make(Args &&...args) {
        return std::make_shared<SIFileConnectorT>(std::forward<Args>(args)...);
    }
    /**
     * constructor
     */
    SIFileConnectorT(const SText address) : T(address) {
    }
};
/**
 * Output FILE Connector coded template
 */
template<class T>
class SOFileConnectorT : public T {
public:
    /**
     * make
     */
    template<typename...Args>
    static OConnector Make(Args &&...args) {
        return std::make_shared<SOFileConnectorT>(std::forward<Args>(args)...);
    }
    /**
     * constructor
     */
    SOFileConnectorT(const SText address) : T(address) {
    }
};
/**
 * definitions
 */
typedef SIFileConnectorT<SIFileConnector> IFileConnector;
typedef SOFileConnectorT<SOFileConnector> OFileConnector;
/**
 * End namespace Message
 */
}
/**
 * End namespace Encoded
 */
}
/**
 */
#endif /* SFILESTREAMCODED_H */

