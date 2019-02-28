/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SLocMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 6, 2016, 11:17 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SLOCMESSAGECONNECTORCODED_H
#define SLOCMESSAGECONNECTORCODED_H
/**
 * Space 
 */
#include "SContainer.h"
#include "SConnector.h"
#include "SLocalResource.h"
/**
 * Kernel
 */
#include "SKernel/SIOMessageConnector.h"
#include "SKernel/SIMessageConnector.h"
#include "SKernel/SOMessageConnector.h"
/**
 * ------------------------------------------------------------------------------------------------
 * Begin namespace Encoded & Message
 * ------------------------------------------------------------------------------------------------
 */
namespace Encoded {
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
        Super::Bind(uri.File());
    }
    inline void Wait(const SAddress& uri) {
        Super::Bind(uri.File());
    }
    inline void Link(const SAddress& uri) {
        Super::Link(uri.File());
    }
    inline void Reset() {
        *this = Super();
    }
};    
// /**
//  * ------------------------------------------------------------------------------------------------
//  * Input Local Connector
//  * ------------------------------------------------------------------------------------------------
//  * template
//  */
// template<class R>
// class SILocConnectorT : public SIMessageConnector<R> {
// public:
//     using SIMessageConnector<R>::SIMessageConnector;
//     /**
//      */
//     SILocConnectorT() = delete;
//     /**
//      * make
//      */
//     template<typename...Args>
//     static IConnector Make(Args &&...args) {
//         return std::make_shared<SILocConnectorT>(std::forward<Args>(args)...);
//     }
// };
// /**
//  * ------------------------------------------------------------------------------------------------
//  * Output Local Connector
//  * ------------------------------------------------------------------------------------------------
//  * template
//  */
// template<class R>
// class SOLocConnectorT : public SOMessageConnector<R> {
// public:
//     using SOMessageConnector<R>::SOMessageConnector;
//     /**
//      */
//     SOLocConnectorT() = delete;
//     /**
//      * make
//      */
//     template<typename...Args>
//     static OConnector Make(Args &&...args) {
//         return std::make_shared<SOLocConnectorT>(std::forward<Args>(args)...);
//     }
// };
// /**
//  * ------------------------------------------------------------------------------------------------
//  * IO Local Connector
//  * ------------------------------------------------------------------------------------------------
//  * template
//  */
template<class R>
class SIOLocConnectorT : public SIOMessageConnector<R> {
public:
    using SIOMessageConnector<R>::SIOMessageConnector;
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
// /**
//  * ------------------------------------------------------------------------------------------------
//  * Definition
//  * ------------------------------------------------------------------------------------------------
//  */
// typedef SIOLocConnectorT<ResourceAdapterLoc> IOLocConnector;
// typedef SILocConnectorT<ResourceAdapterLoc>  ILocConnector;
// typedef SOLocConnectorT<ResourceAdapterLoc>  OLocConnector;
}}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Decoded & Message
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SLOCMESSAGECONNECTORCODED_H */
