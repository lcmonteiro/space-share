/* 
 * File:   SMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 6, 2016, 11:17 PM
 */
#ifndef SLOCMESSAGECONNECTORCODED_H
#define SLOCMESSAGECONNECTORCODED_H
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
#include "SIMessageConnector.h"
#include "SOMessageConnector.h"
#include "SIOMessageConnector.h"
/**
 * Begin namespace Encoded
 */
namespace Encoded {
/**
 * Begin namespace Data
 */
namespace Message {
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * Resource adapter
 * ---------------------------------------------------------------------------------------------------------------------
 */
class ResourceAdapterLoc : private SSocketResource {
public:
    using SSocketResource::SSocketResource;
    using SSocketResource::operator=;
    /**
     * interfaces
     */
    inline SSocketResource& Base() {
        return *this;
    }
    inline void Wait(const Address& uri) {
        SSocketResource::Bind(uri.Path(), MESSAGE);
    }
    inline void Fill(IFrame& buf) {
        SSocketResource::Fill(buf);
    }
    inline void Drain(const Frame& buf) {
        SSocketResource::Drain(buf);
    }
    inline bool Good() {
        SSocketResource::Good();
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
class SILocConnectorT : public SIMessageConnector<R> {
public:
    using SIMessageConnector<R>::SIMessageConnector;
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
class SOLocConnectorT : public SOMessageConnector<R> {
public:
    using SOMessageConnector<R>::SOMessageConnector;
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
 * End namespace Message
 */
}
/**
 * End namespace Encoded
 */
}
/**
 */
#endif /* SLOCMESSAGECONNECTORCODED_H */

