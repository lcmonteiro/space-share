/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SUdpMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 6, 2016, 11:17 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SUDPMESSAGECONNECTOR_H
#define SUDPMESSAGECONNECTOR_H
/**
 * Space
 */
#include "SContainer.h"
#include "SConnector.h"
#include "SRemoteResource.h"
/**
 * Kernel
 */
#include "SKernel/SIOMessageConnector.h"
#include "SKernel/SIMessageConnector.h"
#include "SKernel/SOMessageConnector.h"
/**
 * Tools
 */
#include "SDefault.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Begin namespace Decoded & Message
 * ------------------------------------------------------------------------------------------------
 */
namespace Decoded {
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
    using Super::Read;
    using Super::Drain;
    using Super::Good;
    /**
     * interfaces
     */
    inline Super& Base() {
        return *this;
    }
    inline void Bind(const SAddress& uri) {
        Super::Bind(uri.Host(), uri.Port());
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
template <typename R, typename T> 
using SIMessageConnector = 
Layer::SIMessageConnector<
    T, Base::SIMessageConnector<R, SInputConnector>
>;
template<typename R, typename T>
class SIUdpConnectorT : public SIMessageConnector<R, T> {
public:
    /**
     * properties
     */
    typedef struct {
        const SText  address; 
        const size_t nframes; 
        const size_t maxsmsg;
    } Properties;
    /**
     * constructor
     */
    template<typename...Args>
    SIUdpConnectorT(Args &&...args) 
    : SIMessageConnector<R, T>(Properties{std::forward<Args>(args)...}) {}
    /**
     * make
     */
    template<typename...Args>
    static IConnector Make(Args &&...args) {
        return std::make_shared<SIUdpConnectorT>(std::forward<Args>(args)...);
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * Output UDP Connector
 * ------------------------------------------------------------------------------------------------
 * template
 */
template <typename R, typename T> 
using SOMessageConnector = 
Layer::SOMessageConnector<
    T, Base::SOMessageConnector<R, SOutputConnector>
>;
template<typename R, typename T>
class SOUdpConnectorT : public SOMessageConnector<R, T> {
public:
    /**
     * properties
     */
    typedef struct {
        const SText address; 
    } Properties;
    /**
     * constructor
     */
    template<typename...Args>
    SOUdpConnectorT(Args &&...args) 
    : SOMessageConnector<R, T>(Properties{std::forward<Args>(args)...}) {}
    /**
     * make
     */
    template<typename...Args>
    static OConnector Make(Args &&...args) {
        return std::make_shared<SOUdpConnectorT>(std::forward<Args>(args)...);
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * IO UDP Connector
 * ------------------------------------------------------------------------------------------------
 * template
 */
template <typename R, typename T> 
using SIOMessageConnector = 
Layer::SIMessageConnector<
    T, Layer::SOMessageConnector<
        T, Base::SIOMessageConnector<R, SInOutputConnector>
    >
>;
template<typename R, typename T>
class SIOUdpConnectorT : public SIOMessageConnector<R, T> {
public:
    /**
     * properties
     */
    typedef struct {
        const SText  address; 
        const size_t nframes; 
        const size_t maxsmsg;
    } Properties;
    /**
     * constructor
     */
    template<typename...Args>
    SIOUdpConnectorT(Args &&...args) 
    : SIOMessageConnector<R, T>(Properties{std::forward<Args>(args)...}) {}
    /**
     * make
     */
    template<typename...Args>
    static IOConnector Make(Args &&...args) {
        return std::make_shared<SIOUdpConnectorT>(std::forward<Args>(args)...);
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * Definition
 * ------------------------------------------------------------------------------------------------
 */
typedef SIOUdpConnectorT<ResourceAdapterUdp, SDefault> IOUdpConnector;
typedef SIUdpConnectorT<ResourceAdapterUdp, SDefault>  IUdpConnector;
typedef SOUdpConnectorT<ResourceAdapterUdp, SDefault>  OUdpConnector;
}}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Decoded & Message
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SUDPMESSAGECONNECTOR_H */

