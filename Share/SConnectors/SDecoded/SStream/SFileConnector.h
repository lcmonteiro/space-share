/**
 * ------------------------------------------------------------------------------------------------ 
 * File:   SFileConnector.h
 * Author: Luis Monteiro
 *
 * Created on December 2, 2016, 2:13 PM
 * ------------------------------------------------------------------------------------------------
 */
#ifndef SFILESTREAMCONNECTOR_H
#define SFILESTREAMCONNECTOR_H
/**
 * space
 */
#include "SContainer.h"
#include "SConnector.h"
#include "SFileResource.h"
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
class ResourceAdapterFile : private SFileResource {
public:
    using Super = SFileResource;
    /**
     * default
     */
    using Super::Super;
    using Super::operator=;
    using Super::read;
    using Super::drain;
    using Super::good;
    using Super::size;
    /**
     * interfaces
     */
    inline Super& base() {
        return *this;
    }
    inline void wait(const SAddress& uri) {
        *this = SIFileResource(uri);
    }
    inline void bind(const SAddress& uri) {
        *this = SIFileResource(uri);
    }
    inline void link(const SAddress& uri) {
        *this = SOFileResource(uri);
    }
    inline void reset() {
        *this = Super();
    }
}; 
/**
 * ----------------------------------------------------------------------------
 * Input File Connector
 * ----------------------------------------------------------------------------
 * template
 */
template<class R>
class SIFileConnectorT : public SIStreamConnector <R> {
public:
    using SIStreamConnector<R>::SIStreamConnector;
    /**
     */
    SIFileConnectorT() = delete;
    /**
     * make
     */
    template<typename...Args>
    static IConnector Make(Args &&...args) {
        return make_shared<SIFileConnectorT>(forward<Args>(args)...);
    }
};
/**
 * ----------------------------------------------------------------------------
 * Output File Connector
 * ----------------------------------------------------------------------------
 * template
 */
template<class R>
class SOFileConnectorT : public SOStreamConnector<R> {
public:
    using SOStreamConnector<R>::SOStreamConnector;
    /**
     */
    SOFileConnectorT() = delete;
    /**
     * make
     */
    template<typename...Args>
    static OConnector Make(Args &&...args) {
        return make_shared<SOFileConnectorT>(forward<Args>(args)...);
    }
};
/**
 * ----------------------------------------------------------------------------
 * Definition
 * ----------------------------------------------------------------------------
 */
typedef SIFileConnectorT<ResourceAdapterFile> IFileConnector;
typedef SOFileConnectorT<ResourceAdapterFile> OFileConnector;
}}
/**
 * ------------------------------------------------------------------------------------------------
 * End namespace Decoded & Stream
 * ------------------------------------------------------------------------------------------------
 */
#endif /* SFILESTREAMCONNECTOR_H */


