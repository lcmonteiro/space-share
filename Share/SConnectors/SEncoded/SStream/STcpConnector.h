/* 
 * File:   STcpConnector.h
 * Author: Luis Monteiro
 *
 * Created on June 6, 2018, 11:17 PM
 */
#ifndef STCPSTREAMCONNECTORCODED_H
#define STCPSTREAMCONNECTORCODED_H
/**
 * Space
 */
#include "SContainer.h"
#include "SConnector.h"
#include "SRemoteResource.h"
/**
 * Kernel
 */
#include "SKernel/SIStreamConnector.h"
#include "SKernel/SOStreamConnector.h"
#include "SKernel/SIOStreamConnector.h"
/**
 * Begin namespace Encoded
 */
namespace Encoded {
/**
 * Begin namespace Stream
 */
namespace Stream {
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
    using Super::Read;
    using Super::Drain;
    using Super::Good;
    /**
     * interfaces
     */
    inline Super& Base() {
        return *this;
    }
    inline void Wait(const SAddress& uri) {
        Super::Wait(uri.Host(), uri.Port());
    }
    inline void Link(const SAddress& uri) {
        Super::Link(uri.Host(), uri.Port());
    }
    inline void Reset() {
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
 * definition
 * ------------------------------------------------------------------------------------------------
 */
typedef SIOTcpConnectorT<ResourceAdapterTcp> IOTcpConnector;
typedef SITcpConnectorT<ResourceAdapterTcp>  ITcpConnector;
typedef SOTcpConnectorT<ResourceAdapterTcp>  OTcpConnector;
/**
 * End namespace Stream
 */
}
/**
 * End namespace Encoded
 */
}
/**
 */
#endif /* STCPSTREAMCONNECTORCODED_H */
