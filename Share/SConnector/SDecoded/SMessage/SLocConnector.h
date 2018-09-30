/* 
 * File:   SLocMessageConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 6, 2016, 11:17 PM
 */
#ifndef SLOCMESSAGECONNECTOR_H
#define SLOCMESSAGECONNECTOR_H
/**
 * Space Kernel
 */
#include "SContainer.h"
#include "SConnector.h"
#include "SSocketResource.h"
/**
 * Message Kernel
 */
#include "SIOMessageConnector.h"
#include "SIMessageConnector.h"
#include "SOMessageConnector.h"
/**
 * Message Tools
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
        SSocketResource::Wait(uri.Host(), uri.Port(), STREAM);
    }
    inline void Fill(Frame& buf) {
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
 * Input LOC Connector
 * ---------------------------------------------------------------------------------------------------------------------
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
        return make_shared<SILocConnectorT>(forward<Args>(args)...);
    }
};
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * Output LOC Connector
 * ---------------------------------------------------------------------------------------------------------------------
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
        return make_shared<SOLocConnectorT>(forward<Args>(args)...);
    }
};
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * IO LOC Connector
 * ---------------------------------------------------------------------------------------------------------------------
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
        return make_shared<SIOLocConnectorT>(forward<Args>(args)...);
    }
};
/**
 * ---------------------------------------------------------------------------------------------------------------------
 * definition
 * ---------------------------------------------------------------------------------------------------------------------
 */
typedef SIOLocConnectorT<ResourceAdapterLoc, SDefault> IOLocConnector;
typedef SILocConnectorT<ResourceAdapterLoc, SDefault>  ILocConnector;
typedef SOLocConnectorT<ResourceAdapterLoc, SDefault>  OLocConnector;
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
#endif /* SLOCMESSAGECONNECTOR_H */

