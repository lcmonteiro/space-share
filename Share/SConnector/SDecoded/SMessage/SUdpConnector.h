/* 
 * File:   SUdpMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 6, 2016, 11:17 PM
 */
#ifndef SUDPMESSAGECONNECTOR_H
#define SUDPMESSAGECONNECTOR_H
/**
 * space
 */
#include "SContainer.h"
#include "SConnector.h"
#include "SRemoteResource.h"
/**
 * kernel
 */
#include "SIOMessageConnector.h"
#include "SIMessageConnector.h"
#include "SOMessageConnector.h"
/**
 * tools
 */
#include "SDefault.h"
/**
 * Begin namespace Decoded
 */
namespace Decoded {
/**
 * Begin namespace Stream
 */
namespace Message {
/**
 * ------------------------------------------------------------------------------------------------
 * Resource adapter
 * ------------------------------------------------------------------------------------------------
 */
class ResourceAdapterUdp : private ::Message::SRemoteResource {
public:
    using Super = ::Message::SRemoteResource;
    /**
     * default
     */
    using Super::SRemoteResource;
    using Super::operator=;
    using Super::Fill;
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
 * Input UDP Connector
 * ------------------------------------------------------------------------------------------------
 * template
 */
template<class R, class T>
class SIUdpConnectorT : public SIMessageConnector<R, T> {
public:
    using SIMessageConnector<R, T>::SIMessageConnector;
    /**
     */
    SIUdpConnectorT() = delete;
    /**
     * make
     */
    template<typename...Args>
    static IConnector Make(Args &&...args) {
        return make_shared<SIUdpConnectorT>(forward<Args>(args)...);
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * Output UDP Connector
 * ------------------------------------------------------------------------------------------------
 * template
 */
template<class R, class T>
class SOUdpConnectorT : public SOMessageConnector<R, T> {
public:
    using SOMessageConnector<R, T>::SOMessageConnector;
    /**
     */
    SOUdpConnectorT() = delete;
    /**
     * make
     */
    template<typename...Args>
    static OConnector Make(Args &&...args) {
        return make_shared<SOUdpConnectorT>(forward<Args>(args)...);
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * IO UDP Connector
 * ------------------------------------------------------------------------------------------------
 * template
 */
template<class R, class T>
class SIOUdpConnectorT : public SIOMessageConnector<R, T> {
public:
    using SIOMessageConnector<R, T>::SIOMessageConnector;
    /**
     */
    SIOUdpConnectorT() = delete;
    /**
     * make
     */
    template<typename...Args>
    static IOConnector Make(Args &&...args) {
        return make_shared<SIOUdpConnectorT>(forward<Args>(args)...);
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * definition
 * ------------------------------------------------------------------------------------------------
 */
typedef SIOUdpConnectorT<ResourceAdapterUdp, SDefault> IOUdpConnector;
typedef SIUdpConnectorT<ResourceAdapterUdp, SDefault>  IUdpConnector;
typedef SOUdpConnectorT<ResourceAdapterUdp, SDefault>  OUdpConnector;
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
#endif /* SUDPMESSAGECONNECTOR_H */

