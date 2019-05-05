/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   STcpConnector.h
 * Author: Luis Monteiro
 *
 * Created on June 6, 2018, 11:17 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef STCPSTREAMCONNECTORCODED_H
#define STCPSTREAMCONNECTORCODED_H
/**
 * space
 */
#include "SContainer.h"
#include "SRemoteResource.h"
/**
 * share
 */
#include "SConnector.h"
/**
 * connector
 */
#include "SKernel/SIStreamConnector.h"
#include "SKernel/SOStreamConnector.h"
#include "SKernel/SIOStreamConnector.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Begin namespace Encoded & Stream
 * ------------------------------------------------------------------------------------------------
 */
namespace Encoded {
namespace Stream  {
/**
 * ------------------------------------------------------------------------------------------------
 * Resource adapter
 * ------------------------------------------------------------------------------------------------
 */
class ResourceAdapterTcp : private ::Stream::SRemoteResource {
public:
    using Super = ::Stream::SRemoteResource;
    /**
     * default
     */
    using Super::Super;
    using Super::operator=;
    using Super::read;
    using Super::drain;
    using Super::good;
    /**
     * interfaces
     */
    inline Super& base() {
        return *this;
    }
    inline void wait(const SAddress& uri) {
        Super::wait(uri.host(), uri.port());
    }
    inline void link(const SAddress& uri) {
        Super::link(uri.host(), uri.port());
    }
    inline void reset() {
        *this = Super();
    }
}; 
/**
 * ------------------------------------------------------------------------------------------------
 * Input TCP Connector
 * ------------------------------------------------------------------------------------------------
 * template
 */
template<class R>
class SITcpConnectorT : public SIStreamConnector<R> {
public:
    using SIStreamConnector<R>::SIStreamConnector;
    /**
     */
    SITcpConnectorT() = delete;
    /**
     * make
     */
    template<typename...Args>
    static IConnector Make(Args &&...args) {
        return make_shared<SITcpConnectorT>(forward<Args>(args)...);
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * Output TCP Connector
 * ------------------------------------------------------------------------------------------------
 * template
 */
template<class R>
class SOTcpConnectorT : public SOStreamConnector<R> {
public:
    using SOStreamConnector<R>::SOStreamConnector;
    /**
     */
    SOTcpConnectorT() = delete;
    /**
     * make
     */
    template<typename...Args>
    static OConnector Make(Args &&...args) {
        return make_shared<SOTcpConnectorT>(forward<Args>(args)...);
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * IO TCP Connector
 * ------------------------------------------------------------------------------------------------
 * template
 */
template<class R>
class SIOTcpConnectorT : public SIOStreamConnector<R> {
public:
    using SIOStreamConnector<R>::SIOStreamConnector;
    /**
     */
    SIOTcpConnectorT() = delete;
    /**
     * make
     */
    template<typename...Args>
    static IOConnector Make(Args &&...args) {
        return make_shared<SIOTcpConnectorT>(forward<Args>(args)...);
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * Definition
 * ------------------------------------------------------------------------------------------------
 */
typedef SIOTcpConnectorT<ResourceAdapterTcp> IOTcpConnector;
typedef SITcpConnectorT< ResourceAdapterTcp>  ITcpConnector;
typedef SOTcpConnectorT< ResourceAdapterTcp>  OTcpConnector;
}}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Decoded & Stream
 * ------------------------------------------------------------------------------------------------
 */
#endif /* STCPSTREAMCONNECTORCODED_H */

