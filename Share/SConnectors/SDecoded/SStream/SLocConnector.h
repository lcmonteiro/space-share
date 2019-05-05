/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SLocStreamConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 6, 2016, 11:17 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SLOCSTREAMCONNECTOR_H
#define SLOCSTREAMCONNECTOR_H
/**
 * space
 */
#include "SContainer.h"
#include "SConnector.h"
#include "SLocalResource.h"
/**
 * stream
 */
#include "SKernel/SIStreamConnector.h"
#include "SKernel/SOStreamConnector.h"
#include "SKernel/SIOStreamConnector.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Begin namespace Decoded & Stream
 * ------------------------------------------------------------------------------------------------
 */
namespace Decoded {
namespace Stream  {
/**
 * ----------------------------------------------------------------------------
 * Resource adapter
 * ----------------------------------------------------------------------------
 */
class ResourceAdapterLoc : private ::Stream::SLocalResource {
public:
    using Super = ::Stream::SLocalResource;
    /**
     * default
     */
    using Super::Super;
    using Super::operator=;
    using Super::fill;
    using Super::drain;
    using Super::good;
    /**
     * interfaces
     */
    inline Super& base() {
        return *this;
    }
    inline void wait(const SAddress& uri) {
        Super::bind(uri.path());
    }
    inline void reset() {
        *this = Super();
    }
};    
/**
 * ----------------------------------------------------------------------------
 * Input Local Connector
 * ----------------------------------------------------------------------------
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
 * ----------------------------------------------------------------------------
 * Output Local Connector
 * ----------------------------------------------------------------------------
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
 * ----------------------------------------------------------------------------
 * IO Local Connector
 * ----------------------------------------------------------------------------
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
 * ----------------------------------------------------------------------------
 * Definition
 * ----------------------------------------------------------------------------
 */
typedef SIOLocConnectorT<ResourceAdapterLoc> IOLocConnector;
typedef SILocConnectorT< ResourceAdapterLoc>  ILocConnector;
typedef SOLocConnectorT< ResourceAdapterLoc>  OLocConnector;
}}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Decoded & Stream
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SLOCSTREAMCONNECTOR_H */

