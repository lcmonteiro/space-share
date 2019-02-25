/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SLocMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 6, 2016, 11:17 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SLOCMESSAGECONNECTOR_H
#define SLOCMESSAGECONNECTOR_H
/**
 * Space
 */
#include "SContainer.h"
#include "SConnector.h"
#include "SLocalResource.h"
/**
 * Kernel
 */
#include "SIOMessageConnector.h"
#include "SIMessageConnector.h"
#include "SOMessageConnector.h"
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
class ResourceAdapterLoc : private ::Message::SLocalResource {
public:
    using Super = ::Message::SLocalResource;
    /**
     * default
     */
    using Super::SLocalResource;
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
        Super::Bind(uri.Path());
    }
    inline void Wait(const SAddress& uri) {
        Super::Bind(uri.Path());
    }
    inline void Link(const SAddress& uri) {
        Super::Link(uri.Path());
    }
    inline void Reset() {
        *this = Super();
    }
};    
/**
 * ------------------------------------------------------------------------------------------------
 * Input LOC Connector
 * ------------------------------------------------------------------------------------------------
 * template
 */
template<class R, class T>
class SILocConnectorT : public SIMessageConnector<R, T> {
public:
    using SIMessageConnector<R, T>::SIMessageConnector;
    /**
     */
    SILocConnectorT() = delete;
    /**
     * make
     */
    template<typename...Args>
    static IConnector Make(Args &&...args) {
        return std::make_shared<SILocConnectorT>(std::forward<Args>(args)...);
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * Output LOC Connector
 * ------------------------------------------------------------------------------------------------
 * template
 */
template<class R, class T>
class SOLocConnectorT : public SOMessageConnector<R, T> {
public:
    using SOMessageConnector<R, T>::SOMessageConnector;
    /**
     */
    SOLocConnectorT() = delete;
    /**
     * make
     */
    template<typename...Args>
    static OConnector Make(Args &&...args) {
        return std::make_shared<SOLocConnectorT>(std::forward<Args>(args)...);
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * IO LOC Connector
 * ------------------------------------------------------------------------------------------------
 * template
 */
template<class R, class T>
class SIOLocConnectorT : public SIOMessageConnector<R, T> {
public:
    using SIOMessageConnector<R, T>::SIOMessageConnector;
    /**
     */
    SIOLocConnectorT() = delete;
    /**
     * make
     */
    template<typename...Args>
    static IOConnector Make(Args &&...args) {
        return std::make_shared<SIOLocConnectorT>(std::forward<Args>(args)...);
    }
};
/**
 * ------------------------------------------------------------------------------------------------
 * Definition
 * ------------------------------------------------------------------------------------------------
 */
typedef SIOLocConnectorT<ResourceAdapterLoc, SDefault> IOLocConnector;
typedef SILocConnectorT<ResourceAdapterLoc, SDefault>  ILocConnector;
typedef SOLocConnectorT<ResourceAdapterLoc, SDefault>  OLocConnector;
}}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Decoded & Message
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SLOCMESSAGECONNECTOR_H */

