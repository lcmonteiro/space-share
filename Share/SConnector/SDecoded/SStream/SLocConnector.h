/* 
 * File:   SLocStreamConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 6, 2016, 11:17 PM
 */
#ifndef SLOCSTREAMCONNECTOR_H
#define SLOCSTREAMCONNECTOR_H
/**
 * Space Kernel
 */
#include "SContainer.h"
#include "SConnector.h"
/**
 * Stream Kernel
 */
#include "SIStreamConnector.h"
#include "SOStreamConnector.h"
#include "SIOStreamConnector.h"
/**
 * Begin namespace Data
 */
namespace Decoded {
/**
 * Begin namespace Data
 */
namespace Stream {
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * Resource adapter
 * ---------------------------------------------------------------------------------------------------------------------
 */
class ResourceAdapterLoc : private SSocketResource {
public:
    using SSocketResource::SSocketResource;
    using SSocketResource::operator=;
    using SSocketResource::Fill;
    using SSocketResource::Drain;
    using SSocketResource::Good;
    /**
     * interfaces
     */
    inline SSocketResource& Base() {
        return *this;
    }
    inline void Wait(const SAddress& uri) {
        SSocketResource::bind(uri.Path(), STREAM);
    }
    inline void Reset() {
        *this = SSocketResource();
    }
};    
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * Input Local Connector
 * ---------------------------------------------------------------------------------------------------------------------
 * template
 */
template<class R>
class SILocConnectorT : public SIStreamConnector <R> {
public:
    using SIStreamConnector<R>::SIStreamConnector;
    /**
     */
    SILocConnectorT() = delete;
    /**
     * make
     */
    template<typename...Args>
    static IConnector Make(Args &&...args) {
        return make_shared<SILocConnectorT>(forward<Args>(args)...);
    }
};
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * Output Local Connector
 * ---------------------------------------------------------------------------------------------------------------------
 * template
 */
template<class R>
class SOLocConnectorT : public SOStreamConnector<R> {
public:
    using SOStreamConnector<R>::SOStreamConnector;
    /**
     */
    SOLocConnectorT() = delete;
    /**
     * make
     */
    template<typename...Args>
    static OConnector Make(Args &&...args) {
        return make_shared<SOLocConnectorT>(forward<Args>(args)...);
    }
};
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * IO Local Connector
 * ---------------------------------------------------------------------------------------------------------------------
 * template
 */
template<class R>
class SIOLocConnectorT : public SIOStreamConnector<R> {
public:
    using SIOStreamConnector<R>::SIOStreamConnector;
    /**
     */
    SIOLocConnectorT() = delete;
    /**
     * make
     */
    template<typename...Args>
    static IOConnector Make(Args &&...args) {
        return make_shared<SIOLocConnectorT>(forward<Args>(args)...);
    }
};
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * definition
 * ---------------------------------------------------------------------------------------------------------------------
 */
typedef SIOLocConnectorT<ResourceAdapterLoc> IOLocConnector;
typedef SILocConnectorT<ResourceAdapterLoc>  ILocConnector;
typedef SOLocConnectorT<ResourceAdapterLoc>  OLocConnector;
/**
 * End namespace Stream
 */
}
/**
 * End namespace Decoded
 */
}
/**
 */
#endif /* SLOCSTREAMCONNECTOR_H */

